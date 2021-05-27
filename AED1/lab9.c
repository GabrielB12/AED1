/* 
Programa: Lab 9
Autor: Gabriel Bianchi e Silva
Versao: 1.0 - 08/12/2019
*/

// ##################### Bibliotecas Externas ##############################

#include <stdio.h>
#include <stdlib.h>

// ########################## TAD X.h ######################################

// ###################### Funcoes e Procedimentos do programa ##############

int buscaProfund(int caminhos, int ver, int mat[ver][ver], int aux[ver][ver], int inicio, int fim)
{
    int i, j;

    aux[inicio][inicio] = 1;

    for (i = 0; i < ver; i++)
    {
        if (mat[inicio][i] == 1)
        {
            if (i == fim)
            {
                caminhos = caminhos + 1;
                aux[inicio][inicio] = 0;
                return caminhos;
            }
            if (aux[i][i] != 1)
            {
                caminhos = buscaProfund(caminhos, ver, mat, aux, i, fim);
            }
        }
    }
    aux[inicio][inicio] = 0;
    return caminhos;
}

// ############################ Principal ###################################

int main()
{

    int i, j, vertices, arestas, origem, destino, inicio, fim, caminhos;

    scanf("%d %d", &vertices, &arestas);

    int matriz[vertices][vertices], aux[vertices][vertices];

    for (i = 0; i < vertices; i++)
    {
        for (j = 0; j < vertices; j++)
        {
            matriz[i][j] = 0;
            aux[i][j] = 0;
        }
    }

    for (i = 0; i < arestas; i++)
    {
        scanf("%d %d", &origem, &destino);
        matriz[origem][destino] = 1;
    }

    scanf("%d %d", &inicio, &fim);

    caminhos = buscaProfund(caminhos, vertices, matriz, aux, inicio, fim);

    printf("%d\n", caminhos);

    return 0;
}
