#include "ft_malloc_include.h"

bool    ft_expand_block(t_block *block, size_t size) {
    printf("expand\n");
    t_page  *parent;
    t_block *fragmented_block;
    t_block *new_block;

    parent = block->parent;
    if (block->next == NULL) {
        if (parent->size - parent->used_size + block->size >=  size) {
            parent->used_size -= block->size;
            block->size = size;
            parent->used_size += size;
            return true;
        }
    } else if (block->next && !block->next->allocated) {
        if (block->size + block->next->size >= size) {
            if (block->size + block->next->size - size <= BLOCK_SIZE(ALIGNEMENT)) {
                block->size += block->next->size;
                block->next = block->next->next;
                if (block->next)
                    block->next->prev = block;
                parent->nb_block--;
                parent->nb_freed--;
                #ifdef MALLOC_OVERFLOW
                    set_prot(block); 
                #endif
                return true;
            } else {
                fragmented_block = block->next;
                block->next = (void *)block + size;
                new_block = block->next;
                new_block->size = block->size + fragmented_block->size - size;
                block->size = size;
                if (fragmented_block->next) {
                    new_block->next = fragmented_block->next;
                    new_block->next->prev = new_block;
                }
                #ifdef MALLOC_OVERFLOW
                    set_prot(block); 
                #endif
                new_block->allocated = false;
                new_block->parent = parent;
                #ifdef MALLOC_OVERFLOW
                    set_prot(new_block); 
                #endif
                return true;
            }
        }
    }
    return false;
}

bool    ft_shrink_block(t_block *block, size_t size) {
    printf("shrink\n");
    t_page  *parent;
    t_block *new_block;
    
    parent = block->parent;
    if (block->size - size <= BLOCK_SIZE(ALIGNEMENT)) {
        return true;
    } else {
        new_block = block + size;
        new_block->allocated = false;
        new_block->size = block->size - size;
        new_block->next = block->next;
        new_block->prev = block;
        if (new_block->next)
            new_block->next->prev = new_block;
        new_block->parent = parent;
        parent->nb_block++;
        parent->nb_freed++;
        block->next = new_block;
        block->size = size;
        #ifdef MALLOC_OVERFLOW
        set_prot(block); 
        #endif
        #ifdef MALLOC_OVERFLOW
        set_prot(new_block); 
        #endif
        ft_defragment_block(new_block, new_block->parent);
        return true;
    }
    return false;
}

bool    ft_fragment_if_possible(t_block *block, size_t size) {
    if (size == block->size)
        return true;
    else if (size > block->size)
        return ft_expand_block(block, size);
    else
        return ft_shrink_block(block, size);
}

void    *ft_realloc(void *ptr, size_t size) {
    t_block *block;
    bool    is_realloc;
    void    *new_alloc;

    if (!size) {
        if (ptr)
            ft_free(ptr);
        return NULL;
    }

    if (!ptr)
        return ft_malloc(size);
    
    block = HEADER_BLOCK_DESHIFT(ptr);

    pthread_mutex_lock(&g_heap_mutex);
        is_realloc = ft_fragment_if_possible(block, BLOCK_SIZE(size));
    pthread_mutex_unlock(&g_heap_mutex);

    if (is_realloc)
        return ptr;
    
    new_alloc = ft_malloc(size);
    if (new_alloc) {
        pthread_mutex_lock(&g_heap_mutex);
        ft_memcpy(new_alloc, ptr, block->size - sizeof(t_block));
        pthread_mutex_unlock(&g_heap_mutex);
        ft_free(ptr);
    }
    return new_alloc;
    
}