#ifndef VECTOR_H
#define VECTOR_H

#include <sys/types.h>

typedef struct Vector
{
    void *Data;
    size_t DataSize;
    size_t MemSize;
    size_t Size;
} Vector;

ssize_t VectorInit(Vector *v, size_t DataSize);
ssize_t VectorPushBack(Vector *v, void *Data);
ssize_t VectorPopBack(Vector *v, void *Data);
ssize_t VectorGet(Vector *v, size_t Ind, void *Data);
ssize_t VectorFree(Vector *v, void (*Destructor)(void *));

#endif // VECTOR_H
