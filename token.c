#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cgram.tab.h"
#include "token.h"

void print_token(tokenptr t) {
  printf("%d\t%s\t%d\t%s\t%d\t%s\n",t->category, t->text ,t->lineno, t->filename, t->ival, t->sval);
};

char *get_stringl(char *string) {
  /* \n \t \' \\ \" and \0 */
  int len = 0;
  char* ptr = string;
  char* strl = malloc(strlen(string)); 

  /* Get past first quote */
  while (*ptr++ != '\"') {
    ptr++;
  }

  /* Get to end quote */
  while (*ptr != '\"') {
    if (ptr[0] == '\\') {
      char esc = ptr[1];
      //      printf("Found escape char: %c%c\n",ptr[0],esc);
      if (esc == 'n' || esc == 't' || esc == '\'' || esc == '\\' || esc == '\"' || esc == '\0') {
	ptr++;
	ptr++;
      } 
    } else {
      strl[len] = *ptr;
      len++;
      ptr++;
    }
  }
  strl[len] = '\0';
  strl = realloc(strl, len);
  return strl;
}



tokenptr create_token(int category, char *text, int lineno, char *filename) {
  tokenptr t = malloc(sizeof(struct token));

  t->ival = 0;
  t->sval = "NONE";

  /* Integer code*/
  t->category = category;

  /* Actual string matched */
  /* memory leak? */
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

  /* memory leak? */
  if (category == STRING) {
    t->sval = get_stringl(text);
  }
  return t;
};
