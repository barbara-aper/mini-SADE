#include "tMedico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tMedico
{
    tPessoa *pessoa;
    char login[20];
    char senha[20];
    char CRM[15];
} tMedico;

tMedico *criaMedico()
{
    tMedico *medico = (tMedico *)calloc(1, sizeof(tMedico));

    if (medico == NULL)
        return NULL;

    medico->pessoa = criaPessoa();

    printf("CRM: ");
    scanf("%[^\n]%*c", medico->CRM);
    printf("NOME DE USUARIO: ");
    scanf("%[^\n]%*c", medico->login);
    printf("SENHA: ");
    scanf("%[^\n]%*c", medico->senha);

    return medico;
}

void salvaMedico(tMedico *medico, FILE *arquivo)
{
    fwrite(medico, sizeof(tMedico), 1, arquivo);
    salvaPessoa(medico->pessoa, arquivo);
}

tMedico *recuperaMedico(FILE *arquivo)
{
    tMedico *medico = (tMedico *)calloc(1, sizeof(tMedico));

    fread(medico, sizeof(tMedico), 1, arquivo);
    medico->pessoa = recuperaPessoa(arquivo);

    return medico;
}

void salvaMedicos(tMedico **medicos, char *path, int nMedicos)
{
    char caminho[500];

    sprintf(caminho, "%s/medicos.bin", path);

    FILE *arquivo = fopen(caminho, "wb");

    fwrite(&nMedicos, sizeof(int), 1, arquivo);
    int i;
    for (i = 0; i < nMedicos; i++)
    {
        salvaMedico(medicos[i], arquivo);
    }

    fclose(arquivo);
}

tMedico **recuperaMedicos(FILE *arquivo, int *nMedicos)
{
    int i;

    fread(nMedicos, sizeof(int), 1, arquivo);
    
    tMedico **medicos = (tMedico **)calloc(*nMedicos, sizeof(tMedico *));

    for (i = 0; i < *nMedicos; i++)
        medicos[i] = recuperaMedico(arquivo);

    return medicos;
}

int logouMedico(char *login, char *senha, tMedico *medico)
{
    return !strcmp(login, medico->login) && !strcmp(senha, medico->senha);
}

void desalocaMedico(void *dado)
{
    if (dado == NULL)
        return;

    tMedico *medico = (tMedico *)dado;

    desalocaPessoa(medico->pessoa);
    free(medico);
}

char *retornaCRM(tMedico *medico)
{
    return medico->CRM;
}

tPessoa *pessoaMedico(tMedico *medico)
{
    return medico->pessoa;
}
