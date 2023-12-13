#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <libintl.h>
#include <locale.h>
#define _(STRING) gettext(STRING)

enum
{
    BUFF_SIZE = 256
};

int main(int argc, char ** argv)
{
    setlocale (LC_ALL, "");
    bindtextdomain ("main", ".");
    textdomain ("main");

    int left = 0;
    int right = 100;

    printf(_("Pick a random number between a 1 and a 100\n"));
    
    char buff[BUFF_SIZE];
    while (right - left > 1)
    {
        int middle = (left + right) / 2;

        printf(_("Is your number larger than %d? (yes/no)\n"), middle);
        scanf("%s", buff);

        if (!strcmp(buff, _("yes")))
            left = middle;
        else if (!strcmp(buff, _("no")))
            right = middle;
        else 
            printf(_("Please, enter yes or no\n"));
    }

    printf(_("You've picked number %d!\n"), right);

    return 0;
}