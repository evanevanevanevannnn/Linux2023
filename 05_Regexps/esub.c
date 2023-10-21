#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MATCH_NO = 1 };

int esub(char *RegexpString, char *Substitution, char *String) {

  regex_t Regexp;
  int RC;

  RC = regcomp(&Regexp, RegexpString, REG_EXTENDED);

  if (RC) {
    goto regerr;
  }

  regmatch_t pm[MATCH_NO];
  RC = regexec(&Regexp, String, MATCH_NO, pm, 0);

  if (RC == REG_NOMATCH) {
    printf("%s\n", String);
    regfree(&Regexp);
    return 0;
  }

  if (RC) {
    goto regerr;
  }

  String[pm[0].rm_so] = '\0';
  printf("%s%s%s\n", String, Substitution, String + pm[0].rm_eo);
  regfree(&Regexp);
  return 0;

regerr:;
  size_t ErrLen = regerror(RC, &Regexp, NULL, 0);
  char *Err = malloc(ErrLen);

  regerror(RC, &Regexp, Err, ErrLen);
  fprintf(stderr, "%s\n", Err);

  regfree(&Regexp);
  free(Err);
  return 1;
}

int main(int argc, char **argv) {

  if ((argc < 2) || (argc < 4 && strcmp(argv[1], "--help"))) {
    fprintf(stderr, "Invalid number of arguments, use --help");
    return 0;
  }

  if (!strcmp(argv[1], "--help")) {
    printf("--help: prints this message\n\n"
           "<Regexp> <Substitution> <String>: equivalent to\n"
           "\techo 'String' | sed -E 's/Regexp/Substitution/'\n");
    return 0;
  }

  return esub(argv[1], argv[2], argv[3]);
}
