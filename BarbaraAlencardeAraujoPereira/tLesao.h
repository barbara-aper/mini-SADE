

#ifndef _LESAO_H_
#define _LESAO_H_

typedef struct tLesao tLesao;

tLesao *criaLesao(int rotulo);

tLesao *clonaLesao(tLesao *lesao);

void desalocaLesao(void *dado);

int cirurgiaLesao(tLesao *lesao);

int crioterapiaLesao(tLesao *lesao);

int tamanhoLesao(tLesao *lesao);

void imprimeNaTelaLesao(void *dado);

void imprimeEmArquivoLesao(void *dado, char *path);

#endif