#include "ft_malloc_include.h"

t_g_heap  g_heap = {
    .tiny = {
        .page = NULL,
        .nb_page = 0,
    },
    .small = {
        .page = NULL,
        .nb_page = 0,
    },
    .large = {
        .page = NULL,
        .nb_page = 0,
    }
};

pthread_mutex_t g_heap_mutex = PTHREAD_MUTEX_INITIALIZER;

void    *ft_fragment_block(t_block *block, t_page *page, size_t block_size) {
    t_block *new_block;

    if (block->size - block_size >= BLOCK_SIZE(ALIGNEMENT)) {
        new_block = block + block->size;
        new_block->allocated = false;
        new_block->size = block->size - block_size;
        new_block->parent = page;
        new_block->next = block->next;
        new_block->prev = block;
        block->next = new_block;
        page->nb_block += 1;
        block->size = block_size;
    }
    block->allocated = true;
    return HEADER_BLOCK_SHIFT(block);
}

t_page    *ft_alloc_page(size_t size) {
    struct rlimit	limit;
	t_page			*page;

	getrlimit(RLIMIT_AS, &limit);
	if (size > limit.rlim_max)
		return (NULL);
	page = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (page == MAP_FAILED)
		return (NULL);
	ft_bzero(page, sizeof(t_page));
	page->size = size;
	page->used_size = sizeof(t_page);
	return (page);
}

void    *ft_add_page(t_zone *zone, size_t block_size) {
    t_page  *act_page;

    if (zone->page == NULL) {
        if (block_size <= TINY_BLOCK_MAX) 
            zone->page = ft_alloc_page(TINY_PAGE_SIZE);
        else if (block_size <= SMALL_BLOCK_MAX)
            zone->page = ft_alloc_page(SMALL_PAGE_SIZE);
         else 
            zone->page = ft_alloc_page(LARGE_PAGE_SIZE(block_size));
        act_page = zone->page;
        if (act_page == NULL)
            return NULL;
        act_page->prev = NULL;
        act_page->next = NULL;
    } else {
        act_page = zone->page;
        while (act_page->next) {
            act_page = act_page->next;
        }
        if (block_size <= TINY_BLOCK_MAX) 
            zone->page->next = ft_alloc_page(TINY_PAGE_SIZE);
        else if (block_size <= SMALL_BLOCK_MAX)
            zone->page->next = ft_alloc_page(SMALL_PAGE_SIZE);
         else 
            zone->page->next = ft_alloc_page(LARGE_PAGE_SIZE(block_size));
        if (zone->page->next == NULL)
            return NULL;
        act_page = zone->page->next;
        act_page->prev = zone->page;
    }
    if (act_page == NULL)
        return NULL;
    zone->nb_page++;
    act_page->nb_block = 1;
    act_page->nb_freed = 0;
    act_page->used_size += block_size;
    act_page->block = HEADER_PAGE_SHIFT(act_page);
    act_page->block->allocated = true;
    act_page->block->prev = NULL;
    act_page->block->next = NULL;
    act_page->block->parent = act_page;
    act_page->block->size = block_size;
    return HEADER_BLOCK_SHIFT(act_page->block);
}

void    *ft_find_fitting_block(t_zone *zone, size_t block_size) {
    t_page  *act_page;
    t_block *act_block;
    t_block *last_block;

    if (zone->page == NULL)
        return NULL;
    for (unsigned int i = 0; i < zone->nb_page; i++) {
        act_page = &zone->page[i];
        if (act_page->block == NULL) {
            act_page->nb_block = 1;
            act_page->block = (t_block *)HEADER_PAGE_SHIFT(&act_page);
            act_page->block->allocated = true;
            act_page->block->size = block_size;
            act_page->block->next = NULL;
            act_page->block->prev = NULL;
            act_page->block->parent = act_page;
            act_page->used_size = block_size;
            return HEADER_BLOCK_SHIFT(act_page->block);
        }
        act_block = act_page->block;
        while (act_block) {
                if (!act_block->allocated && act_block->size >= block_size) {
                    return ft_fragment_block(act_block, act_page, block_size);
                }
                last_block = act_block;
                act_block = act_block->next;     
        }
        act_block = last_block;
        if ((act_page->size - act_page->used_size) >= block_size) {
            //add block at the end
            act_page->nb_block += 1;
            act_page->used_size += block_size;
            act_block->next = act_block + act_block->size;
            act_block = act_block->next;
            act_block->prev = last_block;
            act_block->allocated = true;
            act_block->size = block_size;
            act_block->parent = act_page;
            return HEADER_BLOCK_SHIFT(act_block);
        }
    }
    return NULL;
}

void    *ft_alloc(t_zone *zone, size_t block_size) {
    t_block *block_ptr;

    block_ptr = ft_find_fitting_block(zone, block_size);
    if (block_ptr == NULL) {
        block_ptr = ft_add_page(zone, block_size);
    return block_ptr;
    }
    return block_ptr;
}

void    *ft_malloc(size_t size) {
    size_t  block_size;
    void    *ptr;
    
    ptr = NULL;
    block_size = BLOCK_SIZE(size);
    if (size == 0)
        return NULL;

    pthread_mutex_lock(&g_heap_mutex);

    if (block_size <= TINY_BLOCK_MAX)
        ptr = ft_alloc(&g_heap.tiny, block_size);
    else if (block_size <= SMALL_BLOCK_MAX) {
        ptr = ft_alloc(&g_heap.small, block_size);
    }
    else
        ptr = ft_alloc(&g_heap.large, block_size);

    pthread_mutex_unlock(&g_heap_mutex);
    return ptr;
}