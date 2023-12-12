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
    tSecretario *secretario = (tSecretario *)malloc(sizeof(tSecretario));

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
