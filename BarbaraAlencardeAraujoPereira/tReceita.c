#include "tReceita.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tReceita
{
    char nomePaciente[100];
    eTipoUso tipoUso;
    char nomeMedicamento[MAX_TAM_NOME_MEDICAMENTO];
    char tipoMedicamento[MAX_TAM_TIPO_MEDICAMENTO];
    char instrucoes[MAX_TAM_INSTRUCOES];
    int qntd;
    char nomeMedico[100];
    char CRM[50];
    char dataStr[50];
} tReceita;

tReceita *criaReceita(char *nomePaciente, eTipoUso tipoUso, char *nomeMedicamento,
                      char *tipoMedicamento, char *instrucoes, int qntd,
                      char *nomeMedico, char *CRM, char *dataStr)
{
    tReceita *receita = (tReceita *)malloc(sizeof(tReceita));

    if (receita == NULL)
        return NULL;

    receita->tipoUso = tipoUso;
    receita->qntd = qntd;
    strcpy(receita->nomePaciente, nomePaciente);
    strcpy(receita->nomeMedicamento, nomeMedicamento);
    strcpy(receita->tipoMedicamento, tipoMedicamento);
    strcpy(receita->instrucoes, instrucoes);
    strcpy(receita->nomeMedico, nomeMedico);
    strcpy(receita->CRM, CRM);
    strcpy(receita->dataStr, dataStr);

    return receita;
}

void desalocaReceita(void *dado)
{
    if (dado == NULL)
        return;

    tReceita *receita = (tReceita *)dado;

    free(receita);
}

void imprimeNaTelaReceita(void *dado)
{
    if (dado == NULL)
        return;

    tReceita *receita = (tReceita *)dado;

    printf("RECEITUARIO\n");
    printf("NOME: %s\n\n", receita->nomePaciente);
    printf("USO %s\n\n", receita->tipoUso == ORAL ? "ORAL" : "TOPICO");
    printf("%s\n", receita->nomeMedicamento);
    printf("%d %s\n\n", receita->qntd, receita->tipoMedicamento);
    printf("%s\n\n", receita->instrucoes);
    printf("%s (%s)\n", receita->nomeMedico, receita->CRM);
    printf("%s\n\n", receita->dataStr);
}

void imprimeEmArquivoReceita(void *dado, char *path)
{
    if (dado == NULL)
        return;

    if (path == NULL)
        return;

    char caminho[300];

    sprintf(caminho, "%s/%s", path, NOME_ARQUIVO_RECEITA);

    tReceita *receita = (tReceita *)dado;

    FILE *arquivo = fopen(caminho, "a");

    fprintf(arquivo, "RECEITUARIO\n");
    fprintf(arquivo, "NOME: %s\n\n", receita->nomePaciente);
    fprintf(arquivo, "USO %s\n\n", receita->tipoUso == ORAL ? "ORAL" : "TOPICO");
    fprintf(arquivo, "%s\n", receita->nomeMedicamento);
    fprintf(arquivo, "%d %s\n\n", receita->qntd, receita->tipoMedicamento);
    fprintf(arquivo, "%s\n\n", receita->instrucoes);
    fprintf(arquivo, "%s (%s)\n", receita->nomeMedico, receita->CRM);
    fprintf(arquivo, "%s\n\n", receita->dataStr);

    fclose(arquivo);
}