#ifndef STR_H_
#define STR_H_

#include <stdio.h>

#include "assembler.h"

int StrCount(Assembler* assm);
int StrCmp(const char* str1, const char* str2);
char* StrChr(char* str, int c);
bool IsLabel(const char* str);
bool IsEmpty(const char* str);

#endif //STR_H_