#include "verify.h"

#include <stdio.h>


void TrueVerify(stack_t* stk, const char* file, int line)
{
    StackCheck(stk, file, line);
    
    DataCheck(stk, file, line);
    
    CapacityCheck(stk, file, line);

    SizeCheck(stk, file, line);

    CanaryCheck(stk, file, line);
}


void StackCheck(stack_t* stk, const char* file, int line)
{
    if (stk == NULL)
    {
        stk->err = StackPointerNull;
        StackDump(stk, file, line);
    }
}


void DataCheck(stack_t* stk, const char* file, int line)
{
    if (stk->processor == NULL)
    {
        stk->err = DataPointerNull;
        StackDump(stk, file, line);
    }
}


void CapacityCheck(stack_t* stk, const char* file, int line)
{
    if (stk->capacity == 0)
    {
        stk->err = ZeroCapacity;
        StackDump(stk, file, line);
    }
}


void SizeCheck(stack_t* stk, const char* file, int line)
{
    if (stk->size == 0)
    {
        stk->err = ZeroSize;
        StackDump(stk, file, line);
    }
}


void CanaryCheck(stack_t* stk, const char* file, int line)
{
    if (stk->processor[0] != 0xDEADBABE)
    {
        stk->err = LeftCanaryChanged;
        StackDump(stk, file, line);
    }

    if (stk->processor[stk->capacity - 1] != 0xDEADBABE)
    {
        stk->err = RightCanaryChanged;
        StackDump(stk, file, line);
    }
}


void StackDump(stack_t* stk, const char* file, int line)
{
    printf("In %s:%d\n", file, line);

    switch (stk->err)
    {
        case NoError:
            printf("No error\n");
            break;
        case StackPointerNull:
            printf("Referring to a NULL-pointer in stack\n");
            break;
        case DataPointerNull:
            printf("Referring to a NULL-pointer in processor\n");
            break;
        case ZeroSize:
            printf("Zero stack size\n");
            break;
        case ZeroCapacity:
            printf("Zero stack capacity\n");
            break;
        case LeftCanaryChanged:
            printf("Left canary has been changed\n");
            break;
        case RightCanaryChanged:
            printf("Right canary has been changed\n");
            break;
    }

    printf("Stack %p\n", stk);
    printf("Size = %lu\n", stk->size);
    printf("Capacity = %lu\n", stk->capacity);
    printf("Processor %p\n", stk->processor);

    if ((stk->processor != NULL) && (stk != NULL))
    {
        for (size_t i = 0; i < (stk->capacity); i++)
        {
            printf("processor[%lu] = %10d\n", i, stk->processor[i]);
        }
    }

    printf("\n\n");
}


void SpuDump(Spu* spu, Processor* processor, const char* file, int line)
{
    printf("In %s:%d\n", file, line);

    switch (spu->err)
    {
        case NoError:
            printf("No error\n");
            break;
        case UndefinedCommand:
            printf("Attempting to perform an undefined command\n");
            break;
        case WrongRamAddress:
            printf("Referring to an incorrect ram address\n");
            break;
    }

    printf("Spu %p\n", spu);
    printf("Code array address = %p\n", spu->code);
    printf("Amount of commands = %lu\n", processor->nComm);
    printf("Current number = %d\n", spu->ic);

    if ((spu->code != NULL) && (spu != NULL))
    {
        for (size_t i = 0; i < (processor->nComm); i++)
        {
            printf("code[%lu] = %10d\n", i, spu->code[i]);
        }
    }

    printf("Regs array %p\n", spu->regs);

    if ((spu->regs != NULL) && (spu != NULL))
    {
        for (size_t i = 0; i < 10; i++)
        {
            printf("regs[%lu] = %10d\n", i, spu->regs[i]);
        }
    }

    printf("Ram array %p\n", spu->ram);

    if ((spu->ram != NULL) && (spu != NULL))
    {
        for (size_t i = 0; i < 100; i++)
        {
            printf("ram[%lu] = %10d\n", i, spu->ram[i]);
        }
    }

    printf("\n\n");
}