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
    int biopsia;
}tLesao;


tLesao *criaLesao(int rotulo)
{
    tLesao *lesao = (tLesao *)calloc(1, sizeof(tLesao));

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

    lesao->biopsia = 0;

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
    clone->biopsia = lesao->biopsia;

    return clone;
}

void solicitouBiopsia(tLesao *lesao)
{
    if (lesao == NULL)
        return;

    lesao->biopsia = 1;
}

int foiSolicitadaBiopsia(tLesao *lesao)
{
    if (lesao == NULL)
        return 0;

    return lesao->biopsia;
}

void salvaLesoes(FILE *ARQUIVO, tLesao **lesoes, int nLesoes)
{
    fwrite(&nLesoes, sizeof(int), 1, ARQUIVO);

    int i;
    for (i = 0; i < nLesoes; i++)
    {
        solicitouBiopsia(lesoes[i]);
        fwrite(lesoes[i], sizeof(tLesao), 1, ARQUIVO);
    }
}

tLesao **recuperaLesoes(FILE *ARQUIVO, int nLesoes)
{
    fread(&nLesoes, sizeof(int), 1, ARQUIVO);

    tLesao **lesoes = (tLesao **)calloc(nLesoes, sizeof(tLesao *));

    int i;
    for (i = 0; i < nLesoes; i++)
    {
        lesoes[i] = (tLesao *)calloc(1, sizeof(tLesao));
        fread(lesoes[i], sizeof(tLesao), 1, ARQUIVO);
    }

    return lesoes;
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
