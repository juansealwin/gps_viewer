#ifndef TDA_VECTOR__H
#define TDA_VECTOR__H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "registros_gps.h"
#define INIT_CHOP 1

typedef status_t (*destructor_t)(void*);

typedef status_t (*setter_t)(void** , void* , size_t);

typedef struct {
    void** elementos;
    size_t cant_elementos;
    size_t alloc_size;
    destructor_t destructor;
}t_TDA_vector;

status_t TDA_vector_crear(t_TDA_vector ** );

status_t TDA_vector_agregar_elemento(t_TDA_vector** , void* , setter_t);

status_t TDA_vector_borrar(t_TDA_vector**);

status_t TDA_vector_obtener_elemento(const t_TDA_vector* , size_t , void*);

status_t TDA_vector_inic_destructor(t_TDA_vector* nodo , destructor_t);

#endif
