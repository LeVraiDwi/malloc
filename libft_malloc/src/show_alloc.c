#include "ft_malloc_include.h"

t_zone  *get_zone(int i) {
    if (i == 0)
        return &g_heap.tiny;
    if (i == 1)
        return &g_heap.small;
    if (i == 2)
        return &g_heap.large;
    return NULL;
}

void show_page_mem(t_page *page) {
    t_block *block;

    block = page->block;
        while (block) {
            printf("0x%lX - 0x%lX : %zu bytes\n", (unsigned long int)block, (unsigned long int)(block + block->size), (block->size - sizeof(t_block)) );
            block = block->next;
        }
    page = page->next;
    return;
}

void show_alloc_mem() {
    t_page  *page;

    pthread_mutex_lock(&g_heap_mutex);
    page = get_zone(0)->page;
    while (page) {
        printf("TINY : 0x%lX\n", (unsigned long int)page);
        show_page_mem(page);
        page = page->next;
    }
    page = get_zone(1)->page;
    while (page) {
        printf("SMALL : 0x%lX\n", (unsigned long int)page);
        show_page_mem(page);
        page = page->next;
    }
    page = get_zone(2)->page;
    while (page) {
        printf("LARGE : 0x%lX\n", (unsigned long int)page);
        show_page_mem(page);
        page = page->next;
    }
    pthread_mutex_unlock(&g_heap_mutex);

    return;
}