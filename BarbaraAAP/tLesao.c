#include "tLesao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct tLesao 
{
    char diagnostivo[100];
    char regiao[100];
    int rotulo;
    int tamanho;
    int cirurgia;
    int crioterapia;
}tLesao;


tLesao *criaLesao(char *diagnostivo, char *regiao, int rotulo,
                    int tamanho, int cirurgia, int crioterapia)
{
    tLesao *lesao = (tLesao *)malloc(sizeof(tLesao));

    if (lesao == NULL)
        return NULL;

    lesao->rotulo = rotulo;
    lesao->tamanho = tamanho;
    lesao->cirurgia = cirurgia;
    lesao->crioterapia = crioterapia;
    strcpy(lesao->diagnostivo, diagnostivo);
    strcpy(lesao->regiao, regiao);

    return lesao;
}

void desalocaLesao(void *dado)
{
    if (dado == NULL)
        return;

    tLesao *lesao = (tLesao *)dado;

    free(lesao);
}

int cirurgiaLesao(tLesao *lesao)
{
    if (lesao == NULL)
        return 0;

    return lesao->cirurgia;
}

void imprimeNaTelaLesao(void *dado)
{
    if (dado == NULL)
        return;

    tLesao *lesao = (tLesao *)dado;

    printf("L%d - %s - ", lesao->rotulo, lesao->diagnostivo);
    printf("%s - %dMM", lesao->regiao, lesao->tamanho);
}

void imprimeEmArquivoLesao(void *dado, char *path)
{
    if (dado == NULL)
        return;

    tLesao *lesao = (tLesao *)dado;

    FILE *arquivo = fopen(path, "a");

    if (arquivo == NULL)
        return;

    fprintf(arquivo, "L%d - %s - ", lesao->rotulo, lesao->diagnostivo);
    fprintf(arquivo, "%s - %dMM", lesao->regiao, lesao->tamanho);

    fclose(arquivo);
}
