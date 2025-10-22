#include "lexer.h"
#include <stdio.h>

int main(int argc, const char** argv) {
    (void)argc;
    lexer_t result = lexer(argv[1]);
    for (size_t i = 0; i < result.tokens.length; i++) {
        token_t token = token_list_at(&result.tokens, i);
        printf("{ Kind = %d, Start = %ld, Length = %ld } ", token.kind, token.start, token.length);
        for (size_t j = token.start; j < token.start + token.length; j++)
            printf("%c", result.source.data[j]);
        printf("\n");
    }
    return 0;
}
