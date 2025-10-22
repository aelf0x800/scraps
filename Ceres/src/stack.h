#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdint.h>

#define STACK_MAX 32
#define STACK_MIN 0

typedef size_t cell_t;

typedef struct {
    cell_t stack[STACK_MAX];
    uint8_t top;
} stack_t;

void stack_push(stack_t* self, cell_t value);
cell_t stack_pop(stack_t* self);
void stack_swap(stack_t* self);
cell_t stack_top(stack_t* self);

#endif
