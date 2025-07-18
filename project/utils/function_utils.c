#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "function_utils.h"

void salvar(Instrumento instrumentos[], int total)
{
    FILE *f = fopen(ARQ, "w");
    if (!f)
    {
        return;
    }

    for (int i = 0; i < total; i++)
    {
        fprintf(f, "%d|%s|%s|%.2f\n",
                instrumentos[i].id,
                instrumentos[i].nome,
                instrumentos[i].naipe,
                instrumentos[i].preco);
    }

    fclose(f);
}

void carregar(Instrumento instrumentos[], int *total, int *proxId)
{
    FILE *f = fopen(ARQ, "r");
    if (!f)
    {
        *total = 0;
        *proxId = 1;
        return;
    }

    *total = 0;
    *proxId = 1;

    while (fscanf(f, "%d|%79[^|]|%79[^|]|%f\n",
                  &instrumentos[*total].id,
                  instrumentos[*total].nome,
                  instrumentos[*total].naipe,
                  &instrumentos[*total].preco) == 4)
    {
        if (instrumentos[*total].id >= *proxId)
        {
            *proxId = instrumentos[*total].id + 1;
        }
        (*total)++;
    }

    fclose(f);
}

bool cadastrar(Instrumento instrumentos[], char nome[], char naipe[], float preco, int *total, int *proxId)
{
    if (*total >= ESTOQUE || preco <= 0 || strlen(nome) == 0 || strlen(naipe) == 0)
    {
        return false;
    }

    for (int i = 0; nome[i]; i++)
    {
        if (!isspace(nome[i]))
        {
            break;
        }
        if (nome[i + 1] == '\0')
        {
            return false;
        }
    }

    for (int i = 0; naipe[i]; i++)
    {
        if (!isspace(naipe[i]))
        {
            break;
        }
        if (naipe[i + 1] == '\0')
        {
            return false;
        }
    }

    instrumentos[*total].id = (*proxId)++;
    strcpy(instrumentos[*total].nome, nome);
    strcpy(instrumentos[*total].naipe, naipe);
    instrumentos[*total].preco = preco;

    (*total)++;
    salvar(instrumentos, *total);
    return true;
}

bool alterar(Instrumento instrumentos[], int id, float novo, int *total)
{
    if (id <= 0 || novo <= 0)
    {
        return false;
    }

    for (int i = 0; i < *total; i++)
    {
        if (instrumentos[i].id == id)
        {
            instrumentos[i].preco = novo;
            salvar(instrumentos, *total);
            return true;
        }
    }

    return false;
}

bool remover(Instrumento instrumentos[], int id, int *total, int *proxId)
{
    if (id <= 0)
    {
        return false;
    }

    for (int i = 0; i < *total; i++)
    {
        if (instrumentos[i].id == id)
        {
            for (int j = i; j < *total - 1; j++)
            {
                instrumentos[j] = instrumentos[j + 1];
            }

            (*total)--;
            (*proxId)--;
            salvar(instrumentos, *total);
            return true;
        }
    }

    return false;
}
