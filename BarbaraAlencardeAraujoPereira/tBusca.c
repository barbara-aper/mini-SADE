#include "tBusca.h"
#include "tPessoa.h"
#include "tDocumento.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct tBusca
{
    tPessoa **pacientes;
    int qntd;
} tBusca;

tBusca *criaListaBusca(tPaciente **pacientes, char *nome, int nPacientes, tFila *fila)
{
    if (pacientes == NULL || nome == NULL || nPacientes <= 0)
        return NULL;

    tBusca *busca = (tBusca *)malloc(sizeof(tBusca));

    if (busca == NULL)
        return NULL;

    busca->pacientes = (tPessoa **)malloc(sizeof(tPessoa *));

    if (busca->pacientes == NULL)
    {
        free(busca);
        return NULL;
    }

    busca->qntd = 0;

    for (int i = 0; i < nPacientes; i++)
    {
        if (strcmp(retornaNome(pessoaPaciente(pacientes[i])), nome) == 0)
        {
            busca->pacientes = (tPessoa **)realloc(busca->pacientes, sizeof(tPessoa *) * (busca->qntd + 1));

            busca->pacientes[busca->qntd] = clonaPessoa(pessoaPaciente(pacientes[i]));

            busca->qntd++;
        }
    }

    if (busca->qntd == 0)
    {
        free(busca->pacientes);
        free(busca);
        return NULL;
    }

    return busca;
}

void InsereBuscaFila(tBusca *busca, tFila *fila)
{
    if (busca == NULL)
        return;

    insereDocumentoFila(fila, busca, imprimeNaTelaLista, imprimeEmArquivoLista, desalocaLista);
}

void desalocaLista(void *dado)
{
    if (dado == NULL)
        return;

    tBusca *busca = (tBusca *)dado;

    for (int i = 0; i < busca->qntd; i++)
        desalocaPessoa(busca->pacientes[i]);

    free(busca->pacientes);
    free(busca);
}

void imprimeNaTelaLista(void *dado)
{
    if (dado == NULL)
        return;

    tBusca *busca = (tBusca *)dado;

    for (int i = 0; i < busca->qntd; i++)
    {   
        if (busca->pacientes[i] == NULL)
            continue;
        
        printf("%d- ", i + 1);
        imprimePessoa(busca->pacientes[i]);
    }
}

void imprimeEmArquivoLista(void *dado, char *path)
{
    if (dado == NULL)
        return;

    tBusca *busca = (tBusca *)dado;

    char caminho[500];

    sprintf(caminho, "%s/%s", path, NOME_ARQUIVO_BUSCA);

    for (int i = 0; i < busca->qntd; i++)
    {
        FILE *arquivo = fopen(caminho, "a");

        if (arquivo == NULL)
            return;
        fprintf(arquivo, "%d - ", i + 1);
        fclose(arquivo);

        if (busca->pacientes[i] == NULL)
            continue;

        imprimeEmArquivoPessoa(busca->pacientes[i], caminho);
    }
}
