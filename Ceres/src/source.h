#ifndef SOURCE_H
#define SOURCE_H

#include <stddef.h>

typedef struct {
    char* data;
    size_t length;
} source_t;

source_t source_load(const char* path);
char source_at(source_t* self, size_t n);

#endif
