#ifndef FILEREADER_H
#define FILEREADER_H

#include "Vector.h"

typedef struct FileReader
{
    int fd;
} FileReader;

ssize_t FileReaderInit(FileReader *FR, char *Filename);
ssize_t FileReaderReadByLines(FileReader *FR, Vector *Lines);
ssize_t FileReaderFree(FileReader *FR);

#endif // FILEREADER_H
