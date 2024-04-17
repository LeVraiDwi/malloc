#include "ft_malloc_include.h"

void removePage(t_page *page, t_zone *zone) {
    zone->nb_page--;
    if (zone->page == page) {
        if (zone->nb_page == 0) {
            zone->page = NULL;
        }
        else {
            zone->page = page->next;
            zone->page->prev = NULL;
        }
    }
    else {
        if (page->prev) {
            page->prev->next = page->next;
            if (page->next)
                page->next->prev = page->prev;
        }
        else if (page->next) {
            page->next->prev = page->prev;
        }
    }
}

int lastPage(t_zone *tiny, t_zone *small, t_zone *large) {
    int nb_page = large->nb_page + small->nb_page + tiny->nb_page;
    return nb_page;
}

int PageShouldBeFree(t_page *page) {
    t_zone  *page_zone;

    if (page->nb_freed == page->nb_block) {
        if (page->typeOfPage == Small || page->typeOfPage == Tiny) {
            page_zone = ft_get_page_zone(page);
            if (page_zone->nb_page >= 2)
                return 1;
            return 0;
        }
        return 1;
    }
    return 0;
}

t_zone    *ft_get_page_zone(t_page *page) {
    if (page->size == TINY_PAGE_SIZE)
        return &g_heap.tiny;
    else if (page->size == SMALL_PAGE_SIZE)
        return &g_heap.small;
    else
        return &g_heap.large;

}