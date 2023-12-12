#include "tSADE.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("ERRO: informe a pasta de saida de impressao como argumento");
        return 1;
    }

    char database[100];
    char caminhoDb[200];
    char caminhoSaida[200];

    printf("################################################\n");
    printf("DIGITE O CAMINHO DO BANCO DE DADOS: ");
    scanf("%[^\n]%*c", database);
    printf("################################################\n");

    sprintf(caminhoDb, "%s/%s", argv[1], database);
    sprintf(caminhoSaida, "%s/saida", argv[1]);

    printf("Caminho do banco de dados: %s\n", caminhoDb);
    printf("Caminho da pasta de saida: %s\n", caminhoSaida);

    tSADE *sade = criaSADE(caminhoSaida);

    iniciaSADE(sade);

    rodaSADE(sade);

    desalocaSADE(sade);

    return 0;
}