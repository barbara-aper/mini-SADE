#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tSADE.h"
#include "tSecretario.h"
#include "tMedico.h"
#include "tPaciente.h"
#include "tFila.h"
#include "tReceita.h"
#include "tBiopsia.h"

typedef struct tSADE
{
    int qtdSecretarios;
    int qtdMedicos;
    int qtdPacientes;
    tPaciente **pacientes;
    tMedico **medicos;
    tSecretario **secretarios;
    tFila *fila;
} tSADE;

tSADE *criaSADE()
{
    tSADE *sade = (tSADE *)malloc(sizeof(tSADE));

    if (sade == NULL)
        return NULL;

    sade->pacientes = (tPaciente **)malloc(sizeof(tPaciente *));
    sade->medicos = (tMedico **)malloc(sizeof(tMedico *));
    sade->secretarios = (tSecretario **)malloc(sizeof(tSecretario *));
    sade->fila = (tFila *)malloc(sizeof(tFila *));

    sade->qtdMedicos = 0;
    sade->qtdSecretarios = 0;
    sade->qtdPacientes = 0;

    return sade;
}

void desalocaSADE(void *dado)
{
    if (dado == NULL)
        return;

    tSADE *sade = (tSADE *)dado;

    int i;

    for (i = 0; i < sade->qtdMedicos; i++)
    {
        desalocaMedico(sade->medicos[i]);
    }
    free(sade->medicos);

    for (i = 0; i < sade->qtdSecretarios; i++)
    {
        desalocaSecretario(sade->secretarios[i]);
    }
    free(sade->secretarios);

    for (i = 0; i < sade->qtdPacientes; i++)
    {
        desalocaPaciente(sade->pacientes[i]);
    }
    free(sade->pacientes);

    desalocaFila(sade->fila);

    free(sade);
}

void iniciaSADE(tSADE *sade)
{
    printf("####################### MENU PRINCIPAL #########################\n");

    tSecretario *secretario = criaSecretario();

    sade->secretarios[sade->qtdSecretarios] = secretario;

    sade->qtdSecretarios++;

    printf("###############################################################\n");
}

int acessaSADE(tSADE *sade)
{
    char login[20];
    char senha[20];

    printf("######################## ACESSO MINI-SADE ######################\n");
    printf("DIGITE SEU LOGIN: ");
    scanf("%[^\n]%*c", login);
    printf("DIGITE SUA SENHA: ");
    scanf("%[^\n]%*c", senha);

    int i;
    for (i = 0; i < sade->qtdSecretarios; i++)
    {
        if (logouSecretario(login, senha, sade->secretarios[i]))
        {
            if (nivelAdmin(sade->secretarios[i]))
            {
                printf("###############################################################\n");
                return LOGIN_ADMIN;
            }
            else
            {
                printf("###############################################################\n");
                return LOGIN_USER;
            }
        }
    }

    for (i = 0; i < sade->qtdMedicos; i++)
    {
        if (logouMedico(login, senha, sade->medicos[i]))
        {
            printf("###############################################################\n");
            return LOGIN_MED;
        }
    }

    printf("###############################################################\n");
    printf("SENHA INCORRETA OU USUARIO INEXISTENTE\n");
    acessaSADE(sade);
}

void menu(tSADE *sade, int cargo)
{
    if (cargo == LOGIN_ADMIN)
        menuAdmin(sade);
    else if (cargo == LOGIN_USER)
        menuUser(sade);
    else if (cargo == LOGIN_MED)
        menuMedico(sade);
}

