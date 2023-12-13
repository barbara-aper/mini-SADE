#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tSADE.h"
#include "tPaciente.h"
#include "tFila.h"
#include "tConsulta.h"
#include "tBusca.h"
#include "tRelatorio.h"

typedef struct tSADE
{
    int qtdSecretarios;
    int qtdMedicos;
    int qtdPacientes;
    tPaciente **pacientes;
    tMedico **medicos;
    tSecretario **secretarios;
    tFila *fila;
    char path[300];
    char dbPath[300];
} tSADE;


tSADE *abreSade(char *path, char *dbPath)
{
    tSADE *sade = (tSADE *)malloc(sizeof(tSADE));

    if (sade == NULL)
        return NULL;

    int primeiraVez = 0;

    sade->qtdSecretarios = 0;
    sade->qtdMedicos = 0;
    sade->qtdPacientes = 0;
    sade->secretarios = NULL;
    sade->medicos = NULL;
    sade->pacientes = NULL;
    strcpy(sade->path, path);
    strcpy(sade->dbPath, dbPath);
    sade->fila = criaFila();

    char caminhoSecretarios[500], caminhoMedicos[500], caminhoPacientes[500];

    sprintf(caminhoSecretarios, "%s/secretarios.bin", dbPath);

    sprintf(caminhoMedicos, "%s/medicos.bin", dbPath);

    sprintf(caminhoPacientes, "%s/pacientes.bin", dbPath);

    FILE *arquivoMedicos = fopen(caminhoMedicos, "rb");

    if (arquivoMedicos)
    {
        sade->medicos = recuperaMedicos(arquivoMedicos, &sade->qtdMedicos);
        fclose(arquivoMedicos);
    }
    else
    {
        sade->medicos = (tMedico **)calloc(1, sizeof(tMedico *));
        primeiraVez++;
    }

    FILE *arquivoSecretarios = fopen(caminhoSecretarios, "rb");

    if (arquivoSecretarios)
    {
        sade->secretarios = recuperaSecretarios(arquivoSecretarios, &sade->qtdSecretarios);
        fclose(arquivoSecretarios);
    }
    else
    {
        sade->secretarios = (tSecretario **)calloc(1, sizeof(tSecretario *));
        primeiraVez++;
    }

    FILE *arquivoPacientes = fopen(caminhoPacientes, "rb");

    if (arquivoPacientes)
    {
         sade->pacientes = recuperaPacientes(arquivoPacientes, &sade->qtdPacientes);
         fclose(arquivoPacientes);
    }
    else
    {
        sade->pacientes = (tPaciente **)calloc(1, sizeof(tPaciente *));
        primeiraVez++;
    }

    if (primeiraVez == 3)
        iniciaSADE(sade);

    printf("\n\n\nNUMERO DE PACIENTES: %d\n", sade->qtdPacientes);
    printf("NUMERO DE SECRETARIOS: %d\n", sade->qtdSecretarios);
    printf("NUMERO DE MEDICOS: %d\n\n\n", sade->qtdMedicos);

    if (sade->qtdMedicos > 1)
    {
        printf("%s", retornaNome(pessoaMedico(sade->medicos[1])));
    }
    

    return sade;
}

void desalocaSADE(void *dado)
{
    if (dado == NULL)
        return;

    tSADE *sade = (tSADE *)dado;

    int i;

    salvaSecretarios(sade->secretarios, sade->dbPath, sade->qtdSecretarios);
    salvaMedicos(sade->medicos, sade->dbPath, sade->qtdMedicos);
    salvaPacientes(sade->pacientes, sade->dbPath, sade->qtdPacientes);

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
                return i + 1;
            }
            else
            {
                printf("###############################################################\n");
                return i + 1;
            }
        }
    }

    for (i = 0; i < sade->qtdMedicos; i++)
    {
        if (logouMedico(login, senha, sade->medicos[i]))
        {
            printf("###############################################################\n");
            return -(i + 1);
        }
        else
            continue;
    }

    printf("###############################################################\n");
    printf("SENHA INCORRETA OU USUARIO INEXISTENTE\n");

    return acessaSADE(sade);
}

void menuAdmin()
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
}

void menuUser()
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
}

