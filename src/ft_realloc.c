#include "ft_malloc_include.h"

bool    ft_expand_block(t_block *block, size_t new_size) {
    t_page *parent;
    t_block *new_block;

    writeStr("expand\n");
    parent = block->parent;
    //le bloc suivant est non alloc et il y a la place
    if (block->next && !block->next->allocated && block->next->size + block->size >= new_size) {
        t_block *next;

        next = block->next;
        if (next->size + block->size <= BLOCK_SIZE(ALIGNEMENT)) //la somme des block est pile a la bonne taille le block suivant est supprimer
        {
            block->size += next->size;
            parent->nb_block--;
            parent->nb_freed--;
            block->next = next->next;
            if (next->next)
                next->next->prev = block;
            ft_bzero(next, next->size);
            #ifdef MALLOC_OVERFLOW
                    set_prot(block); 
            #endif
        }
        else { //la nouvelle taille fais forcement la taille d'un header t_block
            new_block = block + new_size;
            new_block->allocated = false;
            new_block->next = next->next;
            if (new_block->next)
                new_block->next->prev = new_block;
            new_block->prev = block;
            parent->used_size -= block->size;
            new_block->size = block->size + next->size - new_size;
            block->size = new_size;
            parent->used_size += block->size;
            block->next = new_block;
            ft_bzero(next, new_size - block->size);
            #ifdef MALLOC_OVERFLOW
                    set_prot(block); 
            #endif
            #ifdef MALLOC_OVERFLOW
                    set_prot(block->next); 
            #endif
        }
        return true;
    }
    else if (!block->next && block->parent->size - block->parent->used_size + block->size >= new_size) { //le bloc suivant est null mais il reste de la place non utiliser dans la page
        parent->used_size += new_size - block->size;
        block->size = new_size;
        #ifdef MALLOC_OVERFLOW
                    set_prot(block); 
        #endif
        return true;
    }
    return false; // il y a pas de place pour l'expansion
}

bool    ft_shrink_block(t_block *block, size_t size) {
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
        ft_defragment_block(new_block);
        return true;
    }
    return false;
}

bool ft_expand_possible(t_block *block, size_t new_size) {
    if (block->next && block->next->size + block->size >= new_size) {
        return true;
    }
    else if (!block->next && block->parent->size - block->parent->used_size + block->size >= new_size) {
        return true;
    }
    return false;
}

bool    ft_fragment_if_possible(t_block *block, size_t size) {
    if (size == block->size)
        return true;
    else if (size > block->parent->typeOfPage)
        return false;
    else if (size >= block->size)
        return ft_expand_block(block, size);
    else if (size < block->size)
    {
        return ft_shrink_block(block, size);
    }
    return false; 
        
}

void    *realloc(void *ptr, size_t size) {
    t_block *block;
    bool    is_realloc;
    void    *new_alloc;

    pthread_mutex_lock(&g_heap_mutex);
    if (size <= 0) {
        if (ptr)
            ft_run_free(ptr);
        pthread_mutex_unlock(&g_heap_mutex);
        return NULL;
    }

    if (!ptr)
    {
        pthread_mutex_unlock(&g_heap_mutex);
        return ft_run_malloc(size);
    }
    
    block = HEADER_BLOCK_DESHIFT(ptr);
    is_realloc = ft_fragment_if_possible(block, BLOCK_SIZE(size));

    if (is_realloc)
    {
        writeStr("is_realloc\n");
        pthread_mutex_unlock(&g_heap_mutex);
        return ptr;
    }
    new_alloc = ft_run_malloc(size);
    if (new_alloc) {
        ft_memcpy(new_alloc, ptr, block->size - sizeof(t_block));
        ft_run_free(ptr);
    }
    pthread_mutex_unlock(&g_heap_mutex);

    return new_alloc;
}