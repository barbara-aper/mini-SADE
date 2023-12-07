#include "tFila.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct tFila
{
    tDocumento **lista;
    int tamanho;
} tFila;

tFila *criaFila()
{
    tFila *fila = (tFila *)malloc(sizeof(tFila));
    fila->tamanho = 0;
    fila->lista = (tDocumento **)malloc(20 * sizeof(tDocumento *));

    return fila;
}

void desalocaFila(tFila *f)
{
    if (f == NULL)
        return;

    int i;
    for (i = 0; i < f->tamanho; i++)
    {
        desalocaDocumento(f->lista[i]);
    }
    free(f->lista);

    free(f);
}

void insereDocumentoFila(tFila *f, void *dado, func_ptr_imprimeNaTela imprimeNaTela,
                         func_ptr_imprimeEmArquivo ImprimeEmArquivo,
                         func_ptr_desaloca desaloca)
{
    f->lista[f->tamanho] = criaDocumento(dado, imprimeNaTela, ImprimeEmArquivo, desaloca);
    f->tamanho++;
}

int quantidadeDocumentosNaFila(tFila *f)
{
    return f->tamanho;
}

void imprimeFila(tFila *f, char *path)
{
    int i;
    for (i = 0; i < f->tamanho; i++)
    {
        imprimeNaTelaDocumento(f->lista[i]);
        imprimeEmArquivoDocumento(f->lista[i], path);
    }
}
