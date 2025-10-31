#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>

#include "verify.h"

void StackInit(stack_t* stk);

void StackPush(stack_t* stk, int val);
void InitStackPart(stack_t* stk);
void StackPop(stack_t* stk);

void StackAdd(stack_t* stk);
void StackSub(stack_t* stk);
void StackMul(stack_t* stk);
void StackDiv(stack_t* stk);

void StackSqrt(stack_t* stk);

int StackVariable(stack_t* stk);

void StackPushr(stack_t* stk, int* regs, int num);
void StackPopr(stack_t* stk, int* regs, int num);

void StackDestroy(stack_t* stk);

#endif // STACK_H_