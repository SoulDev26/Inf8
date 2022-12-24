#ifndef STACK_H
#define STACK_H

#include <malloc.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "types.h"


typedef struct {
    void *items;

    u64 size;
    u64 copacity;

    size_t itemSize;
} Stack;


Stack StackNew(size_t itemSize);
void StackDestroy(Stack *stack);

void StackReserve(Stack *stack, u32 itemsCount);

bool StackPush(Stack *stack, void *item);
bool StackPop(Stack *stack, void *dst);


#endif