

#ifndef _MEDICO_H_
#define _MEDICO_H_

#include "tPessoa.h"

typedef struct tMedico tMedico;

tMedico *criaMedico();

int logouMedico(char *login, char *senha, tMedico *medico);

void desalocaMedico(void *dado);

char *retornaCRM(tMedico *medico);

tPessoa *pessoaMedico(tMedico *medico);

#endif