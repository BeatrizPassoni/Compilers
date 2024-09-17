#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define ID 1
#define PLUS 2
#define AST 3
#define LPAREN 4
#define RPAREN 5
#define END 6

char *entrada;
int token;
char ultimo_token[5];
int erro;
int primeiro_print = 1;

int obterToken();
void eat(int t);
void F();
void Tlinha();
void T();
void Elinha();
void E();
void S();


int main() {
    char buffer[131072];
    
    while (fgets(buffer, sizeof(buffer), stdin)) {
        entrada = buffer;
        erro = 0;
        token = obterToken();

        S(); 
        if (erro != 1){
            if(!primeiro_print)
                printf("\n");
            primeiro_print = 0;

            printf("CADEIA ACEITA");
        }
    }
    
    return 0;
}

int obterToken() {
    while (*entrada == ' ') 
        entrada++;

    if (*entrada == '+') {
        strncpy(ultimo_token, entrada, 1);
        ultimo_token[1] = '\0';
        entrada++;
        return PLUS;
    }
    if (*entrada == '*') {
        strncpy(ultimo_token, entrada, 1);
        ultimo_token[1] = '\0';
        entrada++;
        return AST;
    }
    if (*entrada == '(') {
        strncpy(ultimo_token, entrada, 1);
        ultimo_token[1] = '\0';
        entrada++;
        return LPAREN;
    }
    if (*entrada == ')') {
        strncpy(ultimo_token, entrada, 1);
        ultimo_token[1] = '\0';
        entrada++;
        return RPAREN;
    }
    if (*entrada == '$') {
        strncpy(ultimo_token, entrada, 1);
        ultimo_token[1] = '\0';
        entrada++;
        return END;
    }
    
    if (isalpha(*entrada)) {
        entrada++;
        while(isalnum(*entrada))
            entrada++;
        strcpy(ultimo_token, "id");
        ultimo_token[2] = '\0';
        return ID;
    }

    if (*entrada == '\0' || *entrada == '\n') {
        ultimo_token[0] = '\0';
    }
    else {
        strncpy(ultimo_token, entrada, 1);
        ultimo_token[1] = '\0';
        if(!primeiro_print)
                printf("\n");
            primeiro_print = 0;
        printf("ERRO LEXICO: %s", ultimo_token);
        erro = 1;
    }
    
    return -1;
}

void eat(int t) {
    if(erro == 1)
        return;
    
    char *esperado;
    if (token == t)
        token = obterToken();
    else{
        
        switch (t) {
        case ID:
            esperado = "id";
            break;
        
        case PLUS:
            esperado = "+";
            break;
        
        case AST:
            esperado = "*";
            break;
            
        case LPAREN:
            esperado = "(";
            break;
            
        case RPAREN:
            esperado = ")";
            break;
            
        case END:
            esperado = "$";
            break;
        }

        if(!primeiro_print)
                printf("\n");
            primeiro_print = 0;
        if(ultimo_token[0] == '\0')
            printf("ERRO SINTATICO EM: ESPERADO: %s", esperado);
        else
            printf("ERRO SINTATICO EM: %s ESPERADO: %s", ultimo_token, esperado);
        erro = 1;
    }
}

void F() {
    if(erro == 1)
        return;

    switch(token) {
        case LPAREN:
            eat(LPAREN);
            E();
            eat(RPAREN);
            break;

        case ID:
            eat(ID);
            break;

        default:
            if (!primeiro_print)
                printf("\n");
            primeiro_print = 0;

            if(ultimo_token[0] == '\0')
                printf("ERRO SINTATICO EM: ESPERADO: id, (");
            else
                printf("ERRO SINTATICO EM: %s ESPERADO: id, (", ultimo_token);
            erro = 1;
            break;
    }
}

void Tlinha() {
    if(erro == 1)
        return;
    
    if (token == AST) {
        eat(AST);
        F();
        Tlinha();
    }
    else {
        if (token != PLUS && token != RPAREN && token != END) {
            if (!primeiro_print)
                printf("\n");
            primeiro_print = 0;
            if(ultimo_token[0] == '\0')
                printf("ERRO SINTATICO EM: ESPERADO: +, *, ), $");
            else
                printf("ERRO SINTATICO EM: %s ESPERADO: +, *, ), $", ultimo_token);
            erro = 1;
        }
    }
    
}

void T() {
    if(erro == 1)
        return;

    if (token == ID || token == LPAREN) {
        F();
        Tlinha();
    }
    else {
        if (!primeiro_print)
            printf("\n");
        primeiro_print = 0;
        if(ultimo_token[0] == '\0')
            printf("ERRO SINTATICO EM: ESPERADO: id, (");
        else
            printf("ERRO SINTATICO EM: %s ESPERADO: id, (", ultimo_token);
        erro = 1;
    }
    
}

void Elinha() {

    if(erro == 1)
        return;
    
    if(token == PLUS){
        eat(PLUS);
        T();
        Elinha();
    }
    else {
        if (token != RPAREN && token != END) {
            if (!primeiro_print)
                printf("\n");
            primeiro_print = 0;
            if(ultimo_token[0] == '\0')
                printf("ERRO SINTATICO EM: ESPERADO: +, ), $");
            else
                printf("ERRO SINTATICO EM: %s ESPERADO: +, ), $", ultimo_token);
            erro = 1;
        }
    }

}

void E() {

    if(erro == 1)
        return;
    
    if (token == ID || token == LPAREN) {
        T();
        Elinha();
    }
    else {
        if (!primeiro_print)
            printf("\n");
        primeiro_print = 0;
        if(ultimo_token[0] == '\0')
            printf("ERRO SINTATICO EM: ESPERADO: id, (");
        else
        printf("ERRO SINTATICO EM: %s ESPERADO: id, (", ultimo_token);
        erro = 1;
    }
}

void S() {
    
    if(erro == 1)
        return;

    if (token == ID || token == LPAREN) {
        E();
        eat(END);
    }
    else {
        if (!primeiro_print)
            printf("\n");
        primeiro_print = 0;

        if(ultimo_token[0] == '\0')
            printf("ERRO SINTATICO EM: ESPERADO: id, (");
        else
            printf("ERRO SINTATICO EM: %s ESPERADO: id, (", ultimo_token);
        erro = 1;
    }
    
}


