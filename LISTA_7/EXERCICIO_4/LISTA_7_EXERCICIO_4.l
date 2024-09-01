%option noyywrap
 
%{
int total_lines = 0;
int blank_lines = 0;
int lines_w_comments = 0;
int nb_nc_lines = 0;
int semi_colons = 0;
int preproc_direct = 0;
%}
 
%%
 
\n                      {total_lines++;}
^[ \t]*\n               {total_lines++; blank_lines++;}
"//".*                  {lines_w_comments++;}
";"                     {semi_colons++;}
"#include"|"#define"    {preproc_direct++;}
.                       ;
 
%%
 
int main(int argc, char **argv) {
        printf(" total   blank  lines w/   nb, nc   semi-   preproc. file\n");
        printf(" lines   lines  comments   lines   coluns   direct.     \n");
        printf("------+--------+--------+--------+--------+--------+----\n");
 
        for(int i = 1; i < argc; i++) {
                FILE *file = fopen(argv[i], "r");
                if(!file) {
                    printf("ERRO AO ABRIR O ARQUIVO\n");
                }
                else {
                    yyin = file;
                    total_lines = 0;
                    blank_lines = 0;
                    lines_w_comments = 0;
                    semi_colons = 0;
                    preproc_direct = 0;
   
                    yylex();
                    fclose(file);
   
                    nb_nc_lines = total_lines - blank_lines - lines_w_comments;
                    printf("%5d %7d %8d %8d %9d %9d %s\n", total_lines, blank_lines, lines_w_comments, nb_nc_lines, semi_colons, preproc_direct, argv[i]);
                }
        }
 
        return 0;
}