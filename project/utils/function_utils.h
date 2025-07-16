#ifndef FUNCTION_UTILS_H
#define FUNCTION_UTILS_H

#include <stdbool.h>
#include "instrument_utils.h"

void salvar(Instrumento instrumentos[], int total);
bool cadastrar(Instrumento instrumentos[], char nome[], char naipe[], float preco, int *total, int *proxId);
bool alterar(Instrumento instrumentos[], int id, float novo, int *total);
bool remover(Instrumento instrumentos[], int id, int *total, int *proxId);

#endif
