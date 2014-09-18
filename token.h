#ifndef TOKEN_H
#define TOKEN_H 

typedef struct token {
  int category;   /* the integer code returned by yylex */
  char *text;     /* the actual string (lexeme) matched */
  int lineno;     /* the line number on which the token occurs */
  char *filename; /* the source file in which the token occurs */
  int ival;       /* if you had an integer constant, store its value here */
  char *sval;      /* if you had a string constant, malloc space and store */
} *tokenptr;           /*    the string (less quotes and after escapes) here */

tokenptr create_token(int category, char *text, int lineno);
void print_token(tokenptr);
#endif /* TOKEN_H */


