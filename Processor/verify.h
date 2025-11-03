#ifndef VERIFY_H_
#define VERIFY_H_

#include <stdio.h>

#include "processor.h"

void TrueVerify(stack_t* stk, const char* file, int line);
void StackCheck(stack_t* stk, const char* file, int line);
void DataCheck(stack_t* stk, const char* file, int line);
void CapacityCheck(stack_t* stk, const char* file, int line);
void SizeCheck(stack_t* stk, const char* file, int line);
void CanaryCheck(stack_t* stk, const char* file, int line);
void StackDump(stack_t* stk, const char* file, int line);
void SpuDump(Spu* spu, Processor* processor, const char* file, int line);

#define StackVerify(stk) TrueVerify(stk, __FILE__, __LINE__) 


#endif // VERIFY_H_