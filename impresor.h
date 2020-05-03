#ifndef IMPRESOR__H
#define IMPRESOR__H
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "registros_gps.h"
#include "TDA_vector.h"
#define KML_ENCABEZADO "<?xml version=\"1.0\" encoding=\"UTF-8\"?> <kml xmlns=\"http://www.opengis.net/kml/2.2\">"
#define KML_NOMBRE "Rutas"
#define KML_DESCRIPCION "Ejemplos de rutas"
#define KML_ESTILO_ID "yellowLineGreenPoly"
#define KML_COLOR "7f00ffff"
#define KML_ANCHO 4
#define KML_COLOR2 "7f00ff00"
#define KML_NOMBRE_LUGAR "Relieve absoluto"
#define KML_DESCRIPCION_LUGAR "Pared verde transparente con contornos amarillos"
#define KML_ESTILO_URL "#yellowLineGreenPoly"
#define KML_EXTRUDE 1
#define KML_TESSELLATE 1
#define KML_ALTITUD_MODO "absolute"
#define DELIMIT_CSV "|"

status_t imprimir_TDA_vector(t_TDA_vector** , t_formato , FILE* );

status_t imprimir_formato_csv(void** , size_t , FILE* );

status_t imprimir_formato_kml(void** , size_t , FILE* );

#endif
