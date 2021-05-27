/* Programa: Exemplo
 
   Autor: Gabriel Bianchi e Silva
 
   Versao: 1.1 - 07/09/2019
 
*/

// ##################### Bibliotecas Externas ##############################

#include <stdio.h>

// ########################## TAD X.h ######################################

// coloque o codigo da sua implementaÃ§Ã£o e definicao da TAD aqui

typedef struct
{
    int ultimo;
    int tamanho;
    int lista[10];
    int posicao;
} Biblioteca;

// ###################### Funcoes e Procedimentos do programa ##############

// Coloque as demais funcoes do seu programa aqui

void inicia(Biblioteca *teste)
{
    int i;
    teste->tamanho = 0;
    for (i = 0; i < 10; i++)
    {
        teste->lista[i] = 0;
    }
    teste->ultimo = 0;
}

void insereElemento(Biblioteca *teste, int book)
{
    if (teste->tamanho < 10) //nao inserir mais do que o maximo
    {
        teste->tamanho++;
        teste->lista[teste->tamanho - 1] = book;
        teste->ultimo = teste->tamanho - 1;
    }
}

int verifica(Biblioteca *teste, int book)
{
    int i;
    for (i = 0; i < teste->tamanho; i++)
    {
        if (teste->lista[i] == book)
        {
            return 1;
        }
    }
    return 0;
}

void retiraElemento(Biblioteca *teste, int book)
{
    int i, j, pos;
    for (i = 0; i < teste->tamanho; i++)
    {
        if (teste->lista[i] == book)
        {
            teste->lista[i] = 0;
            pos = i;
            for (j = pos + 1; j < teste->tamanho; j++)
            {
                teste->lista[j - 1] = teste->lista[j];
            }
            teste->tamanho--;
            printf("O livro foi retirado com sucesso\n");
        }
    }
}

// ############################ Principal ###################################

int main()
{
    int movimentos, retiradas = 0, reservas = 0, resposta, livro, i, k;
    Biblioteca dados;
    dados.posicao = 0;
    inicia(&dados);

    scanf("%d", &movimentos);

    for (i = 0; i < movimentos; i++)
    {
        scanf("%d %d", &resposta, &livro);
        if (resposta == 1)
        {
            if (dados.tamanho < 10)
            {
                insereElemento(&dados, livro);
                reservas++;
                printf("Sua reserva foi realizada\n");
            }
            else
            {
                printf("Lista de reserva cheia\n");
            }
        }
        else if (resposta == 2)
        {
            k = verifica(&dados, livro);
            if (k == 1)
            {
                retiraElemento(&dados, livro);
                retiradas++;
            }
            else
            {
                printf("Voce nao possui reserva desse livro\n");
            }
        }
    }

    printf("Voce realizou %d reservas e %d retiradas\n", reservas, retiradas);

    return 0;
}
