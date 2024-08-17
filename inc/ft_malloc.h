#ifndef FT_MALLOC_H
#define FT_MALLOC_H

#include <stdlib.h>

void* ft_malloc(size_t size);
void* ft_realloc(void *ptr, size_t size);

#define malloc(x) ft_malloc(x)
#define realloc(x, y) ft_realloc(x, y)

#endif