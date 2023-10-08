#include "FileShower.h"

#include <string.h>
#include <stdlib.h>

enum
{
    WINDOW_OFFSET = 1
};

static void StringDestructor(void *String)
{
    free(*(char **)String);
}

ssize_t FileShowerInit(FileShower *FS, char *Filename)
{
    FileReader FR;
    ssize_t RC;

    RC = FileReaderInit(&FR, Filename);
    if (RC == -1)
    {
        return -1;
    }

    RC = FileReaderReadByLines(&FR, &FS->Lines);
    if (RC == -1)
    {
        FileReaderFree(&FR);
        return -1;
    }

    FileReaderFree(&FR);

    initscr();
    noecho();
    cbreak();
    printw("Filename: %s", Filename);
    refresh();

    FS->Width = COLS - (WINDOW_OFFSET + 1) * 2;
    FS->WidthOffset = 0;
    FS->Height = LINES - (WINDOW_OFFSET + 1) * 2;
    FS->HeightOffset = 0;

    FS->Window = newwin(LINES - WINDOW_OFFSET * 2, COLS - WINDOW_OFFSET * 2, WINDOW_OFFSET, WINDOW_OFFSET);
    if (FS->Window == NULL)
    {
        VectorFree(&FS->Lines, StringDestructor);
        endwin();
        return -1;
    }

    keypad(FS->Window, TRUE);
    scrollok(FS->Window, TRUE);
}

ssize_t FileShowerShow(FileShower *FS)
{
    size_t MaxLineLen = 1;
    size_t MaxLine = FS->Lines.Size;
    while (MaxLine > 0)
    {
        MaxLineLen++;
        MaxLine /= 10;
    }

    wmove(FS->Window, 1, 0);

    for (size_t LineNo = FS->HeightOffset; LineNo < FS->HeightOffset + FS->Height; ++LineNo)
    {
        if (LineNo >= FS->Lines.Size)
        {
            wprintw(FS->Window, "\n");
            continue;
        }

        char *Line;
        VectorGet(&FS->Lines, LineNo, &Line);

        wprintw(FS->Window, " %*d: ", MaxLineLen, LineNo);

        size_t LineLen = strlen(Line);
        for (size_t ColNo = FS->WidthOffset; ColNo < FS->WidthOffset + FS->Width; ++ColNo)
        {
            if (ColNo >= LineLen)
            {
                break;
            }

            wprintw(FS->Window, "%c", Line[ColNo]);
        }

        wprintw(FS->Window, "\n");
    }

    box(FS->Window, 0, 0);
    wmove(FS->Window, FS->Height + 2, 0);
    wrefresh(FS->Window);
    return 0;
}

ssize_t FileShowerNextLine(FileShower *FS)
{
    if (FS->HeightOffset + 1 < FS->Lines.Size)
    {
        FS->HeightOffset++;
    }

    return 0;
}

ssize_t FileShowerNextPage(FileShower *FS)
{
    if (FS->HeightOffset + FS->Height < FS->Lines.Size)
    {
        FS->HeightOffset += FS->Height;
    }
    else
    {
        FS->HeightOffset = FS->Lines.Size - 1;
    }

    return 0;
}

ssize_t FileShowerPrevLine(FileShower *FS)
{
    if (FS->HeightOffset > 0)
    {
        FS->HeightOffset--;
    }

    return 0;
}

ssize_t FileShowerPrevPage(FileShower *FS)
{
    if (FS->HeightOffset - FS->Height >= 0)
    {
        FS->HeightOffset -= FS->Height;
    }
    else
    {
        FS->HeightOffset = 0;
    }

    return 0;
}

ssize_t FileShowerNextColumn(FileShower *FS)
{
    size_t MaxLineLen = 0;
    for (size_t LineNo = FS->HeightOffset; LineNo < FS->HeightOffset + FS->Height; ++LineNo)
    {
        if (LineNo >= FS->Lines.Size)
        {
            break;
        }

        char *Line;
        VectorGet(&FS->Lines, LineNo, &Line);

        MaxLineLen = (MaxLineLen > strlen(Line) ? MaxLineLen : strlen(Line));
    }

    if (FS->WidthOffset < MaxLineLen - 1)
    {
        FS->WidthOffset++;
    }

    return 0;
}

ssize_t FileShowerPrevColumn(FileShower *FS)
{
    if (FS->WidthOffset > 0)
    {
        FS->WidthOffset--;
    }

    return 0;
}

ssize_t FileShowerFree(FileShower *FS)
{
    VectorFree(&FS->Lines, StringDestructor);
    endwin();
}

