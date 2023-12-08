

#ifndef _PESSOA_H_
#define _PESSOA_H_

#define MAX_TAM_NOME 100
#define MAX_TAM_CPF 15
#define MAX_TAM_TELEFONE 15

typedef struct tPessoa tPessoa;

tPessoa *criaPessoa();

void imprimePessoa(tPessoa *pessoa);

int ehIgualCPF(tPessoa *pessoa, char *CPF);

char *retornaCPF(tPessoa *pessoa);

void desalocaPessoa(void *dado);

#endif