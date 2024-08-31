#include <md5.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ft_malloc.h>
#include <utils.h>

/*
    implementation of md5 algorithm
    Source:
    https://en.wikipedia.org/wiki/MD5
*/

typedef struct
{
    uint32_t h[4];
} md5_ctx_t;

static uint32_t leftrotate(uint32_t x, uint32_t c)
{
    return ((x << c) | (x >> (32 - c)));
}

static void md5(const uint8_t *initial_msg, size_t initial_len, uint8_t *digest)
{
    static const uint32_t r[] = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                                  5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
                                  4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                                  6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };

    static const uint32_t k[] = { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
                                  0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
                                  0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
                                  0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
                                  0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
                                  0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
                                  0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
                                  0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

    uint8_t *msg = NULL;

    size_t new_len, offset;
    uint32_t w[16];
    uint32_t a, b, c, d, f, g, temp;

    md5_ctx_t ctx;

    ctx.h[0] = 0x67452301;
    ctx.h[1] = 0xefcdab89;
    ctx.h[2] = 0x98badcfe;
    ctx.h[3] = 0x10325476;

    new_len = initial_len + 1;
    while (new_len % (512 / 8) != 448 / 8)
    {
        new_len++;
    }

    msg = malloc(new_len + 8);
    memset(msg, 0, new_len + 8);
    memcpy(msg, initial_msg, initial_len);
    msg[initial_len] = 0x80;

    uint64_t bits_len = 8 * initial_len;
    memcpy(msg + new_len, &bits_len, 8);


    for (offset = 0; offset < new_len; offset += (512 / 8))
    {
        for (int i = 0; i < 16; i++)
        {
            w[i] = (uint32_t) msg[offset + i * 4] | ((uint32_t) msg[offset + i * 4 + 1] << 8) |
                   ((uint32_t) msg[offset + i * 4 + 2] << 16) | ((uint32_t) msg[offset + i * 4 + 3] << 24);
        }

        a = ctx.h[0];
        b = ctx.h[1];
        c = ctx.h[2];
        d = ctx.h[3];

        for (int i = 0; i < 64; i++)
        {
            if (i < 16)
            {
                f = (b & c) | ((~b) & d);
                g = i;
            }
            else if (i < 32)
            {
                f = (d & b) | ((~d) & c);
                g = (5 * i + 1) % 16;
            }
            else if (i < 48)
            {
                f = b ^ c ^ d;
                g = (3 * i + 5) % 16;
            }
            else
            {
                f = c ^ (b | (~d));
                g = (7 * i) % 16;
            }

            temp = d;
            d = c;
            c = b;
            b = b + leftrotate(a + f + k[i] + w[g], r[i]);
            a = temp;
        }

        ctx.h[0] += a;
        ctx.h[1] += b;
        ctx.h[2] += c;
        ctx.h[3] += d;
    }

    for (int i = 0; i < 4; i++)
    {
        digest[i * 4] = (ctx.h[i] & 0x000000ff);
        digest[i * 4 + 1] = (ctx.h[i] & 0x0000ff00) >> 8;
        digest[i * 4 + 2] = (ctx.h[i] & 0x00ff0000) >> 16;
        digest[i * 4 + 3] = (ctx.h[i] & 0xff000000) >> 24;
    }

    free(msg);
}

void md5_main(char *encrypt, char* procedence, input_type type, int flags, size_t size)
{
    uint8_t digest[16];
    md5((uint8_t*)encrypt, size, digest);

    UNUSED_PARAM(size);

    /**/
    if (!(flags & Q_FLAG) && !(flags & R_FLAG))
    {
        switch (type)
        {
            case TYPE_NORMAL:
                printf("MD5 (\"");
                print_without_newline(encrypt);
                printf("\") = ");
                break;
            case TYPE_FILE:
                printf("MD5 (");
                print_without_newline(procedence);
                printf(") = ");
                break;
            case TYPE_STDIN:
                /* handled outside */
                break;
            case TYPE_STDIN_NORMAL:
                /* handled outside */
                break;
        }
    }

    if (!(flags & Q_FLAG) && ((type == TYPE_STDIN) || (type == TYPE_STDIN_NORMAL)))
    {
        if (flags & P_FLAG) printf("(\""); else printf("(");
            
        print_without_newline(procedence);
        
        if (flags & P_FLAG) printf("\")= "); else printf(")= ");
            
    }

    /* Print digest */
    for (int i = 0; i < 16; i++)
    {
        printf("%2.2x", digest[i]);
    }

    /**/
    if (!(flags & Q_FLAG) && (flags & R_FLAG))
    {
        switch (type)
        {
            case TYPE_NORMAL:
                printf(" \"");
                print_without_newline(encrypt);
                printf("\"");
                break;
            case TYPE_FILE:
                printf(" ");
                print_without_newline(procedence);
                break;
            case TYPE_STDIN:
                /* handled outside */
                break;
            case TYPE_STDIN_NORMAL:
                /* handled outside */
                break;
        }
    }

    printf("\n");
}
