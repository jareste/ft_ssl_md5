/***************************/
/*        INCLUDES         */
/***************************/

#include <ft_malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <ft_ssl.h>
#include <ft_list.h>

/***************************/
/*        DEFINES          */
/***************************/

static const char *g_algorithms[] = {
    "md5",
    "sha256",
    "help",
    "--help",
    "-h",
    NULL
};

/***************************/
/*        METHODS          */
/***************************/

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

static int check_algorithm(char *algorithm)
{
    if (algorithm == NULL) goto error;

    for (int i = 0; g_algorithms[i]; i++)
    {
        if (strcasecmp(algorithm, g_algorithms[i]) == 0)
        {
            return i;
        }
    }
    
error:
    fprintf(stderr, "ft_ssl: Error: '%s' is an invalid command.\n", algorithm);
    // print_usage();
    exit(EXIT_FAILURE);
}

void parse_args(int argc, char *argv[], int *flags, void** encrypt, int* algorithm)
{
    int opt;
    char* stdin_buffer = NULL;
    list_t **list = (list_t **)encrypt;

    *algorithm = check_algorithm(argv[1]);

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
                if (optarg)
                {
                    list_add_last(list, optarg);
                }
                else
                {
                    fprintf(stderr, "Option -l contains garbage as argument: %s.\n", optarg);
                    fprintf(stderr, "This will become fatal error in the future.\n");
                }
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