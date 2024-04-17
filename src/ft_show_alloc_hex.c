#include "ft_malloc_include.h"

void show_page_mem_hex(t_page *page) {
    t_block *block;
    char    *str;

    block = page->block;
        while (block) {
            writeStr("0x");
            WriteHexa((unsigned long int)block, 0);
            writeStr(" - 0x");
            WriteHexa((unsigned long int)(block + block->size), 0);
            writeStr(" : ");
            printUint((unsigned long int)(block->size - sizeof(t_block)));
            writeStr(" bytes\n");
            str = HEADER_BLOCK_SHIFT(block);
            #ifdef MALLOC_OVERFLOW
                writeStr("overflow check: ");
                writeStr(block->start_prot);
                writeStr(" | ");
                writeStr(block->end_prot);
                writeStr("\n");
            #endif
            if (block->allocated) {
                for (size_t i = 0; i + sizeof(t_block) < block->size; i++) {
                    WriteHexa(str[i], 2);
                    writeStr(" ");
                    if ( (i + 1) % 8 == 0)
                        writeStr("\n");
                }
            }
            writeStr("\n");
            block = block->next;
        }
    return;
}

void show_alloc_mem_hex() {
    t_page  *page;

    pthread_mutex_lock(&g_heap_mutex);
    
    page = get_zone(0)->page;
    while (page) {
        writeStr("TINY : 0x");
        WriteHexa((unsigned long int)page, 0);
        writeStr("\n");
        show_page_mem_hex(page);
        page = page->next;
    }
    page = get_zone(1)->page;
    while (page) {
        writeStr("SMALL : 0x");
        WriteHexa((unsigned long int)page, 0);
        writeStr("\n");
        show_page_mem_hex(page);
        page = page->next;
    }
    page = get_zone(2)->page;
    while (page) {
        writeStr("LARGE : 0x");
        WriteHexa((unsigned long int)page, 0);
        writeStr("\n");
        show_page_mem_hex(page);
        page = page->next;
    }

    pthread_mutex_unlock(&g_heap_mutex);

    return;
}