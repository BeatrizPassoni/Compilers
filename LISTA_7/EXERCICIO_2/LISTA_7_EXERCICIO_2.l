%option noyywrap
 
%%
 
(" ")+                          {printf("white space\n", yytext);}
"--"[a-z]*                      {printf("%s comment\n", yytext);}
([0-9]+"."[0-9]*|"."[0.9])      {printf("%s REAL\n", yytext);}
[0-9]+                          {printf("%s NUM\n", yytext);}
"if"                            {printf("%s IF\n", yytext);}
[a-z][a-z0-9]*                       {printf("%s ID\n", yytext);}
\n                              ;
.                               {printf("%s error\n");}
 
%%
 
int main(){
    yylex();
    return 0;
}
