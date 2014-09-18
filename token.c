#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cgram.tab.h"
#include "token.h"

void print_token(tokenptr t) {
  printf("CATEGORY: %d\n",t->category);
};

tokenptr create_token(int category, char *text, int lineno) {
  tokenptr t = malloc(sizeof(struct token));
  t->category = category;

  /* allocate for text field */
  t->text = malloc(strlen(text)+1);
  strcpy(t->text, text);
  t->lineno = lineno;

  /* allocate for filename field */
  /*
  t->filename = malloc(strlen(filename)+1);
  strcpy(t->filename, filename);
  
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



