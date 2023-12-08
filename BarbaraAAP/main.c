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

    scanf("%[^\n]%*c", database);

    sprintf(caminhoDb, "%s/%s", argv[0], database);
    sprintf(caminhoSaida, "%s/saida", argv[0]);

    tSADE *sade = criaSADE();

    iniciaSADE(sade);
    acessaSADE(sade);
    desalocaSADE(sade);

    return 0;
}