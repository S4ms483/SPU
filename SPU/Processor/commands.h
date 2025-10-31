#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <stdio.h>

#include "processor.h"

enum Commands 
{   
    Hlt, 
    Push, 
    Pop, 
    Add, 
    Sub, 
    Mul, 
    Div, 
    Sqrt, 
    Pushr, 
    Popr, 
    In, 
    Out,
    Jb, 
    Jbe, 
    Ja, 
    Jae, 
    Je, 
    Jne, 
    Jmp,
    Call,
    Ret,
    Pushm,
    Popm,
    Label
};

void AddLabels(Processor* processor, Spu* spu);
void AddCode(Processor* processor, Spu* spu);
void PerformCode(Spu* spu, Processor* processor);
void ArifmOperation(stack_t* stk, int command);
bool ComparisonOperations(stack_t* stk, int command);

#endif // COMMANDS_H_