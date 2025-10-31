#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#include <stdio.h>

#include "verify.h"


static const char* File = "../Assembler/bcode.txt";
const size_t nRegs = 10;
const size_t nLabels = 10;
const size_t ramSize = 100;


Processor ProcCreate();
void AddPointers(Processor* processor);
Spu SpuCreate(Processor* processor);
void ProcDestroy(Processor* processor);
void SpuDestroy(Spu* spu);

#endif // PROCESSOR_H_