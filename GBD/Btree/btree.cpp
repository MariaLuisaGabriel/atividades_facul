#include <sys/types.h>
#include <sys/stat.h>
#include <bits/stdc++.h>
#include <algorithm>
#include <math.h>
#include "btree.h"
using namespace std;

#ifndef _BTREE_CPP
#define _BTREE_CPP

bool fileExists(const char *filename)
{
    struct stat statBuf;
    if (stat(filename, &statBuf) < 0)
        return false;
    return S_ISREG(statBuf.st_mode);
}

btree::btree()
{
    char nomearquivo[20] = "arvoreb.dat";

    // se arquivo ja existir, abrir e carregar cabecalho
    if (fileExists(nomearquivo))
    {
        // abre arquivo
        arquivo = fopen(nomearquivo, "r+");
        leCabecalho();
    }
    // senao, criar novo arquivo e salvar o cabecalho
    else
    {
        // cria arquivo
        arquivo = fopen(nomearquivo, "w+");

        // atualiza cabecalho
        cabecalhoArvore.paginaRaiz = 0;
        cabecalhoArvore.alturaArvore = 0;
        cabecalhoArvore.numeroElementos = 0;
        cabecalhoArvore.numeroPaginas = 0;
        salvaCabecalho();
    }
}

btree::~btree()
{
    // fechar arquivo
    fclose(arquivo);
}

int btree::computarTaxaOcupacao()
{
    return 0;
}

void btree::insereChave(int chave, int valor)
{
    insereRecursivo(chave, valor, cabecalhoArvore.paginaRaiz, 1, NULL);
}

