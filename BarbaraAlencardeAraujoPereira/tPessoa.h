

#ifndef _PESSOA_H_
#define _PESSOA_H_

#define MAX_TAM_NOME 100
#define MAX_TAM_CPF 15
#define MAX_TAM_TELEFONE 15

typedef struct tPessoa tPessoa;

tPessoa *criaPessoa();

tPessoa *clonaPessoa(tPessoa *pessoa);

void imprimePessoa(tPessoa *pessoa);

void imprimeEmArquivoPessoa(tPessoa *pessoa, char *path);

int ehIgualCPF(tPessoa *pessoa, char *CPF);

int ehIgualNome(tPessoa *pessoa, char *nome);

char *retornaNome(tPessoa *pessoa);

char *retornaNascimento(tPessoa *pessoa);

char *retornaCPF(tPessoa *pessoa);

int retornaIdade(tPessoa *pessoa);

char *retornaGenero(tPessoa *pessoa);

void desalocaPessoa(void *dado);

#endif