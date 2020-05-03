#ifndef TDA_GGPA__H
#define TDA_GGPA__H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "TDA_vector.h"
#define TIPO_MSJ_GPGGA "$GPGGA"
#define ANCHO_MSJ_GPGGA 6
#define MAX_GPGGA 75
#define LARGO_GPGGA 70
#define CANT_CAMPOS 14
#define MAX_LARGO_CAMPO 15
#define MAX_DELIMITADORES 1
#define POS_LATITUD 2
#define POS_UNIDAD_LATITUD 3
#define POS_LONGITUD 4
#define POS_UNIDAD_LONGITUD 5
#define POS_ALTURA_NIVEL_MAR 9
#define ANCHO_GRADOS_LAT 2
#define ANCHO_GRADOS_LON 3
#define ANCHO_MINUTOS 7
#define UNIDAD_SUR "S"
#define UNIDAD_OESTE "W"
#define CONSTANTE_A_DECIMAL 60
#define MASCARA_7BITS 0x7F

typedef struct {
    float latitud;
    float longitud;
    float altura_nivel_mar;
}t_registro_gga;

status_t es_registro_gpgga (char* , bool_t* );

status_t gps_borar_registro (void* );

status_t agregar_elemento_gps (void** , void* , size_t);

status_t procesar_registro_gps (t_registro_gga* , char* );

status_t suma_de_verificacion (char* , bool_t*);

status_t convertir_registro (t_registro_gga* , char[CANT_CAMPOS][MAX_LARGO_CAMPO]);

#endif
