/* Programa: Ex 2 Judge
 
   Autor: Gabriel Bianchi e Silva
 
   Versao: 1.0 - 18/09/2019
 
*/
// ##################### Bibliotecas Externas ##############################

#include <stdio.h>

// ########################## TAD X.h ######################################

typedef struct
{
    long int valor;
    int proximo;
} Informacao;

typedef struct
{
    int tamanho;
    int primeiro;
    int ultimo;
    int poslivre[10];
    Informacao elemento[10];
} ListaEE;

// coloque o codigo da sua implementação e definicao da TAD aqui

void iniciaLista(ListaEE *teste)
{
    int i;
    teste->tamanho = 0;
    teste->primeiro = -1;
    teste->ultimo = -1;
    for (i = 0; i < 10; i++)
    {
        teste->elemento[i].valor = 0;
        teste->elemento[i].proximo = -1;
        teste->poslivre[i] = 1;
    }
}

int proxposLivre(ListaEE *teste)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        if (teste->poslivre[i] == 1)
        {
            return i;
        }
    }
    return -1;
}

// ###################### Funcoes e Procedimentos do programa ##############

void imprime(ListaEE *teste)
{
    int k = teste->primeiro;
    if (teste->tamanho > 0)
    {
        while (teste->elemento[k].proximo != -1)
        {
            printf("%ld ", teste->elemento[k].valor);
            k = teste->elemento[k].proximo;
        }
        printf("%ld\n",
               teste->elemento[teste->ultimo]
                   .valor); // imprime o ultimo tambem(proximo do ultimo eh -1)
    }
}

void inserefimLista(ListaEE *teste, long int numero)
{
    int aux;
    aux = proxposLivre(teste);
    teste->elemento[aux].valor = numero;
    if (teste->tamanho == 0)
    {
        teste->primeiro = aux;
    }
    else
    {
        teste->elemento[teste->ultimo].proximo = aux;
    }
    teste->elemento[aux].proximo = -1;
    teste->tamanho++;
    teste->ultimo = aux;
    teste->poslivre[aux] = 0;
    imprime(teste);
}

void insereinicioLista(ListaEE *teste, long int numero)
{
    int aux;
    aux = proxposLivre(teste);
    teste->elemento[aux].proximo = teste->primeiro;
    teste->elemento[aux].valor = numero;
    teste->primeiro = aux;
    teste->tamanho++;
    teste->poslivre[aux] = 0;
    imprime(teste);
}

void inseremeioLista(ListaEE *teste, long int numero)
{
    int aux, i = teste->primeiro;
    aux = proxposLivre(teste);
    while (i != -1)
    {
        if (teste->elemento[teste->elemento[i].proximo].valor > numero &&
            teste->elemento[i].valor < numero)
        {
            teste->elemento[aux].proximo = teste->elemento[i].proximo;
            teste->elemento[aux].valor = numero;
            teste->elemento[i].proximo = aux;
            teste->poslivre[aux] = 0;
            teste->tamanho++;
            break; // inserir apenas uma vez
        }
        i = teste->elemento[i].proximo;
    }
    imprime(teste);
}

int checaReserva(ListaEE *teste, long int numero)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        if (numero == teste->elemento[i].valor)
        {
            return i;
        }
    }
    return -1;
}

void retirainicioElemento(ListaEE *teste, int checa)
{
    teste->primeiro = teste->elemento[checa].proximo;
    teste->elemento[checa].proximo = -1;
    teste->elemento[checa].valor = 0;
    teste->tamanho--;
    teste->poslivre[checa] = 1;
    imprime(teste);
}
void retirafinalElemento(ListaEE *teste, int checa)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        if (teste->elemento[i].proximo == checa)
        {
            teste->elemento[i].proximo = -1;
            teste->ultimo = i;
            break;
        }
    }
    teste->elemento[checa].proximo = -1;
    teste->elemento[checa].valor = 0;
    teste->tamanho--;
    teste->poslivre[checa] = 1;
    imprime(teste);
}

void retirameioElemento(ListaEE *teste, int checa)
{
    int i;
    for (i = 0; i < teste->tamanho; i++)
    {
        if (teste->elemento[teste->elemento[i].proximo].valor ==
            teste->elemento[checa].valor)
        {
            teste->elemento[i].proximo = teste->elemento[checa].proximo;
            break;
        }
    }
    teste->elemento[checa].proximo = -1;
    teste->elemento[checa].valor = 0;
    teste->tamanho--;
    teste->poslivre[checa] = 1;
    imprime(teste);
}

// ############################ Principal ###################################

int main()
{
    ListaEE pool;
    iniciaLista(&pool);
    int decisao, movimentos, i, num[8] = {0, 0, 0, 0, 0, 0, 0, 0}, ano = 2012,
                                aux, checa, teste;
    long int carteira;

    scanf("%d", &movimentos);

    for (i = 0; i < movimentos; i++)
    {
        scanf("%d %ld", &decisao, &carteira);
        if (decisao == 1)
        {
            aux = proxposLivre(&pool);
            if (aux != -1)
            {
                teste = (carteira / 10000) - 1;
                num[teste]++;
                if (carteira > pool.elemento[pool.ultimo].valor || pool.tamanho == 0)
                {
                    inserefimLista(&pool, carteira);
                }
                else if (carteira < pool.elemento[pool.primeiro].valor &&
                         pool.tamanho != 0)
                {
                    insereinicioLista(&pool, carteira);
                }
                else
                {
                    inseremeioLista(&pool, carteira);
                }
            }
            else
            {
                printf("Dia cheio\n");
                imprime(&pool);
            }
        }
        else if (decisao == 2)
        {
            checa = checaReserva(&pool, carteira);
            if (checa != -1)
            {
                if (checa == pool.ultimo)
                {
                    retirafinalElemento(&pool, checa);
                }
                else if (checa == pool.primeiro)
                {
                    retirainicioElemento(&pool, checa);
                }
                else
                {
                    retirameioElemento(&pool, checa);
                }
            }
            else
            {
                printf("N�o foi reservado\n");
                imprime(&pool);
            }
        }
    }

    for (i = 0; i < 8; i++)
    {
        printf("%d: %d\n", ano + i, num[i]);
    }

    return 0;
}
