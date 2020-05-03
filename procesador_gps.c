#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "TDA_vector.h"
#include "registros_gps.h"
#include "procesador_gps.h"

status_t procesar_registros_gps (t_TDA_vector** vector, FILE* archivo_txt)
{
    status_t st;
    char reg[MAX_GPGGA+2];
    bool_t tipo_gpgga;
    t_registro_gga* elemento;
    size_t i=0; 

    if(vector == NULL || archivo_txt == NULL)
        return ERROR_PUNTERO_NULO;

    while(fgets(reg, MAX_GPGGA+2 , archivo_txt) != NULL)
    {

        if((st = (es_registro_gpgga(reg, &tipo_gpgga)) != OK))
            return st;

        if(tipo_gpgga == FALSE)
            continue;

	if((st = (suma_de_verificacion(reg+1 , &tipo_gpgga))) != OK)
	    return st;	

        if(tipo_gpgga == FALSE)
            continue;

        if((elemento = (t_registro_gga*)malloc(sizeof(t_registro_gga))) == NULL)
	{
	    for(i=0 ; i<(*vector)->cant_elementos ; i++)
            {
               if((st = (*vector)->destructor((*vector)->elementos[i])) != OK)
                   return st;
            }
            return ERROR_PUNTERO_NULO;
	}

        if((st = (procesar_registro_gps(elemento , reg)) != OK))
            return st;

        if((st = TDA_vector_agregar_elemento(vector , elemento , agregar_elemento_gps)) != OK)
            return st;

    }

    return OK;
}
