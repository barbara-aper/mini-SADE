

#ifndef _SADE_H_
#define _SADE_H_

#include "tSecretario.h"
#include "tMedico.h"
#include "tPaciente.h"
#include "tFila.h"

typedef enum
{
    CADASTRAR_SECRETARIO = 1,
    CADASTRAR_MEDICO = 2,
    CADASTRAR_PACIENTE = 3,
    REALIZAR_CONSULTA = 4,
    BUSCAR_PACIENTES = 5,
    RELATORIO_GERAL = 6,
    FILA_DE_IMPRESSAO = 7,
    FINALIZAR_O_PROGRAMA = 8
} eIndiceMENU;

typedef enum
{
    LOGIN_ADMIN = 1,
    LOGIN_USER = 2,
    LOGIN_MED = 3

} eCargos;

typedef struct tSADE tSADE;

tSADE *criaSADE(char *path);

void desalocaSADE(void *dado);

void iniciaSADE(tSADE *sade);

int acessaSADE(tSADE *sade);

void rodaSADE(tSADE *sade);

void menu(int cargo);

void opcoesAdmin(int opcao, tSADE *sade, tSecretario *secretario);

void opcoesUser(int opcao, tSADE *sade, tSecretario *secretario);

void opcoesMedico(int opcao, tSADE *sade, tMedico *medico);

int staffExisteCPF(tSADE *sade, char *CPF);

int pacienteExisteCPF(tSADE *sade, char *CPF);

void buscaPacientes(tPaciente **pacientes, int nPacientes, tFila *fila);

void cadastroSecretario(tSADE *sade);

void cadastroMedico(tSADE *sade);

void cadastroPaciente(tSADE *sade);

void relatorioGeral(tPaciente **pacientes, int nPacientes, tFila *fila);

#endif