#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cgram.tab.h"
#include "token.h"

void print_token(tokenptr t) {
  printf("%d\t%s\t\t%d\t%s\t%d\t%s\n",t->category, t->text ,t->lineno, t->filename, t->ival, t->sval);
};

tokenptr create_token(int category, char *text, int lineno, char *filename) {
  tokenptr t = malloc(sizeof(struct token));

  t->ival = 0;
  t->sval = "NONE";

  /* Integer code*/
  t->category = category;

  /* Actual string matched */
  t->text = malloc(strlen(text)+1);
  strcpy(t->text, text);

  /* Line Number*/
  t->lineno = lineno;

  /* File name */
  t->filename = malloc(strlen(filename)+1);
  strcpy(t->filename, filename);

  if (category == ICON) {
    t->ival = atoi(text);
  }

  if (category == STRING) {
    t->sval = malloc(strlen(text)+1);
    strcpy(t->sval, text);
  }
  return t;
};
