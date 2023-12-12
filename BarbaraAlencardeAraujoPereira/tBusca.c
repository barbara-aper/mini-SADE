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
        if (ehIgualNome(pessoaPaciente(pacientes[i]), nome))
        {
            busca->qntd++;
            busca->pacientes = realloc(busca->pacientes, sizeof(tPessoa *) * busca->qntd);
            busca->pacientes[i] = clonaPessoa(pessoaPaciente(pacientes[i]));
        }
    }

    if (busca->qntd == 0)
    {
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
        printf("%d- ", i + 1);
        imprimePessoa(busca->pacientes[i]);
    }
}

void imprimeEmArquivoLista(void *dado, char *path)
{
    if (dado == NULL)
        return;

    tBusca *busca = (tBusca *)dado;

    char caminho[300];

    sprintf(caminho, "%s/%s", path, NOME_ARQUIVO_BUSCA);

    for (int i = 0; i < busca->qntd; i++)
    {
        FILE *arquivo = fopen(caminho, "a");

        if (arquivo == NULL)
            return;
        fprintf(arquivo, "%d - ", i + 1);
        fclose(arquivo);

        imprimeEmArquivoPessoa(busca->pacientes[i], caminho);
    }
}
