/*
Programa: Lab 5
Autor: Gabriel Bianchi e Silva
Versao: 1.0 - 9/10/2019
*/

// ##################### Bibliotecas Externas ##############################

#include <stdio.h>
#include <stdlib.h>

// ########################## TAD X.h ######################################

struct elemento
{
    int info;
    struct elemento *prox;
    struct elemento *ant;
    int paes[100];
};

typedef struct elemento Data;

struct estruturaLCDDE
{
    Data *primeiro;
    int tamanho;
};
typedef struct estruturaLCDDE Lista;

void inicializaLista(Lista *teste)
{
    teste->primeiro = NULL;
    teste->tamanho = 0;
}

// ###################### Funcoes e Procedimentos do programa ##############

void insereFim(Lista *teste, int num)
{
    Data *novo = (Data *)malloc(sizeof(Data));

    novo->info = num;
    if (teste->tamanho == 0)
    {
        novo->prox = novo;
        novo->ant = novo;
        teste->primeiro = novo;
    }
    else
    {
        novo->prox = teste->primeiro;
        novo->ant = teste->primeiro->ant;
        teste->primeiro->ant->prox = novo;
        teste->primeiro->ant = novo;
    }
    teste->tamanho++;
}

void printaLista(Lista *teste)
{
    int i;
    Data *aux;
    aux = teste->primeiro;
    for (i = 0; i < teste->tamanho; i++)
    {
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    printf("\n");
}

int removeCrianca(Lista *teste, Data *aux) //numero que parou
{
    if (aux == teste->primeiro)
    {
        aux->prox->ant = aux->ant;
        aux->ant->prox = aux->prox;
        teste->primeiro = aux->prox;
        free(aux);
        teste->tamanho--;
    }
    else
    {
        aux->prox->ant = aux->ant;
        aux->ant->prox = aux->prox;
        free(aux);
        teste->tamanho--;
    }
}

// ############################ Principal ###################################

int main()
{
    Lista ciranda;
    inicializaLista(&ciranda);
    int i, paes, qntcriancas, voltas = 0, numcrianca;

    scanf("%d", &qntcriancas);

    for (i = 0; i < qntcriancas; i++)
    {
        scanf("%d", &numcrianca);
        insereFim(&ciranda, numcrianca);
    }

    printaLista(&ciranda);

    scanf("%d", &paes);
    Data *aux = ciranda.primeiro;
    for (i = 0; i < paes; i++)
    {
        aux->paes[i]++; //inutil, so pra controle
        if (aux == ciranda.primeiro->ant)
        {
            voltas = voltas + 1;
        }
        aux = aux->prox;
    }

    removeCrianca(&ciranda, aux->ant);

    printf("Passadas na lista: %d", voltas);
    printf("\n");
    printaLista(&ciranda);
    return 0;
}
