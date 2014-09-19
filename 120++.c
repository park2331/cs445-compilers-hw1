#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "tlist.h"
#include "clex.h"

extern FILE *yyin;
extern char *yytext;
extern tokenptr yytoken;

/* extern in clex.l to get file name */
char *filetext;

int main(int argc, char **argv) {

  struct node *root = NULL;
  tokenptr get;
  int i;

  for (i = 1; i < argc; i++) {
    printf("%d: %s\n", i, argv[i]);
    filetext = argv[i];
    int code = -1;
    yyin = fopen(argv[i],"r");
    printf("CATEGORY     TEXT     LINE NO.\n");
    while (code != 0) {
      code = yylex();
      get = yytoken;
      add_node(&root, get);
    }
    fclose(yyin);
  }
  print_nodes(&root);
  return 0;
}
