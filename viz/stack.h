#ifndef STACK_H
#define STACK_H

typedef struct {
    float *arr;
    int len;
} Stack;

int stack_init(Stack *stack, float cap);
void stack_push(Stack *stack, float val);

#endif