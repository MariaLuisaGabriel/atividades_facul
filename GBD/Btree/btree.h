#ifndef _BTREE_H
#define _BTREE_H

#include <stdio.h>
#include <queue>

/*
 * Definicao da ordem da arvore
 */
#define ORDEM 3

/*
 * Definicao da estrutura de dados do cabecalho. Um objetivo do cabecalho é guardar qual o numero da pagina raiz da arvore
 */
struct cabecalhoB
{
    int paginaRaiz;      // numero da pagina raiz da arvore
    int alturaArvore;    // altura da arvore
    int numeroElementos; // numero de chaves armazenadas na arvore
    int numeroPaginas;   // numero de paginas da arvore
};
typedef struct cabecalhoB cabecalho;
/*
 * Definicao da estrutura de dados das ç~paginas da arvore
 */
struct paginaB
{
    int numeroElementos; // numero de elementos na pagina
    int numeroPagina;    // vamos guardar o numero da pagina dentro da propria pagina
    int chaves[ORDEM];
    int ponteiros[ORDEM+1];
};
typedef struct paginaB pagina;

struct splitNode
{
    int median; // numero de elementos na pagina
    int numPageLeft;
    int numPageRight;
};
// typedef struct splitNode splitN;

class btree
{
public:
    /*
     * Construtor. Abre arquivo de indice.
     */
    btree();

    /*
     * Destrutor. Fecha arquivo de indice.
     */
    virtual ~btree();

    /*
     * Insere par chave e valor para o registro na árvore
     * Tarefas:
     * - localizar pagina para inserir registro
     * - inserir ordenado na pagina
     * - atualizar numeroElementos na pagina
     * - atualizar recursivamente as páginas ancestrais
     */
    void insereChave(int chave, int valor);

    /*
     * Remove par chave e offset.
     * Tarefas:
     * - localizar pagina para remover registro
     * - inserir ordenado na pagina
     * - atualizar numeroElementos na pagina
     * - atualizar recursivamente as páginas ancestrais
     */
    void removeChave(int chave);

    /*
     * Busca chave e retorna o offset. Retorna -1 caso nao encontre a chave
     * Tarefas:
     * - localizar pagina
     * - retorna offset
     */
    int buscaChave(int chave);

    /*
     * Retorna numero de elementos armazenado no cabecalho da arvore
     */
    int getNumeroElementos() { return cabecalhoArvore.numeroElementos; }

    /*
     * Retorna altura da arvore armazenada no cabecalho da arvore
     */
    int getAlturaArvore() { return cabecalhoArvore.alturaArvore; }

    /*
     * Retorna o numero medio de elementos por pagina da arvore. Considerar apenas paginas folha
     */
    int computarTaxaOcupacao();

    /*
     * Mostra a árvore
     */
    void printBTree()
    {
        std::queue<int> paginasPorNivel;
        int nivel,num=0,aux;
        pagina *p = lePagina(cabecalhoArvore.paginaRaiz);
        printf("lv 1, raíz: %d & %d, ",p->numeroElementos,p->numeroPagina);
        for(int i = 0; i<p->numeroElementos; i++){
            printf("%d ",p->chaves[i]);
        }
        for(int i = 0; i<p->numeroElementos+1; i++){
            paginasPorNivel.push(p->ponteiros[i]);
            num++;
        }
        for(nivel = 2; nivel <= cabecalhoArvore.alturaArvore; nivel++){
            int num2 = 0;
            printf("lv %d, pags: ",nivel);

            for(;num>0;num--){
                aux = paginasPorNivel.front();
                paginasPorNivel.pop();
                p = lePagina(aux);
                printf("\n->%d, %d: ", aux, p->numeroElementos);
                for(int i = 0; i<p->numeroElementos; i++){
                    printf("%d ",p->chaves[i]);
                }

                if(nivel!=cabecalhoArvore.alturaArvore){
                    for(int i = 0; i<p->numeroElementos+1; i++){
                        paginasPorNivel.push(p->ponteiros[i]);
                        num2++;
                    }
                }
            }

            num = num2;
        }   
    }

private:
    /*
     * Cabecalho da arvore
     */
    cabecalho cabecalhoArvore;

    /*
     * Instancia para ler uma pagina
     */
    pagina paginaAtual;

    /*
     * Manipulador do arquivo de dados
     */
    FILE *arquivo;

    /*
     * Criaçao de uma nova pagina. Parametro com numero da pagina deve ser passado por referencia (exemplo: int idpagina;
     * btree->novaPagina(&idpagina);) pois no retorno da funçao o idpagina tera o numero da nova pagina.
     */
    pagina *novaPagina(int *idPagina)
    {
        pagina *pg = new pagina;
        pg->numeroElementos = 0;
        fseek(arquivo, 0, SEEK_END);
        fwrite(pg, sizeof(pg), 1, arquivo);
        leCabecalho();
        cabecalhoArvore.numeroPaginas++;
        salvaCabecalho();
        pg->numeroPagina = cabecalhoArvore.numeroPaginas;
        idPagina[0] = cabecalhoArvore.numeroPaginas;
        return pg;
    }

    splitNode *insereRecursivo(int chave, int valor, int paginaD, int nivel, pagina *pai);

    /*
     * Leitura de uma pagina existente.
     */
    pagina *lePagina(int idPagina)
    {
        pagina *pg = new pagina;
        fseek(arquivo, sizeof(cabecalhoArvore) + (idPagina - 1) * sizeof(pagina), SEEK_SET);
        fread(pg, sizeof(pagina), 1, arquivo);
        return pg;
    }

    /*
     * Persistencia de uma pagina.
     */
    void salvaPagina(int idPagina, pagina *pg)
    {
        fseek(arquivo, sizeof(cabecalhoArvore) + (idPagina - 1) * sizeof(pagina), SEEK_SET);
        fwrite(pg, sizeof(pagina), 1, arquivo);
    }

    /*
     * Salva o cabecalho
     */
    void salvaCabecalho()
    {
        fseek(arquivo, 0, SEEK_SET);
        fwrite(&cabecalhoArvore, sizeof(cabecalhoArvore), 1, arquivo);
    }

    /*
     * Le o cabecalho
     */
    void leCabecalho()
    {
        fseek(arquivo, 0, SEEK_SET);
        fread(&cabecalhoArvore, sizeof(cabecalhoArvore), 1, arquivo);
    }
};

#endif /* _BTREE_H */
