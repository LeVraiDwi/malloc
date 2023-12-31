#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdlib.h>

void    *ft_malloc(size_t size);
void    ft_free(void *ptr);
void    *ft_realloc(void *ptr, size_t size);
void    show_alloc_mem();
void    show_alloc_mem_hex();
#endif