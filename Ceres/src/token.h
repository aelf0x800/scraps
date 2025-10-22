#ifndef TOKEN_H
#define TOKEN_H

#include <stddef.h>

typedef enum {
    TK_NONE,
    TK_IDENTIFIER,
    TK_INTEGER,
    TK_CHARACTER,
    TK_STRING
} token_kind_t;

typedef struct {
    token_kind_t kind;
    size_t start;
    size_t length;
} token_t;

typedef struct {
    token_t* data;
    size_t length;
} token_list_t;

void token_list_push(token_list_t* self, token_t token);
void token_list_pop(token_list_t* self);
token_t token_list_at(token_list_t* self, size_t n);

#endif
