#include "tRelatorio.h"
#include "tPaciente.h"
#include "tLesao.h"
#include "tPessoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tRelatorio 
{
    int pacientesAtendidos;
    int idadeMedia;
    int qntdFeminino;
    int qntdMasculino;
    int qntdOutros;
    int tamanhoMedio;
    int qntdLesoes;
    int qntdCirurgias;
    int qntdCrioterapia;
} tRelatorio;

tRelatorio *criaRelatorio(tPaciente **pacientes, int nPacientes)
{
    tRelatorio *relatorio = (tRelatorio *)malloc(sizeof(tRelatorio));

    if (relatorio == NULL)
        return NULL;

    relatorio->pacientesAtendidos = 0;
    relatorio->qntdFeminino = 0;
    relatorio->qntdMasculino = 0;
    relatorio->qntdOutros = 0;
    relatorio->qntdLesoes = 0;
    relatorio->qntdCirurgias = 0;
    relatorio->qntdCrioterapia = 0;

    int i, soma = 0, tamanho = 0;

    for (i = 0; i < nPacientes; i++)
    {   
        if (strcmp(retornaGenero(pessoaPaciente(pacientes[i])), "FEMININO") == 0)
            relatorio->qntdFeminino++;
        else if (strcmp(retornaGenero(pessoaPaciente(pacientes[i])), "MASCULINO") == 0)
            relatorio->qntdMasculino++;
        else
            relatorio->qntdOutros++;

        if (fumantePaciente(pacientes[i]) >= 0)
            relatorio->pacientesAtendidos++;
        
        relatorio->qntdLesoes += qntdLesao(pacientes[i]);
        relatorio->qntdCirurgias += qntdLesaoCirurgia(pacientes[i]);
        relatorio->qntdCrioterapia += qntdLesaoCrioterapia(pacientes[i]);
        
        tamanho += tamanhoMedioLesao(pacientes[i]);

        soma += retornaIdade(pessoaPaciente(pacientes[i]));
    }

    relatorio->idadeMedia = soma / nPacientes;
    relatorio->tamanhoMedio = tamanho / relatorio->qntdLesoes;

    return relatorio;
}

void desalocaRelatorio(void *dado)
{
    if (dado == NULL)
        return;

    tRelatorio *relatorio = (tRelatorio *)dado;

    free(relatorio);
}

void imprimeNaTelaRelatorio(void *dado)
{
    if (dado == NULL)
        return;

    tRelatorio *relatorio = (tRelatorio *)dado;

    printf("NUMERO TOTAL DE PACIENTES ATENDIDOS: %d\n", relatorio->pacientesAtendidos);
    printf("IDADE MEDIA: %d\n", relatorio->idadeMedia);
    printf("DISTRIBUICAO POR SEXO:\n");
    printf("- FEMININO: %d\n", relatorio->qntdFeminino);
    printf("- MASCULINO: %d\n", relatorio->qntdMasculino);
    printf("- OUTROS: %d\n", relatorio->qntdOutros);
    printf("TAMANHO MEDIO DAS LESOES: %d\n", relatorio->tamanhoMedio);
    printf("NUMERO TOTAL DE LESOES: %d\n", relatorio->qntdLesoes);
    printf("NUMERO TOTAL DE CIRURGIAS: %d\n", relatorio->qntdCirurgias);
    printf("NUMERO TOTAL DE CRIOTERAPIA: %d\n", relatorio->qntdCrioterapia);
}

void imprimeEmArquivoRelatorio(void *dado, char *path)
{
    if (dado == NULL)
        return;

    tRelatorio *relatorio = (tRelatorio *)dado;

    char caminho[100];

    sprintf(caminho, "%s/%s", path, NOME_ARQUIVO_RELATORIO);

    FILE *arquivo = fopen(caminho, "a");

    if (arquivo == NULL)
        return;

    fprintf(arquivo, "NUMERO TOTAL DE PACIENTES ATENDIDOS: %d\n", relatorio->pacientesAtendidos);
    fprintf(arquivo, "IDADE MEDIA: %d\n", relatorio->idadeMedia);
    fprintf(arquivo, "DISTRIBUICAO POR GENERO:\n");
    fprintf(arquivo, "- FEMININO: %d\n", relatorio->qntdFeminino);
    fprintf(arquivo, "- MASCULINO: %d\n", relatorio->qntdMasculino);
    fprintf(arquivo, "- OUTROS: %d\n", relatorio->qntdOutros);
    fprintf(arquivo, "TAMANHO MEDIO DAS LESOES: %d\n", relatorio->tamanhoMedio);
    fprintf(arquivo, "NUMERO TOTAL DE LESOES: %d\n", relatorio->qntdLesoes);
    fprintf(arquivo, "NUMERO TOTAL DE CIRURGIAS: %d\n", relatorio->qntdCirurgias);
    fprintf(arquivo, "NUMERO TOTAL DE CRIOTERAPIA: %d\n", relatorio->qntdCrioterapia);

    fclose(arquivo);
}

