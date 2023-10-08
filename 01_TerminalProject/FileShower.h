#ifndef FILESHOWER_H
#define FILESHOWER_H

#include "Vector.h"
#include "FileReader.h"

#include <ncurses.h>

typedef struct FileShower
{
    Vector Lines;

    size_t Height;
    size_t HeightOffset;
    size_t Width;
    size_t WidthOffset;

    WINDOW *Window;
} FileShower;

ssize_t FileShowerInit(FileShower *FS, char *Filename);
ssize_t FileShowerShow(FileShower *FS);
ssize_t FileShowerNextLine(FileShower *FS);
ssize_t FileShowerNextPage(FileShower *FS);
ssize_t FileShowerPrevLine(FileShower *FS);
ssize_t FileShowerPrevPage(FileShower *FS);
ssize_t FileShowerNextColumn(FileShower *FS);
ssize_t FileShowerPrevColumn(FileShower *FS);
ssize_t FileShowerFree(FileShower *FS);

#endif // FILESHOWER_H
