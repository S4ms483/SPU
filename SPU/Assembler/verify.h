#ifndef VERIFY_H_
#define VERIFY_H_

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

    asmErr_t err;
};

void AsmDump(Assembler* assm, const char* file, int line);

#define AsmVerify(stk) TrueAsmVerify(stk, __FILE__, __LINE__) 


#endif // VERIFY_H_