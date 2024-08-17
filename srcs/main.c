#include <md5.h>
#include <string.h>
#include <stdio.h>
#include <ft_malloc.h>

/* TODO */
void usage()
{
    printf("usage: ft_ssl command [flags] [file/string]\n");
}

// void parse_args()

int main(int argc, char **argv)
{
    char buffer[1024] = {0};

    while (fgets(buffer, sizeof(buffer), stdin)) {
    }

    if (argc < 2)
    {
        usage();
        return 1;
    }

    if (strcmp(argv[1], "md5") == 0)
    {
        md5_main(buffer);
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
