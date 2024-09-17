%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASH_SIZE 211

extern int yylex();
void yyerror(void *s);

extern int yychar;
extern int alterTokenFlag;
extern int endOfFile;

int sintaticError = 0;
int semanticError = 0;

int tipoToken;

typedef struct Node {
    int tipo;
    char *valor;
    struct Node *prox;
} Node;

int calcularHash();
void adicionarNo();
int buscarNo();
void liberarHash();

void **HashTable = NULL;

%}

%union {
    struct {
        char *valor;
        int col;
        int lin;
    } token;
}

%token EOL
%token COMMA
%token INT
%token CHAR
%token FLOAT
%token ID

%start S

%%

S: D D_Quote EOL { sintaticError = 0; return 0; }
    | error      { sintaticError = 1; return 0; } 
;

D_Quote: D D_Quote { }
        | { } 
;

D: T I { } ;

T: INT      { tipoToken = INT; }
    | CHAR  { tipoToken = CHAR; }
    | FLOAT { tipoToken = FLOAT; } 
;

I: ID { 
    if(!buscarNo())
        adicionarNo(); 
}
    | I COMMA ID { 
        if(!buscarNo())
            adicionarNo(); 
} ;

%%

void yyerror(void *s) {}

int calcularHash() {
    int hash = 0;
    for(int i = 0; i < strlen(yylval.token.valor); i++)
        hash += yylval.token.valor[i];
    return hash % HASH_SIZE;
}

void adicionarNo() {
    int index = calcularHash(yylval.token.valor);
    Node *novo = calloc(1, sizeof(Node));
    novo->tipo = tipoToken;
    novo->valor = calloc(strlen(yylval.token.valor) + 1, sizeof(char));
    strcpy(novo->valor, yylval.token.valor);

    Node *head = (Node*) HashTable[index];
    if(!head) {
        HashTable[index] = novo;
    } else {
        while(head->prox) 
            head = head->prox;
        head->prox = novo;
    }

}

int buscarNo() {
    if(!HashTable) 
        return 0;
    int index = calcularHash(yylval.token.valor);
    int ocorrencia = 0;
    Node *aux = (Node*) HashTable[index];

    while(aux) {
        if(!strcmp(yylval.token.valor, aux->valor)) { // existe outro identificador na hash
            ocorrencia++;
            if(ocorrencia == 1) 
                continue;  
            if(tipoToken == aux->tipo) {  // mesmo tipo
                if(alterTokenFlag) 
                    printf("\n");
                printf("%d: identifier '%s' already declared", yylval.token.lin, yylval.token.valor);
                semanticError = 1;
                alterTokenFlag = 1;
                return 1;
            } else {  // tipos diferentes
                if(alterTokenFlag) 
                    printf("\n");
                printf("%d: redefinition of identifier '%s'", yylval.token.lin, yylval.token.valor);
                semanticError = 1;
                alterTokenFlag = 1;
                return 1;
            }
        }
        aux = aux->prox;
    }
    return 0;
}

void liberarHash() {
    for(int i = 0; i < HASH_SIZE; i++) {
        Node *head = HashTable[i];
        while(head) {
            Node *aux = head->prox;
            if(head->valor) 
                free(head->valor);
            free(head);
            head = aux;
        }
        HashTable[i] = NULL; 
    }
}

int main(int argc, char *argv[]) {
    HashTable = calloc(HASH_SIZE, sizeof(Node));
    while(!endOfFile) {
        yyparse();

        if(yychar == 0) 
            break;
        if(semanticError == 0) {
            if(alterTokenFlag) 
                printf("\n");
            printf("%d: All Identifiers on Hash.", yylval.token.lin);
            alterTokenFlag = 1;
            liberarHash();
        } else {
            semanticError = 0;
            liberarHash();
        }        
    }
    if(HashTable) {
        liberarHash(HashTable);
        free(HashTable);
    }

    return 0;
}
