O        [0-7]
D        [0-9]
L        [a-zA-Z_]
H        [a-fA-F0-9]
E        [Ee][+-]?{D}+
FS       (f|F|l|L)
IS       (u|U|l|L)
W        [ \t\f]*
LIT      \"(\\.|[^\\"])*\"

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "cgram.tab.h"
#include "token.h"
#include "tlist.h"

/* ENUM types */
#define TRUE 1
#define FALSE 0

/* extern */
extern int yychar;
extern char *filetext;
extern FILE *yyin;
extern nodeptr filestack;

/* Global variables */
tokenptr yytoken;
FILE *saved_yyin;
int saved_yylineno;
char* saved_filetext;
int errors = 0;

/* #include flags */
int ctime = FALSE;
int iostream = 0;
int iomanip = FALSE;
int cmath = FALSE;
int cstdlib = FALSE;
int cstring = FALSE;
int fstream = FALSE;
int string = FALSE;

/* helper functions */
void handle_include();
int handle_EOF();
void lexerr(char *s);
void tokenize(int);

%}
/* lexer options */
%option yylineno
%option default
%option noyywrap
/* To fix 'undefined reference errors' */
%option header-file="clex.h"

%%

\n                      { }
[ \t\f]+                { }
"/*"([^*]*|"*"+[^/]*)"*/" { /* ignore c style comments */ }
"#include <iostream>"   { iostream = TRUE;}
"#include <ctime>"      { ctime = TRUE; }
"#include <iomanip>"    { iomanip = TRUE; }
"#include <cmath>"      { cmath = TRUE; }
"#include <cstdlib>"    { cstdlib = TRUE; }
"#include <cstring>"    { cstring = TRUE; }
"#include <fstream>"    { fstream = TRUE; }
"#include <string>"     { string  = TRUE; }
"#include"[ ]*\"[^\\"]+\" {handle_include(); }
"using namespace std"   { } 

"break"                 { tokenize(BREAK); return BREAK; }
"case"                  { tokenize(CASE); return CASE; }
"char"                  { tokenize(CHAR); return CHAR; }
"const"                 { tokenize(CONST); return CONST; }
"continue"              { tokenize(CONTINUE); return CONTINUE; }
"default"               { tokenize(DEFAULT); return DEFAULT; }
"do"                    { tokenize(DO); return DO; }
"double"                { tokenize(DOUBLE); return DOUBLE; }
"else"                  { tokenize(ELSE); return ELSE; }
"enum"                  { tokenize(ENUM); return ENUM; }
"extern"                { tokenize(EXTERN); return EXTERN; }
"float"                 { tokenize(FLOAT); return FLOAT; }
"for"                   { tokenize(FOR); return FOR; }
"goto"                  { tokenize(GOTO); return GOTO; }
"if"                    { tokenize(IF); return IF; }
"int"                   { tokenize(INT); return INT; }
"long"                  { tokenize(LONG); return LONG; }
"register"              { tokenize(REGISTER); return REGISTER; }
"return"                { tokenize(RETURN); return RETURN; }
"short"                 { tokenize(SHORT); return SHORT; }
"signed"                { tokenize(SIGNED); return SIGNED; }
"sizeof"                { tokenize(SIZEOF); return SIZEOF; }
"static"                { tokenize(STATIC); return STATIC; }
"struct"                { tokenize(STRUCT); return STRUCT; }
"switch"                { tokenize(SWITCH); return SWITCH; }
"typedef"               { tokenize(TYPEDEF); return TYPEDEF; }
"union"                 { tokenize(UNION); return UNION; }
"unsigned"              { tokenize(UNSIGNED); return UNSIGNED; }
"void"                  { tokenize(VOID); return VOID; }
"volatile"              { tokenize(VOLATILE); return VOLATILE; }
"while"                 { tokenize(WHILE); return WHILE; }

{L}({L}|{D})*           { tokenize(IDENTIFIER); return IDENTIFIER; }

0[xX]{H}+{IS}?          { printf("Hex not supported\n"); }
0{O}+{IS}?              { printf("Octal not supported\n"); }

