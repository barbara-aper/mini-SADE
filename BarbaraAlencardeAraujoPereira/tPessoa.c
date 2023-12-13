#include "tPessoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tPessoa
{
    char nome[MAX_TAM_NOME];
    char telefone[MAX_TAM_TELEFONE];
    char cpf[MAX_TAM_CPF];
    char nascimento[15];
    int idade;
    char genero[20];

} tPessoa;

tPessoa *criaPessoa()
{
    tPessoa *pessoa = (tPessoa *)calloc(1, sizeof(tPessoa));

    if (pessoa == NULL)
        return NULL;

    int dia, mes, ano;

    printf("NOME COMPLETO: ");
    scanf("%[^\n]%*c", pessoa->nome);
    printf("CPF: ");
    scanf("%[^\n]%*c", pessoa->cpf);
    printf("DATA DE NASCIMENTO: ");
    scanf("%d/%d/%d%*c", &dia, &mes, &ano);
    printf("TELEFONE: ");
    scanf("%[^\n]%*c", pessoa->telefone);
    printf("GENERO: ");
    scanf("%[^\n]%*c", pessoa->genero);

    sprintf(pessoa->nascimento, "%d/%d/%d", dia, mes, ano);

    if (mes <= 11 && dia <= 9)
        pessoa->idade = 2023 - ano;
    else
        pessoa->idade = 2022 - ano;

    return pessoa;
}

tPessoa *clonaPessoa(tPessoa *pessoa)
{
    tPessoa *clone = (tPessoa *)calloc(1, sizeof(tPessoa));

    if (clone == NULL)
        return NULL;

    strcpy(clone->nome, pessoa->nome);
    strcpy(clone->cpf, pessoa->cpf);
    strcpy(clone->telefone, pessoa->telefone);
    strcpy(clone->nascimento, pessoa->nascimento);
    strcpy(clone->genero, pessoa->genero);
    clone->idade = pessoa->idade;

    return clone;
}

void salvaPessoa(tPessoa *pessoa, FILE *arquivo)
{
    fwrite(pessoa, sizeof(tPessoa), 1, arquivo);
}

tPessoa *recuperaPessoa(FILE *arquivo)
{
    tPessoa *pessoa = (tPessoa *)calloc(1, sizeof(tPessoa));

    fread(pessoa, sizeof(tPessoa), 1, arquivo);

    return pessoa;
}

int ehIgualCPF(tPessoa *pessoa, char *CPF)
{
    return !strcmp(CPF, pessoa->cpf);
}

char *retornaNome(tPessoa *pessoa)
{
    return pessoa->nome;
}

char *retornaNascimento(tPessoa *pessoa)
{
    return pessoa->nascimento;
}

char *retornaCPF(tPessoa *pessoa)
{
    return pessoa->cpf;
}

int retornaIdade(tPessoa *pessoa)
{
    return pessoa->idade;
}

char *retornaGenero(tPessoa *pessoa)
{
    return pessoa->genero;
}

void imprimePessoa(tPessoa *pessoa)
{
    printf("%s ", pessoa->nome);
    printf("(%s)\n", pessoa->cpf);
}

void imprimeEmArquivoPessoa(tPessoa *pessoa, char *path)
{
    FILE *arquivo = fopen(path, "a");

    if (arquivo == NULL)
        return;

    fprintf(arquivo, "%s ", pessoa->nome);
    fprintf(arquivo, "(%s)\n", pessoa->cpf);

    fclose(arquivo);
}

void desalocaPessoa(void *dado)
{
    if (dado == NULL)
        return;

    tPessoa *pessoa = (tPessoa *)dado;

    free(pessoa);
}