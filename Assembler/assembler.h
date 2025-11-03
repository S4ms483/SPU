#ifndef ASSEMBLER_H_
#define ASSEMBLER_H_

#include <stdio.h>

enum AsmErr
{
    NoError,
    UnknownCommand,
    NoArgument,
    UnknownLabel,
    LabelRedifinition
};

typedef enum AsmErr asmErr_t;

struct Assembler
{
    size_t bufferSize; 
    char* buffer;
    
    size_t nStr;
    char** strs;
    
    size_t nComm;
    int* commands;

    int* labels;

    asmErr_t err;
};

const size_t nLabels = 10;

Assembler AssemblerCreate();
void AddPointers(Assembler* assm);
void AssemblerDestroy(Assembler* assm);

#endif // ASSEMBLER_H_