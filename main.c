#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "TDA_vector.h"
#include "procesador_gps.h"
#include "registros_gps.h"
#include "impresor.h"
#include "errores.h"
#define POS_TXT 2
#define POS_SALIDA 4
#define POS_ENTRADA 5
#define POS_FMT 2
#define POS_
#define MAX_ARGS 6
#define LARGO_FORMATO 3

char* dic_formatos[]={
    "csv",
    "kml",
    "txt"
};

status_t validar_argumentos(int argc , char* argv[] , t_config* config)
{ 
    size_t largo_salida; 
    size_t largo_entrada;

    if(argv == NULL || config == NULL)
        return ERROR_PUNTERO_NULO;

   largo_salida = strlen(argv[POS_SALIDA]);
   largo_entrada = strlen(argv[POS_ENTRADA]);

    if(argc != MAX_ARGS)
        return ERROR_ARGS_INVALIDOS;
    
    if(!strcmp(argv[POS_FMT] , dic_formatos[FMT_SALIDA_CSV]))
        config->formato = FMT_SALIDA_CSV;
   
    else if(!strcmp(argv[POS_FMT] , dic_formatos[FMT_SALIDA_KML]))
        config->formato = FMT_SALIDA_KML;
    
    else
        return ERROR_FORMATO_INVALIDO;
    
    if(!strcmp(argv[POS_SALIDA] + largo_salida - LARGO_FORMATO , dic_formatos[config->formato]))
        strcpy(config->salida , argv[POS_SALIDA]);

    else
        return ERROR_RUTA_INVALIDA;

    if(!strcmp(argv[POS_ENTRADA] + largo_entrada - LARGO_FORMATO , dic_formatos[POS_TXT]))
        strcpy(config->entrada , argv[POS_ENTRADA]);
    
    else
        return ERROR_RUTA_INVALIDA;

    return OK;
}


int main(int argc , char* argv[])
{
    status_t st;
    FILE* archivo_entrada = NULL;
    FILE* archivo_salida = NULL;
    t_TDA_vector* vector;
    t_config config;


    if((st = (validar_argumentos(argc , argv , &config))) != OK)
    {
        if(imprimir_error(st) != OK)
            return st;
    }

    if((st = TDA_vector_crear(&vector)) != OK)
    {
        if(imprimir_error(st) != OK)
            return st;
    }

    if((st = TDA_vector_inic_destructor(vector , &gps_borar_registro)) != OK)
    {
        if(imprimir_error(st) != OK)
            return st;
    }

    if((archivo_entrada = fopen(config.entrada , "rt")) == NULL)
    {
        imprimir_error(ERROR_APERTURA_ARCHIVO);
        return ERROR_APERTURA_ARCHIVO;
    }

    if((st = procesar_registros_gps(&vector , archivo_entrada)) != OK)
    {
        if(imprimir_error(st) != OK)
            return st;
    }

    if((archivo_salida = fopen(config.salida , "wb")) == NULL)
    {
        imprimir_error(ERROR_APERTURA_ARCHIVO);
        return ERROR_APERTURA_ARCHIVO;
    }

    if((st = imprimir_TDA_vector(&vector , config.formato , archivo_salida)) != OK)
    {
        if(imprimir_error(st) != OK)
            return st;
    }

    if((st = TDA_vector_borrar(&vector)) != OK)
    {
        if(imprimir_error(st) != OK)
            return st;
    }

    if(fclose(archivo_entrada) == EOF)
        return EXIT_FAILURE;

    if(fclose(archivo_salida) == EOF)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
