#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "verify.h"

void StackInit(stack_t* stk)
{
    if (stk == NULL)
        stk->err = StackPointerNull;

    stk->capacity = 3;
    stk->processor = (int *) calloc(stk->capacity, sizeof(int));
    stk->processor[0] = 0xDEADBABE;
    stk->processor[stk->capacity - 1] = 0xDEADBABE;
    stk->size = 0;
}


void StackPush(stack_t* stk, int val)
{
    stk->size++;
    // fprintf(stderr, "stack size = %d\n", stk->size);

    StackVerify(stk); 

    if (stk->size == (stk->capacity - 1))
    {
        stk->processor[stk->size] = 0;
        stk->capacity = (stk->capacity-2) * 2 + 2;

        void* pointer = realloc(stk->processor, stk->capacity * sizeof(int));
        assert(pointer != NULL);

        stk->processor = (int*)pointer;
        
        InitStackPart(stk);

        stk->processor[stk->capacity - 1] = 0xDEADBABE;
    }

    stk->processor [stk->size] = val;

    StackVerify(stk);

    // StackDump(stk, __FILE__, __LINE__);
}


void InitStackPart(stack_t* stk)
{
    for (size_t i = stk->size; i < (stk->capacity); i++)
    {
        stk->processor[i] = 0;
    }
}


void StackPop(stack_t* stk)
{
    StackVerify(stk);

    stk->processor[stk->size--] = 0;

    StackVerify(stk);

    // StackDump(stk, __FILE__, __LINE__);
}


void StackAdd(stack_t* stk)
{
    StackVerify(stk);

    int b = StackVariable(stk);
    int a = StackVariable(stk);

    StackPush(stk, a + b);

    StackVerify(stk);
}


void StackSub(stack_t* stk)
{
    StackVerify(stk);

    int b = StackVariable(stk);
    int a = StackVariable(stk);

    StackPush(stk, a - b);

    StackVerify(stk);
}


void StackMul(stack_t* stk)
{
    StackVerify(stk);

    int b = StackVariable(stk);
    int a = StackVariable(stk);

    StackPush(stk, a * b);

    StackVerify(stk);
}


void StackDiv(stack_t* stk)
{
    StackVerify(stk);

    int b = StackVariable(stk);
    int a = StackVariable(stk);

    StackPush(stk, a / b);

    StackVerify(stk);
}


void StackSqrt(stack_t* stk)
{
    StackVerify(stk);

    int a = StackVariable(stk);

    StackPush(stk, (int)sqrt(a));

    StackVerify(stk);
}


int StackVariable(stack_t* stk)
{
    int res = stk->processor[stk->size];
    StackPop(stk);
    return res;
}


void StackPushr(stack_t* stk, int* regs, int num)
{
    StackVerify(stk);

    int val = regs[num];

    StackPush(stk, val);

    StackVerify(stk);
}


void StackPopr(stack_t* stk, int* regs, int num)
{
    StackVerify(stk);

    int val = StackVariable(stk);
    regs[num] = val;

    StackVerify(stk);
}


void StackDestroy(stack_t* stk)
{
    free(stk->processor);
    stk->processor = NULL;
    stk->capacity = 0;
}