#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <assert.h>

#include "file.h"
#include "processor.h"
#include "commands.h"

int main()
{
    Processor processor = ProcCreate();

    Spu spu = SpuCreate(&processor);

    // for (int i = 0; i < processor.nComm; i++)
    // {
    //     printf("%d\n", spu.code[i]);
    // }

    PerformCode(&spu, &processor);

    // StackDump(&spu.stack, __FILE__, __LINE__);

    ProcDestroy(&processor);

    SpuDestroy(&spu);
}