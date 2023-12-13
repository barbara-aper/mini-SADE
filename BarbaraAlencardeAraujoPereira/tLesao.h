

#ifndef _LESAO_H_
#define _LESAO_H_

#include <stdio.h>

typedef struct tLesao tLesao;

tLesao *criaLesao(int rotulo);

tLesao *clonaLesao(tLesao *lesao);

void solicitouBiopsia(tLesao *lesao);

int foiSolicitadaBiopsia(tLesao *lesao);

void salvaLesoes(FILE *ARQUIVO, tLesao **lesoes, int nLesoes);

tLesao **recuperaLesoes(FILE *ARQUIVO, int nLesoes);

void desalocaLesao(void *dado);

int cirurgiaLesao(tLesao *lesao);

int crioterapiaLesao(tLesao *lesao);

int tamanhoLesao(tLesao *lesao);

void imprimeNaTelaLesao(void *dado);

void imprimeEmArquivoLesao(void *dado, char *path);

#endif