#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cgram.tab.h"
#include "token.h"

void print_token(tokenptr t) {
  printf("CATEGORY: %d\n",t->category);
  printf("STRING: %s\n",t->text);
  printf("LINE NO: %d\n",t->lineno);
  printf("FILE: %s\n",t->filename);
};

tokenptr create_token(int category, char *text, int lineno, char *filename) {
  tokenptr t = malloc(sizeof(struct token));
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

  /*  
  if (category == ICON) {
    t->ival = aoti(text);
  }

  if (category == CCON) {
    t->sval = malloc(strlen(text)+1);
    strcpy(t->sval, text);
  }
  */
  return t;
};



