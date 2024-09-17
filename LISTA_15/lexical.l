%option noyywrap
%option yylineno

%{

#include <syntactic.tab.h>
extern YYSTYPE yylval;

int endOfFile = 0;
int alterTokenFlag = 0;
int colunaAtual = 1;

void salvaToken() {
    yylval.token.valor = strdup(yytext);
    yylval.token.col = colunaAtual;
    yylval.token.lin = yylineno;
    colunaAtual += strlen(yytext);
}

%}

%%

<<EOF>> { endOfFile = 1; return 0; }

"$"     { return EOL; }
"int"   { salvaToken(); return INT; } 
"char"  { salvaToken(); return CHAR; }
"float" { salvaToken(); return FLOAT; }
","     { salvaToken(); return COMMA; }
" "     { colunaAtual++; }
\n      { colunaAtual = 1; }
[a-z]+  { salvaToken(); return ID; }

.     { if(alterTokenFlag) printf("\n");
        printf("error:lexical:%d:%d: %s", yylineno, colunaAtual, yytext);
        colunaAtual += strlen(yytext);
        exit(1);
}

%% 
