#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define IF 1
#define THEN 2
#define ELSE 3
#define BEGIN 4
#define END 5
#define PRINT 6
#define SEMI 7
#define NUM 8
#define EQ 9

char *entrada;
int token;
char ultimo_token[5];                           
int flag;                                       
int primeira_impressao = 1;

int is_digit(char c); 
int obterToken();
void eat(int t);
void L();
void E();
void S();

int main() {

    char string[60000];
    while (fgets(string, sizeof(string), stdin)) {
        entrada = string;
        flag = 0;                                                                       
        token = obterToken();                                                        
        S();  
        if (flag != 1){
            if(!primeira_impressao)
                printf("\n");
            primeira_impressao = 0;

            printf("CADEIA ACEITA");
        }
    }
    
    return 0;
}

int is_digit(char c) {
    return (c >= '0' && c <= '9');
}

int obterToken() {
    while (*entrada == ' ') 
        entrada++; 
    
    if (strncmp(entrada, "if", 2) == 0 && (isspace(entrada[2]) || entrada[2] == '\0' || entrada[2] == '\n')) {
        strncpy(ultimo_token, entrada, 2);
        ultimo_token[2] = '\0';
        entrada += 2;
        return IF;
    }
    if (strncmp(entrada, "then", 4) == 0 && (isspace(entrada[4]) || entrada[4] == '\0' || entrada[4] == '\n'))  {
        strncpy(ultimo_token, entrada, 4);
        ultimo_token[4] = '\0';
        entrada += 4;
        return THEN;
    }
    if (strncmp(entrada, "else", 4) == 0 && (isspace(entrada[4]) || entrada[4] == '\0' || entrada[4] == '\n'))  {
        strncpy(ultimo_token, entrada, 4);
        ultimo_token[4] = '\0';
        entrada += 4;
        return ELSE;
    }
    if (strncmp(entrada, "begin", 5) == 0 && (isspace(entrada[5]) || entrada[5] == '\0' || entrada[5] == '\n'))  {
        strncpy(ultimo_token, entrada, 5);
        ultimo_token[5] = '\0';
        entrada += 5;
        return BEGIN;
    }
    if (strncmp(entrada, "end", 3) == 0 && (isspace(entrada[3]) || entrada[3] == '\0' || entrada[3] == '\n'))  {
        strncpy(ultimo_token, entrada, 3);
        ultimo_token[3] = '\0';
        entrada += 3;       
        return END;
    }
    if (strncmp(entrada, "print", 5) == 0 && (isspace(entrada[5]) || entrada[5] == '\0' || entrada[5] == '\n'))  {
        strncpy(ultimo_token, entrada, 5);
        ultimo_token[5] = '\0';
        entrada += 5;
        return PRINT;
    }
    if (*entrada == ';') {
        strncpy(ultimo_token, entrada, 1);
        ultimo_token[1] = '\0';
        entrada++;
        return SEMI;
    }
    if (*entrada == '=') {
        strncpy(ultimo_token, entrada, 1);
        ultimo_token[1] = '\0';
        entrada++;
        return EQ;
    }

    if (isdigit(*entrada) || ((*entrada == '+' || *entrada == '-') && isdigit(*(entrada + 1)))) {
        entrada++;
        while (isdigit(*entrada)) 
            entrada++;
        strcpy(ultimo_token,"num\0");
        return NUM;
    }

    if (*entrada == '\0' || *entrada == '\n') {
        ultimo_token[0] = '\0';
    }
    
    return -1; 
}

void eat(int t) {
    if(flag == 1)
        return;
    
    char *string;
    if (token == t)
        token = obterToken();
    else{
        if (ultimo_token[0] == '\0') {
            if(!primeira_impressao)
                printf("\n");
            primeira_impressao = 0;
            printf("ERRO SINTATICO: CADEIA INCOMPLETA");
            flag = 1;
            return;
        }
        
        switch (t) {
        case IF:
            string = "if";
            break;
        
        case THEN:
            string = "then";
            break;
        
        case ELSE:
            string = "else";
            break;
            
        case BEGIN:
            string = "begin";
            break;
            
        case END:
            string = "end";
            break;
            
        case PRINT:
            string = "print";
            break;
            
        case SEMI:
            string = ";";
            break;

        case NUM:
            string = "num";
            break;
        
        case EQ:
            string = "=";
            break;
        }

        if(!primeira_impressao)
                printf("\n");
            primeira_impressao = 0;

        printf("ERRO SINTATICO EM: %s ESPERADO: %s", ultimo_token, string);
        flag = 1;
    }
}

void L() {
    if(flag == 1)
        return;

    switch (token) {
        case END:
            eat(END);
            break;

        case SEMI:
            eat(SEMI);
            S();
            L();
            break;

        default:
            if(!primeira_impressao)
                printf("\n");
            primeira_impressao = 0;

            printf("ERRO SINTATICO EM: %s ESPERADO: end, ;", ultimo_token);
            flag = 1;
    }
}

void E() {
    if(flag == 1)
        return;

    eat(NUM);
    eat(EQ);
    eat(NUM);
}

void S() {
    if(flag == 1)
        return;

    switch (token) {
        case IF:
            eat(IF);
            E();
            eat(THEN);
            S();
            eat(ELSE);
            S();
            break;

        case BEGIN:
            eat(BEGIN);
            S();
            L();
            break;

        case PRINT:
            eat(PRINT);
            E();
            break;

        default:
            if(!primeira_impressao)
                printf("\n");
            primeira_impressao = 0;

            printf("ERRO SINTATICO EM: %s ESPERADO: if, begin, print", ultimo_token);
            flag = 1;
    }
}
