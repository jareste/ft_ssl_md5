#ifndef FT_MALLOC_H
#define FT_MALLOC_H

#include <stdlib.h>

void* ft_malloc(size_t size);
void* ft_realloc(void *ptr, size_t size);
char* ft_strdup(const char *s);

#define malloc(x) ft_malloc(x)
#define realloc(x, y) ft_realloc(x, y)
#define strdup(x) ft_strdup(x)

#endif