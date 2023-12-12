

#ifndef _TBIOPSIA_H_
#define _BIOPSIA_H_

#include "tLesao.h"

#define NOME_ARQUIVO_BIOPSIA "biopsia.txt"

typedef struct tBiopsia tBiopsia;

tBiopsia *criaBiopsia(char *nomePaciente, char *CPF, tLesao** lesoes,
                    int qntd,  char *nomeMedico, char *CRM, char *dataStr);

void desalocaBiopsia(void *dado);

void imprimeNaTelaBiopsia(void *dado);

void imprimeEmArquivoBiopsia(void *dado, char *path);

#endif