splitNode *btree::insereRecursivo(int chave, int valor, int paginaD, int nivel, pagina *pai)
{
    if(pai!=NULL){
    printf("\n\n===============%d/%d, pai: %d==================\n\n",nivel,cabecalhoArvore.alturaArvore,pai->numeroPagina);
    }
    // printf("enter\n");
    // printf("paginaD: %d\n", paginaD);
    splitNode *split = NULL;
    int pageToRead = paginaD;

    printf("A");
    // /// verificar se raiz existe!
    if (cabecalhoArvore.paginaRaiz == 0)
    {
        //printf("Creating header\n");
        pagina *pg = new pagina;
        pg = novaPagina(&cabecalhoArvore.paginaRaiz);
        //printf("Page: %d\n", pg->numeroPagina);
        //printf("Elements: %d\n", pg->numeroElementos);
        for (int i = 0; i < ORDEM; i++)
        {
            pg->chaves[i] = 0;
            pg->ponteiros[i] = 0;
        }

        salvaPagina(pg->numeroPagina, pg);
        leCabecalho();
        cabecalhoArvore.paginaRaiz++;
        cabecalhoArvore.alturaArvore = 1;
        salvaCabecalho();
        pageToRead = pg->numeroPagina;
    }

    printf("A");
    // /// chamada recursiva incrementando nível até chegar na folha (quando nivel == cabecalho.alturaArvore)
    if (nivel != cabecalhoArvore.alturaArvore)
    {
        //para inserir a chave no local certo, é necessário achar a página certa!
        pagina *p = lePagina(paginaD);
        int m;

        for(m = 0; chave<p->chaves[m] && m<p->numeroElementos; m++);
            //a chave i está entre os ponteiros i e i+1
            //caso a chave seja menor que a chave analisada atualmente, quer dizer que 
            //aquela chave deve ser inserida numa página que possui valores menores
            // p0 k0 p1:
            //vai para p0 se chave>k0, e vai para p1 caso chave<k0
            printf("\n%d\n",p->ponteiros[m]);
        //printf("\n%d,%d\n",p->numeroPagina,cabecalhoArvore.paginaRaiz);

        split = insereRecursivo(chave, valor, p->ponteiros[m], nivel + 1, p);
        if (split == NULL)
            return split;
    }

    pagina *pg = lePagina(paginaD);

    printf("A, %d",pg->numeroElementos);
    // Split Logic
    if((pg->numeroElementos + 1) > ORDEM){
        printf("A A A A A");
        printf("\n===page full:");
        pagina *p = lePagina(paginaD);
        printf("\n===%d,%d===",p->numeroPagina,p->numeroElementos);
        printf("\naaaaa");
        int median = (int)floor((p->numeroElementos-1)/2);
        int medNextIdx = (int)floor((ORDEM-1)/2.0) + 1;
        printf("\nasdfj");
        int med = p->chaves[median];
        printf("\nmedian: %d",med);
        int idx;
        printf("\n??????????");
        //tira o elemento med da pagina
        for(idx = medNextIdx; idx < ORDEM; idx++){
            (*p).chaves[idx-1] = (*p).chaves[idx];
        }
        printf("\na");
        (*p).numeroElementos--;
        printf("\na\n");
        int *id;
        printf("\na");
        pagina *aux = novaPagina(id);
        pagina right = *aux;
        aux = NULL;
        printf("\na");
        //copiar os dados da página com overflow, mas com um número de página diferente
        aux = novaPagina(id);
        pagina left = *aux;
        left = *p;
        left.numeroPagina = *id;
        printf("\na");
        //divide as chaves da página com overflow entre as novas páginas: right e left
        for(idx = medNextIdx-1; idx < ORDEM-1;  idx++){ 
            right.chaves[idx - medNextIdx +1] = left.chaves[idx];
            right.numeroElementos++;
            left.numeroElementos--;
        }
        printf("\na");
        split = new splitNode;
        split->median = median;
        split->numPageLeft = left.numeroPagina;
        split->numPageRight = right.numeroPagina;
        printf("\na");
        //divide os ponteiros da página com overflow entre as novas páginas: right e left
        for(idx = medNextIdx; idx <= ORDEM; idx++){
            right.ponteiros[idx - medNextIdx] = left.ponteiros[idx];
            left.ponteiros[idx] = -1;
        }
        printf("\na");
        printf("\nok????");
        printf("\na");
        if(pai == NULL){
            // Nao tem pai, quer dizer que é a raíz que está com overflow
            pai = novaPagina(&(cabecalhoArvore.paginaRaiz)); //pai é salvo no local da antiga raíz
            pai->numeroElementos = 0;
            (*pai).ponteiros[0] = left.numeroPagina;
            (*pai).ponteiros[1] = right.numeroPagina;
            (*pai).chaves[0] = med;
            (*pai).numeroElementos++;
            salvaPagina(left.numeroPagina, &left);//possui numero de página novo
            salvaPagina(right.numeroPagina, &right);//possui numero de página novo
            salvaPagina(cabecalhoArvore.paginaRaiz, pai);//deve possuir o numero de página da raíz antiga
            cabecalhoArvore.alturaArvore++;
            salvaCabecalho();
            insereRecursivo(chave,0,cabecalhoArvore.paginaRaiz,1,NULL);
            printf("\n\n");
            printBTree();
            return NULL;
        }
        else{
            printf("\n===pai existe!!!!===%d,%d",pai->numeroElementos,pai->numeroPagina);
            printf("\na");
        if((*pai).numeroElementos + 1 <= ORDEM) { //pai tem espaço pra inserir elementos
            // Insere no pai
            //acha qual a posição que med deve se encaixar em pai
            printf("\n===pai existe!!!!===");
            for (idx = (*pai).numeroElementos; med > (*pai).chaves[idx] && idx < 0; idx--);
        
            int idx2;
            for (idx2 = (*pai).numeroElementos; idx2 > idx; idx2--) {
                (*pai).chaves[idx2] = (*pai).chaves[idx2-1];
            }
            (*pai).chaves[idx] = med;
            (*pai).numeroElementos++;

            for (idx2 = (*pai).numeroElementos; idx2 > idx+1; idx2--) {
                (*pai).ponteiros[idx2] = (*pai).ponteiros[idx2-1];
            }
            (*pai).ponteiros[idx+1] = right.numeroPagina;

            salvaPagina(left.numeroPagina, &left);
            salvaPagina(right.numeroPagina, &right);
            cabecalhoArvore.numeroElementos++;
            salvaCabecalho();

            printf("\npai: ");
            printf(" %d, %d\n",pai->numeroElementos,pai->chaves[idx]);
            //for(int i = 0; i<pai->numeroElementos;i++){
            //    printf(" %d",pai->chaves[i]);
            //}

            //insereRecursivo(chave,0,cabecalhoArvore.paginaRaiz,1,NULL);

            return NULL;

        }/*else if((*pai).numeroElementos + 1 > ORDEM) { //se fizer split no filho, o pai entra em overflow
            //1º: faz split no filho
            //...
            pagina *p = lePagina(paginaD);
            int median = (int)floor((p->numeroElementos-1)/2);
            int medNextIdx = (int)floor((ORDEM-1)/2.0) + 1;

            int med = p->chaves[median];
            int idx;

            //tira o elemento med da pagina
            for(idx = medNextIdx; idx < ORDEM; idx++){
            (*p).chaves[idx-1] = (*p).chaves[idx];
            }
            (*p).numeroElementos--;

            pagina right = *novaPagina(NULL);

            //copiar os dados da página com overflow, mas com um número de página diferente
            pagina left = *novaPagina(NULL);
            int aux = left.numeroPagina;
            left = *p;
            left.numeroPagina = aux;

            //divide as chaves da página com overflow entre as novas páginas: right e left
            for(idx = medNextIdx-1; idx < ORDEM-1;  idx++){ 
                right.chaves[idx - medNextIdx +1] = left.chaves[idx];
                right.numeroElementos++;
                left.numeroElementos--;
            }

            split = new splitNode;
            split->median = median;
            split->numPageLeft = left.numeroPagina;
            split->numPageRight = right.numeroPagina;

            //divide os ponteiros da página com overflow entre as novas páginas: right e left
            for(idx = medNextIdx; idx <= ORDEM; idx++){
                right.ponteiros[idx - medNextIdx] = left.ponteiros[idx];
                left.ponteiros[idx] = 0;
            }

            salvaPagina(left.numeroPagina, &left);
            salvaPagina(right.numeroPagina, &right);

            printf("\nright:");
            for(int i = 0; i<right.numeroElementos; i++){
                printf(" %d",right.chaves[i]);
            }

            printf("\nleft:");
            for(int i = 0; i<left.numeroElementos; i++){
                printf(" %d",left.chaves[i]);
            }

            printf("\npai:");

            //fez o split do filho, faz inserção da chave na página certa
            insereChave(chave,0);

            //2º trigger split do pai, inserindo o med
            insereChave(med, 0);
        }*/
        }
    }
    else
    { //page is not full
        printf("\n===page not full:");
        pg->chaves[pg->numeroElementos] = chave;
        pg->numeroElementos++;
        sort(pg->chaves, pg->chaves + pg->numeroElementos, greater<int>());
        for(int i = 0; i<pg->numeroElementos;i++){
            printf(" %d",pg->chaves[i]);
        }

        /*if(pai!=NULL){
        printf(" pai: ");
        printf(" %d, ",pai->numeroElementos);
        for(int i = 0; i<pai->numeroElementos;i++){
            printf(" %d",pai->chaves[i]);
        }
        }*/
        printf("===\n");
        cabecalhoArvore.numeroElementos++;
        
        salvaPagina(pg->numeroPagina, pg);

        printBTree();
    }

    // z = INTEIRO(ORDEM/2)
    // pg->chaves[z]
    // pg->chaves[z]
    // y = novaPagina(0:esqZ)
    // ofset da pagina de z apontando para y
    // p = novaPagina(z+1:dirZ)
    // ofset da pagina de z apontando para p
    // limpar todos os valores da pagina de z setando para 0 menos z

    // // 1) chave/valor inserido na pagina sem alterar maior valor da página
    // 2) chave/valor inserido na pagina e novo maior valor da página é a chave inserida
    // 3) overflow, divisão da pagina, para a página existente atualizar a maior chave e para
    //    a nova pagína, armazenar o identificador da página e a maior chave

    // se inserir, atualizar cabecalho
    salvaCabecalho();

    return split;
}

void btree::removeChave(int chave)
{

    // se remover, atualizar cabecalho
    if (true)
    {
        cabecalhoArvore.numeroElementos--;
        salvaCabecalho();
    }
}

int btree::buscaChave(int chave)
{
    // caso não encontrar chave, retornar -1
    return -1;
}

#endif /* _BTREE_CPP */
