/* Programa: Exemplo

   Autor: Gabriel Bianchi e Silva
   
   Versao: 1.0 - 11/10/2019
*/

// ##################### Bibliotecas Externas ##############################

#include <stdio.h>
#include <stdlib.h>

// ########################## TAD X.h ######################################

typedef struct
{
    int primeiro;
    int tamanho;
    int ultimo;
    int elementos[100];
} Fila;

void iniciaFila(Fila *teste)
{
    int i;
    teste->primeiro = -1;
    teste->tamanho = 0;
    teste->ultimo = -1;
    for (i = 0; i < 100; i++)
    {
        teste->elementos[i] = 0;
    }
}

// ###################### Funcoes e Procedimentos do programa ##############

int vazia(Fila *teste)
{
    if (teste->tamanho == 0)
    {
        return 1; //vazia
    }
    else
    {
        return 0;
    }
}

void removeinicio(Fila *teste)
{
    int aux;
    aux = teste->elementos[teste->primeiro];
    if (teste->tamanho == 1)
    {
        iniciaFila(teste);
    }
    else
    {
        teste->elementos[teste->primeiro] = 0;
        teste->primeiro = (teste->primeiro + 1) % 100;
        aux = -1;
        teste->tamanho--;
    }
}

void inserefim(Fila *teste, int num)
{
    if (teste->primeiro != -1 && teste->ultimo != -1) //nao esta vazia
    {
        teste->elementos[(teste->ultimo + 1) % 100] = num;
        teste->ultimo = ((teste->ultimo + 1) % 100);
        teste->tamanho++;
    }
    else //vazia
    {
        teste->elementos[0] = num;
        teste->primeiro = 0;
        teste->ultimo = 0;
        teste->tamanho++;
    }
}

int printaFila(Fila *teste)
{
    int i;
    if (teste->tamanho == 0)
    {
        return -1;
    }
    else
    {
        for (i = teste->ultimo; i > teste->primeiro; i = ((100 + i) - 1) % 100)
        {
            printf("%d ", teste->elementos[i]);
        }
        printf("%d\n", teste->elementos[teste->primeiro]);
    }
}
// ############################ Principal ###################################

int main()
{
    Fila tarefas;
    iniciaFila(&tarefas);
    int movimentos, escolha, codigo, i, aux, aux2;

    scanf("%d", &movimentos);

    for (i = 0; i < movimentos; i++)
    {
        scanf("%d", &escolha);
        if (escolha == 1)
        {
            scanf("%d", &codigo);
            inserefim(&tarefas, codigo);
        }
        else if (escolha == 2)
        {
            aux = vazia(&tarefas);
            if (aux != 1)
            {
                removeinicio(&tarefas);
            }
            else
            {
                printf("A fila está vazia\n");
            }
        }
        else if (escolha == 3)
        {
            if (tarefas.tamanho == 0)
            {
                printf("A fila está vazia\n");
            }
            else
            {
                aux2 = tarefas.elementos[tarefas.primeiro];
                removeinicio(&tarefas);
                inserefim(&tarefas, aux2);
            }
        }
    }
    printaFila(&tarefas);

    return 0;
}
