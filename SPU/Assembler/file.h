#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>

char* CreateBuffer(size_t* bufferSize, const char* file);
void FileOutput(int* commands, size_t nStr, size_t nComm);

#endif // FILE_H_