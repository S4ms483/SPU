#include "commands.h"

#include <stdio.h>
#include <assert.h>

#include "assembler.h"
#include "str.h"

const char* Commands[] = {
    "HLT", 
    "PUSH", 
    "POP", 
    "ADD", 
    "SUB", 
    "MUL", 
    "DIV",
    "SQRT", 
    "PUSHR", 
    "POPR", 
    "IN", 
    "OUT",
    "JB", 
    "JBE", 
    "JA", 
    "JAE", 
    "JE", 
    "JNE", 
    "JMP",
    "CALL",
    "RET",
    "PUSHM",
    "POPM",
};

// FIXME как проверить что столько же сколько комманд - verify

void AddCommands(Assembler* assm)
{
    assert(assm != NULL);

    for (size_t i = 0; i < assm->nStr; i++)
    {
        
        char currstring[commandLen] = {0};
        sscanf(assm->strs[i], "%s", currstring);
        
        int command = DefineCommand(currstring);
        
        if (IsLabel(assm->strs[i]))
        {
            command = Label;
        }

        if (command < 0)
        {
            continue;
        }
        assm->commands[assm->nComm++] = command;

        switch (command)
        {
        case Push:
            {
            int arg = 0;
            int amount = sscanf(assm->strs[i], "%*s %d", &arg);
            assert(amount != 0);
            assm->commands[assm->nComm++] = arg;
            break;
            }

        case Pushr:
        case Popr:
            {
            char arg[argLen] = {0};
            int amount = sscanf(assm->strs[i], "%*s %4s", arg);
            assert(amount != 0);
// fprintf(stderr, "Reg num = %d\n", int(arg[1]));

            assm->commands[assm->nComm++] = arg[1] - 'A';
            break;
            }
        case Jb:
        case Jbe:
        case Ja:
        case Jae:
        case Je:
        case Jne:
        case Jmp:
        case Call:
            {
            int arg = 0;
            int amount = sscanf(assm->strs[i], "%*s :%d", &arg);
            assert(amount != 0);
// fprintf(stderr, "arg = %d\n", arg);
            assm->commands[assm->nComm++] = arg;
// fprintf(stderr, "label address is %d\n", assm->labels[arg]);
            break;
            }
        case Pushm:
        case Popm:
            {
            char arg[argLen] = {0};
            int amount = sscanf(assm->strs[i], "%*s [%3s]", arg);
            assert(amount != 0);

            assm->commands[assm->nComm++] = arg[0] - 'A';
            break;
            }
        case Label:
            {
            int arg = 0;
            int amount = sscanf(assm->strs[i], ":%d", &arg);
            assert(amount != 0);
            assm->commands[assm->nComm++] = arg;
            break;
            }
        }
    }
}


int DefineCommand(const char* str)
{
    assert(str != NULL);

    for (int i = 0; i < nComm - 1; i++)
    {
        if (!(StrCmp(str, Commands[i])))
        {
            return i;
        }
    }

    return -1;
}