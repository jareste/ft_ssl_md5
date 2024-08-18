#ifndef FT_SSL_H
#define FT_SSL_H

#define UNUSED_PARAM(x) (void)(x)
#define P_FLAG 0x0001
#define Q_FLAG 0x0002
#define S_FLAG 0x0008
#define R_FLAG 0x0004

// #define NONE 0
// #define MD5 1
// #define SHA256 2

typedef enum {
    TYPE_STDIN,
    TYPE_FILE,
    TYPE_NORMAL
} input_type;

typedef enum {
    MD5,
    SHA256,
    HELP,
    NONE
} algorithms;


#endif