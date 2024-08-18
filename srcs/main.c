#include <md5.h>
#include <string.h>
#include <stdio.h>
#include <ft_malloc.h>
#include <parse_arg.h>
#include <sha256.h>
#include <ft_list.h>
#include <ft_ssl.h>
#include <utils.h>

/* TODO */
static void usage(int code)
{
    printf("usage: ft_ssl command [flags] [file/string]\n");
    exit(code);
}

int main(int argc, char **argv)
{
    int flags = 0;
    void *encrypt = NULL;
    algorithms algorithm = NONE;

    if (argc < 2) usage(0);

    parse_args(argc, argv, &flags, &encrypt, &algorithm);
    if (encrypt == NULL)
    {
        printf("ft_ssl: Error: No input data.\n");
        usage(1);
        exit(EXIT_FAILURE);
    }

    exec_algorithm(encrypt, flags, algorithm);

    return 0;
}
