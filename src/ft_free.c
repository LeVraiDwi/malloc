#include "ft_malloc_include.h"

void    ft_defragment_block(t_block *block) {
    if (block->next != NULL && block->next->allocated == false) {
        ft_defragment_block(block->next);
    }
    else if (block->prev) { //merge avec le bloc precedent
            //si le block est suivis d'un block on le conserve pour eviter de decaler ce block dans la memoire
            if (block->prev->allocated == false) {
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
                ft_defragment_block(prev);
            }
            else if (!block->next) {
                block->parent->nb_block--;
                block->parent->nb_freed--;
                block->parent->used_size -= block->size;
                block->prev->next = NULL;
                ft_bzero(block, block->size);
            }
    }
    else if (block->next == NULL) { //si dernier bloc de la page
        if (PageShouldBeFree(block->parent)) {
            ft_free_page(block->parent);
        }
        else {
            block->parent->nb_block--;
            block->parent->nb_freed--;
            block->parent->used_size -= block->size;
            block->parent->block = NULL;
            ft_bzero(block, block->size);
        }
    }
    return;
}


void    ft_free_page(t_page *page) {
    t_zone  *page_zone;
    
    page_zone = ft_get_page_zone(page);
    if (page_zone->nb_page >= 1) {
        removePage(page, page_zone);
        if (munmap(page, page->size))
            ft_putstr_fd("free() : munmap fail\n", 2);
        
    }
}

bool could_be_free(void *ptr) {
    t_page  *page;
    t_zone  *zone;
    t_block *block;

    zone = &g_heap.tiny;
    page = zone->page;
    while (page) {
        block = page->block;
        while (block) {
            if (block == ptr)
                return true;
            block = block->next;
        }
        page = page->next;
    }

    zone = &g_heap.small;
    page = zone->page;
    while (page) {
        block = page->block;
        while (block) {
            if (block == ptr)
                return true;
            block = block->next;
        }
        page = page->next;
    }

    zone = &g_heap.large;
    page = zone->page;
    while (page) {
        block = page->block;
        while (block) {
            if (block == ptr)
                return true;
            block = block->next;
        }
        page = page->next;
    }
    return false;
}

void ft_run_free(void *ptr) {
    t_page  *page;
    t_block *block = HEADER_BLOCK_DESHIFT(ptr);

    if (!ptr)
        return;
    //if (!could_be_free(block))
      //   return;
    page = block->parent;
    block->allocated = false;
    page->nb_freed++;
    if (PageShouldBeFree(page)) {
        ft_free_page(page);
    } else {
        ft_defragment_block(block);
    }
    return;
}

void    free(void *ptr) {
    pthread_mutex_lock(&g_heap_mutex);
    ft_run_free(ptr);
    pthread_mutex_unlock(&g_heap_mutex);
    return;
}