#ifndef WHIRLPOOL_H
#define WHIRLPOOL_H

#include <stddef.h>
#include <stdint.h>

#define WHIRLPOOL_DIGEST_LENGTH 64

void whirlpool_main(const char *data, char* procedence, int type, int flags, size_t size);

#endif
