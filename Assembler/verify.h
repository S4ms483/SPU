#ifndef VERIFY_H_
#define VERIFY_H_

#include <stdio.h>

#include "assembler.h"

void AsmDump(Assembler* assm, const char* file, int line);

#define AsmVerify(stk) TrueAsmVerify(stk, __FILE__, __LINE__) 


#endif // VERIFY_H_