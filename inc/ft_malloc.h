#ifndef FT_MALLOC_H
#define FT_MALLOC_H

#include <stdlib.h>

void* ft_malloc(size_t size);

#define malloc(x) ft_malloc(x)

#endif