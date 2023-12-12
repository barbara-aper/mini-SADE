

#ifndef _CONSULTA_H_
#define _CONSULTA_H_

typedef enum
{
    CADASTRAR_LESAO = 1,
    GERAR_RECEITA_MEDICA = 2,
    SOLICITACAO_DE_BIOPSIA = 3,
    ENCAMINHAMENTO = 4,
    ENCERRAR_CONSULTA = 5
} eIndiceConsulta;

typedef enum
{
    MEDICO = 1,
    SECRETARIO = 2
} eAgente;

#include "tPaciente.h"
#include "tMedico.h"
#include "tSecretario.h"
#include "tReceita.h"
#include "tFila.h"
#include "tBiopsia.h"
#include "tEncaminhamento.h"

void menuConsulta();

void RealizaConsulta(void *agente, tPaciente *paciente, tFila *fila, eAgente cargo);

void cadastraLesao(tPaciente *paciente);

void geraReceitaMedica(tPaciente *paciente, void *agente, char *data, tFila *fila, eAgente cargo);

void solicitaBiopsia(tPaciente *paciente, void *agente, char *data, tFila *fila, eAgente cargo);

void encaminhaPaciente(tPaciente *paciente, void *agente, char *data, tFila *fila, eAgente cargo);

#endif