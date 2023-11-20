#include "stdlib.h"
#include "stdio.h"
#include <errno.h>
#include "string.h"
#include <unistd.h>
#include <fcntl.h>

extern int errno;

enum
{
    READ_SIZE = 100
};

void PrintError()
{
    int errnum = errno;
    fprintf(stderr, "Value of errno: %d\n", errno);
    perror("Error printed by perror");
    fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
}

int main(int argc, char** argv)
{
    int inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1)
    {
        PrintError();
        return 0;
    }

    int outputFd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0666);
    if (outputFd == -1)
    {
        PrintError();
        close(inputFd);
        return 0;
    }

    int read_bytes = 0;
    char read_buffer[READ_SIZE];

    do {
        read_bytes = read(inputFd, read_buffer, READ_SIZE);
        if (read_bytes  == -1)
        {
            PrintError();
            close(inputFd);
            unlink(argv[2]);
            return 0;
        }

        int write_bytes = write(outputFd, read_buffer, read_bytes);
        if (write_bytes != read_bytes)
        {
            PrintError();
            close(inputFd);
            unlink(argv[2]);
            return 0;
        }
    } while (read_bytes == READ_SIZE);

    close(inputFd);
    close(outputFd);

    unlink(argv[1]);
    return 0;
}