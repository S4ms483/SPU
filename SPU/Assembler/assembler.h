#ifndef ASSEMBLER_H_
#define ASSEMBLER_H_

#include <stdio.h>

#include "verify.h"

const size_t nLabels = 10;

Assembler AssemblerCreate();
void AddPointers(Assembler* assm);
void AssemblerDestroy(Assembler* assm);

#endif // ASSEMBLER_H_