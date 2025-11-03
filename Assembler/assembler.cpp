#include "assembler.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "file.h"
#include "commands.h"
#include "str.h"

const char* sourceFile = "code.txt";
const int maxnComm = 2;

Assembler AssemblerCreate()
{
    Assembler assm = {};
    
    assm.bufferSize = 0;

    assm.buffer = CreateBuffer(&assm.bufferSize, sourceFile);

    assm.nStr = StrCount(&assm);

    assm.strs = (char**)calloc(assm.nStr, sizeof(char*));
    assert(assm.strs != NULL);

    assm.commands = (int*)calloc(assm.nStr * maxnComm, sizeof(int));
    assert(assm.commands != NULL);

    int labels[nLabels] = {};

    for (size_t i = 0; i < nLabels; i++)
    {
        labels[i] = -1;
    }

    assm.labels = labels;

    AddPointers(&assm);

    AddLabels(&assm);
    
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