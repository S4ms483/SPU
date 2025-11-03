#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "file.h"
#include "assembler.h"
#include "commands.h"

int main()
{
    Assembler assm = AssemblerCreate();

    //printf("%d\n", assm.nComm);

    // for (size_t i = 0; i < assm.nComm; i++)
    // {
    //     printf("%d\n", assm.commands[i]);
    // }

    FileOutput(assm.commands, assm.nStr, assm.nComm);
    
    AssemblerDestroy(&assm);
}