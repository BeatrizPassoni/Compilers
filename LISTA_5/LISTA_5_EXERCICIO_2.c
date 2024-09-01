#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ESTADO_INICIAL 1
#define TAM 1024

int eEstadoFinal(int estado){
    if((estado >= 2 && estado <= 9) || (estado >= 11 && estado <= 13)) 
        return 1;
    else 
        return 0;  
}

int getIndex(char caractere){  
    if(caractere == ' ') return 0;
    else if(caractere >= 'a' && caractere <= 'z') return (caractere - 96);
    else if(caractere >= '0' && caractere <= '9') return (26 + (caractere - 47));
    else if(caractere == '.') return 37;
    else if(caractere == '-') return 38;
    else if(caractere == '\n') return 39;
    else return 40; // Caracter invalido
}

int getNextState(int estadoAtual, char caractere, int transicoes[][41]){
    int indice = getIndex(caractere);
    return transicoes[estadoAtual][indice];
}

void getToken(char* endereco, int tamanho, int estadoFinal){
    if(tamanho == 0) return;
    char temp = endereco[tamanho];
    endereco[tamanho] = '\0';

    if(estadoFinal == 2 || estadoFinal == 4) 
        printf("%s ID\n", endereco);
    else if(estadoFinal == 3)
        printf("IF\n");
    else if(estadoFinal == 12)
        printf("white space\n");
    else if(estadoFinal == 13 || estadoFinal == 9 || estadoFinal == 5)
        printf("%s error\n", endereco);
    else if(estadoFinal == 6 || estadoFinal == 8)
        printf("%s REAL\n", endereco);
    else if(estadoFinal == 7)
        printf("%s NUM\n", endereco);
    else if(estadoFinal == 11){
        endereco[tamanho-1] = '\0';
        printf("%s comment\n", endereco);
        endereco[tamanho-1] = '\n';
    }
    endereco[tamanho] = temp;
}


int main(void){
    
    int transicoes[][41] = {
            /*      Blank  a   b   c   d   e   f   g   h   i   j   k   l   m   n   o   p   q   r   s   t   u   v   w   x   y   z   0   1   2   3   4   5   6   7   8   9   .   -   \n  O*/   // Ultimo para invalidos 
        /*state 0*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 1*/  {12, 4,  4,  4,  4,  4,  4,  4,  4,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  5,  9, 13, 13},
        /*state 2*/  {0,  4,  4,  4,  4,  4,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  0,  0,  0,  0},
        /*state 3*/  {0,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  0,  0,  0,  0},
        /*state 4*/  {0,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  0,  0,  0,  0},
        /*state 5*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  0,  0,  0,  0},
        /*state 6*/  {0,  0,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  0,  0,  0,  0},
        /*state 7*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,   7,  7,  7,  7,  7,  7,  7,  7,  8,  0,  0,  0},
        /*state 8*/  {0,  0,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  0,  0,  0,  0},
        /*state 9*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10,  0,  0},
        /*state 10*/ {0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 11,  0},
        /*state 11*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 12*/ {12, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 13*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    };

    char entrada[TAM];

    while(fgets(entrada, TAM, stdin) != NULL){
        
        int ultimoEstadoFinal = 0;
        int estadoAtual = ESTADO_INICIAL;
        
        int aceita = 0;
        int index = 0;
        char* enderecoBase = entrada;

        while(1){         

            char caractereAtual = enderecoBase[index];
            index++;
            estadoAtual = getNextState(estadoAtual, caractereAtual, transicoes);
            
            if(estadoAtual == 0){ // Token 
                
                if(*enderecoBase == '\n' || *enderecoBase == '\0') 
                    break;

                getToken(enderecoBase, aceita, ultimoEstadoFinal);
                enderecoBase += aceita;
                aceita = 0;
                index = 0;
                ultimoEstadoFinal = 0;
                estadoAtual = ESTADO_INICIAL;

            }
            else if(eEstadoFinal(estadoAtual)){ // Reconhecido estado final, necessário salvar
                ultimoEstadoFinal = estadoAtual;
                aceita = index;
            }
        }

    }

    return 0;
}
