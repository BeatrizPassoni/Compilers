%{
    #include <stdio.h>
    
    extern int yylex();      // Função gerada pelo Flex
    extern char* yytext;     // Texto atual
    extern int yychar;       // Token atual
	extern char buffer[1024];
	extern int lines;
	extern int columns;
    void yyerror(void *s);   // Função de erro 
%}

%token INT CHAR VOID RETURN BREAK SWITCH CASE DEFAULT DO WHILE FOR IF ELSE TYPEDEF STRUCT
%token PLUS MINUS MULTIPLY DIV REMAINDER INC DEC BITWISE_AND BITWISE_OR BITWISE_NOT BITWISE_XOR
%token NOT LOGICAL_AND LOGICAL_OR EQUAL NOT_EQUAL LESS_THAN GREATER_THAN LESS_EQUAL GREATER_EQUAL
%token L_SHIFT R_SHIFT ASSIGN ADD_ASSIGN MINUS_ASSIGN SEMICOLON COMMA COLON L_PAREN R_PAREN
%token L_CURLY_BRACKET R_CURLY_BRACKET L_SQUARE_BRACKET R_SQUARE_BRACKET TERNARY_CONDITIONAL
%token NUMBER_SIGN POINTER PRINTF SCANF DEFINE EXIT IDENTIFIER NUM_OCTAL NUM_INTEGER NUM_HEXA
%token STRING CHARACTER

%start StartSymbol  // Símbolo inicial

%%

// Regras da gramática 
StartSymbol
    : FunctionDeclaration LoopFuncDec 
    ;

FunctionDeclaration
    : Declarations
    | Function
    ;

LoopFuncDec 
    : FunctionDeclaration LoopFuncDec
    | 
    ;

Declarations 
    : NUMBER_SIGN DEFINE IDENTIFIER Expression 
    | VariableDeclaration
    | PrototypeDeclaration
    ;

Function 
    : Type LoopPointers IDENTIFIER Parameters L_CURLY_BRACKET LoopFuncDec Commands R_CURLY_BRACKET
    ;

LoopPointers 
    : MULTIPLY LoopPointers
    | 
    ;

VariableDeclaration 
    : Type LoopDeclareVar SEMICOLON
    ;

LoopDeclareVar 
    : LoopPointers IDENTIFIER LoopExpression AssignsValue AnotherDec
    ;

AssignsValue
    : ASSIGN ExpressionAssignment
	| 
    ;

AnotherDec
    : COMMA LoopDeclareVar
	| 
    ;

LoopExpression 
    : L_SQUARE_BRACKET Expression R_SQUARE_BRACKET LoopExpression
    | 
    ;

PrototypeDeclaration
    : Type LoopPointers IDENTIFIER Parameters SEMICOLON
    ;

Parameters
    : L_PAREN LoopParameters R_PAREN
    ;

LoopParameters 
    : Type LoopPointers IDENTIFIER LoopExpression AnotherParameters
    | 
    ;

AnotherParameters
    : COMMA LoopParameters
    | 
    ;

Type 
    : INT
    | CHAR
    | VOID
    ;

Commands 
    : CommandsList LoopListCommands
    ;

LoopListCommands
    : CommandsList LoopListCommands
    | 
    ;

CommandsList
    : DO Block WHILE L_PAREN Expression R_PAREN SEMICOLON
    | IF L_PAREN Expression R_PAREN Block ElseBlock
    | WHILE L_PAREN Expression R_PAREN Block
    | FOR L_PAREN Expression SEMICOLON Expression SEMICOLON Expression R_PAREN Block
    | PRINTF L_PAREN STRING AdditionalExpression R_PAREN SEMICOLON
    | SCANF L_PAREN STRING COMMA BITWISE_AND R_PAREN SEMICOLON
    | EXIT L_PAREN Expression R_PAREN SEMICOLON
    | RETURN Expression SEMICOLON
    | Expression SEMICOLON
    | SEMICOLON
    | Block
    ;

Block
    : L_CURLY_BRACKET Commands R_CURLY_BRACKET
    ;

ElseBlock
    : ELSE Block
    | 
    ;

AdditionalExpression 
    : COMMA Expression
    | 
    ;

Expression 
    : ExpressionAssignment
    | Expression COMMA ExpressionAssignment
    ;

ExpressionAssignment 
    : ExpressionConditional
    | ExpressionUnary AssignOperator ExpressionAssignment
    ;

