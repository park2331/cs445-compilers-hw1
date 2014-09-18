#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "tlist.h"
#include "clex.h"

extern FILE *yyin;
extern char *yytext;
extern tokenptr yytoken;

int main(int argc, char**argv) {

  struct node *root = NULL;

  int code = -1;
  int i;

  //  yyin = fopen("argv[1]","r");
  yyin = fopen("test.c++","r");

  printf("CATEGORY     TEXT     LINE NO.\n");
  while (code != 0) {
    code = yylex();

    //    printf("%d %s %d\n", yytoken->category, yytoken->text, yytoken->lineno);
    //    add_token(yytoken, root);
  }
  fclose(yyin);
}
