#include "Vector.h"
#include <stdlib.h>
#include <string.h>

enum
{
    VECTOR_INIT_SIZE = 16
};

ssize_t VectorInit(Vector *v, size_t DataSize)
{
    v->Data = (void *)malloc(VECTOR_INIT_SIZE * DataSize);
    v->DataSize = DataSize;
    v->MemSize = VECTOR_INIT_SIZE;
    v->Size = 0;

    return (v->Data == NULL ? -1 : 0);
}

ssize_t VectorPushBack(Vector *v, void *Data)
{
    if (v->Size == v->MemSize)
    {
        void *NewData = (void *)realloc(v->Data, v->MemSize * 2 * v->DataSize);
        if (NewData == NULL)
        {
            return -1;
        }

        v->MemSize *= 2;
        v->Data = NewData;
    }

    memmove(v->Data + v->Size * v->DataSize, Data, v->DataSize);
    v->Size++;
    return 0;
}

ssize_t VectorPopBack(Vector *v, void *Data)
{
    if (v->Size == 0)
    {
        return -1;
    }

    if (Data != NULL)
    {
        memmove(Data, v->Data + v->Size * v->DataSize, v->DataSize);
    }

    v->Size--;
    if (v->Size * 2 < v->MemSize)
    {
        void *NewData = realloc(v->Data, v->Size * 2 * v->DataSize);
        if (NewData == NULL)
        {
            v->Size++;
            return -1;
        }

        v->Data = NewData;
        v->MemSize = v->Size * 2;
        return 0;
    }
}

ssize_t VectorGet(Vector *v, size_t Ind, void *Data)
{
    if (Ind >= v->Size)
    {
        return -1;
    }

    memmove(Data, v->Data + Ind * v->DataSize, v->DataSize);
    return 0;
}

ssize_t VectorFree(Vector *v, void (*Destructor)(void *))
{
    if (Destructor != NULL)
    {
        for (size_t i = 0; i < v->Size; ++i)
        {
            Destructor(v->Data + i * v->DataSize);
        }
    }

    free(v->Data);
    return 0;
}
