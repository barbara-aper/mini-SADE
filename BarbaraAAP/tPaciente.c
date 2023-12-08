#include "tPaciente.h"
#include "tLesao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tPaciente
{
    tPessoa *pessoa;
    int diabetes;
    int fumante;
    int alergia;
    int cancer;
    int pele;
    tLesao **lesao;
} tPaciente;

tPaciente *criaPaciente()
{
    tPaciente *paciente = (tPaciente *)malloc(sizeof(tPaciente));

    if (paciente == NULL)
        return NULL;

    paciente->pessoa = criaPessoa();

    return paciente;
}

void desalocaPaciente(void *dado)
{
    if (dado == NULL)
        return;

    tPaciente *paciente = (tPaciente *)dado;

    desalocaPessoa(paciente->pessoa);
    free(paciente);
}

tPessoa *pessoaPaciente(tPaciente *paciente)
{
    return paciente->pessoa;
}
