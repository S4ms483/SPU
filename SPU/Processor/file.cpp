#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


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

    size_t size = (size_t)statistics.st_size;
    char* buffer = (char*)calloc((size_t)size + 1, sizeof(char));

    *bufferSize = fread(buffer, sizeof(char), size, fp);

    fclose(fp);

    return buffer;
}