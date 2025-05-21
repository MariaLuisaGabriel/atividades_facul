/*
 * ALUNO: COLOQUE SEU NOME AQUI
 * File:   main.cpp
 */

#include <stdlib.h>
#include <time.h>
#include <cstdio>

#include "btree.h"

int main(int argc, char **argv)
{

    // iniciar a semente aleatoria
    srand(time(NULL));

    remove("arvoreb.dat");

    // criar arvore b
    btree *arvore = new btree();

    //printf("Use essas chaves como exemplos de consultas que devem ser encontradas: ");

    // inserir numeros aleatorios na arvore
    /*for (int i = 0; i < 3; i++)
    {
        int valor = rand() % 1000000 + 1;
        // printf("VALOR %d\n", i);
        arvore->insereChave(valor, valor + 1);
        //if (i % 1000 == 0)
            printf("%d, ", valor);
    }*/

    // arvore->insereChave(12, 32);

    int opcao = 0;
    while (opcao != 4)
    {
        printf("\n\nEstatisticas:\n");
        printf("Numero de elementos: %d\n", arvore->getNumeroElementos());
        printf("Altura da arvore: %d\n", arvore->getAlturaArvore());
        printf("\n\nMenu: 1-inserir 2-remover 3-consultar 4-sair: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
            int valor, offset;
        case 1:
            printf("\nInsere chave: ");
            scanf("%d", &valor);
            arvore->insereChave(valor, valor);

            //arvore->printBTree();
            break;
        case 2:
            printf("\nRemove chave: ");
            scanf("%d", &valor);
            arvore->removeChave(valor);
            break;
        case 3:
            printf("\nConsulta chave: ");
            scanf("%d", &valor);
            offset = arvore->buscaChave(valor);
            if (offset == -1)
                printf("\nChave %d nao encontrada.\n", valor);
            else
                printf("\nChave %d encontrada e offset=%d.\n", valor, offset);
            break;
        case 4:
            // exit :-)
            break;
        default:
            opcao = 0;
            break;
        }
    }

    delete arvore;

    return (EXIT_SUCCESS);
}
