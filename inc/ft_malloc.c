#include <ft_malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#undef malloc

#ifdef NDEBUG

    #define ft_assert(expr, message) \
        if (!(expr)) { \
            fprintf(stderr, "Assertion failed: %s\nFile: %s, Line: %d\n", message, __FILE__, __LINE__); \
            abort(); \
        }
#else
    #define ft_assert(expr, message) \
        if (!(expr)) { \
            fprintf(stderr, "Assertion failed: %s\nFile: %s, Line: %d\n", message, __FILE__, __LINE__); \
            exit(EXIT_FAILURE); \
        }
#endif

void* ft_malloc(size_t size)
{
    void *ptr = malloc(size);
    ft_assert(ptr != NULL, "malloc failed");
    return ptr;
}