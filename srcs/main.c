#include <md5.h>
#include <string.h>
#include <stdio.h>

/* TODO */
void usage()
{
    printf("usage: ft_ssl command [flags] [file/string]\n");
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        usage();
        return 1;
    }

    if (strcmp(argv[1], "md5") == 0)
    {
        md5_main(argc - 1, &argv[1]);
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
