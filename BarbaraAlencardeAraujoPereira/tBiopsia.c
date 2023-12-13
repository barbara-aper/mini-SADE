#include "tBiopsia.h"
#include "tLesao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tBiopsia
{
    char nomePaciente[100];
    char CPF[15];
    tLesao **lesoes;
    int qntd;
    char nomeMedico[100];
    char CRM[50];
    char dataStr[50];
} tBiopsia;

tBiopsia *criaBiopsia(char *nomePaciente, char *CPF, tLesao **lesoes,
                      int qntd, char *nomeMedico, char *CRM, char *dataStr)
{
    tBiopsia *biopsia = (tBiopsia *)malloc(sizeof(tBiopsia));

    if (biopsia == NULL)
        return NULL;

    biopsia->qntd = qntd;
    strcpy(biopsia->nomePaciente, nomePaciente);
    strcpy(biopsia->CPF, CPF);
    strcpy(biopsia->nomeMedico, nomeMedico);
    strcpy(biopsia->CRM, CRM);
    strcpy(biopsia->dataStr, dataStr);

    biopsia->lesoes = (tLesao **)malloc(sizeof(tLesao *) * qntd);

    int i;
    for (i = 0; i < qntd; i++)
        biopsia->lesoes[i] = clonaLesao(lesoes[i]);

    return biopsia;
}

void desalocaBiopsia(void *dado)
{
    if (dado == NULL)
        return;

    tBiopsia *biopsia = (tBiopsia *)dado;

    for (int i = 0; i < biopsia->qntd; i++)
        desalocaLesao(biopsia->lesoes[i]);

    free(biopsia->lesoes);
    free(biopsia);
}

void imprimeNaTelaBiopsia(void *dado)
{
    if (dado == NULL)
        return;

    tBiopsia *biopsia = (tBiopsia *)dado;

    printf("PACIENTE: %s\n", biopsia->nomePaciente);
    printf("CPF: %s\n\n", biopsia->CPF);

    printf("SOLICITACAO DE BIOPSIA PARA AS LESOES:\n");

    for (int i = 0; i < biopsia->qntd; i++)
        if (cirurgiaLesao(biopsia->lesoes[i]) && !foiSolicitadaBiopsia(biopsia->lesoes[i]))
            imprimeNaTelaLesao(biopsia->lesoes[i]);

    printf("\n%s (%s)\n", biopsia->nomeMedico, biopsia->CRM);
    printf("%s\n\n", biopsia->dataStr);
}

void imprimeEmArquivoBiopsia(void *dado, char *path)
{
    if (dado == NULL)
        return;

    if (path == NULL)
        return;

    char caminho[500];

    sprintf(caminho, "%s/%s", path, NOME_ARQUIVO_BIOPSIA);

    FILE *arquivo = fopen(caminho, "a");

    if (arquivo == NULL)
        return;

    tBiopsia *biopsia = (tBiopsia *)dado;

    fprintf(arquivo, "PACIENTE: %s\n", biopsia->nomePaciente);
    fprintf(arquivo, "CPF: %s\n\n", biopsia->CPF);

    fprintf(arquivo, "SOLICITACAO DE BIOPSIA PARA AS LESOES:\n");

    fclose(arquivo);

    for (int i = 0; i < biopsia->qntd; i++)
        if (cirurgiaLesao(biopsia->lesoes[i]) && !foiSolicitadaBiopsia(biopsia->lesoes[i]))
            imprimeEmArquivoLesao(biopsia->lesoes[i], caminho);

    arquivo = fopen(caminho, "a");

    fprintf(arquivo, "\n%s (%s)\n", biopsia->nomeMedico, biopsia->CRM);
    fprintf(arquivo, "%s\n\n", biopsia->dataStr);

    fclose(arquivo);
}
