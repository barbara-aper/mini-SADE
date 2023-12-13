#ifndef _SECRETARIO_H_
#define _SECRETARIO_H_

#include "tPessoa.h"

typedef struct tSecretario tSecretario;

tSecretario *criaSecretario();

void salvaSecretario(tSecretario *secretario, FILE *arquivo);

tSecretario *recuperaSecretario(FILE *arquivo);

void salvaSecretarios(tSecretario **secretarios, char *path, int nSecretarios);

tSecretario **recuperaSecretarios(FILE *arquivo, int *nSecretarios);

int logouSecretario(char *login, char *senha, tSecretario *secretario);

int nivelAdmin(tSecretario *secretario);

void desalocaSecretario(void *dado);

tPessoa *pessoaSecretario(tSecretario *secretario);

#endif