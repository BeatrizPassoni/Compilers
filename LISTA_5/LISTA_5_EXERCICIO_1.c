#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ESTADO_INICIAL 1
#define TAM 1024

int eEstadoFinal(int estado){
    if((estado  >= 2 && estado <= 5) || estado == 8) return 1;
    else return 0;  
}

int obterProximoEstado(int estadoAtual, char entrada){

    if(estadoAtual == 0 || estadoAtual == 3 || estadoAtual == 4 || entrada == '\n' || entrada == '\0') return 0;
    
    else if (estadoAtual == 1){ // Estado inicial

        if(entrada == '+') return 3;
        if(entrada == '-') return 4;
        if(entrada >= '0' && entrada <= '9') return 5;
        if(entrada >= 'a' && entrada <= 'z') return 2;

        return -1;

    }else if (estadoAtual == 2){
        
        if(entrada == '+' || entrada ==  '-') return 0;
        if((entrada >= '0' && entrada <= '9') || (entrada >= 'a' && entrada <= 'z')) return 2;

        return 0;

    }else if (estadoAtual == 5){
        
        if(entrada == '+' || entrada ==  '-') return 0;
        if(entrada >= '0' && entrada <= '9')  return 5;
        if(entrada == 'e') return 6;
        if(entrada >= 'a' && entrada <= 'z') return 0;

        return 0;

    }else if (estadoAtual == 6){
        
        if(entrada == '+' || entrada ==  '-') return 7;
        if(entrada >= '0' && entrada <= '9')  return 8;
        if(entrada >= 'a' && entrada <= 'z') return 0;

        return 0;

    }else if (estadoAtual == 7 || estadoAtual == 8){
        if(entrada == '+' || entrada ==  '-') return 0;
        if(entrada >= '0' && entrada <= '9')  return 8;
        if(entrada >= 'a' && entrada <= 'z') return 0;

        return 0;

    }else return -1;

}

void obterToken(char* endereco, int comprimento){
    if(comprimento == 0) return;
    char temp = endereco[comprimento];
    endereco[comprimento] = '\0';
    printf("%s\n", endereco);
    endereco[comprimento] = temp;
}

int main(void){

    char linhaEntrada[TAM];

    while(fgets(linhaEntrada, TAM, stdin) != NULL){
        
        int estadoAtual = ESTADO_INICIAL;
        
        int aceitar = 0;
        int index = 0;
        char* enderecoBase = linhaEntrada;

        while(1){         

            char caractereAtual = enderecoBase[index];
            index++;
            estadoAtual = obterProximoEstado(estadoAtual, caractereAtual);
            
            if(estadoAtual == -1){ // Caractere inválido
                printf("ERRO\n");
                enderecoBase += 1;
                aceitar = 0;
                index = 0;
                estadoAtual = ESTADO_INICIAL;
                continue; // Vai para próximo do loop
            }
            else if(estadoAtual == 0){ 
                if(*enderecoBase == '\n' || *enderecoBase == '\0') break; // Finalizou o processamento da linha

                obterToken(enderecoBase, aceitar);
                enderecoBase += aceitar;
                aceitar = 0;
                index = 0;
                estadoAtual = ESTADO_INICIAL;

            }
            else if(eEstadoFinal(estadoAtual))
                aceitar = index;
        }

    }

    return 0;
}