{D}+{IS}?               { tokenize(ICON); return ICON; }
'(\\.|[^\\'])+'         { tokenize(CCON); return CCON; }
{D}+{E}{FS}?            { tokenize(FCON); return FCON; }
{D}*"."{D}+({E})?{FS}?  { tokenize(FCON); return FCON; }
{D}+"."{D}*({E})?{FS}?  { tokenize(FCON); return FCON; }
{LIT}                   { tokenize(STRING); return STRING; }
L?{LIT}                 { tokenize(STRINGL); return STRINGL; }

">>="                   { tokenize(SRASN); return SRASN; }
"<<="                   { tokenize(SLASN); return SLASN; }
"+="                    { tokenize(PLASN); return PLASN; }
"-="                    { tokenize(MIASN); return MIASN; }
"*="                    { tokenize(MUASN); return MUASN; }
"/="                    { tokenize(DIASN); return DIASN; }
"%="                    { tokenize(MOASN); return MOASN; }
"&="                    { tokenize(ANASN); return ANASN; }
"^="                    { tokenize(ERASN); return ERASN; }
"|="                    { tokenize(ORASN); return ORASN; }
">>"                    { tokenize(SHR); return SHR; }
"<<"                    { tokenize(SHL); return SHL; }
"++"                    { tokenize(INCOP); return INCOP; }
"--"                    { tokenize(DECOP); return DECOP; }
"->"                    { tokenize(FOLLOW); return FOLLOW; }
"&&"                    { tokenize(ANDAND); return ANDAND; }
"||"                    { tokenize(OROR); return OROR; }
"<="                    { tokenize(LE); return LE; }
">="                    { tokenize(GE); return GE; }
"=="                    { tokenize(EQ); return EQ; }
"!="                    { tokenize(NE); return NE; }
";"                     { tokenize(SM); return SM; }
"{"                     { tokenize(LC); return LC; }
"}"                     { tokenize(RC); return RC; }
","                     { tokenize(CM); return CM; }
":"                     { tokenize(COLON); return COLON; }
"="                     { tokenize(ASN); return ASN; }
"("                     { tokenize(LP); return LP; }
")"                     { tokenize(RP); return RP; }
"["                     { tokenize(LB);return LB; }
"]"                     { tokenize(RB); return RB; }
"."                     { tokenize(DOT); return DOT; }
"&"                     { tokenize(AND); return AND; }
"!"                     { tokenize(BANG); return BANG; }
"~"                     { tokenize(NOT); return NOT; }
"-"                     { tokenize(MINUS); return MINUS; }
"+"                     { tokenize(PLUS); return PLUS; }
"*"                     { tokenize(MUL); return MUL; }
"/"                     { tokenize(DIV); return DIV; }
"%"                     { tokenize(MOD); return MOD; }
"<"                     { tokenize(LT); return LT; }
">"                     { tokenize(GT); return GT; }
"^"                     { tokenize(ER); return ER; }
"|"                     { tokenize(OR); return OR; }
"?"                     { tokenize(QUEST); return QUEST; }
.                       { printf("HERE\n"); /* add in error message*/ }
<<EOF>>                 { 

  yypop_buffer_state();
  pop_node(&filestack);
  if (filestack == NULL) {
    yyterminate();    
    printf("ALL FILES PARSED!\n");
  }

  yylineno = 1;
  if (!YY_CURRENT_BUFFER) {
    printf("NO MORE BUFFERS!\n");
    yyterminate();
  } 
}
%%

void tokenize(int category) {
  filetext = filestack->filename;
  yytoken = create_token(category, yytext, yylineno, filetext);
};

/*
void lexerr(char *s)
{
  errors++;
  fprintf(stderr, "%s: lexical error", s);

  fprintf(stderr, ", token = \"%s\"\n", yytext);
};
*/

void handle_include() {
  FILE *include_buffer;
  YY_BUFFER_STATE incl_state;

  char *fname = malloc(strlen(yytext)+1-strlen("#include \"\""));
  fname = strchr(yytext, '\"')+1;
  fname[strlen(fname)-1] = '\0';
  printf("%s\n",fname);
  yyin = fopen(fname,"r");
  push_node(&filestack, fname);
  yypush_buffer_state(yy_create_buffer(yyin, YY_BUF_SIZE));

};
