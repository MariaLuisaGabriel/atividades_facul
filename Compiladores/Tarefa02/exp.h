/*
    id (identificadores), OK
    relop (operadores relacionais), OK
    separadores (espaço, \t e \n), OK
    num_int (constante numérica inteira), OK
    num_float (constante numérica float), OK
    comentários (/* texto ), OK
    EOF (final de arquivo),
    atribuição (“:=”) OK
    e as palavras reservadas “begin”, “end”, “while”, “repeat” e “until” OK
*/

// constantes booleanas
#define TRUE 1
#define FALSE 0

// constantes para nome de token
#define TOK_NUM "INTEIRO" //int
#define TOK_OP "OPERACAO ARITMETICA"
#define TOK_PONT "PARENTESIS"
#define TOK_ERRO "ERRO"
#define TOK_ID "ID"
#define TOK_RELOP "RELOP"
#define TOK_FLOAT "FLOAT"
#define TOK_COMENTARIO "COMENTARIO"
#define TOK_EOF "EOF"
#define TOK_ATTR "ATRIBUICAO"
#define TOK_RESERVADO "PALAVRA RESERVADA"
#define TOK_SEPARADOR "SEPARADOR"

// constantes para operadores
#define SOMA 0
#define SUB 1
#define MULT 2
#define DIV 3

// constantes para parenteses
#define PARESQ 0
#define PARDIR 1

// estrutura de um token
typedef struct {
 char* tipo;
 void *valor;
} Token;

// funcao para criar um token
extern Token *token();
// funcao do analisador lexico
extern Token *yylex();