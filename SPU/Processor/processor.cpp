#include "processor.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "file.h"
#include "commands.h"
#include "stack.h"
#include "str.h"

Processor ProcCreate()
{
    Processor processor = {0, 0, {}, {}, {}};
    
    processor.bufferSize = 0;

    // fprintf(stderr, "File path %s\n", File);

    processor.buffer = CreateBuffer(&processor.bufferSize, File);

    processor.nStr = StrCount(&processor);

    processor.strs = (char**)calloc((size_t)processor.nStr, sizeof(char*));
    assert(processor.strs != NULL);

    AddPointers(&processor);

    return processor;
}


void AddPointers(Processor* processor)
{
    char *currstring = processor->buffer;
    processor->nComm = 0;

    processor->strs[0] = processor->buffer;

    for (int i = 1; i < processor->nStr; i++)
    {
        currstring = StrChr(currstring, '\n') + 1;

        // printf("%p\n", currstring);

        *(currstring - 1) = '\0';
        processor->strs[i] = currstring;
    }

    assert(processor->strs != NULL);
    sscanf(processor->strs[0], "%d", &(processor->nComm));
}


Spu SpuCreate(Processor* processor)
{
    Spu spu = {{}, {}, 0, {}, {}, {}};

    StackInit(&(spu.stack));

    StackInit(&(spu.retAdrs));

    int labels[nLabels] = {};

    for (size_t i = 0; i < nLabels; i++)
    {
        labels[i] = -1;
    }

    spu.labels = labels;

    spu.code = (int*)calloc((size_t)(processor->nComm), sizeof(int));
    assert(spu.code != NULL);

    spu.regs = (int*)calloc(nRegs, sizeof(int));
    assert(spu.regs != NULL);

    spu.ram = (int*)calloc(ramSize, sizeof(int));
    assert(spu.ram != NULL);

    // fprintf(stderr, "spu.regs address - %p\n", spu.regs);

    AddLabels(processor, &spu);

    // for (size_t i = 0; i < 10; i++)
    // {
    //     fprintf(stderr, " label[%d] = %d\n", i, spu.labels[i]);
    // }

    AddCode(processor, &spu);

    spu.ic = 0;

    return spu;
}


void ProcDestroy(Processor* processor)
{
    free(processor->strs);
    free(processor->buffer);
}


void SpuDestroy(Spu* spu)
{
    StackDestroy(&(spu->stack));
    StackDestroy(&(spu->retAdrs));
    free(spu->code);
    free(spu->regs);
    free(spu->ram);
    spu->ic = -1;
}