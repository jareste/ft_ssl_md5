#include <md5.h>
#include <string.h>
#include <stdio.h>
#include <ft_malloc.h>
#include <parse_arg.h>

/* TODO */
void usage()
{
    printf("usage: ft_ssl command [flags] [file/string]\n");
}

// void parse_args()

int main(int argc, char **argv)
{
    int flags = 0;
    char* encrypt = NULL;

    if (argc < 2)
    {
        usage();
        return 1;
    }

    parse_args(argc, argv, &flags, &encrypt);

    if (strcmp(argv[1], "md5") == 0)
    {
        md5_main(encrypt);
    }
    else if (strcmp(argv[1], "sha256") == 0)
    {
        /* TODO */
    }
    else
    {
        printf("ft_ssl: Error: '%s' is an invalid command.\n", argv[1]);
        usage();
        return 1;
    }

    return 0;
}
