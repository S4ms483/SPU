#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <stdio.h>

#include "assembler.h"

enum Commands 
{   
    Hlt, 
    Push, 
    Pop,                            
    Add, 
    Sub, 
    Mul,                      
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
    Popm
};

const int nComm = 24;
const int commandLen = 6;
const size_t argLen = 5;

void AddCommands(Assembler* assm);
void AddLabels(Assembler* assm);
int DefineCommand(const char* str);

#endif // COMMANDS_H_