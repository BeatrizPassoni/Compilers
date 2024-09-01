%option noyywrap
 
%%
 
("+"|"-")                                   {printf("%s\n", yytext);}
[a-z][a-z0-9]*                              {printf("%s\n", yytext);}
([0-9]+|[0-9]+("e"("+"|"-"|[0-9])[0-9]*))   {printf("%s\n", yytext);}
\n                                          ;
.                                           {printf("ERRO\n");}
 
%%
 
int main(){
    yylex();
    return 0;
}
