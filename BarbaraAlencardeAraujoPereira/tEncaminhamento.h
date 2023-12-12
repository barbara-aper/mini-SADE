

#ifndef _ENCAMINHAMENTO_H_
#define _ENCAMINHAMENTO_H_

#define NOME_ARQUIVO_ENCAMINHAMENTO "encaminhamento.txt"

typedef struct tEncaminhamento tEncaminhamento;

tEncaminhamento *criaEncaminhamento(char *nomePaciente, char *CPF, char *nomeMedico, char *CRM, char *dataStr);

void desalocaEncaminhamento(void *dado);

void imprimeNaTelaEncaminhamento(void *dado);

void imprimeEmArquivoEncaminhamento(void *dado, char *path);

#endif