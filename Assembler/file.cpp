#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "commands.h"


char* CreateBuffer(size_t* bufferSize, const char* file)
{
    assert(bufferSize != NULL);

    FILE* fp = fopen(file, "r");
    assert(fp != NULL);

    int descriptor = fileno(fp);
    assert(descriptor != -1);

    struct stat statistics;
    fstat(descriptor, &statistics);
    assert(statistics.st_size != -1);

    //size_t size = (size_t)statistics.st_size;// !!!
    size_t size = (size_t)statistics.st_size / sizeof(char);
    char* buffer = (char*)calloc((size_t)size + 1, sizeof(char));

    *bufferSize = fread(buffer, sizeof(char), size, fp);

    fclose(fp);

    return buffer;
}


void FileOutput(int* commands, size_t nStr, size_t numCom)
{
    assert(commands != NULL);

    const char* bcode = "bcode.txt";

    FILE* bcodefile = fopen(bcode, "w");
    assert(bcodefile != NULL);

    fprintf(bcodefile, "%lu\n", numCom);

    for (size_t i = 0; i < numCom; i++)
    {
        switch (commands[i])
        {
            case (Push):
            case (Pushr):
            case (Popr):
            case (Jb):
            case (Jbe):
            case (Ja):
            case (Jae):
            case (Je):
            case (Jne):
            case (Jmp):
            case (Call):
            {
                fprintf(bcodefile, "%d %d\n", commands[i], commands[i+1]);
                i++;
                break;
            }

            default:
            {
                fprintf(bcodefile, "%d\n", commands[i]);
            }
        }

    }

    fclose(bcodefile);
}