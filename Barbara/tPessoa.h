

#ifndef _PESSOA_H_
#define _PESSOA_H_

#define MAX_TAM_NOME 100
#define MAX_TAM_CPF 15
#define MAX_TAM_TELEFONE 15

typedef enum
{
    MASCULINO,
    FEMININO,
    OUTRO
} eGenero;

typedef struct tPessoa tPessoa;

tPessoa *criaPessoa();

void desalocaPessoa(void *dado);

#endif