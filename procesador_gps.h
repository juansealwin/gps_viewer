#ifndef PROCESADOR_GPS__H
#define PROCESADOR_GPS__H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "TDA_vector.h"
#include "registros_gps.h"

status_t procesar_registros_gps (t_TDA_vector** , FILE*);

#endif
