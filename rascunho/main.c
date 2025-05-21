#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAMANHO 10000000

typedef struct registro { unsigned long chave; char nome[100]; time_t nascimento; } registro;

/*
  Integrantes do Grupo:
  Geraldo Rodrigues de Melo Neto Nº12121BCC008
  Maria Luisa Gabriel Domingues Nº12121BCC010
  Pedro de Araujo Ribeiro Nº12121BCC002
*/

char nomes[60][20] = {"Abner","Ana","Anderson","Antonio","Arthur","Augusto","Beatriz","Brendo","Caio","Carla","Carlos","Clara","Claudia","Claudio","Enzo","Ernani","Fabiana","Felipe","Fernanda","Fernando","Flavia","Flavio","Frederico","Gabriel","Geraldo","Geraldo","Giovanna","Graziela","Guilherme","Gustavo","Henrique","Hugo","Humberto","Joao","Jose","Julia","Laylla","Lucas","Luisa","Luiz","Luiza","Manoela","Marcela","Marcelo","Marcus","Maria","Marques","Matheus","Pacheco","Pedro","Rafael","Renata","Thiago","Valter","Victor","Vinicius","Vinicius","Vitor","Wallace","Yuri"};
char sobrenomes[60][20] = {"Almeida","Alves","Amorim","Andrade","Araujo","Borges","Chagas","Corsi","Cunha","Custodio","Domingues","Duarte","Faria","Farias","Ferreira","Florencio","Fontes","Franco","Freitas","Gastao","Godoi","Gomes","Goulart","Gouveia","Graciano","Guimaraes","Ignacio","Lazzarini","Lima","Macarini","Macedo","Matos","Martins","Matias","Melo","Meres","Nunes","Oliveira","Otoni","Paula","Pereira","Pinheiro","Pinho","Pio","Pontes","Prado","Reis","Ribeiro","Rocha","Rodrigues","Royer","Silva","Siqueira","Soares","Souza","Sticca","Ventino","Ventura","Vezono"};

void troca(int *V, int pivo, int i) {
    int aux = V[i];
    V[i] = V[pivo];
    V[pivo] = aux;
}
int particao(int *v, int esq, int dir, FILE *f) {
    int i, fim;
    registro r, r2;
    fim = esq;
    fseek(f, esq * sizeof(registro), SEEK_SET);
    fread(&r, sizeof(registro), 1, f);
    for (i = esq + 1; i <= dir; i++) {
        fseek(f, i * sizeof(registro), SEEK_SET);
        fread(&r2, sizeof(registro), 1, f);
        if (strcmp(r2.nome, r.nome) < 0) {
            fim++;
            troca(v, fim, i);
        }
    }
    troca(v, esq, fim);
    return fim;
}

void quicksort(int *v, int esq, int dir, FILE *f) {
    int i;
    if (esq >= dir)
        return;
    i = particao(v, esq, dir,f);
    quicksort(v, esq, i-1,f);
    quicksort(v, i+1, dir,f);
}

void buscaBin(char nome[],int n, FILE *fd, FILE *fi){
    int inicio = 0, fim = n, pos;
    registro r;
    int key, resCmp;

    while(inicio<fim){
        pos = (inicio+fim)/2;

        //busca pelo índice central da ordenação
        fseek(fi,pos*sizeof(int),SEEK_SET);
        fread(&key,sizeof(int),1,fi);

        //busca pelo nome que o índice referencia
        fseek(fd,key*sizeof(registro),SEEK_SET);
        fread(&r,sizeof(registro ),1,fd);

        resCmp = strcmp(r.nome,nome);

        if(resCmp == 0){
            printf("\n%s\n",r.nome);
            return;
        }
        else if(resCmp > 0){
            fim = pos;
        }
        else inicio = pos+1;
    }
    printf("Nome não encontrado\n");
}

void gera_vet(){
    int *pos = (int *)malloc(TAMANHO * sizeof(int));
    registro r;
    FILE *f = fopen("dados.bin","rb+");
    for(int i = 0; i < TAMANHO; i++){
        pos[i] = i;
    }
    printf("\nQUICKSORT==============================\n");
    quicksort(pos,0,TAMANHO-1,f);
    fclose(f);
    /*
    for(int i = 0; i < 1000; i++){
        printf("%d ", pos[i]);
    }
    */
    FILE *f2 = fopen("indice.bin","wb+");
    for(int i = 0; i < TAMANHO; i++){
        if(i%10==0) printf("%d%\n",i);
        fwrite(&pos[i], sizeof(int), 1, f2);
    }
    fclose(f2);
}

void novo_nome(char *str) {
   int posicao = rand() % 60;
   strcpy(str,nomes[posicao]); // primeiro nome
   strcat(str," ");
   int segundonome = rand() % 2;
   if (segundonome == 1) {
       posicao = rand() % 60;
       strcat(str,nomes[posicao]); // segundo nome
       strcat(str," ");
   }
   int quantidade = rand() % 3 + 1;
   for (int i = 0; i < quantidade; i++) {
       posicao = rand() % 60;
       strcat(str,sobrenomes[posicao]); // sobrenomes
       if (i < quantidade-1)
           strcat(str," ");
   }
}

void novo_nascimento(time_t *data) {
    time(data); // data corrente
    int dia = rand() % 18250; // um dia nos últimos 50 anos
    *data -= (dia * 24 * 60 * 60);
}

/*
int main() {
    srand(time(NULL));

    int numregistros = 10000000;
    printf("Tamanho do registro: %d bytes\n", sizeof(registro));
    printf("Numero de registros: %d\n", numregistros);
    printf("Tamanho do arquivo: %d bytes (%.1f Mbytes)\n", sizeof(registro) * numregistros, (sizeof(registro) * numregistros) / (float)(1024*1024));

    registro r;
    FILE *f = fopen("dados.bin","wb+");
    for (int i = 1; i <= numregistros; i++) {
        r.chave = i;
        novo_nome(r.nome);
        novo_nascimento(&r.nascimento);
        fwrite(&r, sizeof(r), 1, f);
        if ((i + 1) % (numregistros/10) == 0) printf("\n%.0f%%",((i + 1)/(float)numregistros)*100.0);
        //struct tm * t = localtime(&r.nascimento);
        //printf("%s %d/%d/%d %s", r.nome, t->tm_mday, t->tm_mon+1, t->tm_year+1900, ctime(&r.nascimento));
    }
    fclose(f);

    return 0;
}*/

int main() {
    char nome[100];
    registro r;
    gera_vet();
    clock_t start=0, end=0;
    double tempo;
    FILE *fd = fopen("dados.bin", "rb+");
    FILE *aux = fopen("dados.bin", "rb+");
    FILE *fi = fopen("indice.bin", "rb+");
    
    for(int ii = 0;ii<1000;ii++) {
        //fread(&r,sizeof(registro),1,aux);
        printf("%d/10\n", ii);
        //novo_nome(nome);
        //printf("%s\n", r.nome);
        start = clock();
        buscaBin(nome, TAMANHO, fd, fi);
        end = clock();
        tempo = ((end - start) / (double) CLOCKS_PER_SEC);
        printf("Busca binária: %f\n", tempo);
    }

    for(int ii = 0;ii<1000;ii++){
        fread(&r,sizeof(registro),1,aux);
        printf("%s\n", r.nome);
    }

    fclose(fd);
    fclose(fi);
    fclose(aux);
    return 0;
}

/*
Iteração1:


Iteração2:


Iteração3:


Iteração4:


Iteração5:


Iteração6:


Iteração7:


Iteração8:


Iteração9:


Iteração10:


Média de 10000 iterações:

*/