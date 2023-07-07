#ifndef FT_MALLOC_INCLUDE_H
# define FT_MALLOC_INCLUDE_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include "libft.h"

# define ALIGNEMENT 8
# define ALIGNE(size) ((size + (ALIGNEMENT - 1)) & ~(ALIGNEMENT - 1))
# define BLOCK_SIZE(size) (ALIGNE(size + sizeof(t_block)))

# define HEADER_PAGE_SHIFT(page) ((void *)page + sizeof(t_page))
# define HEADER_BLOCK_DESHIFT(ptr) ((void *)ptr - sizeof(t_page))


# define HEADER_BLOCK_SHIFT(block) ((void *)block + sizeof(t_block))
# define HEADER_BLOCK_DESHIFT(ptr) ((void *)ptr - sizeof(t_block))



# define MIN_PAGE_BLOCK 128

# define TINY_BLOCK_MAX 256
# define TINY_BLOCK_SIZE BLOCK_SIZE(TINY_BLOCK_MAX);
# define TINY_PAGE_SIZE (((TINY_BLOCK_SIZE * MIN_PAGE_BLOCK + sizeof(t_page)) / getpagesize() + 1) * getpagesize())

# define SMALL_BLOCK_MAX 2048
# define SMALL_BLOCK_SIZE BLOCK_SIZE(SMALL_BLOCK_MAX);
# define SMALL_PAGE_SIZE (((SMALL_BLOCK_SIZE * MIN_PAGE_BLOCK + sizeof(t_page)) / getpagesize() + 1) * getpagesize())

# define LARGE_PAGE_SIZE(size) (((BLOCK_SIZE(size) + sizeof(t_page)) / getpagesize() + 1) * getpagesize())

extern t_heap g_heap;
extern pthread_mutex_t g_heap_mutex;

typedef struct s_page t_page;

typedef s_block {
    size_t          size;
    bool            allocated;
    t_page          *parent;
    void            *index;
    struct s_block  *next;
    struct s_block  *prev;
}       t_block;

typedef s_page {
    size_t          size;
    size_t          used_size;
    unsigned int    nb_block;
    unsigned int    nb_freed;
    t_block         *block;
    struct s_page   next;
    struct s_page   prev;
}       t_page;

typedef s_zone {
    t_page          *page;
    unsigned int    nb_page;
}       t_zone;

typedef s_heap {
    t_zone  *tiny;
    t_zone  *small;
    t_zone  *large;
}       t_heap;
#endif