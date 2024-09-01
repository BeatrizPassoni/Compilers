#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define estadoInicial 1
#define TAM 4098 
#define numEstados 22

int isFinalState(int state){
    if((state  >= 13 && state <= 19) || state == 3 || state == 6 || state == 8 || state == 10 || state == 22) return 1;
    else return 0;  
}

int getCharColumnIndex(char *alfabeto, char character){ 
    for(int i = 0; i < 21; i++) {
        if(alfabeto[i] == character)
            return i;
    }
    return 20;
}

int getNextState(char *alfabeto, int atual, char character, int arestas[][21]){
    int index = getCharColumnIndex(alfabeto, character);
    return arestas[atual][index];
}

void imprimeToken(char* endereco, int tam, int estadoFinal, int* primeiroToken){
    char temp = endereco[tam];
    endereco[tam] = '\0';

    if(*primeiroToken)
        *primeiroToken = 0;
    else
        printf("\n");

    if(estadoFinal == 3) 
        printf("ELE");
    else if(estadoFinal == 6)
        printf("ELA");
    else if(estadoFinal == 8)
        printf("DELE");
    else if(estadoFinal == 10)
        printf("DELA");
    else if(estadoFinal == 13)
        printf("GATO");
    else if(estadoFinal == 15)
        printf("GATOS");
    else if(estadoFinal == 14)
        printf("CARRO");
    else if(estadoFinal == 16)
        printf("CARROS");
    else if(estadoFinal == 17)
        printf("MAIS");
    else if(estadoFinal == 18)
        printf("MENOS");
    else if(estadoFinal == 19)
        printf("INTEIRO %s", endereco);
    else if(estadoFinal == 22)
        printf("REAL %s", endereco);

    endereco[tam] = temp;
}


int main(void){
    
    int arestas[][numEstados-1] = {
                  /*  +   -   0   1   2   3   4   5   6   7   8   9   a   c   e   h   i   r   s   t   O */
        /*state 0*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 1*/  {17,18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,  0, 11,  0,  2,  0,  0,  4,  0,  0},
        /*state 2*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  0,  7,  0,  0,  0,  0},
        /*state 3*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9,  0,  0,  0},
        /*state 4*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  5,  0,  0,  0,  0,  0},
        /*state 5*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  0,  0,  0,  0,  0,  0},
        /*state 6*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 7*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  0,  0},
        /*state 8*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 9*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10,  0,  0},
        /*state 10*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 11*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 12,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 12*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 14,  0, 13,  0},
        /*state 13*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15,  0,  0},
        /*state 14*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16,  0,  0},
        /*state 15*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 16*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 17*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 18*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 19*/ {0,  0, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,  0,  0, 20,  0,  0,  0,  0,  0,  0},
        /*state 20*/ {21,21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 21*/ {0,  0, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 22*/ {0,  0, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    };

    char alfabeto[21] = {'+', '-', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'c', 'e', 'h', 'i', 'r', 's', 't', 'O'};

    char entrada[TAM];
    int primeiroToken = 1;

    while(fgets(entrada, TAM, stdin) != NULL){
        
        int ultimoFinal = 0;
        int atual = estadoInicial;
        int indexAceito = 0;
        int index = 0;

        char* enderecoBase = entrada;

        while(!(*enderecoBase == '\n' || *enderecoBase == '\0')){         

            char caracter = enderecoBase[index];
            index++;
            atual = getNextState(alfabeto, atual, caracter, arestas);
            
            if(atual == 0){ 

                if(indexAceito != 0){ // Reconhecido começando em enderecoBase e terminando em ((enderecoBase + indexAceito) - 1).
                    imprimeToken(enderecoBase, indexAceito, ultimoFinal, &primeiroToken);
                    enderecoBase += indexAceito;
                    indexAceito = 0;
                }
                else{ // Nenhum token aceito 
                    if(*enderecoBase != ' '){ // Se for espaço, não printa erro
                        if(primeiroToken)
                            primeiroToken = 0;
                        else
                            printf("\n");  
                        printf("ERRO");
                    }
                    enderecoBase += 1; // Base aumenta e vamos para o proximo!
                }
                index = 0;
                ultimoFinal = 0;
                atual = estadoInicial;

            }
            else if(isFinalState(atual)){ //
                ultimoFinal = atual;
                indexAceito = index;
            }
        }

    }

    return 0;
}
