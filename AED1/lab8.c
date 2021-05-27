/*
Programa: Lab 8
Autor: Gabriel Bianchi e Silva
Versao: 1.0 - 16/11/2019
*/

// ##################### Bibliotecas Externas ##############################

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ########################## TAD X.h ######################################

struct noABB
{
    char nome[30];
    char father[30];
    char sexo;
    int nascimento;
    struct noABB *esq;
    struct noABB *dir;
};
typedef struct noABB arvore;

void inicia(char name[30], char sex, int data, arvore *teste)
{
    teste->nascimento = data;
    strcpy(teste->nome, name); //funcao que copia string
    teste->sexo = sex;
    teste->dir = NULL;
    teste->esq = NULL;
}
// ###################### Funcoes e Procedimentos do programa ##############

arvore *insereNo(char name[30], char sex, int data, char pai[30])
{
    arvore *novo = (arvore *)malloc(sizeof(arvore));
    novo->sexo = sex;
    novo->nascimento = data;
    strcpy(novo->nome, name);
    strcpy(novo->father, pai);
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

void insereOrdem(char name[30], char sexo, int data, char pai[30], arvore *teste)
{
    if (strcmp(teste->nome, pai) == 0)
    {
        if (teste->esq == NULL)
        {
            teste->esq = insereNo(name, sexo, data, pai);
        }
        else
        {
            if (sexo == 'M' && teste->esq->sexo == 'F' && teste->esq->nascimento < 2011)
            {
                teste->dir = teste->esq;
                teste->esq = insereNo(name, sexo, data, pai);
            }
            else if (teste->sexo == 'F' && data >= 2011 && data < teste->esq->nascimento)
            {
                teste->dir = teste->esq;
                teste->esq = insereNo(name, sexo, data, pai);
            }
            else
            {
                teste->dir = insereNo(name, sexo, data, pai);
            }
        }
    }
    if (teste->esq != NULL)
    {
        insereOrdem(name, sexo, data, pai, teste->esq);
    }
    if (teste->dir != NULL)
    {
        insereOrdem(name, sexo, data, pai, teste->dir);
    }
}

void limpaTudo(arvore *teste)
{
    int i;
    teste->dir = NULL;
    teste->esq = NULL;
    for (i = 0; i < 30; i++)
    {
        teste->nome[i] = '\0';
    }
}

void imprimeArvore(arvore *teste) //em ordem de descendencia(em pre ordem)
{
    if (teste != NULL)
    {
        printf("%s\n", teste->nome);
    }
    if (teste->esq != NULL)
    {
        imprimeArvore(teste->esq);
    }
    if (teste->dir != NULL)
    {
        imprimeArvore(teste->dir);
    }
}

arvore *busca(char name[30], arvore *teste)
{
    arvore *aux = NULL;
    if (teste != NULL)
    {
        if (strcmp(teste->nome, name) == 0) //comparar strings
        {
            return teste;
        }
        else
        {
            if (teste->dir != NULL)
            {
                aux = busca(name, teste->dir);
                if (aux != NULL)
                {
                    return aux;
                }
            }
            if (teste->esq != NULL)
            {
                aux = busca(name, teste->esq);
                if (aux != NULL)
                {
                    return aux;
                }
            }
        }
    }
    return NULL;
}

void removeNo(char name[30], arvore *teste)
{
    if (teste != NULL)
    {
        removeNo(name, teste->dir);
        removeNo(name, teste->esq);
        free(teste);
    }
}

// ############################ Principal ###################################

int main()
{
    int ano, i, movimentos, escolha;
    char nome[30], sexo, pai[30];
    arvore raiz;

    for (i = 0; i < 30; i++)
    {
        nome[i] = '\0';
    }

    scanf("%s %c %d", nome, &sexo, &ano);
    inicia(nome, sexo, ano, &raiz);
    scanf("%d", &movimentos);
    for (i = 0; i < movimentos; i++)
    {
        scanf("%d", &escolha);
        if (escolha == 1)
        {
            scanf("%s %c %d %s", nome, &sexo, &ano, pai);
            insereOrdem(nome, sexo, ano, pai, &raiz);
        }
        else if (escolha == 2)
        {
            scanf("%s", nome);
            arvore *aux = busca(nome, &raiz);
            arvore *aux2 = busca(aux->father, &raiz);
            if (aux2->dir == aux)
            {
                aux2->dir = NULL;
                removeNo(nome, aux);
            }
            else if (aux2->esq == aux)
            {
                aux2->esq = NULL;
                removeNo(nome, aux);
            }
        }
    }
    imprimeArvore(&raiz);

    return 0;
}
