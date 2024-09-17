%option noyywrap

%{
#include <stdio.h>
#include <string.h>
#include <sintatico.tab.h>

int lines = 1;
int columns = 1;
int flag = 1; 
int lines_comment = 0;
int columns_comment = 0; 
char buffer[1024];


#define print_warning() { printf("warning:%i:%i: '/*' within block comment\n", lines, columns); }

#define print_error() { printf("error:lexical:%i:%i: %s\n", lines, columns, yytext); exit(EXIT_FAILURE); }

#define print_long_identifier() { printf("error:lexical:%i:%i: identifier too long\n", lines, columns); exit(EXIT_FAILURE); }

#define print_comment_error() { printf("error:lexical:%i:%i: unterminated comment\n", lines_comment, columns_comment); exit(EXIT_FAILURE); }
 
%}

%x COMENTARIO

%%

<INITIAL>{
"\n"                    { lines++; columns = 1; }
[ \t]+                  { columns += strlen(yytext); }
"void"                  { columns+=yyleng; return VOID; }
"int"                   { columns+=yyleng; return INT; }
"char"                  { columns+=yyleng; return CHAR; }
"return"                { columns+=yyleng; return RETURN; }
"break"                 { columns+=yyleng; return BREAK; }
"switch"                { columns+=yyleng; return SWITCH; }
"case"                  { columns+=yyleng; return CASE; }
"default"               { columns+=yyleng; return DEFAULT; }
"do"                    { columns+=yyleng; return DO; }
"while"                 { columns+=yyleng; return WHILE; }
"for"                   { columns+=yyleng; return FOR; }
"if"                    { columns+=yyleng; return IF; }
"else"                  { columns+=yyleng; return ELSE; }
"typedef"               { columns+=yyleng; return TYPEDEF; }
"struct"                { columns+=yyleng; return STRUCT; }
"+"                     { columns+=yyleng; return PLUS; }
"-"                     { columns+=yyleng; return MINUS; }
"*"                     { columns+=yyleng; return MULTIPLY; }
"/"                     { columns+=yyleng; return DIV; }
"%"                     { columns+=yyleng; return REMAINDER; }
"++"                    { columns+=yyleng; return INC; }
"--"                    { columns+=yyleng; return DEC; }
"&"                     { columns+=yyleng; return BITWISE_AND; }
"|"                     { columns+=yyleng; return BITWISE_OR; }
"~"                     { columns+=yyleng; return BITWISE_NOT; }
"^"                     { columns+=yyleng; return BITWISE_XOR; }
"!"                     { columns+=yyleng; return NOT; }
"&&"                    { columns+=yyleng; return LOGICAL_AND; }
"||"                    { columns+=yyleng; return LOGICAL_OR; }
"=="                    { columns+=yyleng; return EQUAL; }
"!="                    { columns+=yyleng; return NOT_EQUAL; }
"<"                     { columns+=yyleng; return LESS_THAN; }
">"                     { columns+=yyleng; return GREATER_THAN; }
"<="                    { columns+=yyleng; return LESS_EQUAL; }
">="                    { columns+=yyleng; return GREATER_EQUAL; }
">>"                    { columns+=yyleng; return R_SHIFT; }
"<<"                    { columns+=yyleng; return L_SHIFT; }
"="                     { columns+=yyleng; return ASSIGN; }
"+="                    { columns+=yyleng; return ADD_ASSIGN; }
"-="                    { columns+=yyleng; return MINUS_ASSIGN; }
";"                     { columns+=yyleng; return SEMICOLON; }
","                     { columns+=yyleng; return COMMA; }
":"                     { columns+=yyleng; return COLON; }
"("                     { columns+=yyleng; return L_PAREN; }
")"                     { columns+=yyleng; return R_PAREN; }
"{"                     { columns+=yyleng; return L_CURLY_BRACKET; }
"}"                     { columns+=yyleng; return R_CURLY_BRACKET; }
"["                     { columns+=yyleng; return L_SQUARE_BRACKET; }
"]"                     { columns+=yyleng; return R_SQUARE_BRACKET; }
"?"                     { columns+=yyleng; return TERNARY_CONDITIONAL; }
"#"                     { columns+=yyleng; return NUMBER_SIGN; }
"->"                    { columns+=yyleng; return POINTER; }
"printf"                { columns+=yyleng; return PRINTF; }
"scanf"                 { columns+=yyleng; return SCANF; }
"define"                { columns+=yyleng; return DEFINE; }
"exit"                  { columns+=yyleng; return EXIT; }     

[a-zA-Z_][a-zA-Z0-9_]*  {if (yyleng > 255){print_long_identifier(); } else{columns+=yyleng; return IDENTIFIER; }}

0[1-7][0-7]*            {columns+=yyleng; return NUM_OCTAL; }
(0x|0X)[a-fA-F0-9]+     {columns+=yyleng; return NUM_HEXA; }
[0-9]+                  {columns+=yyleng; return NUM_INTEGER; }

"//".*                  {columns += strlen(yytext); } 
"/*"                    { columns_comment = columns; lines_comment = lines; columns += 2; BEGIN(COMENTARIO); }

\"(\\.|[^"\\])*\"	    {columns+=yyleng; return STRING; }
'([^'\\\n]|\\.)'        {columns+=yyleng; return CHARACTER; }

.                       {print_error(); }
}

<COMENTARIO>{
    "/*/"|"*/"                   { BEGIN(INITIAL); columns += strlen(yytext); }
    "/*"                         { print_warning(); columns += 2; }
    \n                           { columns = 1; lines++; }
    .                            { columns++; }
    <<EOF>>                      { print_comment_error(); return 0; }
}


%%

void set(int total_lines)
{
    fseek(stdin, 0, SEEK_SET);
    for(int i = 0; i < total_lines; i++)
    {
        fgets(buffer, 1000, stdin);
    }
}