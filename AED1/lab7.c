/* 
Programa: Lab 
Autor: Gabriel Bianchi e Silva
Versao: 1.0 - 19/10/2019
*/

// ##################### Bibliotecas Externas ##############################

#include <stdio.h>
#include <stdlib.h>

// ########################## TAD X.h ######################################

struct elemento
{
    int valor;
    struct elemento *ant;
};
typedef struct elemento tipoElemento;

struct pilha
{
    int tamanho;
    tipoElemento *topo;
};
typedef struct pilha tipoPilha;

void iniciapilha(tipoPilha *teste)
{
    teste->tamanho = 0;
    teste->topo = NULL;
}
// ###################### Funcoes e Procedimentos do programa ##############

void inseretopo(tipoPilha *teste, int num) //empilhar(push)
{
    tipoElemento *novoElem = malloc(sizeof(tipoElemento));
    novoElem->valor = num;

    if (teste->tamanho == 0)
    {
        teste->topo = novoElem;
        teste->topo->ant = NULL;
    }
    else
    {
        novoElem->ant = teste->topo;
        teste->topo = novoElem;
    }
    teste->tamanho++;
}

void removetopo(tipoPilha *teste) //desempilhar(pop)
{
    tipoElemento *aux = teste->topo;
    teste->topo = aux->ant;
    free(aux);
    teste->tamanho--;
}

int checatopo(tipoPilha *teste, int num) //peek
{
    tipoElemento *aux = teste->topo;
    if (aux->valor == num)
    {
        return 1;
    }
    return 0;
}

void printapilha(tipoPilha *teste) //list
{
    int i;
    tipoElemento *aux = teste->topo;
    if (teste->tamanho == 1)
    {
        printf("%d\n", aux->valor);
    }
    else
    {
        for (i = 0; i < teste->tamanho; i++)
        {
            printf("%d ", aux->valor);
            aux = aux->ant;
        }
        printf("\n");
    }
}

// ############################ Principal ###################################

int main()
{
    int movimentos, escolha, codigo, i, aux;
    tipoPilha estacionamento;
    iniciapilha(&estacionamento);

    scanf("%d", &movimentos);

    for (i = 0; i < movimentos; i++)
    {
        scanf("%d %d", &escolha, &codigo);
        if (escolha == 1)
        {
            inseretopo(&estacionamento, codigo);
            printapilha(&estacionamento);
        }
        else if (escolha == 2 && checatopo(&estacionamento, codigo) == 1)
        {
            removetopo(&estacionamento);
            printapilha(&estacionamento);
        }
        else if (escolha == 2 && checatopo(&estacionamento, codigo) != 1)
        {
            printf("Não foi possível remover esse carro agora\n");
            printapilha(&estacionamento);
        }
    }

    return 0;
}