AssignOperator
    : ASSIGN
    | ADD_ASSIGN
    | MINUS_ASSIGN
    ;

ExpressionConditional
    : ExpressionLogicalOr ConditionalOperator
    ;

ConditionalOperator 
    : TERNARY_CONDITIONAL Expression COLON ExpressionConditional
    | 
    ;

ExpressionLogicalOr 
    : ExpressionLogicalAnd
    | ExpressionLogicalOr LOGICAL_OR ExpressionLogicalAnd
    ;

ExpressionLogicalAnd 
    : ExpressionBitwiseOr
    | ExpressionLogicalAnd LOGICAL_AND ExpressionBitwiseOr
    ;

ExpressionBitwiseOr 
    : ExpressionBitwiseXor
    | ExpressionBitwiseOr BITWISE_OR ExpressionBitwiseXor
    ;

ExpressionBitwiseXor 
    : ExpressionBitwiseAnd
    | ExpressionBitwiseXor BITWISE_XOR ExpressionBitwiseAnd
    ;

ExpressionBitwiseAnd 
    : ExpressionEquality
    | ExpressionBitwiseAnd BITWISE_AND ExpressionEquality
    ;

ExpressionEquality 
    : ExpressionRelational
    | ExpressionEquality EQUAL ExpressionRelational
    | ExpressionEquality NOT_EQUAL ExpressionRelational
    ;

ExpressionRelational 
    : ExpressionShift
    | ExpressionRelational LESS_THAN ExpressionShift
    | ExpressionRelational GREATER_THAN ExpressionShift
    | ExpressionRelational LESS_EQUAL ExpressionShift
    | ExpressionRelational GREATER_EQUAL ExpressionShift
    ;

ExpressionShift 
    : ExpressionAdd
    | ExpressionShift L_SHIFT ExpressionAdd
    | ExpressionShift R_SHIFT ExpressionAdd
    ;

ExpressionAdd 
    : ExpressionMultiply
    | ExpressionAdd PLUS ExpressionMultiply
    | ExpressionAdd MINUS ExpressionMultiply
    ;

ExpressionMultiply 
    : ExpressionCast
    | ExpressionMultiply MULTIPLY ExpressionCast
    | ExpressionMultiply DIV ExpressionCast
    | ExpressionMultiply REMAINDER ExpressionCast
    ;

ExpressionCast 
    : ExpressionUnary
    | L_PAREN Type LoopPointers R_PAREN ExpressionCast
    ;

ExpressionUnary 
    : ExpressionPostfix
    | INC ExpressionUnary
    | DEC ExpressionUnary
    | BITWISE_AND ExpressionCast
    | MULTIPLY ExpressionCast
    | PLUS ExpressionCast
    | MINUS ExpressionCast
    | NOT ExpressionCast
    | BITWISE_NOT ExpressionCast
    ;

ExpressionPostfix
    : PrimaryExpression
    | ExpressionPostfix L_SQUARE_BRACKET Expression R_SQUARE_BRACKET
    | ExpressionPostfix INC
    | ExpressionPostfix DEC
    | ExpressionPostfix L_PAREN ArgumentExpressionList R_PAREN
    ;

ArgumentExpressionList 
    : ExpressionAssignment ArgumentExpressionRest
    | 
    ;

ArgumentExpressionRest 
    : COMMA ExpressionAssignment ArgumentExpressionRest
    | 
    ;

PrimaryExpression 
    : IDENTIFIER
    | Numeric
    | CHARACTER
    | STRING
    | L_PAREN Expression R_PAREN
    ;

Numeric 
    : NUM_INTEGER
    | NUM_HEXA
    | NUM_OCTAL
    ;

%%

void yyerror(void *s)
{
    set(lines);   // Definir linha do erro

    if (yychar == 0){
        printf("error:syntax:%d:%d: expected declaration or statement at end of input\n%s\n", lines, columns, buffer);
    } else {
	    columns -= strlen(yytext);
        printf("error:syntax:%d:%d: %s\n%s", lines, columns, yytext, buffer);
    }

    // Imprimir seta para indicar o erro
    for(int i = 0; i < columns-1; i++) {
		printf(" "); 
	}
	printf("^");
	exit(0);
}

int main(int argc, char **argv) {
    yyparse();    // Iniciar a análise
    printf("SUCCESSFUL COMPILATION.");
    return 0;
}
