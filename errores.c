#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "errores.h"

char* errores[MAX_ERRORS]={
    MSJ_OK,
    MSJ_ERROR_PUNTERO_NULO,
    MSJ_ERROR_ARGS,
    MSJ_ERROR_FORMATO,
    MSJ_ERROR_RUTA,
    MSJ_ERROR_MEMORIA,
    MSJ_ERROR_APERTURA_ARCHIVO,
    MSJ_ERROR_REGISTRO_INVALIDO
};

status_t imprimir_error(status_t status)
{
    fprintf(stderr , "%s " , errores[status]);
    return OK;
}
