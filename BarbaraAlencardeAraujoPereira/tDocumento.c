#include "tDocumento.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct tDocumento
{
    void *dado;
    func_ptr_imprimeNaTela imprimeNaTela;
    func_ptr_imprimeEmArquivo imprimeEmArquivo;
    func_ptr_desaloca desaloca;
} tDocumento;

typedef void (*func_ptr_imprimeNaTela)(void *dado);
typedef void (*func_ptr_imprimeEmArquivo)(void *dado, char *path);
typedef void (*func_ptr_desaloca)(void *dado);

tDocumento *criaDocumento(void *dado, func_ptr_imprimeNaTela imprimeNaTela,
                          func_ptr_imprimeEmArquivo ImprimeEmArquivo,
                          func_ptr_desaloca desaloca)
{
    tDocumento *doc = (tDocumento *)malloc(sizeof(tDocumento));

    if (dado == NULL)
        return NULL;

    doc->dado = dado;
    doc->imprimeNaTela = imprimeNaTela;
    doc->imprimeEmArquivo = ImprimeEmArquivo;
    doc->desaloca = desaloca;

    return doc;
}

void desalocaDocumento(tDocumento *doc)
{
    if (doc == NULL)
        return;

    doc->desaloca(doc->dado);
    free(doc);
}

void imprimeNaTelaDocumento(tDocumento *doc)
{
    if (doc == NULL)
        return;

    doc->imprimeNaTela(doc->dado);
}

void imprimeEmArquivoDocumento(tDocumento *doc, char *path)
{
    if (doc == NULL)
        return;

    doc->imprimeEmArquivo(doc->dado, path);
}
