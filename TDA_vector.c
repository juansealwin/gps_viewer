#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "TDA_vector.h"
#include "registros_gps.h"

status_t TDA_vector_crear(t_TDA_vector ** vector)
{
    size_t i;

    if(( *vector = (t_TDA_vector*)malloc(sizeof(t_TDA_vector))) == NULL)
        return ERROR_MEMORIA_INSUFICIENTE;

    if(((*vector)->elementos = (void**)malloc(INIT_CHOP*sizeof(void*)))==NULL)
    {
        free(*vector);
        (*vector) = NULL;
        return ERROR_MEMORIA_INSUFICIENTE;
    }
    (*vector)->alloc_size = INIT_CHOP;

    /* Inicializa los elementos en NULL */
    for(i=0 ; i<(*vector)->alloc_size ; i++)
        (*vector)->elementos[i] = NULL;

    (*vector)->cant_elementos = 0;

    return OK;
}

status_t TDA_vector_agregar_elemento(t_TDA_vector** vector , void* nuevo_elemento , setter_t setter)
{
    void** aux;

    if(vector == NULL || nuevo_elemento == NULL)
        return ERROR_PUNTERO_NULO;

    if((*vector)->cant_elementos == (*vector)->alloc_size)
    {
        if((aux = realloc((*vector)->elementos , ((*vector)->alloc_size+1)*sizeof(void*))) == NULL)
        {
            free((*vector)->elementos);

            (*vector)->elementos = NULL;

            free(*vector);
  
            *vector = NULL;
 
            return ERROR_MEMORIA_INSUFICIENTE;
        }

        (*vector)->elementos = aux;

        (*vector)->alloc_size = (*vector)->alloc_size + INIT_CHOP;
    }

    setter((*vector)->elementos , nuevo_elemento , (*vector)->cant_elementos);

    
    (*vector)->cant_elementos++;
    
    return OK;
}

status_t TDA_vector_borrar(t_TDA_vector** vector)
{
    size_t i;
    status_t st;

    if(vector == NULL)
        return ERROR_PUNTERO_NULO;


    for(i=0 ; i<(*vector)->cant_elementos ; i++)
    {
            if((st = (*vector)->destructor((*vector)->elementos[i])) != OK)
                return st;
    }

    free((*vector)->elementos);

    (*vector)->elementos = NULL;

    free(*vector);

    *vector = NULL;

    return OK;
}

status_t TDA_vector_obtener_elemento(const t_TDA_vector* vector , size_t pos ,void* elemento)
{
    if(vector == NULL || elemento == NULL)
        return ERROR_PUNTERO_NULO;

    if( pos < 0 || pos > (vector->cant_elementos))
        return ERROR_ARGS_INVALIDOS;

    elemento = vector->elementos[pos];

    return OK;
}

status_t TDA_vector_inic_destructor(t_TDA_vector* vector , destructor_t destructor)
{
    if(vector == NULL)
        return ERROR_PUNTERO_NULO;

    vector->destructor = destructor;

    return OK;
}
