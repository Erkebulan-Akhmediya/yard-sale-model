#include "stack.h"
#include <stdlib.h>

int stack_init(Stack *stack, float cap) {
    stack->arr = calloc(cap, sizeof(float));
    if (stack->arr == NULL)
        return -1;

    stack->len = 0;
    return 0;
}

void stack_push(Stack *stack, float val) {
    stack->arr[stack->len++] = val;
}