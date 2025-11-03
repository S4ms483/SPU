#include "verify.h"

#include <stdio.h>


void AsmDump(Assembler* assm, const char* file, int line)
{
    printf("Error in %s:%d\n", file, line);

    switch (assm->err)
    {
        case NoError:
            printf("No error\n");
            break;
        case UnknownCommand:
            printf("Referring to an unknown command in byte-code\n");
            break;
        case NoArgument:
            printf("No argument given to a function that requires one\n");
            break;
        case UnknownLabel:
            printf("Referring to an undefined label\n");
            break;
        case LabelRedifinition:
            printf("Attempting to redefine a label\n");
            break;
    }

    printf("Asm address %p\n", assm);

    printf("String array address %p\n", assm->strs);
    printf("Number of strings = %lu\n", assm->nStr);

    if ((assm->strs != NULL) && (assm != NULL))
    {
        for (size_t i = 0; i < assm->nStr; i++)
        {
            printf("assm->nStrs[%lu] = %s\n", i, assm->strs[i]);
        }
    }

    printf("Commands array address %p\n", assm->commands);
    printf("Number of commands = %lu\n", assm->nComm);

    if ((assm->commands != NULL) && (assm != NULL))
    {
        for (size_t i = 0; i < assm->nComm; i++)
        {
            printf("assm->commands[%lu] = %10d\n", i, assm->commands[i]);
        }
    }
}