#include "error.h"
#include "lexer.h"
#include <ctype.h>
#include <stdbool.h>

static token_t lexer_lex_character(lexer_t* self);
static token_t lexer_lex_string(lexer_t* self);
static token_t lexer_lex_literal(lexer_t* self);
static char lexer_get(lexer_t* self, size_t off);
static bool lexer_in_range(lexer_t* self, size_t off);

lexer_t lexer(const char* path) {
    lexer_t self = {
        .source = source_load(path),
        .tokens = {0},
        .idx = 0
    };

    while (lexer_in_range(&self, 0)) {
        // Skip whitespace
        if (isspace(lexer_get(&self, 0))) {
            while (lexer_in_range(&self, 0) && isspace(lexer_get(&self, 0)))
                self.idx++;
            continue;
        }

        switch (lexer_get(&self, 0)) {
        // Skip a comment
        case '#':
            while (lexer_in_range(&self, 0) && lexer_get(&self, 0) != '\n')
                self.idx++;
            break;
        // Tokenise the various literal types
        case '\'': token_list_push(&self.tokens, lexer_lex_character(&self)); break;
        case '"': token_list_push(&self.tokens, lexer_lex_string(&self)); break;
        default: token_list_push(&self.tokens, lexer_lex_literal(&self)); break;
        }
    }

    return self;
}

static token_t lexer_lex_character(lexer_t* self) {
    token_t token = {
        .kind = TK_CHARACTER,
        .start = self->idx + 1,
        .length = 1,
    };

    // Triggered if the character literal in not closed
    if (!lexer_in_range(self, 2) || lexer_get(self, 2) != '\'')
        error("Bad character literal : %ld", self->idx);

    // Advance past the character's closing quote
    self->idx += 3;
    
    return token;
}

static token_t lexer_lex_string(lexer_t* self) {
    token_t token = {
        .kind = TK_STRING,
        .start = ++self->idx,
        .length = 0
    };

    while (lexer_in_range(self, 0) && lexer_get(self, 0) != '"') {
        token.length++;
        self->idx++;
    }

    // Advance past the string's closing double quote
    self->idx++;

    // Triggered if the string literal is not closed
    if (!lexer_in_range(self, 0))
        error("Bad string literal : %ld", self->idx);
    
    return token;
}

static token_t lexer_lex_literal(lexer_t* self) {
    token_t token = {
        .kind = TK_INTEGER,
        .start = self->idx,
        .length = 0
    };
    
    while (
        lexer_in_range(self, 0) &&
        !isspace(lexer_get(self, 0)) &&
        lexer_get(self, 0) != '\'' &&
        lexer_get(self, 0) != '"' &&
        lexer_get(self, 0) != '#'
    ) {
        // Initially we assume that the literal is an integer as it is easier to check if
        // it is not an integer.
        if (!isdigit(lexer_get(self, 0)))
            token.kind = TK_IDENTIFIER;
        
        token.length++;
        self->idx++;
    }
    
    return token;
}

static char lexer_get(lexer_t* self, size_t off) {
    return source_at(&self->source, self->idx + off);
}

static bool lexer_in_range(lexer_t* self, size_t off) {
    return self->idx + off < self->source.length;
}
