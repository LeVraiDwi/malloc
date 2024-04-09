#ifndef FT_MALLOC_INCLUDE_H
# define FT_MALLOC_INCLUDE_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
#include <sys/resource.h>
# include "libft.h"

# define ALIGNEMENT 8
# define ALIGNE(size) ((size + (ALIGNEMENT - 1)) & ~(ALIGNEMENT - 1))
# define BLOCK_SIZE(size) (ALIGNE(size + sizeof(t_block)))

# define HEADER_PAGE_SHIFT(page) ((void *)page + sizeof(t_page))
# define HEADER_PAGE_DESHIFT(ptr) ((void *)ptr - sizeof(t_page))


# define HEADER_BLOCK_SHIFT(block) ((void *)block + sizeof(t_block))
# define HEADER_BLOCK_DESHIFT(ptr) ((void *)ptr - sizeof(t_block))

#define TINY_PAGE 0
#define SMALL_PAGE 2
#define LARGE_PAGE 3

# define MIN_PAGE_BLOCK 128

# define TINY_BLOCK_MAX 256
# define TINY_BLOCK_SIZE BLOCK_SIZE(TINY_BLOCK_MAX)
# define TINY_PAGE_SIZE ((((TINY_BLOCK_SIZE * MIN_PAGE_BLOCK) + sizeof(t_page)) / getpagesize() + 1) * getpagesize())

# define SMALL_BLOCK_MAX 2048
# define SMALL_BLOCK_SIZE BLOCK_SIZE(SMALL_BLOCK_MAX)
# define SMALL_PAGE_SIZE ((((SMALL_BLOCK_SIZE * MIN_PAGE_BLOCK) + sizeof(t_page)) / getpagesize() + 1) * getpagesize())

# define LARGE_PAGE_SIZE(size) (((size + sizeof(t_page)) / getpagesize() + 1) * getpagesize())

typedef struct s_page t_page;

typedef struct s_block {
    # ifdef MALLOC_OVERFLOW
    char            start_prot[9];
    # endif
    # ifdef MALLOC_HISTORY
        unsigned int    nb_reallocation;
        size_t          old_size;
    # endif
    size_t          size;
    bool            allocated;
    t_page          *parent;
    struct s_block  *next;
    struct s_block  *prev;
    # ifdef MALLOC_OVERFLOW
    char            end_prot[9];
    # endif
}       t_block;

typedef enum    e_type_page {
    Large = 0, Tiny = TINY_BLOCK_SIZE, Small = SMALL_BLOCK_SIZE

}               t_type_page;

typedef struct s_page {
    size_t          size;
    size_t          used_size;
    t_type_page     typeOfPage;
    unsigned int    nb_block;
    unsigned int    nb_freed;
    t_block         *block;
    struct s_page   *next;
    struct s_page   *prev;
}       t_page;

typedef struct s_zone {
    t_page          *page;
    unsigned int    nb_page;
}       t_zone;

typedef struct s_g_heap {
    t_zone  tiny;
    t_zone  small;
    t_zone  large;
}       t_g_heap;

extern t_g_heap g_heap;
extern pthread_mutex_t g_heap_mutex;

void    *ft_find_fitting_block(t_zone *zone, size_t block_size);
void    *ft_fragment_block(t_block *block, t_page *page, size_t block_size);
void    *ft_add_page(t_zone *zone, size_t block_size);
void    *ft_alloc(t_zone *zone, size_t block_size);
void    *ft_malloc(size_t size);
void    *ft_run_malloc(size_t size);

void    ft_free(void *ptr);
void    ft_defragment_block(t_block *block);
void    set_prot(t_block *block);
void    ft_run_free(void *ptr);
void    ft_free_page(t_page *page);

t_page  *ft_alloc_page(size_t size, t_type_page type);

t_zone  *get_zone(int i);

#endif