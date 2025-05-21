#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int linha = 1;
int coluna = 1;

void resetColuna(){
    coluna = 1;
}

void addElementoAoLexema(int *sizeLexema, char* lexema, char* elemento){
    *sizeLexema++;
    lexema = realloc(lexema, *sizeLexema * sizeof(char));
    lexema[*sizeLexema-1] = *elemento;
}

typedef struct Token {
    char* nome;
    void* atributo;
    int linha;
    int coluna;
} Token;

void *AFD(char *arquivo, int *i){
    int estado = 0;

    char* lexema;//tudo entre o ini e o prox
    int sizeLexema = 0;

    while(1){
        switch(estado){
            case 0:{
                if(arquivo[*i] >= '0' && arquivo[*i] <= '9'){
                    estado = 1;
                    coluna++;
                    
                }else if((arquivo[*i] >= 'a' && arquivo[*i] <= 'z') || (arquivo[*i] >= 'A' && arquivo[*i] <= 'Z') || (arquivo[*i] == '_')){
                    estado = 2;
                    coluna++;
                    
                }else if((arquivo[*i] == '\'')){
                    estado = 3;
                    coluna++;
                    
                }else if(arquivo[*i] == ' '){
                    estado = 4;
                }
                else if((arquivo[*i] == '\n')){
                    estado = 4;
                    linha ++;
                    resetColuna();
                }
                else if(arquivo[*i] == '\t'){
                    estado = 4;
                    coluna += 4;
                }
                else if((arquivo[*i] == '{')){
                    estado = 5;
                    linha ++;
                    
                }else if((arquivo[*i] == '(')){
                    estado = 6;
                    linha ++;
                    
                }else if((arquivo[*i] == ')')){
                    estado = 7;
                    linha ++;
                    
                }else if((arquivo[*i] == '[')){
                    estado = 8;
                    linha ++;
                    
                }else if((arquivo[*i] == ']')){
                    estado = 9;
                    linha ++;
                    
                }else if((arquivo[*i] == '%')){
                    estado = 10;
                    linha ++;
                    
                }else if((arquivo[*i] == ',')){
                    estado = 11;
                    linha ++;
                    
                }else if((arquivo[*i] == ';')){
                    estado = 12;
                    linha ++;
                    
                }else if((arquivo[*i] == ':')){
                    estado = 13;
                    linha ++;
                    
                }else if((arquivo[*i] == '<')){
                    estado = 14;
                    linha ++;
                    
                }else if((arquivo[*i] == '>')){
                    estado = 15;
                    linha ++;
                    
                }else if((arquivo[*i] == '=')){
                    estado = 16;
                    linha ++;
                    
                }else if((arquivo[*i] == '+')){
                    estado = 17;
                    linha ++;
                    
                }else if((arquivo[*i] == '-')){
                    estado = 18;
                    linha ++;
                    
                }else if((arquivo[*i] == '/')){
                    estado = 19;
                    linha ++;
                    
                }else if((arquivo[*i] == '*')){
                    estado = 20;
                    linha ++;
                    
                }else{
                    return "Simbolo nao reconhecido";
                }

                addElementoAoLexema(sizeLexema, lexema, arquivo[*i]);

                break;
            }
        
            case 1:{
                if(arquivo[*i]>='0' && arquivo[*i]<='9'){
                    estado = 1;

                }else if(arquivo[*i]=='.'){
                    estado = 33;

                }else if(arquivo[*i]=='E'){
                    estado = 31;

                }else{
                    return "Simbolo nao reconhecido";
                }

                addElementoAoLexema(sizeLexema, lexema, arquivo[*i]);

                break;
            }

            case 2:{//estado com lookahead
                if((arquivo[*i] >= '0' && arquivo[*i] <= '9') || (arquivo[*i] >= 'a' && arquivo[*i] <= 'z') || (arquivo[*i] >= 'A' && arquivo[*i] <= 'Z') || (arquivo[*i] == '_')){
                    estado = 2;
                    addElementoAoLexema(sizeLexema, lexema, arquivo[*i]);

                }else{//lexema acabou, de acordo com o lookahead
                    estado = 21;

                    *i--;
                }

                coluna++;

                break;
            }
        
            case 3:{

                if((arquivo[*i] >= 'a' && arquivo[*i] <= 'z') || (arquivo[*i] >= 'A' && arquivo[*i] <= 'Z')){
                    estado = 22;
                }else{
                    return "Simbolo nao reconhecido";
                }

                addElementoAoLexema(sizeLexema, lexema, arquivo[*i]);

                break;
            }
        
            case 4:{//estado com lookahead
                if(arquivo[*i] == ' '){
                    estado = 4;

                    addElementoAoLexema(sizeLexema, lexema, arquivo[*i]);
                }
                else if((arquivo[*i] == '\n')){
                    estado = 4;
                    linha ++;
                    resetColuna();

                    addElementoAoLexema(sizeLexema, lexema, arquivo[*i]);
                }
                else if(arquivo[*i] == '\t'){
                    estado = 4;
                    coluna += 4;

                    addElementoAoLexema(sizeLexema, lexema, arquivo[*i]);
                }else{
                    estado = 46;
                    *i--;
                }

                break;
            }
        
            case 5:{
                if(arquivo[*i] == '#'){
                    estado = 23;
                }else if(arquivo[*i] == '%'){
                    estado = 24;
                }else{
                    return "Simbolo nao reconhecido";
                }

                addElementoAoLexema(sizeLexema, lexema, arquivo[*i]);

                break;
            }
        
            case 6:{//estado final
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                tk->nome = '(';
                tk->atributo = NULL;
                tk->linha = linha;
                tk->coluna = coluna;

                *i--;
                return tk;
            }

            case 7:{//estado final
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                tk->nome = ')';
                tk->atributo = NULL;
                tk->linha = linha;
                tk->coluna = coluna;

                *i--;
                return tk;
            }

            case 8:{//estado final
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                tk->nome = '[';
                tk->atributo = NULL;
                tk->linha = linha;
                tk->coluna = coluna;

                *i--;
                return tk;
            }

            case 9:{//estado final
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                tk->nome = ']';
                tk->atributo = NULL;
                tk->linha = linha;
                tk->coluna = coluna;

                *i--;
                return tk;
            }

            case 10:{
                if(arquivo[*i] == '}'){
                    estado = 25;

                    addElementoAoLexema(sizeLexema, lexema, arquivo[*i]);
                }else{
                    return "Símbolo não reconhecido";
                }

                break;
            }
            
            case 11:{//estado final
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                tk->nome = ',';
                tk->atributo = NULL;
                tk->linha = linha;
                tk->coluna = coluna;

                *i--;
                return tk;
            }

            case 12:{//estado final
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                tk->nome = ';';
                tk->atributo = NULL;
                tk->linha = linha;
                tk->coluna = coluna;

                *i--;
                return tk;
            }

            case 13:{
                if(arquivo[*i] == '=')
                    estado = 41;
                else
                    estado = 42;

                break;
            }

            case 14:{
                if(arquivo[*i] == '>')
                    estado = 44;
                else if(arquivo[*i] == '=')
                    estado = 43;
                else
                    estado = 45;

                break;
            }

            case 15:{
                if(arquivo[*i] == '=')
                    estado = 39;
                else
                    estado = 40;

                break;
            }

            case 16:{//estado final
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                tk->nome = "RELOP";
                tk->atributo = "EQ";
                tk->linha = linha;
                tk->coluna = coluna;

                *i--;
                return tk;
            }

            case 17:{//estado final
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                tk->nome = "aritmetico_3";
                tk->atributo = "SUM";
                tk->linha = linha;
                tk->coluna = coluna;

                *i--;
                return tk;
            }

            case 18:{//estado final
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                tk->nome = "aritmetico_3";
                tk->atributo = "SUB";
                tk->linha = linha;
                tk->coluna = coluna;

                *i--;
                return tk;
            }

            case 19:{//estado final
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                tk->nome = "aritmetico_2";
                tk->atributo = "DIV";
                tk->linha = linha;
                tk->coluna = coluna;

                *i--;
                return tk;
            }

            case 20:{
                if(arquivo[*i] == '*')
                    estado = 26;
                else
                    estado = 27;

                break;
            }

            case 21:{//estado final
                estado = 0;
                Token *tk = malloc(sizeof(Token));

                //tabela de símbolos
                /*
                if (posTS = isinTS(lexema)) != NULL
                    tk->nome = "palavra reservada sla";
                    tk->atributo = valor da TS;
                else
                    pos = addinTS(lexema)
                    tk->nome = "ID"
                    tk->atributo = pos;
                */

                *i--;
                return tk;
            }

            case 22:{
                if(arquivo[*i] == '=')
                    estado = 28;
                else
                    return "Símbolo não reconhecido";
                
                break;
            }

            case 23:{
                if(arquivo[*i] == '#')
                    estado = 29;
                else
                    estado = 23;
                
                break;
            }

            case 24:{//estado final
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                tk->nome = '{%';
                tk->atributo = NULL;
                tk->linha = linha;
                tk->coluna = coluna;

                *i--;
                return tk;
            }

            case 25:{//estado final
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                tk->nome = '%}';
                tk->atributo = NULL;
                tk->linha = linha;
                tk->coluna = coluna;

                *i--;
                return tk;
            }

            case 26:{//estado final
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                tk->nome = "aritmetico_1";
                tk->atributo = "EXP";
                tk->linha = linha;
                tk->coluna = coluna;

                *i--;
                return tk;
            }

            case 27:{//estado final
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                tk->nome = "aritmetico_2";
                tk->atributo = "MUL";
                tk->linha = linha;
                tk->coluna = coluna;

                *i--;
                return tk;
            }

            case 28:{//estado final
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                
                /*
                if  (posTS = isinTS(lexema)) != NULL
                    tk->nome = "const_char";
                    tk->atributo = posTS;
                else
                    pos = addinTS(lexema)
                    tk->nome = "const_char"
                    tk->atributo = pos;
                */
                tk->linha = linha;
                tk->coluna = coluna;

                *i--;
                return tk;
            }

            case 29:{
                if(arquivo[*i] == '}')
                    estado = 30;
                else
                    estado = 23;
                
                break;
            }

            case 30:{//estado final
                estado = 0;

                //é um prox_token()
                lexema = NULL;
                sizeLexema = 0;

                *i--;
                break;
            }

            case 31:{
                if(arquivo[*i] >= '0' && arquivo[*i] <= '9')
                    estado = 37;
                else if(arquivo[*i] == '+' || arquivo[*i] == '-')
                    estado = 36;
                else 
                    return "Simbolo não reconhecido";
            
                break;
            }

            case 32:{//estado final//constnum
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                
                /*
                if  (posTS = isinTS(lexema)) != NULL
                    tk->nome = "const";
                    tk->atributo = posTS;
                else
                    pos = addinTS(lexema)
                    tk->nome = "const"
                    tk->atributo = pos;
                */
                tk->linha = linha;
                tk->coluna = coluna;

                *i--;
                return tk;
            }

            case 33:{
                if(arquivo[*i] >= '0' && arquivo[*i] <= '9')
                    estado = 34;
                else
                    return "Símbolo não reconhecido";
                
                break;
            }

            case 34:{
                if(arquivo[*i] >= '0' && arquivo[*i] <= '9')
                    estado = 34;
                else if(arquivo[*i] == 'E')
                    estado = 31;
                else if((arquivo[*i] >= 'a' && arquivo[*i] <= 'z') || (arquivo[*i] >= 'A' && arquivo[*i] <= 'Z') || (arquivo[*i] == '_'))
                    estado = 35;

                break;
            }

            case 35:{//estado final//constnum
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                
                /*
                if  (posTS = isinTS(lexema)) != NULL
                    tk->nome = "const";
                    tk->atributo = posTS;
                else
                    pos = addinTS(lexema)
                    tk->nome = "const"
                    tk->atributo = pos;
                */
                tk->linha = linha;
                tk->coluna = coluna;

                *i--;
                return tk;
            }

            case 36:{
                if(arquivo[*i] >= '0' && arquivo[*i] <= '9')
                    estado = 37;
                break;
            }

            case 37:{
                if(arquivo[*i] >= '0' && arquivo[*i] <= '9')
                    estado = 37;
                else
                    estado = 38;
                break;
            }

            case 38:{//estado final//constnum
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                
                /*
                if  (posTS = isinTS(lexema)) != NULL
                    tk->nome = "const";
                    tk->atributo = posTS;
                else
                    pos = addinTS(lexema)
                    tk->nome = "const"
                    tk->atributo = pos;
                */
                tk->linha = linha;
                tk->coluna = coluna;

                *i--;
                return tk;
            }

            case 39:{//estado final
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                tk->nome = "RELOP";
                tk->atributo = "LQ";
                tk->linha = linha;
                tk->coluna = coluna;

                *i--;
                return tk;
            }

            case 40:{//estado final
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                tk->nome = "RELOP";
                tk->atributo = "GT";
                tk->linha = linha;
                tk->coluna = coluna;

                *i--;
                return tk;
            }

            case 41:{//estado final
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                tk->nome = ':=';
                tk->atributo = NULL;

                *i--;
                return tk;
            }

            case 42:{//estado final
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                tk->nome = ':';
                tk->atributo = NULL;

                *i--;
                return tk;
            }

            case 43:{//estado final
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                tk->nome = "RELOP";
                tk->atributo = "LE";
                tk->linha = linha;
                tk->coluna = coluna;

                *i--;
                return tk;
            }

            case 44:{//estado final
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                tk->nome = "RELOP";
                tk->atributo = "NE";
                tk->linha = linha;
                tk->coluna = coluna;

                *i--;
                return tk;
            }

            case 45:{//estado final
                estado = 0;
                Token *tk = malloc(sizeof(Token));
                tk->nome = "RELOP";
                tk->atributo = "LT";
                tk->linha = linha;
                tk->coluna = coluna;

                *i--;
                return tk;
            }
            
            case 46:{//estado final
                estado = 0;
                
                lexema = NULL;
                sizeLexema = 0;

                *i--;
                break;
            }
        }

        *i++;
    }

    return -1;
}

void main(){
    //mostrar erro:
    //printf("Na linha %d, coluna %d: %s",linha, coluna, AFD(""));
}