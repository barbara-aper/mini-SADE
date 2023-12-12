

#ifndef _RELATORIO_H_
#define _RELATORIO_H_

#include "tPaciente.h"

#define NOME_ARQUIVO_RELATORIO "relatorio_geral.txt"

typedef struct tRelatorio tRelatorio;

tRelatorio *criaRelatorio(tPaciente **pacientes, int nPacientes);

void desalocaRelatorio(void *dado);

void imprimeNaTelaRelatorio(void *dado);

void imprimeEmArquivoRelatorio(void *dado, char *path);

#endif