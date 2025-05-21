#include "exp.h"
#include "lexer.h"
#include <stdio.h>
#include <string.h>


/* Carrega uma string como entrada */
YY_BUFFER_STATE buffer;
void inicializa(char *str) {
 buffer = yy_scan_string(str);
}
Token *proximo_token() {
 return yylex();
}
void imprime_token( Token *tok) {
 /* Aqui deve implementar o código para mostrar o token retornado pelo
 analisador léxico <token, atributo> de acordo com o tipo do token
 (obs: lembre-se que alguns tokens não possuem atributo)*/
    if(strcmp(tok->tipo,"INTEIRO")==0){ //int
        printf("< %s, %d>\n",tok->tipo, *((int*)tok->valor));

    }else if(strcmp(tok->tipo,"ID")==0){ //ID
        printf("< %s, %s>\n",tok->tipo, (char*)tok->valor);

    }else if(strcmp(tok->tipo,"RELOP")==0){ //relop
        printf("< %s, %s>\n",tok->tipo, (char*)tok->valor);

    }else if(strcmp(tok->tipo,"FLOAT")==0){ //float
        printf("< %s, %f>\n",tok->tipo, *(float*)tok->valor);

    }else{ //int
        printf("< %s, ->\n",tok->tipo);

    }
}

int main(int argc, char **argv) {
 Token *tok;
// Definicao da entrada
 char entrada[200];
 printf("\nAnalise Lexica da expressao: \n");
 fgets(entrada, 200, stdin);
 inicializa(entrada);
 tok = proximo_token();
 while (tok != NULL) {
 imprime_token(tok);
 if(strcmp(tok->tipo,"EOF")==0) break; //evitar pegar infinitos EOF
 tok = proximo_token();
 }
 return 0;
}