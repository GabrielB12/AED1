/* 
Programa: Lab 3
Autor: Gabriel Bianchi e Silva
Versao: 1.45 - 23/09/2019
*/

// ##################### Bibliotecas Externas ##############################

#include <stdio.h>
#include <stdlib.h>

// ########################## TAD X.h ######################################
struct inform
{
    int codjogo;
    int qntExemplares;
    int qntAdicionada;
    float precoLocacao;
    float aluguel;
};
typedef struct inform Info;

struct Dados
{
    Info numeros;
    struct Dados *prox;
};
typedef struct Dados Data;

typedef struct
{
    Data *primeiro;
    Data *ultimo;
    int tamanho;

} Lista;

void inicia(Lista *teste)
{
    teste->primeiro = NULL;
    teste->ultimo = NULL;
    teste->tamanho = 0;
}
// ###################### Funcoes e Procedimentos do programa ##############

void insereFim(Lista *teste, int cod, int qnt, float preco)
{
    Data *novoElem = malloc(sizeof(Data));
    novoElem->numeros.codjogo = cod;
    novoElem->numeros.qntExemplares = qnt;
    novoElem->numeros.precoLocacao = preco;

    if (teste->tamanho == 0)
    {
        novoElem->prox = NULL;
        teste->primeiro = novoElem;
        teste->ultimo = novoElem;
    }
    else
    {
        novoElem->prox = NULL;
        teste->ultimo->prox = novoElem;
        teste->ultimo = novoElem;
    }
    teste->tamanho++;
}

void insereInicio(Lista *teste, int cod, int qnt, float preco)
{
    Data *novoElem = malloc(sizeof(Data));
    novoElem->numeros.codjogo = cod;
    novoElem->numeros.qntExemplares = qnt;
    novoElem->numeros.precoLocacao = preco;
    novoElem->prox = teste->primeiro;
    teste->primeiro = novoElem;
    teste->tamanho++;
}

void insereMeio(Lista *teste, int cod, int qnt, float preco)
{
    Data *novoElem = malloc(sizeof(Data));
    novoElem->numeros.codjogo = cod;
    novoElem->numeros.qntExemplares = qnt;
    novoElem->numeros.precoLocacao = preco;
    Data *aux;
    aux = teste->primeiro;
    while (aux != NULL)
    {
        if (aux->numeros.precoLocacao > preco && aux->prox->numeros.precoLocacao <= preco)
        {
            novoElem->prox = aux->prox;
            aux->prox = novoElem;
        }
        aux = aux->prox;
        teste->tamanho++;
    }
}

Data *buscaElemento(Lista *teste, int cod) //saber se ja existe para adicionar elementos
{
    Data *aux;
    aux = teste->primeiro;
    while (aux != NULL)
    {
        if (aux->numeros.codjogo == cod)
        {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

void adicionaElemento(Lista *teste, int cod, int qntadicionada)
{
    Data *aux;
    aux = buscaElemento(teste, cod);
    {
        if (aux->numeros.codjogo == cod)
        {
            aux->numeros.qntExemplares = aux->numeros.qntExemplares + qntadicionada;
        }
    }
}
void removeFim(Lista *teste, int cod)
{
    Data *aux = teste->primeiro;
    while (aux->prox->numeros.codjogo != cod)
    {
        aux = aux->prox;
    }
    free(aux->prox);
    aux->prox = NULL;
    teste->ultimo = aux;
}

void removeInicio(Lista *teste)
{
    Data *aux = teste->primeiro;
    teste->primeiro = aux->prox;
    free(aux);
    teste->tamanho--;
}

void removeMeio(Lista *teste, int cod)
{
    Data *aux = teste->primeiro, *baux = buscaElemento(teste, cod);
    while (aux != NULL)
    {
        if (aux->numeros.precoLocacao >= baux->numeros.precoLocacao && aux->prox->numeros.codjogo == baux->numeros.codjogo)
        {
            aux->prox = baux->prox;
            free(baux);
            break;
        }
        aux = aux->prox;
    }
}
// ############################ Principal ###################################

int main()
{
    int i, movimentos, opcao, codjogo, qntexemplares, qntadicionada;
    Data *verifica;
    float preco;
    Lista jogos;
    inicia(&jogos);
    scanf("%d", &movimentos);
    for (i = 0; i < movimentos; i++)
    {
        scanf("%d ", &opcao);
        if (opcao == 1) //novo jogo
        {
            scanf(" %d", &codjogo);
            scanf(" %d", &qntexemplares);
            scanf(" %f", &preco);
            verifica = buscaElemento(&jogos, codjogo);
            if (verifica == NULL)
            {
                if (jogos.tamanho == 0 || jogos.ultimo->numeros.precoLocacao >= preco)
                {
                    insereFim(&jogos, codjogo, qntexemplares, preco);
                }
                else if (jogos.primeiro->numeros.precoLocacao <= preco && jogos.tamanho != 0)
                {
                    insereInicio(&jogos, codjogo, qntexemplares, preco);
                }
                else
                {
                    insereMeio(&jogos, codjogo, qntexemplares, preco);
                }
            }
            else
            {
                printf("O jogo já está cadastrado\n");
            }
        }
        else if (opcao == 2) //aumentar
        {
            scanf("%d", &codjogo);
            scanf("%d", &qntadicionada);
            verifica = buscaElemento(&jogos, codjogo); //rever
            if (verifica != NULL)
            {
                adicionaElemento(&jogos, codjogo, qntadicionada);
            }
            else
            {
                printf("Não há\n");
            }
        }
        else if (opcao == 3) //remocao da lista, aluguel
        {
            scanf("%d", &codjogo);
            verifica = buscaElemento(&jogos, codjogo);
            if (verifica->numeros.qntExemplares > 0)
            {
                verifica->numeros.aluguel = verifica->numeros.aluguel + verifica->numeros.precoLocacao;
                verifica->numeros.qntExemplares--;
            }
            else
            {
                printf("Não há\n");
            }
        }
        else if (opcao == 4) //excluir jogo cadastrado
        {
            scanf("%d", &codjogo);
            verifica = buscaElemento(&jogos, codjogo);
            if (verifica != NULL)
            {
                if (jogos.primeiro->numeros.precoLocacao <= verifica->numeros.precoLocacao)
                {
                    removeInicio(&jogos);
                }
                else if (jogos.ultimo->numeros.precoLocacao >= verifica->numeros.precoLocacao)
                {
                    removeFim(&jogos, codjogo);
                }
                else
                {
                    removeMeio(&jogos, codjogo);
                }
            }
            else
            {
                printf("Não há\n");
            }
        }
    }

    Data *aux;
    aux = jogos.primeiro;
    while (aux != NULL)
    {
        printf("%d %f\n", aux->numeros.codjogo, aux->numeros.aluguel);
        aux = aux->prox;
    }
    return 0;
}
