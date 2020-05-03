#ifndef ERRORES__H
#define ERRORES__H
#include <stdlib.h>
#include "types.h"
#define MAX_ERRORS 8
#define MSJ_OK "Proceso realizado.\n"
#define MSJ_ERROR_PUNTERO_NULO "No se puden leer los datos.\n"
#define MSJ_ERROR_ARGS "Argumentos inválidos.\n"
#define MSJ_ERROR_FORMATO "Formato inválido.\n"
#define MSJ_ERROR_RUTA "Ruta inválida.\n"
#define MSJ_ERROR_MEMORIA "Falta de memoria.\n"
#define MSJ_ERROR_APERTURA_ARCHIVO "No se pudo abrir el archivo de texto.\n"
#define MSJ_ERROR_REGISTRO_INVALIDO "El registro es inválido.\n"

status_t imprimir_error(status_t);

#endif
