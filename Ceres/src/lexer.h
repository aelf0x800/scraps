#ifndef LEXER_H
#define LEXER_H

#include "source.h"
#include "token.h"
#include <stddef.h>
#include <stdint.h>

typedef struct {
    source_t source;
    token_list_t tokens;
    size_t idx;
} lexer_t;

lexer_t lexer(const char* path);

#endif
