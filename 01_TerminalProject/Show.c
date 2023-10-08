#include "FileShower.h"

#include <stdio.h>

int main(int Argc, char *Argv[])
{
    if (Argc < 2)
    {
        printf("No input file specified\n");
        return -1;
    }

    FileShower FS;
    ssize_t RC;

    RC = FileShowerInit(&FS, Argv[1]);
    if (RC == -1)
    {
        printf("Specified file cannot be read\n");
        return -1;
    }

    RC = FileShowerShow(&FS);
    if (RC == -1)
    {
        printf("Specified file cannot be shown\n");
        FileShowerFree(&FS);
        return -1;
    }

    int c;
    while ((c = wgetch(FS.Window)) != 27)
    {
        switch (c)
        {
            case ' ':
            case KEY_DOWN:
                FileShowerNextLine(&FS);
                break;

            case KEY_NPAGE:
                FileShowerNextPage(&FS);
                break;

            case KEY_UP:
                FileShowerPrevLine(&FS);
                break;

            case KEY_PPAGE:
                FileShowerPrevPage(&FS);
                break;

            case KEY_RIGHT:
                FileShowerNextColumn(&FS);
                break;

            case KEY_LEFT:
                FileShowerPrevColumn(&FS);
                break;
        }

        RC = FileShowerShow(&FS);
        if (RC == -1)
        {
            printf("Specified file cannot be shown\n");
            break;
        }
    }

    FileShowerFree(&FS);
    return 0;
}
