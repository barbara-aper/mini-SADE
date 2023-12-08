

#ifndef _LESAO_H_
#define _LESAO_H_

typedef struct tLesao tLesao;

tLesao *criaLesao(char *diagnostivo, char *regiao, int rotulo,
                    int tamanho, int cirurgia, int crioterapia);

void desalocaLesao(void *dado);

int cirurgiaLesao(tLesao *lesao);

void imprimeNaTelaLesao(void *dado);

void imprimeEmArquivoLesao(void *dado, char *path);

#endif