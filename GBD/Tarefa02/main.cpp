#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

using namespace std;

/*PARTE 1 DA TAREFA:

verificada a troca do número 31 por outro primo, 41, na função hash gerou resultados catastróficos:
quase todas as strings se concentraram num mesmo bucket (bucket 95), enquanto com hashing ainda usando 31 como valor da base
da potência, houve melhor distribuição.
*/
#define TAM_HISTOGRAMA 100

int getHash31(char *str) {
    // implementar funcao hash para distribuir strings com uniformidade e aleatoriedade
    int sum = 0;
    int length = strlen(str);
    for(int i = 0; i<length; i++){
        sum += str[i]*pow(31,length-(i+1));
    }
    return sum%TAM_HISTOGRAMA;
}

int getHash41(char *str) {
    // implementar funcao hash para distribuir strings com uniformidade e aleatoriedade
    int sum = 0;
    int length = strlen(str);
    for(int i = 0; i<length; i++){
        sum += str[i]*pow(41,length-(i+1));
    }
    return sum%TAM_HISTOGRAMA;
}

/*PARTE 2 DA TAREFA:

A quantidade de buckets deve ser definida pelo tamanho máximo oferecido pelo arquivo,
dividido pelo tamanho máximo que cabe em cada bucket.

tamanho máximo oferecido pelo arquivo: ~7 milhões de strings com 200 caracteres (1.400.000.000)
tamanho máximo do bucket: 200 strings com 200 caracteres (40.000)
numero de buckets: 1400000000/40000 = 35.000

com 35.000 buckets, são necessários 16 bits (no mínimo) para armazenamento de index dos buckets
são 2^16 entradas no diretório
*/
#define TAM_HISTOGRAMA2 35000

unsigned int getHash(char *str) {
    // implementar funcao hash para distribuir strings com uniformidade e aleatoriedade
    unsigned int sum = 0;
    unsigned int length = strlen(str);
    for(int i = 0; i<length; i++){
        sum += str[i]*pow(31,length-(i+1));
    }
    return sum%TAM_HISTOGRAMA2;
}

int main() {
    FILE *f = fopen("dblp.txt","rb");
    if (f == NULL) {
        printf("Sinto muito, nao consegui abrir arquivo de dados.");
        return 0;
    }

    srand (time(NULL));
    char linha[1024];

    // vetor que armazenara histograma de contagem
    unsigned int histograma[TAM_HISTOGRAMA2];
    for (unsigned int i = 0; i < TAM_HISTOGRAMA2; i++)
        histograma[i] = 0;

    while (true) {
        // ler linha
        fgets(linha,200,f);
        if (feof(f))
            break;

        // computar hash e atualizar contagem no histograma
        unsigned int hash = getHash(linha);
        histograma[hash]++;
        //printf("%d\n",hash);
    }
    fclose(f);

    for(int i = 0;i<TAM_HISTOGRAMA2;i++)
        {
            if(histograma[i]>200) printf("bucket %d com estouro de %d;\n",i,histograma[i]);
        }

    // criar grafico de contagem do hash
    FILE *grafico = fopen("grafico.plt","wb");
    fprintf(grafico,"# executar esse arquivo com GNUPLOT\n");
    fprintf(grafico,"# http://www.gnuplot.info/download.html\n");
    fprintf(grafico,"# no linux: gnuplot grafico.plt\n");
    fprintf(grafico,"# no windows: wgnuplot grafico.plt\n");
    fprintf(grafico,"set title \"Histograma\"\n");
    fprintf(grafico,"set encoding iso_8859_1\n");
    fprintf(grafico,"set xlabel \"Hash\"\n");
    fprintf(grafico,"set ylabel \"Quantidade\"\n");
    fprintf(grafico,"plot '-' title 'Quantidade' with linespoints linewidth 2 linetype 1 pointtype 1\n");
    for (int i = 0; i < TAM_HISTOGRAMA2; i++)
        fprintf(grafico,"%d %d\n",i,histograma[i]);
    fprintf(grafico,"end\n");
    fprintf(grafico,"pause -1\n");
    fclose(grafico);

    printf("\n\nThat's all, folks!\n\n");

    return 0;
}