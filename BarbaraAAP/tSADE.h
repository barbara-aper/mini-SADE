

#ifndef _SADE_H_
#define _SADE_H_

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
} indiceMENU;

typedef enum
{
    LOGIN_ADMIN = 1,
    LOGIN_USER = 2,
    LOGIN_MED = 3

} cargos;

typedef struct tSADE tSADE;

tSADE *criaSADE();

void desalocaSADE(void *dado);

void iniciaSADE(tSADE *sade);

int acessaSADE(tSADE *sade);

void menuAdmin(tSADE *sade);

void menuUser(tSADE *sade);

void menuMedico(tSADE *sade);

void cadastroSecretario(tSADE *sade);

void cadastroMedico(tSADE *sade);

void cadastroPaciente(tSADE *sade);

int staffExisteCPF(tSADE *sade, char *CPF);

int pacienteExisteCPF(tSADE *sade, char *CPF);

#endif