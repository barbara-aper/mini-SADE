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
    tMedico *medico = (tMedico *)malloc(sizeof(tMedico));

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
