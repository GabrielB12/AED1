#include <stdio.h>
#include <stdlib.h>

struct noArvoreBinaria
{
    int chave;
    struct noArvoreBinaria *esq;
    struct noArvoreBinaria *dir;
};
typedef struct noArvoreBinaria tipoNoABB;

void inicializa(int c, tipoNoABB *arvoreAux)
{
    arvoreAux->chave = c;
    arvoreAux->esq = NULL;
    arvoreAux->dir = NULL;
}

tipoNoABB *insereNo(int c)
{
    tipoNoABB *novo = (tipoNoABB *)malloc(sizeof(tipoNoABB));
    novo->chave = c;
    novo->dir = NULL;
    novo->esq = NULL;
    return novo;
}

void insereABB(int chave, tipoNoABB *Aux)
{
    if (chave < Aux->chave)
    {
        if (Aux->esq == NULL)
            Aux->esq = insereNo(chave);
        else
            insereABB(chave, Aux->esq);
    }
    else if (chave > Aux->chave)
        if (Aux->dir == NULL)
            Aux->dir = insereNo(chave);
        else
            insereABB(chave, Aux->dir);
    else
        printf("Elemento Existente!");
}

void imprime(tipoNoABB *aux)
{
    if (aux != NULL)
        printf("%d ", aux->chave);
    if (aux->dir != NULL)
        imprime(aux->dir);
    if (aux->esq != NULL)
        imprime(aux->esq);
}

tipoNoABB *buscaElemento(int chave, tipoNoABB *Aux)
{
    if (Aux != NULL)
        if (chave < Aux->chave)
            buscaElemento(chave, Aux->esq);
        else if (chave > Aux->chave)
            buscaElemento(chave, Aux->dir);
        else
            return Aux;
    else
        return Aux;
}

tipoNoABB *buscaMaior(tipoNoABB *Aux)
{
    if (Aux->dir != NULL)
        buscaMaior(Aux->dir);
    else
        return Aux;
}

tipoNoABB *removeElemento(int chave, tipoNoABB *Aux)
{
    if (Aux != NULL)
        if (chave < Aux->chave)
            Aux->esq = removeElemento(chave, Aux->esq);
        else if (chave > Aux->chave)
            Aux->dir = removeElemento(chave, Aux->dir);
        else
        {

            int chave_temp;
            tipoNoABB *condenado, *aux2;
            condenado = Aux;

            if (condenado != NULL)
            {

                if (condenado->esq != NULL && condenado->dir != NULL) // tem 2 filhos
                {
                    aux2 = buscaMaior(condenado->esq);
                    chave_temp = condenado->chave;
                    condenado->chave = aux2->chave;
                    aux2->chave = chave_temp;

                    condenado->esq = removeElemento(chave_temp, condenado->esq);
                    return condenado;
                }
                else if (condenado->esq != NULL) // 1 filho
                {

                    aux2 = condenado->esq;
                    free(condenado);
                    return aux2;
                }
                else if (condenado->dir != NULL) // folha
                {

                    aux2 = condenado->dir;
                    free(condenado);
                    return aux2;
                }

                else

                {
                    free(condenado);
                    return NULL;
                }
            }
            else
                return Aux;
        }
}

void main()
{
    int c;

    tipoNoABB *raiz = NULL;

    do
    {

        if (raiz == NULL)
        {
            printf("insira a Raiz \n");
            scanf("%d", &c);
            raiz = insereNo(c);
        }
        else
            insereABB(c, raiz);

        imprime(raiz);

        printf("\nInsira um novo elemento (sair: -1) \n");
        scanf("%d", &c);
    } while (c != -1);

    do
    {

        imprime(raiz);

        printf("\nInsira um valor a remover (sair: -1) \n");
        scanf("%d", &c);
        removeElemento(c, raiz);
    } while (c != -1);
}
