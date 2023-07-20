#include "ft_malloc_include.h"

void show_page_mem_hex(t_page *page) {
    t_block *block;
    char    *str;

    block = page->block;
        while (block) {
            printf("0x%X - 0x%X : %zu bytes\n", (unsigned int)block, (unsigned int)(block + block->size), (block->size) );
            str = HEADER_BLOCK_SHIFT(block);
            if (block->allocated) {
                for (size_t i = 0; i + sizeof(t_block) < block->size; i++) {
                    printf("%.2X ", str[i]);
                    if ( (i + 1) % 8 == 0)
                        printf("\n");
                }
                printf("\n");
            }
            block = block->next;
        }
    page = page->next;
    return;
}

void show_alloc_mem_hex() {
    t_page  *page;

    pthread_mutex_lock(&g_heap_mutex);
    page = get_zone(0)->page;
    while (page) {
        printf("TINY : 0x%X\n", (unsigned int)page);
        show_page_mem_hex(page);
        page = page->next;
    }
    page = get_zone(1)->page;
    while (page) {
        printf("SMALL : 0x%X\n", (unsigned int)page);
        show_page_mem_hex(page);
        page = page->next;
    }
    page = get_zone(2)->page;
    while (page) {
        printf("LARGE : 0x%X\n", (unsigned int)page);
        show_page_mem_hex(page);
        page = page->next;
    }
    pthread_mutex_unlock(&g_heap_mutex);

    return;
}