void menuMedico()
{
    printf("####################### MENU PRINCIPAL #########################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("    (%d) REALIZAR CONSULTA\n", REALIZAR_CONSULTA);
    printf("    (%d) BUSCAR PACIENTES\n", BUSCAR_PACIENTES);
    printf("    (%d) RELATORIO GERAL\n", RELATORIO_GERAL);
    printf("    (%d) FILA DE IMPRESSAO\n", FILA_DE_IMPRESSAO);
    printf("    (%d) FINALIZAR O PROGRAMA\n", FINALIZAR_O_PROGRAMA);
    printf("###############################################################\n");
}

void menu(int cargo)
{
    if (cargo == LOGIN_ADMIN)
        menuAdmin();
    else if (cargo == LOGIN_USER)
        menuUser();
    else if (cargo == LOGIN_MED)
        menuMedico();
    else
        return;
}

void opcoesAdmin(int opcao, tSADE *sade, tSecretario *secretario)
{
    if (opcao == CADASTRAR_SECRETARIO)
        cadastroSecretario(sade);
    else if (opcao == CADASTRAR_MEDICO)
        cadastroMedico(sade);
    else if (opcao == CADASTRAR_PACIENTE)
        cadastroPaciente(sade);
    else if (opcao == REALIZAR_CONSULTA)
    {
        printf("#################### CONSULTA MEDICA #######################\n");
        printf("CPF DO PACIENTE: ");

        char CPF[15];

        scanf("%[^\n]%*c", CPF);

        int i, paciente = -1;
        for (i = 0; i < sade->qtdPacientes; i++)
        {
            if (!strcmp(CPF, retornaCPF(pessoaPaciente(sade->pacientes[i]))))
            {
                paciente = i;
                break;
            }
        }

        if (paciente == -1)
        {
            printf("PACIENTE SEM CADASTRO\n");
            printf("PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
            printf("###############################################################\n");
            scanf("%*c%*c");
            return;
        }
        else
            RealizaConsulta(secretario, sade->pacientes[paciente], sade->fila, SECRETARIO);
    }
    else if (opcao == BUSCAR_PACIENTES)
    {
        buscaPacientes(sade->pacientes, sade->qtdPacientes, sade->fila);
    }
    else if (opcao == RELATORIO_GERAL)
    {
        relatorioGeral(sade->pacientes, sade->qtdPacientes, sade->fila);
    }
    else if (opcao == FILA_DE_IMPRESSAO)
    {
        printf("################ FILA DE IMPRESSAO MEDICA ##################\n");
        printf("ESCOLHA UMA OPCAO:\n");
        printf("    (1) EXECUTAR FILA DE IMPRESSAO\n");
        printf("    (2) RETORNAR AO MENU PRINCIPAL\n");
        printf("############################################################\n");

        int opcaoFila;

        scanf("%d%*c", &opcaoFila);

        if (opcaoFila == 1)
            imprimeFila(sade->fila, sade->path);
    }
}

void opcoesUser(int opcao, tSADE *sade, tSecretario *secretario)
{
    if (opcao == CADASTRAR_MEDICO)
        cadastroMedico(sade);
    else if (opcao == CADASTRAR_PACIENTE)
        cadastroPaciente(sade);
    else if (opcao == BUSCAR_PACIENTES)
    {
        buscaPacientes(sade->pacientes, sade->qtdPacientes, sade->fila);
    }
    else if (opcao == RELATORIO_GERAL)
    {
        relatorioGeral(sade->pacientes, sade->qtdPacientes, sade->fila);
    }
    else if (opcao == FILA_DE_IMPRESSAO)
    {
        imprimeFila(sade->fila, sade->path);
    }
}

void opcoesMedico(int opcao, tSADE *sade, tMedico *medico)
{
    if (opcao == REALIZAR_CONSULTA)
    {
        printf("#################### CONSULTA MEDICA #######################\n");
        printf("CPF DO PACIENTE: ");

        char CPF[15];

        scanf("%[^\n]%*c", CPF);

        int i, paciente = -1;
        for (i = 0; i < sade->qtdPacientes; i++)
        {
            if (!strcmp(CPF, retornaCPF(pessoaPaciente(sade->pacientes[i]))))
            {
                paciente = i;
                break;
            }
        }

        if (paciente == -1)
        {
            printf("PACIENTE SEM CADASTRO\n");
            printf("PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
            printf("###############################################################\n");
            scanf("%*c%*c");
            return;
        }
        else
            RealizaConsulta(medico, sade->pacientes[paciente], sade->fila, MEDICO);
    }
    else if (opcao == BUSCAR_PACIENTES)
    {
        buscaPacientes(sade->pacientes, sade->qtdPacientes, sade->fila);
    }
    else if (opcao == RELATORIO_GERAL)
    {
        relatorioGeral(sade->pacientes, sade->qtdPacientes, sade->fila);
    }
    else if (opcao == FILA_DE_IMPRESSAO)
    {
        imprimeFila(sade->fila, sade->path);
    }
}

void cadastroSecretario(tSADE *sade)
{
    printf("#################### CADASTRO SECRETARIO #######################\n");

    tSecretario *secretario = criaSecretario();

    if (staffExisteCPF(sade, retornaCPF(pessoaSecretario(secretario))))
    {
        desalocaSecretario(secretario);
        printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA.\n");
        return;
    }
    else
    {
        sade->secretarios = realloc(sade->secretarios, (sade->qtdSecretarios + 1) * sizeof(tSecretario *));

        sade->secretarios[sade->qtdSecretarios] = secretario;

        sade->qtdSecretarios++;

        printf("\nCADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
        printf("###############################################################\n");

        scanf("%*c%*c");

        return;
    }
}

void cadastroMedico(tSADE *sade)
{
    printf("#################### CADASTRO MEDICO #######################\n");

    tMedico *medico = criaMedico();

    if (staffExisteCPF(sade, retornaCPF(pessoaMedico(medico))))
    {
        desalocaMedico(medico);
        printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA.\n");
        return;
    }
    else
    {
        sade->medicos = realloc(sade->medicos, (sade->qtdMedicos + 1) * sizeof(tMedico *));

        sade->medicos[sade->qtdMedicos] = medico;

        sade->qtdMedicos++;

        printf("\nCADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
        printf("###############################################################\n");

        scanf("%*c");

        return;
    }
}

void cadastroPaciente(tSADE *sade)
{
    printf("#################### CADASTRO PACIENTE #######################\n");

    tPaciente *paciente = criaPaciente();

    if (pacienteExisteCPF(sade, retornaCPF(pessoaPaciente(paciente))))
    {
        desalocaPaciente(paciente);
        printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA.\n");
        return;
    }
    else
    {
        sade->pacientes = realloc(sade->pacientes, (sade->qtdPacientes + 1) * sizeof(tPaciente *));

        sade->pacientes[sade->qtdPacientes] = paciente;

        sade->qtdPacientes++;

        printf("\nCADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
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

void buscaPacientes(tPaciente **pacientes, int nPacientes, tFila *fila)
{
    printf("#################### BUSCAR PACIENTES #######################\n");
    char nome[50];
    printf("NOME DO PACIENTE: ");
    scanf("%[^\n]%*c", nome);

    tBusca *busca = criaListaBusca(pacientes, nome, nPacientes, fila);

    if (busca == NULL)
    {
        printf("NENHUM PACIENTE ENCONTRADO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
        printf("############################################################\n");
        scanf("%*c%*c");
        return;
    }

    printf("PACIENTES ENCONTRADOS:\n");

    imprimeNaTelaLista(busca);

    printf("\n#################### BUSCAR PACIENTES #######################\n");
    printf("SELECIONE UMA OPCAO: \n");
    printf("    (1) ENVIAR LISTA PARA IMPRESSAO\n");
    printf("    (2) RETORNAR AO MENU PRINCIPAL\n");
    printf("###############################################################\n");

    int opcaoBusca;

    scanf("%d%*c", &opcaoBusca);

    if (opcaoBusca == 1)
    {
        InsereBuscaFila(busca, fila);
        printf("LISTA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU PRINCIPAL\n");
        scanf("%*c%*c");
        printf("###############################################################\n");
    }
    else
    {
        desalocaLista(busca);
        return;
    }
}

void relatorioGeral(tPaciente **pacientes, int nPacientes, tFila *fila)
{
    printf("#################### RELATORIO GERAL #######################\n");

    tRelatorio *relatorio = criaRelatorio(pacientes, nPacientes);

    imprimeNaTelaRelatorio(relatorio);

    printf("\nSELECIONE UMA OPCAO: \n");
    printf("    (1) ENVIAR LISTA PARA IMPRESSAO\n");
    printf("    (2) RETORNAR AO MENU PRINCIPAL\n");
    printf("###############################################################\n");

    int opcaoRelatorio;

    scanf("%d%*c", &opcaoRelatorio);

    if (opcaoRelatorio == 1)
    {
        printf("#################### RELATORIO GERAL #######################\n");
        insereDocumentoFila(fila, relatorio, imprimeNaTelaRelatorio, imprimeEmArquivoRelatorio, desalocaRelatorio);
        printf("RELATÓRIO ENVIADO PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
        scanf("%*c%*c");
        printf("############################################################\n");
    }
    else
    {
        desalocaRelatorio(relatorio);
        return;
    }
}

void rodaSADE(tSADE *sade)
{
    int login = acessaSADE(sade);

    int cargo;

    if (login > 0 && nivelAdmin(sade->secretarios[login - 1]))
        cargo = LOGIN_ADMIN;
    else if (login > 0 && !nivelAdmin(sade->secretarios[login - 1]))
        cargo = LOGIN_USER;
    else if (login < 0)
    {
        cargo = LOGIN_MED;
        login *= -1;
    }
    else
        return;

    while (1)
    {
        menu(cargo);

        int opcao;

        scanf("%d%*c", &opcao);

        if (opcao == FINALIZAR_O_PROGRAMA)
            break;

        if (cargo == LOGIN_ADMIN)
            opcoesAdmin(opcao, sade, sade->secretarios[login - 1]);
        else if (cargo == LOGIN_USER)
            opcoesUser(opcao, sade, sade->secretarios[login - 1]);
        else if (cargo == LOGIN_MED)
            opcoesMedico(opcao, sade, sade->medicos[login - 1]);
    }
}
