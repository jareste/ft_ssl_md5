#include <ft_malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#undef malloc
#undef realloc

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

void* ft_realloc(void *ptr, size_t size)
{
    void* new_ptr = realloc(ptr, size);
    ft_assert(new_ptr != NULL, "realloc failed");
    return new_ptr;
}

char *ft_strdup(const char *s)
{
    size_t len = strlen(s);
    char *new_s = ft_malloc(len + 1);
    strcpy(new_s, s);
    return new_s;
}