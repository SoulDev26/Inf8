#include "../include/stack.h"


Stack StackNew(u32 itemSize)
{
    Stack stack;

    stack.copacity = 0;
    stack.size = 0;
    stack.itemSize = itemSize;
    stack.items = NULL;

    return stack;
}

void StackDestroy(Stack *stack)
{
    if (stack->copacity == 0) return;

    stack->copacity = 0;
    stack->size = 0;
    
    free(stack->items);
    stack->items = NULL;
}

void StackReserve(Stack *stack, u32 itemsCount)
{
    stack->copacity += itemsCount;
    
    void *newItems = malloc(stack->itemSize * stack->copacity);
    memcpy(newItems, stack->items, stack->itemSize * stack->size);
    free(stack->items);

    stack->items = newItems;
}

bool StackPush(Stack *stack, void *item)
{
    if (item == NULL) return true;

    if (stack->size == stack->copacity)
    {
        StackReserve(stack, stack->size * 2);
    }

    memcpy(stack->items + stack->itemSize * stack->size, item, stack->itemSize);
    return false;
}

void* StackPop(Stack *stack, u64 id)
{
    void *item = malloc(stack->itemSize);
    memcpy(item, stack->items + stack->itemSize * --stack->size, stack->itemSize);

    return item;
}