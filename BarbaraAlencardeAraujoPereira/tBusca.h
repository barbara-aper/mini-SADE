#ifndef _BUSCA_H_
#define _BUSCA_H_

#include "tPaciente.h"
#include "tFila.h"

#define NOME_ARQUIVO_BUSCA "lista_busca.txt"

typedef struct tBusca tBusca;

tBusca *criaListaBusca(tPaciente **pacientes, char *nome, int nPacientes, tFila *fila);

void InsereBuscaFila(tBusca *busca, tFila *fila);

void desalocaLista(void *dado);

void imprimeNaTelaLista(void *dado);

void imprimeEmArquivoLista(void *dado, char *path);

#endif