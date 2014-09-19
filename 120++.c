#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "tlist.h"
#include "clex.h"

extern FILE *yyin;
extern char *yytext;
extern tokenptr yytoken;

int main(int argc, char **argv) {

  struct node *root = NULL;
  char files[argc];
  int i;

  for (i = 1; i < argc; i++) {
    printf("%d: %s\n", i, argv[i]);
    int code = -1;
    yyin = fopen(argv[i],"r");
    printf("CATEGORY     TEXT     LINE NO.\n");
    while (code != 0) {
      code = yylex();
    }
    fclose(yyin);
  }
  return 0;
}
