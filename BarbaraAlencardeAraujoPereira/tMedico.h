#ifndef _MEDICO_H_
#define _MEDICO_H_

#include "tPessoa.h"

typedef struct tMedico tMedico;

tMedico *criaMedico();

void salvaMedico(tMedico *medico, FILE *arquivo);

tMedico *recuperaMedico(FILE *arquivo);

void salvaMedicos(tMedico **medicos, char *path, int nMedicos);

tMedico **recuperaMedicos(FILE *arquivo, int *nMedicos);

int logouMedico(char *login, char *senha, tMedico *medico);

void desalocaMedico(void *dado);

char *retornaCRM(tMedico *medico);

tPessoa *pessoaMedico(tMedico *medico);

#endif