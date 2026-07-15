#ifndef STACK_H
#define STACK_H

typedef struct {
    float *arr;
    int len;
} Stack;

void stack_init(Stack *stack, float *buff);
void stack_push(Stack *stack, float val);

#endif