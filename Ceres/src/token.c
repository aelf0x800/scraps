#include "error.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>

void token_list_push(token_list_t* self, token_t token) {
    self->data = realloc(self->data, (self->length + 1) * sizeof(token_t));
    if (self->data == NULL)
        error("Failed to grow the token list");

    self->data[self->length++] = token;
}

void token_list_pop(token_list_t* self) {
    if (self->length == 0)
        error("Trying to pop an empty token list");
    
    self->data = realloc(self->data, --self->length * sizeof(token_t));
    if (self->data == NULL)
        error("Failed to shrink the token list");
}

token_t token_list_at(token_list_t* self, size_t n) {
    if (n >= self->length)
        error("Token list access out of bounds : %ld", n);

    return self->data[n];
}
