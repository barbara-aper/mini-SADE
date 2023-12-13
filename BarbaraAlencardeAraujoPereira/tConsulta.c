#include "tConsulta.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menuConsulta()
{
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("ESCOLHA UMA OPCAO:\n");
	printf("    (%d) CADASTRAR LESAO\n", CADASTRAR_LESAO);
	printf("    (%d) GERAR RECEITA MEDICA\n", GERAR_RECEITA_MEDICA);
	printf("    (%d) SOLICITACAO DE BIOPSIA\n", SOLICITACAO_DE_BIOPSIA);
	printf("    (%d) ENCAMINHAMENTO\n", ENCAMINHAMENTO);
	printf("    (%d) ENCERRAR CONSULTA\n", ENCERRAR_CONSULTA);
    printf("############################################################\n");
}

void RealizaConsulta(void *agente, tPaciente *paciente, tFila *fila, eAgente cargo)
{
    printf("---\n");
    printf("- NOME: %s\n", retornaNome(pessoaPaciente(paciente)));
    printf("- DATA DE NASCIMENTO: %s\n", retornaNascimento(pessoaPaciente(paciente)));
    printf("---\n");

    char dataConsulta[15];
    int dia, mes, ano;
    
    printf("DATA DA CONSULTA: ");
    scanf("%d/%d/%d%*c", &dia, &mes, &ano);

    sprintf(dataConsulta, "%d/%d/%d", dia, mes, ano);

    infoPaciente(paciente);

    printf("############################################################\n");

    while (1)
    {
        menuConsulta();

        int opcao;
        scanf("%d%*c", &opcao);

        if (opcao == CADASTRAR_LESAO)
            cadastraLesao(paciente);
        else if (opcao == GERAR_RECEITA_MEDICA)
            geraReceitaMedica(paciente, agente, dataConsulta, fila, cargo);
        else if (opcao == SOLICITACAO_DE_BIOPSIA)
            solicitaBiopsia(paciente, agente, dataConsulta, fila, cargo);
        else if (opcao == ENCAMINHAMENTO)
            encaminhaPaciente(paciente, agente, dataConsulta, fila, cargo);
        else if (opcao == ENCERRAR_CONSULTA)
            break;
    }
}

void cadastraLesao(tPaciente *paciente)
{
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("CADASTRO DE LESAO:\n");
    adicionaLesao(paciente, criaLesao(qntdLesaoNova(paciente) + 1));
    printf("LESAO REGISTRADA COM SUCESSO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    scanf("%*c%*c");
    printf("############################################################\n");
}

void geraReceitaMedica(tPaciente *paciente, void *agente, char *data, tFila *fila, eAgente cargo)
{
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("RECEITA MEDICA:\n");

    char tipoMed[50];
    char nomeMed[50];
    char inst[100];
    int qtd;
    char tipoUso[7];
    eTipoUso tipo;

    printf("TIPO DE USO: ");
    scanf("%[^\n]%*c", tipoUso);
    printf("NOME DO MEDICAMENTO: ");
    scanf("%[^\n]%*c", nomeMed);
    printf("TIPO DE MEDICAMENTO: ");
    scanf("%[^\n]%*c", tipoMed);
    printf("QUANTIDADE: ");
    scanf("%d%*c", &qtd);
    printf("INSTRUCOES DE USO: ");
    scanf("%[^\n]%*c", inst);

    if (strcmp(tipoUso, "ORAL") == 0)
    {
        tipo = ORAL;
    }
    else
        tipo = TOPICO;

    if (cargo == MEDICO)
    {
        agente = (tMedico *)agente;

        tReceita *receita = criaReceita(retornaNome(pessoaPaciente(paciente)), tipo, nomeMed, tipoMed, inst,
                                         qtd, retornaNome(pessoaMedico(agente)), retornaCRM(agente), data);

        insereDocumentoFila(fila, receita, imprimeNaTelaReceita, imprimeEmArquivoReceita, desalocaReceita);
    }
    else if (cargo == SECRETARIO)
    {
        tReceita *receita = criaReceita(retornaNome(pessoaPaciente(paciente)), tipo, nomeMed, tipoMed, inst, 
                                        qtd, "\0", "\0", data);

        insereDocumentoFila(fila, receita, imprimeNaTelaReceita, imprimeEmArquivoReceita, desalocaReceita);
    }
    
    printf("RECEITA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    scanf("%*c%*c");
    printf("############################################################\n");
}

void solicitaBiopsia(tPaciente *paciente, void *agente, char *data, tFila *fila, eAgente cargo)
{
    printf("#################### CONSULTA MEDICA #######################\n");
    if (qntdLesao(paciente) == 0 || !possuiLesaoCirurgica(paciente))
        printf("NAO E POSSIVEL SOLICITAR BIOPSIA SEM LESAO CIRURGICA. ");
    else
    {
        if (cargo == MEDICO)
        {
            agente = (tMedico *)agente;

            insereDocumentoFila(fila, criaBiopsia(retornaNome(pessoaPaciente(paciente)), retornaCPF(pessoaPaciente(paciente)), retornaLesao(paciente), 
            qntdLesao(paciente), retornaNome(pessoaMedico(agente)), retornaCRM(agente), data), imprimeNaTelaBiopsia, imprimeEmArquivoBiopsia, desalocaBiopsia);
        }
        else if (cargo == SECRETARIO)
        {
            insereDocumentoFila(fila, criaBiopsia(retornaNome(pessoaPaciente(paciente)), retornaCPF(pessoaPaciente(paciente)), retornaLesao(paciente), 
            qntdLesao(paciente), "\0", "\0", data), imprimeNaTelaBiopsia, imprimeEmArquivoBiopsia, desalocaBiopsia);
        }
        
        printf("SOLICITACAO DE BIOPSIA ENVIADA PARA FILA DE IMPRESSAO. ");
    }

    printf("PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    scanf("%*c%*c");
    printf("############################################################\n");
}

void encaminhaPaciente(tPaciente *paciente, void *agente, char *data, tFila *fila, eAgente cargo)
{
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("ENCAMINHAMENTO:\n");

     if (cargo == MEDICO)
    {
        agente = (tMedico *)agente;

        insereDocumentoFila(fila, criaEncaminhamento(retornaNome(pessoaPaciente(paciente)), retornaCPF(pessoaPaciente(paciente)), 
        retornaNome(pessoaMedico(agente)), retornaCRM(agente), data), imprimeNaTelaEncaminhamento, imprimeEmArquivoEncaminhamento, desalocaEncaminhamento);
    }
    else if (cargo == SECRETARIO)
    {
        insereDocumentoFila(fila, criaEncaminhamento(retornaNome(pessoaPaciente(paciente)), retornaCPF(pessoaPaciente(paciente)), 
        "\0", "\0", data), imprimeNaTelaEncaminhamento, imprimeEmArquivoEncaminhamento, desalocaEncaminhamento);
    }
    
    printf("ENCAMINHAMENTO ENVIADO PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    scanf("%*c%*c");
    printf("############################################################\n");
}