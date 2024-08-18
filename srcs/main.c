#include <md5.h>
#include <string.h>
#include <stdio.h>
#include <ft_malloc.h>
#include <parse_arg.h>
#include <sha256.h>
#include <ft_list.h>

/* TODO */
void usage()
{
    printf("usage: ft_ssl command [flags] [file/string]\n");
}

// void parse_args()

int main(int argc, char **argv)
{
    int flags = 0;
    list_t *encrypt = NULL;
    int algorithm = NONE;

    if (argc < 2)
    {
        usage();
        return 1;
    }

    parse_args(argc, argv, &flags, (void**)&encrypt, &algorithm);
    if (encrypt == NULL)
    {
        printf("ft_ssl: Error: No input data.\n");
        return 1;
    }

    if (algoithm == MD5)
    {
        md5_main(encrypt->data, flags);
    }
    else if (algorithm == SHA256)
    {
        sha256_main(encrypt->data, flags);
    }
    else
    {
        printf("ft_ssl: Error: '%s' is an invalid command.\n", argv[1]);
        usage();
        return 1;
    }

    list_clear(&encrypt);

    return 0;
}
