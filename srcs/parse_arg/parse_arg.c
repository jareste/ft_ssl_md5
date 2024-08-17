#include <ft_malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <ft_ssl.h>

static void read_stdin(char **encrypt) {
    size_t buffer_size = 1024;
    size_t total_size = 0;
    char *buffer = malloc(buffer_size);
    int c;

    while ((c = getchar()) != EOF) {
        if (total_size + 1 >= buffer_size) {
            buffer_size *= 2;
            char *new_buffer = realloc(buffer, buffer_size);
            if (new_buffer == NULL) {
                free(buffer);
                fprintf(stderr, "Memory reallocation failed\n");
                exit(EXIT_FAILURE);
            }
            buffer = new_buffer;
        }
        buffer[total_size++] = (char)c;
    }

    buffer[total_size] = '\0';

    *encrypt = buffer;
}

void parse_args(int argc, char *argv[], int *flags, char** encrypt, char** filename)
{
    int opt;

    

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

    /* no input recieved, read from stdin. */
    if (*encrypt == NULL)
    {
        read_stdin(encrypt);
    }
}