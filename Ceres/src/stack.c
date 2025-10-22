#include "stack.h"

void stack_push(stack_t* self, cell_t value) {
    if (self->top == STACK_MAX)
        return;
    
    self->stack[self->top++] = value;
}

cell_t stack_pop(stack_t* self) {
    if (self->top == STACK_MIN)
        return 0;
        
    return self->stack[--self->top + 1];
}

void stack_swap(stack_t* self) {
    if (self->top < STACK_MIN + 2)
        return;

    cell_t tmp = self->stack[self->top - 1];
    self->stack[self->top - 1] = self->stack[self->top - 2];
    self->stack[self->top - 2] = tmp;
}

cell_t stack_top(stack_t* self) {
    if (self->top == STACK_MIN)
        return 0;

    return self->stack[self->top - 1];
}
