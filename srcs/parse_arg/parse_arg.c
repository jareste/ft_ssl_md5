#include <ft_malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <ft_ssl.h>
#include <ft_list.h>

static void read_stdin(char **encrypt) {
    size_t buffer_size = 1024;
    size_t total_size = 0;
    char *buffer = malloc(buffer_size);
    int c;

    while ((c = getchar()) != EOF) {
        printf("c: %c\n", c);
        if (total_size + 1 >= buffer_size) {
            buffer_size *= 2;
            buffer = realloc(buffer, buffer_size);
        }
        buffer[total_size++] = (char)c;
    }

    if (total_size == 0) {
        free(buffer);
        *encrypt = NULL;
        return;
    }

    buffer[total_size] = '\0';
    *encrypt = buffer;
}

void parse_args(int argc, char *argv[], int *flags, void** encrypt, char** filename)
{
    int opt;
    char* stdin_buffer = NULL;
    list_t **list = (list_t **)encrypt;

    if (strcasecmp(argv[1], "md5") == 0)
    {
        // printf("MD5\n");
    }
    else if (strcasecmp(argv[1], "sha256") == 0)
    {
        // printf("SHA256\n");
    }
    else if (strcasecmp(argv[1], "help") == 0)
    {
        // print_usage();
    }
    else
    {
        fprintf(stderr, "Invalid command: '%s'; try 'help' for a list.\n", argv[1]);
        exit(1);
    }

    UNUSED_PARAM(filename);
    while ((opt = getopt(argc, argv, "?hpqrs:")) != -1)
    {
        switch (opt)
        {
            case '?':
            case 'h':
                // print_usage();
                exit(0);
            case 'p':
                *flags |= P_FLAG;
                break;
            case 'q':
                *flags |= Q_FLAG;
                break;
            case 'r':
                *flags |= R_FLAG;
                break;
            case 's':
                *encrypt = strdup(optarg);
                break;
            default:
                // print_usage();
                exit(1);
        }
    }

    if (optind >= argc)
    {
        fprintf(stderr, "Expected argument after options\n");
        // print_usage();
        exit(1);
    }

    /* chekc if something to read from stdin. */
    if (!isatty(fileno(stdin))) {
        read_stdin((char **)encrypt);
        list_add_last(list, stdin_buffer);
        free(stdin_buffer);
    }
}