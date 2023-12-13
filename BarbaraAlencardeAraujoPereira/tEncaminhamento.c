#include "tEncaminhamento.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct tEncaminhamento
{
    char nomePaciente[100];
    char CPF[15];
    char nomeMedico[100];
    char CRM[50];
    char dataStr[50];
    char especialidade[50];
    char motivo[100];
} tEncaminhamento;

tEncaminhamento *criaEncaminhamento(char *nomePaciente, char *CPF, char *nomeMedico, char *CRM, char *dataStr)
{
    tEncaminhamento *encaminhamento = (tEncaminhamento *)malloc(sizeof(tEncaminhamento));

    printf("ESPECIALIDADE ENCAMINHADA: ");
    scanf("%[^\n]%*c", encaminhamento->especialidade);
    printf("MOTIVO: ");
    scanf("%[^\n]%*c", encaminhamento->motivo);

    strcpy(encaminhamento->nomePaciente, nomePaciente);
    strcpy(encaminhamento->CPF, CPF);
    strcpy(encaminhamento->nomeMedico, nomeMedico);
    strcpy(encaminhamento->CRM, CRM);
    strcpy(encaminhamento->dataStr, dataStr);

    return encaminhamento;
}

void desalocaEncaminhamento(void *dado)
{
    if (dado == NULL)
        return;

    tEncaminhamento *encaminhamento = (tEncaminhamento *)dado;

    free(encaminhamento);
}

void imprimeNaTelaEncaminhamento(void *dado)
{
    if (dado == NULL)
        return;

    tEncaminhamento *encaminhamento = (tEncaminhamento *)dado;

    printf("PACIENTE: %s\n", encaminhamento->nomePaciente);
    printf("CPF: %s\n\n", encaminhamento->CPF);
    printf("ESPECIALIDADE ENCAMINHADA: %s\n", encaminhamento->especialidade);
    printf("MOTIVO: %s\n\n", encaminhamento->motivo);
    printf("%s (%s)\n", encaminhamento->nomeMedico, encaminhamento->CRM);
    printf("%s\n\n", encaminhamento->dataStr);
}

void imprimeEmArquivoEncaminhamento(void *dado, char *path)
{
    if (dado == NULL)
        return;

    tEncaminhamento *encaminhamento = (tEncaminhamento *)dado;

    char caminho[500];

    sprintf(caminho, "%s/%s", path, NOME_ARQUIVO_ENCAMINHAMENTO);

    FILE *arquivo = fopen(caminho, "a");

    fprintf(arquivo, "PACIENTE: %s\n", encaminhamento->nomePaciente);
    fprintf(arquivo, "CPF: %s\n\n", encaminhamento->CPF);
    fprintf(arquivo, "ESPECIALIDADE ENCAMINHADA: %s\n", encaminhamento->especialidade);
    fprintf(arquivo, "MOTIVO: %s\n\n", encaminhamento->motivo);
    fprintf(arquivo, "%s (%s)\n", encaminhamento->nomeMedico, encaminhamento->CRM);
    fprintf(arquivo, "%s\n\n", encaminhamento->dataStr);

    fclose(arquivo);
}