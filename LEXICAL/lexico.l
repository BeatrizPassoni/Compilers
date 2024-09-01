%option noyywrap

%{
#include <stdio.h>
#include <string.h>

int lines = 1;
int columns = 1;
int flag = 1;
int columns_comment = 0;
int lines_comment = 0;
char *strBuffer = NULL;

#define print_token(token) { if(flag == 1) { printf("%s", token); flag = 0; } else { printf("\n%s", token); } }

#define print_error() { printf("\nerror:lexical:%i:%i: %s", lines, columns, yytext); }

#define print_long_identifier() { printf("\nerror:lexical:%i:%i: identifier too long", lines, columns); }

#define print_comment_error() { printf("\nerror:lexical:%i:%i: unterminated comment", lines_comment, columns_comment); }

#define print_warning() { printf("\nwarning:%i:%i: '/*' within block comment", lines, columns); }

%}

%x COMENTARIO
%x STRING

%%

"\n"                  { lines++; columns = 1; }
[ \t]+                { columns += strlen(yytext); }
"void"                { print_token("VOID"); columns += strlen(yytext); }
"int"                 { print_token("INT"); columns += strlen(yytext); }
"char"                { print_token("CHAR"); columns += strlen(yytext); }
"return"              { print_token("RETURN"); columns += strlen(yytext); }
"break"               { print_token("BREAK"); columns += strlen(yytext); }
"switch"              { print_token("SWITCH"); columns += strlen(yytext); }
"case"                { print_token("CASE"); columns += strlen(yytext); }
"default"             { print_token("DEFAULT"); columns += strlen(yytext); }
"do"                  { print_token("DO"); columns += strlen(yytext); }
"while"               { print_token("WHILE"); columns += strlen(yytext); }
"for"                 { print_token("FOR"); columns += strlen(yytext); }
"if"                  { print_token("IF"); columns += strlen(yytext); }
"else"                { print_token("ELSE"); columns += strlen(yytext); }
"typedef"             { print_token("TYPEDEF"); columns += strlen(yytext); }
"struct"              { print_token("STRUCT"); columns += strlen(yytext); }
"+"                   { print_token("PLUS"); columns += strlen(yytext); }
"-"                   { print_token("MINUS"); columns += strlen(yytext); }
"*"                   { print_token("MULTIPLY"); columns += strlen(yytext); }
"/"                   { print_token("DIV"); columns += strlen(yytext); }
"%"                   { print_token("REMAINDER"); columns += strlen(yytext); }
"++"                  { print_token("INC"); columns += strlen(yytext); }
"--"                  { print_token("DEC"); columns += strlen(yytext); }
"&"                   { print_token("BITWISE_AND"); columns += strlen(yytext); }
"|"                   { print_token("BITWISE_OR"); columns += strlen(yytext); }
"~"                   { print_token("BITWISE_NOT"); columns += strlen(yytext); }
"^"                   { print_token("BITWISE_XOR"); columns += strlen(yytext); }
"!"                   { print_token("NOT"); columns += strlen(yytext); }
"&&"                  { print_token("LOGICAL_AND"); columns += strlen(yytext); }
"||"                  { print_token("LOGICAL_OR"); columns += strlen(yytext); }
"=="                  { print_token("EQUAL"); columns += strlen(yytext); }
"!="                  { print_token("NOT_EQUAL"); columns += strlen(yytext); }
"<"                   { print_token("LESS_THAN"); columns += strlen(yytext); }
">"                   { print_token("GREATER_THAN"); columns += strlen(yytext); }
"<="                  { print_token("LESS_EQUAL"); columns += strlen(yytext); }
">="                  { print_token("GREATER_EQUAL"); columns += strlen(yytext); }
">>"                  { print_token("R_SHIFT"); columns += strlen(yytext); }
"<<"                  { print_token("L_SHIFT"); columns += strlen(yytext); }
"="                   { print_token("ASSIGN"); columns += strlen(yytext); }
"+="                  { print_token("ADD_ASSIGN"); columns += strlen(yytext); }
"-="                  { print_token("MINUS_ASSIGN"); columns += strlen(yytext); }
";"                   { print_token("SEMICOLON"); columns += strlen(yytext); }
","                   { print_token("COMMA"); columns += strlen(yytext); }
":"                   { print_token("COLON"); columns += strlen(yytext); }
"("                   { print_token("L_PAREN"); columns += strlen(yytext); }
")"                   { print_token("R_PAREN"); columns += strlen(yytext); }
"{"                   { print_token("L_CURLY_BRACKET"); columns += strlen(yytext); }
"}"                   { print_token("R_CURLY_BRACKET"); columns += strlen(yytext); }
"["                   { print_token("L_SQUARE_BRACKET"); columns += strlen(yytext); }
"]"                   { print_token("R_SQUARE_BRACKET"); columns += strlen(yytext); }
"?"                   { print_token("TERNARY_CONDITIONAL"); columns += strlen(yytext); }
"#"                   { print_token("NUMBER_SIGN"); columns += strlen(yytext); }
"->"                  { print_token("POINTER"); columns += strlen(yytext); }
"printf"              { print_token("PRINTF"); columns += strlen(yytext); }
"scanf"               { print_token("SCANF"); columns += strlen(yytext); }
"define"              { print_token("DEFINE"); columns += strlen(yytext); }
"exit"                { print_token("EXIT"); columns += strlen(yytext); }

([a-zA-Z]|"_")([a-zA-Z0-9]|"_")* { if(strlen(yytext) < 256) { print_token("IDENTIFIER"); printf("(%s)", yytext); } else { print_long_identifier(); } columns += strlen(yytext); }

[0][1-7][0-7]*                   { print_token("NUM_OCTAL"); printf("(%s)", yytext); columns += strlen(yytext); }
(0x|0X)[a-fA-F0-9]+              { print_token("NUM_HEXA"); printf("(%s)", yytext); columns += strlen(yytext); }
[0-9]+                           { print_token("NUM_INTEGER"); printf("(%s)", yytext); columns += strlen(yytext); }

"//".*                           { columns += strlen(yytext); }
"/*"                             { columns_comment = columns; lines_comment = lines; columns += 2; BEGIN(COMENTARIO); }

\'\\[abfnrtv\\"\'0?]\'           { print_token("CHARACTER"); printf("(%c%c)", yytext[1], yytext[2]); columns += strlen(yytext); }
\'.\'                            { print_token("CHARACTER"); printf("(%c)", yytext[1]); columns += strlen(yytext); }

\"                               { strBuffer = (char *)calloc(1, sizeof(char)); columns++; BEGIN(STRING); }

.                                { print_error(); columns += strlen(yytext); }

<COMENTARIO>{
    "/*/"|"*/"                   { BEGIN(INITIAL); columns += strlen(yytext); }
    "/*"                         { print_warning(); columns += 2; }
    \n                           { columns = 1; lines++; }
    .                            { columns++; }
    <<EOF>>                      { print_comment_error(); return 0; }
}

<STRING>{
    \\\"                        { strBuffer = (char *)realloc(strBuffer, strlen(strBuffer) + strlen(yytext) + 1); strcat(strBuffer, yytext); columns += strlen(yytext); }
    \"                          { print_token("STRING"); printf("(%s)", strBuffer); free(strBuffer); columns++; BEGIN(INITIAL);}
    [^\"\n]                     { strBuffer = (char *)realloc(strBuffer, strlen(strBuffer) + strlen(yytext) + 1); strcat(strBuffer, yytext); columns++; }
}

%%

int main() {
    yylex();
    return 0;
}
