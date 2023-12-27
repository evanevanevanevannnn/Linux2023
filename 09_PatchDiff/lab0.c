#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

static char WallSymb;
static char PassSymb;

typedef struct index_t index_t;

typedef struct MazeData MazeData;
typedef struct MazeData* Maze;

index_t BuildIndex(int i, int j);

void BuildMaze(Maze *maze, int roomsSize);
void FreeMaze(Maze maze);
void FillConnectivity(Maze maze, index_t room);
void SetWall(Maze maze, index_t index, bool IsPassage);
bool AreAllConnected(Maze maze);
bool IsWall(Maze maze, index_t index);
bool IsWallConnectingRooms(Maze maze, index_t index);
bool IsValidWall(Maze maze, index_t i);
void FillMaze(Maze maze);
void PrintMaze(Maze maze);

struct index_t {
    int i;
    int j;
};

struct MazeData {
    bool **maze;
    bool **copy;
    int size;
    int roomsSize;
};

index_t BuildIndex(int i, int j)
{
    index_t res;
    res.i = i;
    res.j = j;
    return res;
}

void BuildMaze(Maze *maze, int roomsSize)
{
    Maze newMaze = malloc(sizeof(MazeData));

    newMaze->roomsSize = roomsSize;
    newMaze->size = roomsSize * 2 + 1;

    newMaze->maze = malloc(newMaze->size * sizeof(bool *));
    newMaze->copy = malloc(newMaze->size * sizeof(bool *));

    for (int i = 0; i < newMaze->size; ++i)
    {
        newMaze->maze[i] = malloc(newMaze->size * sizeof(bool));
        newMaze->copy[i] = malloc(newMaze->size * sizeof(bool));
    }

    for (int i = 0; i < newMaze->size; ++i)
        for (int j = 0; j < newMaze->size; ++j)
        {
            index_t index = BuildIndex(i, j);
            SetWall(newMaze, index, !IsWall(newMaze, index));
        }
    
    *maze = newMaze;
}

void FreeMaze(Maze maze)
{
    for (int i = 0; i < maze->size; ++i)
    {
        free(maze->maze[i]);
        free(maze->copy[i]);
    }

    free(maze->maze);
    free(maze->copy);
    free(maze);
}

void ClearCopy(Maze maze)
{
    for (int i = 0; i < maze->roomsSize; ++i)
        for (int j = 0; j < maze->roomsSize; ++j)
            maze->copy[i * 2 + 1][j * 2 + 1] = false;
}

void FillConnectivity(Maze maze, index_t room)
{
    if (maze->copy[room.i][room.j])
        return;
    
    maze->copy[room.i][room.j] = true;

    for (int i = -1; i < 2; ++i)
    {
        for (int j = -1; j < 2; ++j)
        {
            if (!((i == 0) ^ (j == 0)))
                continue;

            if (!maze->maze[room.i + i][room.j + j])
                continue;

            index_t connectedRoom = BuildIndex(room.i + i * 2, room.j + j * 2);

            if (connectedRoom.i < 0 || connectedRoom.i >= maze->size ||
                connectedRoom.j < 0 || connectedRoom.j >= maze->size)
                continue;
            
            FillConnectivity(maze, connectedRoom);
        }
    }
}

void SetWall(Maze maze, index_t index, bool IsPassage)
{
    maze->maze[index.i][index.j] = IsPassage;
}

bool AreAllConnected(Maze maze)
{
    index_t index = BuildIndex(1, 1);

    ClearCopy(maze);
    FillConnectivity(maze, index);

    for (int i = 0; i < maze->roomsSize; ++i)
        for (int j = 0; j < maze->roomsSize; ++j)
            if (!maze->copy[i * 2 + 1][j * 2 + 1])
                return false;
    
    return true;
}

bool IsWall(Maze maze, index_t index)
{
    if (index.i == 0 || index.i == maze->size - 1 ||
        index.j == 0 || index.j == maze->size - 1)
        return true;

    bool firstIndexIsWall = index.i % 2 == 0;
    bool secondIndexIsWall = index.j % 2 == 0;

    return firstIndexIsWall || secondIndexIsWall;
}

bool IsWallConnectingRooms(Maze maze, index_t index)
{
    if (!IsWall(maze, index))
        return false;
    
    bool firstIndexIsWall = index.i % 2 == 0;
    bool secondIndexIsWall = index.j % 2 == 0;

    return firstIndexIsWall ^ secondIndexIsWall;
}

bool IsValidWall(Maze maze, index_t index)
{
    if (maze->maze[index.i][index.j])
        return false;
    
    index_t firstRoom = index;
    index_t secondRoom = index;

    if (index.i % 2 == 0)
    {
        firstRoom.i = index.i - 1;
        secondRoom.i = index.i + 1;
    }
    else
    {
        firstRoom.j = index.j - 1;
        secondRoom.j = index.j + 1;
    }

    ClearCopy(maze);
    FillConnectivity(maze, firstRoom);
    return !maze->copy[secondRoom.i][secondRoom.j];
}

void CollectValidWalls(Maze maze, index_t **validWalls, int *size)
{
    *size = 0;

    for (int i = 1; i < maze->size - 1; ++i)
        for (int j = 1; j < maze->size - 1; ++j)
        {
            index_t index = BuildIndex(i, j);
            if (IsWallConnectingRooms(maze, index) && IsValidWall(maze, index))
                (*size)++;
            
        }
    
    index_t *res = malloc((*size) * sizeof(index_t));
    *validWalls = res;

    for (int i = 1; i < maze->size - 1; ++i)
        for (int j = 1; j < maze->size - 1; ++j)
        {
            index_t index = BuildIndex(i, j);
            if (IsWallConnectingRooms(maze, index) && IsValidWall(maze, index))
                *(res++) = index;
        }
}

void FillMaze(Maze maze)
{
    while (!AreAllConnected(maze))
    {
        index_t *validWalls;
        int size;

        CollectValidWalls(maze, &validWalls, &size);

        int ind = rand() % size;
        SetWall(maze, validWalls[ind], true);
        free(validWalls);
    }
}

void PrintMaze(Maze maze)
{
    for (int i = 0; i < maze->size; ++i)
    {
        for (int j = 0; j < maze->size; ++j)
            printf("%c", maze->maze[i][j] ? PassSymb : WallSymb);
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    int N;
    int seed;

    if (argc < 1)
        return 0;

    seed = 0;

    PassSymb = '.';
    WallSymb = '#';

    N = 6;

    srand(seed);

    Maze maze;
    
    BuildMaze(&maze, N);
    FillMaze(maze);
    PrintMaze(maze);
    FreeMaze(maze);

    return 0;
}