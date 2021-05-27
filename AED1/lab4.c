/* 
Programa: Lab 4
Autor: Gabriel Bianchi e Silva
Versao: 1.0 - 02/10/2019
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
};

typedef struct elemento Data;

struct estruturaLDDE
{
    Data *primeiro;
    Data *ultimo;
    int tamanho;
};
typedef struct estruturaLDDE Lista;

void inicializaLista(Lista *teste)
{
    teste->primeiro = NULL;
    teste->ultimo = NULL;
    teste->tamanho = 0;
}

// ###################### Funcoes e Procedimentos do programa ##############

void insereinicio(Lista *teste, int num)
{
    Data *novo = (Data *)malloc(sizeof(Data));

    novo->info = num;
    novo->ant = NULL;
    novo->prox = teste->primeiro;
    teste->primeiro->ant = novo;
    teste->primeiro = novo;
    teste->tamanho++;
}

void inseremeio(Lista *teste, int num, int pos)
{
    int i;
    Data *novo = (Data *)malloc(sizeof(Data));
    novo->info = num;
    Data *aux;
    aux = teste->primeiro;
    for (i = 0; i < pos; i++)
    {
        aux = aux->prox;
    }

    aux->ant->prox = novo;
    novo->ant = aux->ant;
    novo->prox = aux;
    aux->ant = novo;
    teste->tamanho++;
}

void inserefim(Lista *teste, int num)
{
    Data *novo = (Data *)malloc(sizeof(Data));

    novo->info = num;
    if (teste->tamanho == 0)
    {
        novo->prox = NULL;
        novo->ant = NULL;
        teste->primeiro = novo;
        teste->ultimo = novo;
    }
    else
    {
        novo->prox = NULL;
        novo->ant = teste->ultimo;
        teste->ultimo->prox = novo;
        teste->ultimo = novo;
    }
    teste->tamanho++;
}

void printaLista(Lista *teste)
{
    Data *aux;
    aux = teste->primeiro;
    while (aux->prox != NULL)
    {
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    printf("%d \n", teste->ultimo->info);
}

Data *checadoze(Lista *teste)
{
    Data *aux;
    int soma;
    aux = teste->primeiro->prox;
    while (aux != NULL && aux->prox != NULL)
    {
        soma = aux->info + aux->ant->info + aux->prox->info;
        if (soma == 12)
        {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

void removeinicio(Lista *teste)
{
    Data *aux = teste->primeiro;
    teste->primeiro = aux->prox;
    if (teste->primeiro != NULL && teste->primeiro->ant != NULL)
    {
        teste->primeiro->ant = NULL;
    }
    free(aux);
    teste->tamanho--;
}

void removemeio(Data *aux, Lista *teste)
{
    aux->ant->ant->prox = aux->prox->prox;
    aux->prox->prox->ant = aux->ant->ant;
    free(aux->ant);
    free(aux->prox);
    free(aux);
    teste->tamanho = teste->tamanho - 3;
}

void removefim(Lista *teste)
{
    Data *aux;
    aux = teste->ultimo->ant;
    teste->ultimo = aux;
    teste->ultimo->prox = NULL;
    free(aux->prox);
    teste->tamanho--;
}

// ############################ Principal ###################################

int main()
{
    int i, numadicionado, posicaoadicionar, itemlista, j;
    Data *checa;
    Lista doze;
    inicializaLista(&doze);

    for (i = 0; i < 10; i++) //10 primeiros
    {
        scanf("%d", &itemlista);
        inserefim(&doze, itemlista); //se for 0 o tamanho ja insere no inicio
    }
    printaLista(&doze);

    for (j = 0; j < 5; j++)
    {
        scanf("%d %d", &numadicionado, &posicaoadicionar);
        if (posicaoadicionar == 0)
        {
            insereinicio(&doze, numadicionado);
        }
        else if (posicaoadicionar == doze.tamanho)
        {
            inserefim(&doze, numadicionado);
        }
        else
        {
            inseremeio(&doze, numadicionado, posicaoadicionar);
        }

        checa = checadoze(&doze);
        while (checa)
        {
            checa = checadoze(&doze);
            Data *aux;
            aux = checa ? doze.primeiro->prox : NULL;
            Data *aux2;
            aux2 = checa ? doze.ultimo->ant : NULL;
            if (aux != NULL && aux->info + aux->ant->info + aux->prox->info == 12)
            {
                removeinicio(&doze);
                removeinicio(&doze);
                removeinicio(&doze);
            }
            else if (aux != NULL && aux2->info + aux2->ant->info + aux2->prox->info == 12)
            {
                removefim(&doze);
                removefim(&doze);
                removefim(&doze);
            }
            else if (checa)
            {
                removemeio(checa, &doze);
            }
            if (doze.tamanho == 0)
            {
                break;
            }
        }
        if (doze.tamanho == 0)
        {
            break;
        }
        printaLista(&doze);
    }
    //vitoria ou derrota
    if (doze.tamanho == 0)
    {
        printf("Eba, você ganhou!");
    }
    else if (doze.tamanho != 0)
    {
        printf("Ih, não foi dessa vez");
    }
    return 0;
}
