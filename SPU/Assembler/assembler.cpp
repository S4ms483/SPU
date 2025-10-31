#include "assembler.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "file.h"
#include "commands.h"
#include "str.h"
//  как написать норм мейкфайл
const char* sourceFile = "code.txt";
const int maxnComm = 2;

Assembler AssemblerCreate()
{
    Assembler assm = {};
// fprintf(stderr, "Size of assm is %lu\n", sizeof(assm));
// fprintf(stderr, "Size of bufferSize is %lu\n", sizeof(assm.bufferSize));
// fprintf(stderr, "Size of nStr is %lu\n", sizeof(assm.nStr));
// fprintf(stderr, "Size of buffer is %lu\n", sizeof(assm.buffer));
// fprintf(stderr, "Size of strs is %lu\n", sizeof(assm.strs));
// fprintf(stderr, "Size of n_Comm is %lu\n", sizeof(assm.nComm));
// fprintf(stderr, "Size of commands is %lu\n", sizeof(assm.commands));
// fprintf(stderr, "Size of labels is %lu\n", sizeof(assm.labels));
// fprintf(stderr, "Size of elemements is %lu\n", 
//         sizeof(size_t) + sizeof(int) + sizeof(char*) + sizeof(char**) + sizeof(int) + 2*sizeof(int*));
// fprintf(stderr, "Assembler strs are: buffer %p, strs %p, commands %p, labels %p\n",
//         assm.buffer, assm.strs, assm.commands, assm.labels);
    
    assm.bufferSize = 0;

    assm.buffer = CreateBuffer(&assm.bufferSize, sourceFile);

    assm.nStr = StrCount(&assm);

    assm.strs = (char**)calloc(assm.nStr, sizeof(char*));
    assert(assm.strs != NULL);

    assm.commands = (int*)calloc(assm.nStr * maxnComm, sizeof(int));
    assert(assm.commands != NULL);

    AddPointers(&assm);

// fprintf(stderr, "Currr string: %d\n", assm.strs[10][0]);
    
    AddCommands(&assm);

    return assm;
}


void AddPointers(Assembler* assm)
{
    assert(assm != NULL);

    char *currstring = assm->buffer;
    assm->strs[0] = assm->buffer;

    for (size_t i = 1; i < assm->nStr; i++)
    {
        currstring = StrChr(currstring, '\n') + 1;
        *(currstring - 1) = '\0';

        if (IsEmpty(currstring) || (int)currstring[0] ==0)
        {
            fprintf(stderr, "Empty string is %s num is %lu\n", currstring, i);
            continue;
        }

        assm->strs[i] = currstring;
    }
}


void AssemblerDestroy(Assembler* assm)
{
    assert(assm != NULL);

    free(assm->strs);
    free(assm->buffer);
    free(assm->commands);
}