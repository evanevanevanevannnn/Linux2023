#include "config.h"
#include <ctype.h>
#include <errno.h>
#include <rhash.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef USE_READLINE
#include <readline/history.h>
#endif

enum 
{
    OUTPUT_SIZE = 1024
};

void PrintHelp() {
  fprintf(stderr, "usage: <hash-name> [fileName, \"string]\n");
  fprintf(stderr, "<hash-name> = md5 | sha1 | tth\n");
  fprintf(stderr, "capitalize first hash name symbol if you want to print "
                  "result in base64, otherwise it will be printed in hex\n");
}

bool GetNewLine(char **line)
{
#ifdef USE_READLINE
    return (*line = readline(NULL));
#else
    return getline(line, &len, stdin) != -1;
#endif
}

int main()
{   
    size_t len = 0;
    rhash_library_init();

    char *buff;
    while (GetNewLine(&buff))
    {
        char *hashName = strtok(dubb, " ");
        char *inputStr = strtok(strtok(NULL, " "), "\n");

        if (!inputStr || !hashName)
        {
            printHelp();
            continue;
        }

        int outputFormat = hashName[0] == tolower(hashName[0]) ? RHPR_BASE64 : RHPR_HEX;
        
        for (size_t i = 0; i < strlen(hasName); ++i)
            hashName[i] = tolower(hashName[i]);

        int hash = 0;
        if      (!strcmp(hashName, "md5"))
            hash = RHASH_MD5;
        else if (!strcmp(hashName, "sha1"))
            hash = RHASH_SHA1;
        else if (!strcmp(hashName, "tth"))
            hash = RHASH_TTH;
        else
        {
            fprintf(stderr, "Wrong hash, <hash-name> = md5 | sha1 | tth\n");
            continue;
        }

        bool isFile = true;
        if (inputStr[0] == '\"')
        {
            isFile = false;
            inputStr++;
            inputStr[strlen(inputStr) - 1] = '\0';
        }

        int res;
        unsigned char digest[64];
        if (isFile)
            res = rhash_file(hash, inputStr, digest);
        else
            res = rhash_msg(hash, inputStr, strlen(inputStr), digest);

        if (res < 0)
        {
            fprintf(stderr, "Error while hashing data!\n");
            fprintf(stderr, "%s\n", strerror(errno));
            continue;
        }

        char output[OUTPUT_SIZE];
        rhash_print_bytes(output, digest, rhash_get_digest_size(hash), outputFormat);
        fprintf(stdout, "%s\n", output);

        if (buff)
            free(buff);
    }

  return 0;
}