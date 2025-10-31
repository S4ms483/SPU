#ifndef VERIFY_H_
#define VERIFY_H_

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

    int* labels;

    int* regs;
    stack_t retAdrs;

    int* ram;

    spuErr_t err;
};

void TrueVerify(stack_t* stk, const char* file, int line);
void StackCheck(stack_t* stk, const char* file, int line);
void DataCheck(stack_t* stk, const char* file, int line);
void CapacityCheck(stack_t* stk, const char* file, int line);
void SizeCheck(stack_t* stk, const char* file, int line);
void CanaryCheck(stack_t* stk, const char* file, int line);
void StackDump(stack_t* stk, const char* file, int line);
void SpuDump(Spu* spu, Processor* processor, const char* file, int line);

#define StackVerify(stk) TrueVerify(stk, __FILE__, __LINE__) 


#endif // VERIFY_H_