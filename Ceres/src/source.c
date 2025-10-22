#include "error.h"
#include "source.h"
#include <stdio.h>
#include <stdlib.h>

source_t source_load(const char* path) {
    source_t source = {0};
    
    FILE* source_fp = fopen(path, "r");
    if (source_fp == NULL)
        error("Failed to open %s", path);

    if (fseek(source_fp, 0, SEEK_END) != 0)
        error("Failed to get the size of the source");

    source.length = ftell(source_fp);
    source.data = malloc(source.length);
    if (source.data == NULL)
        error("Failed to allocate space for the source");

    if (fseek(source_fp, 0, SEEK_SET) != 0)
        error("Failed to return to start of the source");
    if (fread(source.data, sizeof(char), source.length, source_fp) < source.length)
        error("Failed to read the source");
    
    fclose(source_fp);

    return source;
}

char source_at(source_t* self, size_t n) {
    if (n >= self->length)
        error("Source access out of bounds : %ld", n);

    return self->data[n];
}
