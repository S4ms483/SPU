#include "str.h"

#include <stdio.h>
#include <assert.h>

#include "processor.h"

int StrCount(Processor* processor)
{
    assert(processor->buffer != NULL);

    int amount = 1;

    for (size_t i = 0; i < processor->bufferSize; i++)
    {
        assert(processor->buffer[i] != '\0');

        if (processor->buffer[i] == '\n')
        {
            amount++;
        }
    }

    return amount;
}


int StrCmp(const char* str1, const char* str2)
{
    int i = 0;

    while ((str1[i] == str2[i] && str1[i] != '\0'))
    {
        i++;
    }

    if (str1[i] == '\0' && str2[i] == '\0')
    {
        return 0;
    }

    return (str1[i] > str2[i]) ? 1 : -1;
}


char* StrChr(char* str, int c)
{

    while (*str != '\0')
    {
        if (*str == c) 
        {
            return str;
        }
        ++str;
    }

    if (c == '\0')          
    {
        return str;
    }

    return NULL;
}