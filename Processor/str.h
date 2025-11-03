#ifndef STR_H_
#define STR_H_

#include <stdio.h>

#include "processor.h"

int StrCount(Processor* processor);
int StrCmp(const char* str1, const char* str2);
char* StrChr(char* str, int c);

#endif //STR_H_