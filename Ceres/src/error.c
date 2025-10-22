#include "error.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void error(const char* format, ...) {
    fprintf(stderr, "error: ");
    
    va_list args = {0};
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    fprintf(stderr, "\n");
    
    exit(1);
}
