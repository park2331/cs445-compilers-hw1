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
nodeptr *filestack = NULL;

int main(int argc, char **argv) {

  struct node *root = NULL;

  tokenptr get;
  int i;
  int code = -1;
  const char *filelist[argc];

  if(argc == 1) {
    printf("No files to (F)lex!\n");
    return 0;
  }
  /* Put file names in list */
  argc--;
  argv++;
  for (i = 0; i < argc; i++) {
    filelist[i] = argv[i];
  }

  /* Push onto flex's convenient buffer */
  for (i = 0; i < argc; i++) {
    yyin = fopen(filelist[i],"r");
    if (yyin == NULL) {
      printf("%s is not a file!\n",filelist[i]);
      return 0;
    }
    filetext = filelist[i];
    push_fname(&filestack, filelist[i]);
    yypush_buffer_state(yy_create_buffer(yyin, YY_BUF_SIZE));
  }
  
  /* Until 'code' returns 0 */
  while(code != 0) {
    code = yylex();
    if(yytoken != NULL) {
      get = yytoken;
      add_node(&root, get);
    }
  }

  printf("CODE\tTEXT\tLINE\tFILE\t\tiVAL\tsVAL\n");
  if(root == NULL) {
    printf("No tokens!\n");
  } else {
    print_nodes(&root);
  }
  return 0;
}
