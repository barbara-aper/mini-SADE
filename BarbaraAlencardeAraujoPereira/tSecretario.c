#include "tSecretario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tSecretario
{
    tPessoa *pessoa;
    char login[20];
    char senha[20];
    char nivel[10];
} tSecretario;

tSecretario *criaSecretario()
{
    tSecretario *secretario = (tSecretario *)calloc(1, sizeof(tSecretario));

    if (secretario == NULL)
        return NULL;

    secretario->pessoa = criaPessoa();

    printf("NOME DE USUARIO: ");
    scanf("%[^\n]%*c", secretario->login);
    printf("SENHA: ");
    scanf("%[^\n]%*c", secretario->senha);
    printf("NIVEL DE ACESSO: ");
    scanf("%[^\n]%*c", secretario->nivel);

    return secretario;
}

void salvaSecretario(tSecretario *secretario, FILE *arquivo)
{
    fwrite(secretario, sizeof(tSecretario), 1, arquivo);
    salvaPessoa(secretario->pessoa, arquivo);
}

tSecretario *recuperaSecretario(FILE *arquivo)
{
    tSecretario *secretario = (tSecretario *)calloc(1, sizeof(tSecretario));

    fread(secretario, sizeof(tSecretario), 1, arquivo);
    secretario->pessoa = recuperaPessoa(arquivo);

    return secretario;
}

void salvaSecretarios(tSecretario **secretarios, char *path, int nSecretarios)
{
    char caminho[500];

    sprintf(caminho, "%s/secretarios.bin", path);

    FILE *arquivo = fopen(caminho, "wb");

    fwrite(&nSecretarios, sizeof(int), 1, arquivo);
    int i;
    for (i = 0; i < nSecretarios; i++)
    {
        salvaSecretario(secretarios[i], arquivo);
    }

    fclose(arquivo);
}

tSecretario **recuperaSecretarios(FILE *arquivo, int *nSecretarios)
{
    int i;

    fread(nSecretarios, sizeof(int), 1, arquivo);

    tSecretario **secretarios = (tSecretario **)calloc(*nSecretarios, sizeof(tSecretario *));

    for (i = 0; i < *nSecretarios; i++)
        secretarios[i] = recuperaSecretario(arquivo);


    return secretarios;
}

int logouSecretario(char *login, char *senha, tSecretario *secretario)
{
    return !strcmp(login, secretario->login) && !strcmp(senha, secretario->senha);
}

int nivelAdmin(tSecretario *secretario)
{
    return !strcmp("ADMIN", secretario->nivel);
}

void desalocaSecretario(void *dado)
{
    if (dado == NULL)
        return;

    tSecretario *secretario = (tSecretario *)dado;

    desalocaPessoa(secretario->pessoa);
    free(secretario);
}

tPessoa *pessoaSecretario(tSecretario *secretario)
{
    return secretario->pessoa;
}
