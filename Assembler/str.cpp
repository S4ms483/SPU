#include "str.h"

#include <stdio.h>
#include <assert.h>

#include "assembler.h"

int StrCount(Assembler* assm)
{
    assert(assm->buffer != NULL);

    int amount = 1;

    for (size_t i = 0; i < assm->bufferSize; i++)
    {
        assert(assm->buffer[i] != '\0');

        if (assm->buffer[i] == '\n')
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


bool IsLabel(const char* str)
{
    assert(str != NULL);

    if (str[0] == ':')
    {
        return true;
    }
    
    int i = 1;
    bool flag = 0;
    while (str[i] != '\0')
    {
        if (str[i++] != ' ') 
        {
            flag = false;
        } 
    }
    
    // fprintf(stderr, "Current string is - %s\n", str);
    return (flag);
}


bool IsEmpty(const char* str)
{
    assert(str != NULL);
    
    bool flag = false;
    if (str[0] == 0)
    {
        return true;
    }

    return false;
}