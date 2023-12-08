

#ifndef _PACIENTE_H_
#define _PACIENTE_H_

#include "tPessoa.h"

typedef struct tPaciente tPaciente;

tPaciente *criaPaciente();

void desalocaPaciente(void *dado);

tPessoa *pessoaPaciente(tPaciente *paciente);

#endif