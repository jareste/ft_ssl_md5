#include <md5.h>
#include <ft_list.h>
#include <ft_malloc.h>
#include <sha256.h>
#include <string.h>
#include <ft_ssl.h>

#include <stdio.h>

void exec_algorithm(void *encrypt, int flags, int algorithm)
{
    list_t *list = (list_t *)encrypt;

    /* SHOULD NEVER HAPPEN */
    ft_assert(list, "Fatal error: No input data.");

    while (list)
    {
        switch (algorithm)
        {
        case MD5:
            md5_main(list->node.data, list->node.procedence, flags);
            break;
        case SHA256:
            sha256_main(list->node.data, list->node.procedence, flags);
            break;
        default:
            ft_assert(0, "Fatal error: Unknown algorithm.");
            break;
        }
        list = list_get_next(list);
    }

    /* reset list pointer for cleaning */
    list = (list_t *)encrypt;
    list_clear(&list);
}