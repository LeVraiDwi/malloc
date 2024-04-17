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
            writeStr("0x");
            WriteHexa((unsigned long int)block, 0);
            writeStr(" - 0x");
            WriteHexa((unsigned long int)(block + block->size), 0);
            writeStr(" : ");
            printUint((unsigned long int)(block->size - sizeof(t_block)));
            writeStr(" bytes\n");
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
        writeStr("TINY : 0x");
        WriteHexa((unsigned long int)page, 0);
        writeStr("\n");
        show_page_mem(page);
        page = page->next;
    }
    page = get_zone(1)->page;
    while (page) {
        writeStr("SMALL : 0x");
        WriteHexa((unsigned long int)page, 0);
        writeStr("\n");
        show_page_mem(page);
        page = page->next;
    }
    page = get_zone(2)->page;
    while (page) {
        writeStr("LARGE : 0x");
        WriteHexa((unsigned long int)page, 0);
        writeStr("\n");
        show_page_mem(page);
        page = page->next;
    }
    pthread_mutex_unlock(&g_heap_mutex);

    return;
}