#ifndef STACK_H
#define STACK_H

#include <malloc.h>
#include <stdbool.h>
#include <string.h>

#include "types.h"


typedef struct {
    void *items;

    u64 size;
    u64 copacity;

    u32 itemSize;
} Stack;


Stack StackNew(u32 itemSize);
void StackDestroy(Stack *stack);

void StackReserve(Stack *stack, u32 itemsCount);

bool StackPush(Stack *stack, void *item);
void* StackPop(Stack *stack, u64 id);


#endif