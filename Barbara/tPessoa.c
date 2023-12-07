#include "tPessoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tPessoa 
{
    char nome[MAX_TAM_NOME];
    char telefone[MAX_TAM_TELEFONE];
    char nascimento[15];
    int idade;
    eGenero genero;

}tPessoa;


tPessoa *criaPessoa()
{
    tPessoa *pessoa = (tPessoa *)malloc(sizeof(tPessoa));

    if (pessoa == NULL)
        return NULL;

    return pessoa;

}

void desalocaPessoa(void *dado)
{
    if (dado == NULL)
        return;

    tPessoa *pessoa = (tPessoa *)dado;

    free(pessoa);
}
