#include "tPaciente.h"
#include "tLesao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tPaciente
{
    tPessoa *pessoa;
    int diabetes;
    int fumante;
    int alergia;
    int cancer;
    char pele[5];
    tLesao **lesao;
    int qtdLesao;
} tPaciente;

tPaciente *criaPaciente()
{
    tPaciente *paciente = (tPaciente *)calloc(1, sizeof(tPaciente));

    if (paciente == NULL)
        return NULL;

    paciente->pessoa = criaPessoa();

    paciente->diabetes = -1;
    paciente->fumante = -1;
    paciente->alergia = -1;
    paciente->cancer = -1;

    paciente->qtdLesao = 0;

    paciente->lesao = (tLesao **)calloc(1, sizeof(tLesao *));

    return paciente;
}


void salvaPaciente(tPaciente *paciente, FILE *arquivo)
{
    fwrite(paciente, sizeof(tPaciente), 1, arquivo);

    fwrite(&paciente->qtdLesao, sizeof(int), 1, arquivo);
    salvaLesoes(arquivo, paciente->lesao, paciente->qtdLesao);

    salvaPessoa(paciente->pessoa, arquivo);
}

tPaciente *recuperaPaciente(FILE *arquivo)
{
    tPaciente *paciente = (tPaciente *)calloc(1, sizeof(tPaciente));

    fread(paciente, sizeof(tPaciente), 1, arquivo);

    fread(&paciente->qtdLesao, sizeof(int), 1, arquivo);
    paciente->lesao = recuperaLesoes(arquivo, paciente->qtdLesao);

    paciente->pessoa = recuperaPessoa(arquivo);

    return paciente;
}

void salvaPacientes(tPaciente **pacientes, char *path, int nPacientes)
{
    char caminho[500];

    sprintf(caminho, "%s/pacientes.bin", path);

    FILE *arquivo = fopen(caminho, "wb");

    fwrite(&nPacientes, sizeof(int), 1, arquivo);

    int i;
    for (i = 0; i < nPacientes; i++)
        salvaPaciente(pacientes[i], arquivo);

    fclose(arquivo);
}

tPaciente **recuperaPacientes(FILE *arquivo, int *nPacientes)
{
    int i;

    fread(nPacientes, sizeof(int), 1, arquivo);

    tPaciente **pacientes = (tPaciente **)calloc(*nPacientes, sizeof(tPaciente *));

    for (i = 0; i < *nPacientes; i++)
        pacientes[i] = recuperaPaciente(arquivo);

    return pacientes;
}

void infoPaciente(tPaciente *paciente)
{
    printf("POSSUI DIABETES: ");
    scanf("%d%*c", &paciente->diabetes);
    printf("FUMANTE: ");  
    scanf("%d%*c", &paciente->fumante);
    printf("ALERGIA A MEDICAMENTO: ");
    scanf("%d%*c", &paciente->alergia);
    printf("HISTORICO DE CANCER: ");
    scanf("%d%*c", &paciente->cancer);
    printf("TIPO DE PELE: ");
    scanf("%[^\n]%*c", paciente->pele);
}

void desalocaPaciente(void *dado)
{
    if (dado == NULL)
        return;

    tPaciente *paciente = (tPaciente *)dado;

    int i;

    for (i = 0; i < paciente->qtdLesao; i++)
        desalocaLesao(paciente->lesao[i]);
    free(paciente->lesao);

    desalocaPessoa(paciente->pessoa);
    free(paciente);
}

tPessoa *pessoaPaciente(tPaciente *paciente)
{
    return paciente->pessoa;
}

void adicionaLesao(tPaciente *paciente, tLesao *lesao)
{
    paciente->lesao = (tLesao **)realloc(paciente->lesao, sizeof(tLesao *) * (paciente->qtdLesao + 1));
    paciente->lesao[paciente->qtdLesao] = lesao;
    paciente->qtdLesao++;
}

int possuiLesaoCirurgica(tPaciente *paciente)
{
    int i;

    for (i = 0; i < paciente->qtdLesao; i++)
    {
        if (cirurgiaLesao(paciente->lesao[i]))
            return 1;
    }

    return 0;
}

int fumantePaciente(tPaciente *paciente)
{
    return paciente->fumante;
}

int diabetesPaciente(tPaciente *paciente)
{
    return paciente->diabetes;
}

int alergiaPaciente(tPaciente *paciente)
{
    return paciente->alergia;
}

int cancerPaciente(tPaciente *paciente)
{
    return paciente->cancer;
}

int qntdLesao(tPaciente *paciente)
{
    return paciente->qtdLesao;
}

int qntdLesaoNova(tPaciente *paciente)
{
    int i, qtd = 0;

    for (i = 0; i < paciente->qtdLesao; i++)
    {
        if (!foiSolicitadaBiopsia(paciente->lesao[i]))
            qtd++;
    }

    return qtd;
}    

int qntdLesaoCirurgia(tPaciente *paciente)
{
    int i, qtd = 0;

    for (i = 0; i < paciente->qtdLesao; i++)
    {
        if (cirurgiaLesao(paciente->lesao[i]))
            qtd++;
    }

    return qtd;
}

int qntdLesaoCrioterapia(tPaciente *paciente)
{
    int i, qtd = 0;

    for (i = 0; i < paciente->qtdLesao; i++)
    {
        if (crioterapiaLesao(paciente->lesao[i]))
            qtd++;
    }

    return qtd;
}

int tamanhoMedioLesao(tPaciente *paciente)
{
    int i, soma = 0;

    if (qntdLesao(paciente) == 0)
        return 0;
    
    for (i = 0; i < paciente->qtdLesao; i++)
    {
        soma += tamanhoLesao(paciente->lesao[i]);
    }

    return soma;
}

tLesao **retornaLesao(tPaciente *paciente)
{
    return paciente->lesao;
}
