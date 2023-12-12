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


tLesao *criaLesao(int rotulo)
{
    tLesao *lesao = (tLesao *)malloc(sizeof(tLesao));

    if (lesao == NULL)
        return NULL;

    lesao->rotulo = rotulo;

    printf("DIAGNOSTICO CLINICO: ");
    scanf("%[^\n]%*c", lesao->diagnostivo);
    printf("REGIAO DO CORPO: ");
    scanf("%[^\n]%*c", lesao->regiao);
    printf("TAMANHO: ");
    scanf("%d%*c", &lesao->tamanho);
    printf("ENVIAR PARA CIRURGIA: ");
    scanf("%d%*c", &lesao->cirurgia);
    printf("ENVIAR PARA CRIOTERAPIA: ");
    scanf("%d%*c", &lesao->crioterapia);

    return lesao;
}

tLesao *clonaLesao(tLesao *lesao)
{
    tLesao *clone = (tLesao *)malloc(sizeof(tLesao));

    if (clone == NULL)
        return NULL;

    strcpy(clone->diagnostivo, lesao->diagnostivo);
    strcpy(clone->regiao, lesao->regiao);
    clone->rotulo = lesao->rotulo;
    clone->tamanho = lesao->tamanho;
    clone->cirurgia = lesao->cirurgia;
    clone->crioterapia = lesao->crioterapia;

    return clone;
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

int crioterapiaLesao(tLesao *lesao)
{
    if (lesao == NULL)
        return 0;

    return lesao->crioterapia;
}

int tamanhoLesao(tLesao *lesao)
{
    if (lesao == NULL)
        return 0;

    return lesao->tamanho;
}

void imprimeNaTelaLesao(void *dado)
{
    if (dado == NULL)
        return;

    tLesao *lesao = (tLesao *)dado;

    printf("L%d - %s - ", lesao->rotulo, lesao->diagnostivo);
    printf("%s - %dMM\n", lesao->regiao, lesao->tamanho);
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
    fprintf(arquivo, "%s - %dMM\n", lesao->regiao, lesao->tamanho);

    fclose(arquivo);
}
