

#ifndef _PACIENTE_H_
#define _PACIENTE_H_

#include "tPessoa.h"
#include "tLesao.h"

typedef struct tPaciente tPaciente;

tPaciente *criaPaciente();

void infoPaciente(tPaciente *paciente);

void desalocaPaciente(void *dado);

tPessoa *pessoaPaciente(tPaciente *paciente);

void adicionaLesao(tPaciente *paciente, tLesao *lesao);

int possuiLesaoCirurgica(tPaciente *paciente);

int fumantePaciente(tPaciente *paciente);

int diabetesPaciente(tPaciente *paciente);

int alergiaPaciente(tPaciente *paciente);

int cancerPaciente(tPaciente *paciente);

int qntdLesao(tPaciente *paciente);

int qntdLesaoCirurgia(tPaciente *paciente);

int qntdLesaoCrioterapia(tPaciente *paciente);

int tamanhoMedioLesao(tPaciente *paciente);

tLesao **retornaLesao(tPaciente *paciente);

#endif