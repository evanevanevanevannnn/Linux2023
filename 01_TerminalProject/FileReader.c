#include "FileReader.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

enum 
{
    BUFF_SIZE = (1 << 15)
};

ssize_t FileReaderInit(FileReader *FR, char *Filename)
{
    FR->fd = open(Filename, O_RDONLY);
    return (FR->fd == -1 ? -1 : 0);
}

ssize_t FileReaderReadByLines(FileReader *FR, Vector *Lines)
{
    ssize_t RC = VectorInit(Lines, sizeof(char *));
    if (RC == -1)
    {
        return -1;
    }

    char *Buff = (void *)malloc(BUFF_SIZE);
    if (Buff == NULL)
    {
        return -1;
    }

    char *CurrentString = NULL;
    int CurrentStringSize = 0;

    int Count, StrStart;
    while ((Count = read(FR->fd, Buff, BUFF_SIZE)) != -1)
    {
        if (Count == 0)
        {
            break;
        }

        StrStart = 0;
        for (size_t i = 0; i < Count; ++i)
        {
            if (Buff[i] == '\n')
            {
                if (CurrentString != NULL)
                {
                    char *NewCurrentString = realloc(CurrentString, CurrentStringSize + i - StrStart + 1);
                    CurrentString = NewCurrentString;

                    memmove(CurrentString + CurrentStringSize, Buff + StrStart, i - StrStart);
                    CurrentString[CurrentStringSize + i - StrStart] = '\0';
                } 
                else
                {
                    CurrentString = (char *)malloc(i - StrStart + 1);
                    
                    memmove(CurrentString, Buff + StrStart, i - StrStart);
                    CurrentString[i - StrStart] = '\0';
                }

                VectorPushBack(Lines, &CurrentString);
                CurrentString = NULL;
                CurrentStringSize = 0;
                StrStart = i + 1;
            }
        }

        if (StrStart != Count)
        {
            CurrentString = (char *)malloc(Count - StrStart);
            
            memmove(CurrentString, Buff + StrStart, Count - StrStart);
            CurrentStringSize = Count - StrStart;
        }
    }

    if (CurrentString != NULL)
    {
        char *NewCurrentString = (char *)realloc(CurrentString, CurrentStringSize + 1);
        CurrentString = NewCurrentString;

        VectorPushBack(Lines, &CurrentString);
    }
}

ssize_t FileReaderFree(FileReader *FR)
{
    close(FR->fd);
    return 0;
}
