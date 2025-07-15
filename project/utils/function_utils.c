#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "function_utils.h"

void salvar(Instrumento instrumentos[], int total)
{
    FILE *f = fopen(ARQ, "w");
    if (!f)
    {
        return;
    }
    
    time_t h = time(NULL);
    fprintf(f, "%s", ctime(&h));

    for (int i = 0; i < total; i++)
    {
        fprintf(f, "%d| Nome: %s Naipe: %s R$%.2f\n",
                instrumentos[i].id,
                instrumentos[i].nome,
                instrumentos[i].naipe,
                instrumentos[i].preco);
    }

    fprintf(f, "\nSALVE ESSE ARQUIVO ANTES DE TERMINAR A EXECUÇÃO DO PROGRAMA!");
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

    int id, maior = 0;
    char nome[STR], naipe[STR];
    float preco;
    *total = 0;

    while (fscanf(f, "%d| Nome: %29[^|] Naipe: %29[^R$] R$%f\n", &id, nome, naipe, &preco) == 4 && *total < ESTOQUE)
    {
        instrumentos[*total].id = id;
        strcpy(instrumentos[*total].nome, nome);
        strcpy(instrumentos[*total].naipe, naipe);
        instrumentos[*total].preco = preco;

        if (id > maior)
        {
            maior = id;
        }

        (*total)++;
    }

    *proxId = maior + 1;
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
