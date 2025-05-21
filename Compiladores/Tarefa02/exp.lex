%option noyywrap
%option nodefault
%option outfile="lexer.c" header-file="lexer.h"
%{
#include "exp.h"
#include <stdlib.h>
%}
NUM [0-9]+
FLOAT [0-9]+\.[0-9]+
SEPARATOR [  \n\t]+
COMM \/\*[^\*\/]+?\*\/
RES (begin|end|while|repeat|until)
ID [A-Za-z]([A-Za-z_0-9]+)?

%%
{NUM} {
    int a = atoi(yytext);
    void* r = &a;
    return token(TOK_NUM, r); 
    }
\+ { return token(TOK_OP, SOMA); }
- { return token(TOK_OP, SUB); }
\* { return token(TOK_OP, MULT); }
\/ { return token(TOK_OP, DIV); }
\( { return token(TOK_PONT, PARESQ); }
\) { return token(TOK_PONT, PARDIR); }
{FLOAT} { 
    float a = atof(yytext);
    void* r = &a;
    return token(TOK_FLOAT, r); 
    }
\> { return token(TOK_RELOP, yytext); }
\< { return token(TOK_RELOP, yytext); }
\>= { return token(TOK_RELOP, yytext); }
\<= { return token(TOK_RELOP, yytext); }
\<> { return token(TOK_RELOP, yytext); }
{COMM} { return token(TOK_COMENTARIO, NULL); }
{RES} { return token(TOK_RESERVADO, NULL); }
{ID} { return token(TOK_ID, yytext); }
{SEPARATOR} { return token(TOK_SEPARADOR, NULL); }
:= { return token(TOK_ATTR, NULL); }
<<EOF>> { return token(TOK_EOF, NULL); }
. { return token(TOK_ERRO, NULL); } /* Tratamento para token desconhecido */
%% 

// variavel global para um token
Token tok;
Token * token (char* tipo, void *valor) {
 tok.tipo = tipo;
 tok.valor = valor;
 return &tok;
}