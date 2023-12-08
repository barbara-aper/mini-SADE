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
    tPessoa *pessoa = (tPessoa *)malloc(sizeof(tPessoa));

    if (pessoa == NULL)
        return NULL;

    printf("NOME COMPLETO: ");
    scanf("%[^\n]%*c", pessoa->nome);
    printf("CPF: ");
    scanf("%[^\n]%*c", pessoa->cpf);
    printf("DATA DE NASCIMENTO: ");
    scanf("%[^\n]%*c", pessoa->nascimento);
    printf("TELEFONE: ");
    scanf("%[^\n]%*c", pessoa->telefone);
    printf("GENERO: ");
    scanf("%[^\n]%*c", pessoa->genero);

    return pessoa;
}

int ehIgualCPF(tPessoa *pessoa, char *CPF)
{
    return !strcmp(CPF, pessoa->cpf);
}

char *retornaCPF(tPessoa *pessoa)
{
    return pessoa->cpf;
}

void imprimePessoa(tPessoa *pessoa)
{

    printf("NOME COMPLETO: ");
    printf("%s\n", pessoa->nome);
    printf("CPF: ");
    printf("%s\n", pessoa->cpf);
    printf("DATA DE NASCIMENTO: ");
    printf("%s\n", pessoa->nascimento);
    printf("TELEFONE: ");
    printf("%s\n", pessoa->telefone);
    printf("GENERO: ");
    printf("%s\n", pessoa->genero);
}

void desalocaPessoa(void *dado)
{
    if (dado == NULL)
        return;

    tPessoa *pessoa = (tPessoa *)dado;

    free(pessoa);
}
