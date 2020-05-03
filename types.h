#ifndef TYPES__H
#define TYPES__H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_LARGO_CADENA 50

typedef enum{
    OK,
    ERROR_PUNTERO_NULO,
    ERROR_ARGS_INVALIDOS,
    ERROR_FORMATO_INVALIDO,
    ERROR_RUTA_INVALIDA,
    ERROR_MEMORIA_INSUFICIENTE,
    ERROR_APERTURA_ARCHIVO,
    ERROR_REGISTRO_INVALIDO
}status_t;

typedef enum{
    FMT_SALIDA_CSV=0,
    FMT_SALIDA_KML=1
}t_formato;

typedef struct{
    t_formato formato;
    char entrada[MAX_LARGO_CADENA];
    char salida[MAX_LARGO_CADENA];
}t_config;

typedef enum{TRUE , FALSE}bool_t;


#endif
