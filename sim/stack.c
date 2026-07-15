#include "stack.h"
#include <stdlib.h>

void stack_init(Stack *stack, float *buff) {
    stack->arr = buff;
    stack->len = 0;
}

void stack_push(Stack *stack, float val) {
    stack->arr[stack->len++] = val;
}