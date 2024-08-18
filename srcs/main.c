#include <md5.h>
#include <string.h>
#include <stdio.h>
#include <ft_malloc.h>
#include <parse_arg.h>
#include <sha256.h>
#include <ft_list.h>
#include <ft_ssl.h>

/* TODO */
void usage(int code)
{
    printf("usage: ft_ssl command [flags] [file/string]\n");
    exit(code);
}

int main(int argc, char **argv)
{
    int flags = 0;
    list_t *encrypt = NULL;
    int algorithm = NONE;

    if (argc < 2) usage(0);

    parse_args(argc, argv, &flags, (void**)&encrypt, &algorithm);
    if (encrypt == NULL)
    {
        printf("ft_ssl: Error: No input data.\n");
        // usage();
        return 1;
    }

    if (algorithm == MD5)
    {
        md5_main(encrypt->data, flags);
    }
    else if (algorithm == SHA256)
    {
        sha256_main(encrypt->data, flags);
    }
    else /* error */
    {
        printf("ft_ssl: Error: '%s' is an invalid command.\n", argv[1]);
        usage(1);
    }

    list_clear(&encrypt);

    return 0;
}
