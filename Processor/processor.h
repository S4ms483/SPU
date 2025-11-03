#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include <stdio.h>


enum StackErr
{
    NoError,
    StackPointerNull,
    DataPointerNull,
    ZeroSize,
    ZeroCapacity,
    LeftCanaryChanged,
    RightCanaryChanged,
};

typedef enum StackErr stackErr_t;

struct stack_t
{
    int* processor;
    size_t size;
    size_t capacity;
    stackErr_t err;
};


enum SpuErr
{
    NoSpuError,
    UndefinedCommand,
    WrongRamAddress,
};


typedef enum SpuErr spuErr_t;


struct Processor
{
    size_t bufferSize;
    char* buffer;
    
    int nStr;
    char** strs;

    int nComm;
};


struct Spu
{
    stack_t stack;
    int* code;

    int ic;

    int* regs;
    stack_t retAdrs;

    int* ram;

    spuErr_t err;
};


static const char* File = "../Assembler/bcode.txt";
const size_t nRegs = 10;
const size_t nLabels = 10;
const size_t ramSize = 100;


Processor ProcCreate();
void AddPointers(Processor* processor);
Spu SpuCreate(Processor* processor);
void ProcDestroy(Processor* processor);
void SpuDestroy(Spu* spu);

#endif // PROCESSOR_H_