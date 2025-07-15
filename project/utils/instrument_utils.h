#ifndef INSTRUMENT_UTILS_H
#define INSTRUMENT_UTILS_H

#define ESTOQUE 50
#define STR 80
#define ARQ "instrumentos.txt"

typedef struct
{
    int id;
    char nome[STR];
    char naipe[STR];
    float preco;
} Instrumento;

#endif