void menuAdmin(tSADE *sade)
{
    printf("####################### MENU PRINCIPAL #########################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("    (%d) CADASTRAR SECRETARIO\n", CADASTRAR_SECRETARIO);
    printf("    (%d) CADASTRAR MEDICO\n", CADASTRAR_MEDICO);
    printf("    (%d) CADASTRAR PACIENTE\n", CADASTRAR_PACIENTE);
    printf("    (%d) REALIZAR CONSULTA\n", REALIZAR_CONSULTA);
    printf("    (%d) BUSCAR PACIENTES\n", BUSCAR_PACIENTES);
    printf("    (%d) RELATORIO GERAL\n", RELATORIO_GERAL);
    printf("    (%d) FILA DE IMPRESSAO\n", FILA_DE_IMPRESSAO);
    printf("    (%d) FINALIZAR O PROGRAMA\n", FINALIZAR_O_PROGRAMA);
    printf("###############################################################\n");

    int opcao;

    scanf("%d%*c", &opcao);

    if (opcao == CADASTRAR_SECRETARIO)
    {
        cadastroSecretario(sade);
    }
    else if (opcao == CADASTRAR_MEDICO)
    {
        cadastroMedico(sade);
    }
    else if (opcao == CADASTRAR_PACIENTE)
    {
        cadastroPaciente(sade);
    }
    else if (REALIZAR_CONSULTA)
    {
        /* code */
    }

    else if (opcao == BUSCAR_PACIENTES)
    {
        /* code */
    }
    else if (opcao == RELATORIO_GERAL)
    {
        /* code */
    }
    else if (opcao == FILA_DE_IMPRESSAO)
    {
        /* code */
    }
    else if (opcao == FINALIZAR_O_PROGRAMA)
    {
        return;
    }

    menuAdmin(sade);
}

void menuUser(tSADE *sade)
{
    printf("####################### MENU PRINCIPAL #########################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("    (%d) CADASTRAR MEDICO\n", CADASTRAR_MEDICO);
    printf("    (%d) CADASTRAR PACIENTE\n", CADASTRAR_PACIENTE);
    printf("    (%d) BUSCAR PACIENTES\n", BUSCAR_PACIENTES);
    printf("    (%d) RELATORIO GERAL\n", RELATORIO_GERAL);
    printf("    (%d) FILA DE IMPRESSAO\n", FILA_DE_IMPRESSAO);
    printf("    (%d) FINALIZAR O PROGRAMA\n", FINALIZAR_O_PROGRAMA);
    printf("###############################################################\n");

    int opcao;

    scanf("%d%*c", &opcao);

    if (opcao == CADASTRAR_MEDICO)
    {
        cadastroMedico(sade);
    }
    else if (opcao == CADASTRAR_PACIENTE)
    {
        cadastroPaciente(sade);
    }
    else if (opcao == BUSCAR_PACIENTES)
    {
        /* code */
    }
    else if (opcao == RELATORIO_GERAL)
    {
        /* code */
    }
    else if (opcao == FILA_DE_IMPRESSAO)
    {
        /* code */
    }
    else if (opcao == FINALIZAR_O_PROGRAMA)
    {
        return;
    }

    menuUser(sade);
}

void menuMedico(tSADE *sade)
{
    printf("####################### MENU PRINCIPAL #########################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("    (%d) REALIZAR CONSULTA\n", REALIZAR_CONSULTA);
    printf("    (%d) BUSCAR PACIENTES\n", BUSCAR_PACIENTES);
    printf("    (%d) RELATORIO GERAL\n", RELATORIO_GERAL);
    printf("    (%d) FILA DE IMPRESSAO\n", FILA_DE_IMPRESSAO);
    printf("    (%d) FINALIZAR O PROGRAMA\n", FINALIZAR_O_PROGRAMA);
    printf("###############################################################\n");

    int opcao;

    scanf("%d%*c", &opcao);

    if (opcao == REALIZAR_CONSULTA)
    {
        /* code */
    }
    else if (opcao == BUSCAR_PACIENTES)
    {
        /* code */
    }
    else if (opcao == RELATORIO_GERAL)
    {
        /* code */
    }
    else if (opcao == FILA_DE_IMPRESSAO)
    {
        /* code */
    }
    else if (opcao == FINALIZAR_O_PROGRAMA)
    {
        return;
    }

    menuMedico(sade);
}

void cadastroSecretario(tSADE *sade)
{
    printf("####################### MENU PRINCIPAL #########################\n");

    tSecretario *secretario = criaSecretario();

    if (staffExisteCPF(sade, retornaCPF(pessoaSecretario(secretario))))
    {
        desalocaSecretario(secretario);
        printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA.\n");
        return;
    }
    else
    {
        sade->secretarios = realloc(sade->secretarios, sade->qtdSecretarios + 1 * sizeof(tSecretario *));

        sade->secretarios[sade->qtdSecretarios] = secretario;

        sade->qtdSecretarios++;

        printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
        printf("###############################################################\n");

        scanf("%*c%*c");

        return;
    }
}

void cadastroMedico(tSADE *sade)
{
    printf("####################### MENU PRINCIPAL #########################\n");

    tMedico *medico = criaMedico();

    if (staffExisteCPF(sade, retornaCPF(pessoaMedico(medico))))
    {
        desalocaMedico(medico);
        printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA.\n");
        return;
    }
    else
    {
        sade->medicos = realloc(sade->medicos, sade->qtdMedicos + 1 * sizeof(tMedico *));

        sade->medicos[sade->qtdMedicos] = medico;

        sade->qtdMedicos++;

        printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
        printf("###############################################################\n");

        scanf("%*c");

        return;
    }
}

void cadastroPaciente(tSADE *sade)
{
    printf("####################### MENU PRINCIPAL #########################\n");

    tPaciente *paciente = criaPaciente();

    if (pacienteExisteCPF(sade, retornaCPF(pessoaPaciente(paciente))))
    {
        desalocaPaciente(paciente);
        printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA.\n");
        return;
    }
    else
    {
        sade->pacientes = realloc(sade->pacientes, sade->qtdPacientes + 1 * sizeof(tPaciente *));

        sade->pacientes[sade->qtdPacientes] = paciente;

        sade->qtdPacientes++;

        printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
        printf("###############################################################\n");

        scanf("%*c");

        return;
    }
}

int staffExisteCPF(tSADE *sade, char *CPF)
{
    int i;

    for (i = 0; i < sade->qtdMedicos; i++)
    {
        if (ehIgualCPF(pessoaMedico(sade->medicos[i]), CPF))
        {
            return 1;
        }
    }

    for (i = 0; i < sade->qtdSecretarios; i++)
    {
        if (ehIgualCPF(pessoaSecretario(sade->secretarios[i]), CPF))
        {
            return 1;
        }
    }

    return 0;
}

int pacienteExisteCPF(tSADE *sade, char *CPF)
{
    int i;

    for (i = 0; i < sade->qtdPacientes; i++)
    {
        if (ehIgualCPF(pessoaPaciente(sade->pacientes[i]), CPF))
        {
            return 1;
        }
    }

    return 0;
}
