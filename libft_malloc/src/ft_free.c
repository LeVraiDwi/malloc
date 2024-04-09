#include "ft_malloc_include.h"

t_zone    *ft_get_page_zone(t_page *page) {
    if (page->size == TINY_PAGE_SIZE)
        return &g_heap.tiny;
    else if (page->size == SMALL_PAGE_SIZE)
        return &g_heap.small;
    else
        return &g_heap.large;
}
//arrivee au dernier block non alloue puis les lierer en remontant si prev est nul beri si next si next rien sinon suppr page
void    ft_defragment_block(t_block *block) {
    if (block->next != NULL && block->next->allocated == false) {
        ft_defragment_block(block->next);
    }
    else if (block->prev != NULL) {
        if (block->next == NULL) {
            t_page *page = block->parent;
            t_block *prev = block->prev;

            #ifdef MALLOC_OVERFLOW
                 set_prot(prev); 
            #endif
            prev->next = NULL;
            page->nb_block--;
            page->nb_freed--;
            page->used_size -= block->size;
            ft_bzero(block, block->size);
        }
        else {
            t_block *prev = block->prev;
            prev->next = block->next;
            if (prev->next)
                block->next->prev = prev;
            prev->size += block->size;
            block->parent->nb_block--;
            block->parent->nb_freed--;
            ft_bzero(block, block->size);
            #ifdef MALLOC_OVERFLOW
                 set_prot(prev); 
            #endif
        }
        
    }
    else if (block->next == NULL) {
        ft_free_page(block->parent);
    }
    return;
}
// void    ft_defragment_block(t_block *block, t_page *page) {
//     t_block *act_block;
    
//     act_block = block->prev;
//     while (act_block && act_block->allocated == false) {
//         act_block->size += block->size;
//         if (block->next)
//             block->next->prev = act_block;
//         act_block->next = block->next;
//         ft_bzero(HEADER_BLOCK_SHIFT(act_block), act_block->size - sizeof(t_block));
//         page->nb_block--;
//         page->nb_freed--;
//         block = act_block;
//         #ifdef MALLOC_OVERFLOW
//             set_prot(act_block); 
//         #endif
//         act_block = act_block->prev;
//     }
//     act_block = block->next;
//     while (act_block && act_block->allocated == false) {
//         block->size += act_block->size;
//         if (act_block->next)
//             act_block->next->prev = block;
//         block->next = act_block->next;
//         //ft_bzero(HEADER_BLOCK_SHIFT(block), block->size - sizeof(t_block));
//         page->nb_block--;
//         page->nb_freed--;
//         #ifdef MALLOC_OVERFLOW
//             set_prot(act_block); 
//         #endif
//         act_block = block->next;
//     }
//     if (!block->next) {
//         page->nb_block--;
//         page->nb_freed--;
//         page->used_size -= block->size;
//         if (block->prev)
//             block->prev->next = NULL;
//         //ft_bzero(block, block->size);
//     }
//     return;
// }

void    ft_free_page(t_page *page) {
    t_zone  *page_zone;

    page_zone = ft_get_page_zone(page);
    if (page_zone->nb_page >= 1) {
        page_zone->nb_page--;
        if (page_zone->page == page)
            page_zone->page = page->next;
        if (page->prev)
            page->prev->next = page->next;
        if (page->next)
            page->next->prev = page->prev;
        if (munmap(page, page->size))
            ft_putstr_fd("free() : munmap fail\n", 2);
    }
}

void ft_run_free(void *ptr) {
    t_page  *page;
    t_block *block = HEADER_BLOCK_DESHIFT(ptr);
    if (!ptr)
        return;
    page = block->parent;
    block->allocated = false;
    page->nb_freed++;
    if (page->nb_freed == page->nb_block) {
        ft_free_page(page);
    } else {
        ft_defragment_block(block);
    }
    return;
}

void    ft_free(void *ptr) { 
    pthread_mutex_lock(&g_heap_mutex);
    ft_run_free(ptr);
    pthread_mutex_unlock(&g_heap_mutex);
    return;
}