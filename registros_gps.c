#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "TDA_vector.h"
#include "registros_gps.h"

status_t es_registro_gpgga (char* line , bool_t* tipo_gpgga)
{
    *tipo_gpgga = FALSE;

    if(line == NULL || tipo_gpgga == NULL)
        return ERROR_PUNTERO_NULO;

    if(strncmp(line , TIPO_MSJ_GPGGA , ANCHO_MSJ_GPGGA) == 0)
        *tipo_gpgga = TRUE;

    if(strlen(line) < LARGO_GPGGA)
	*tipo_gpgga = FALSE;

    return OK;
}

status_t gps_borar_registro(void* reg)
{
    if(reg == NULL)
        return ERROR_PUNTERO_NULO;

    free(reg);

    reg = NULL;

    return OK;
}

status_t agregar_elemento_gps (void** elementos , void* elemento , size_t cant_elementos)
{
    if(elementos == NULL || elemento == NULL)
        return ERROR_PUNTERO_NULO;

    elementos[cant_elementos] = elemento;

    return OK;
}

status_t procesar_registro_gps(t_registro_gga* elemento_gga , char* registro)
{
    char campos[CANT_CAMPOS][MAX_LARGO_CAMPO];
    char* aux = registro;
    char* campo_actual;
    char dels_gps_registro[MAX_DELIMITADORES] = ",";
    size_t i,j;
    status_t st;

    if(elemento_gga == NULL || registro == NULL)
        return ERROR_PUNTERO_NULO;

    /*Inicializa el arreglo de char, asi después temp queda apuntando en '\0' donde no hay dato */
    for(i=0 ; i < CANT_CAMPOS ; i++)
    {
        for(j=0 ; j < MAX_LARGO_CAMPO ; j++)
        {
           campos[i][j] = '\0';
        }
	
    }

    for(i = 0 ; (campo_actual = strtok(aux , dels_gps_registro)) != NULL ; aux = NULL)
    {
        strcpy(campos[i] , campo_actual);
        i++;
    }

    if((st = (convertir_registro(elemento_gga , campos))) != OK)
        return st;

    return OK;
}

status_t convertir_registro (t_registro_gga* elemento_gga , char campos[CANT_CAMPOS][MAX_LARGO_CAMPO])
{
    char* temp;
    char grados_latitud[ANCHO_GRADOS_LAT];
    char minutos_latitud[ANCHO_MINUTOS];
    char grados_longitud[ANCHO_GRADOS_LON];
    char minutos_longitud[ANCHO_MINUTOS];
    float grados_dec;
    float minutos_dec;

    if(elemento_gga == NULL || campos == NULL)
        return ERROR_PUNTERO_NULO;

    memcpy(grados_latitud , campos[POS_LATITUD] , ANCHO_GRADOS_LAT);
	
    memcpy(minutos_latitud , campos[POS_LATITUD]+ANCHO_GRADOS_LAT , ANCHO_MINUTOS);

    grados_dec = strtod(grados_latitud , &temp );
    
    if(*temp)
        return ERROR_REGISTRO_INVALIDO;

    minutos_dec = strtod(minutos_latitud , &temp );
    
    if(*temp)
        return ERROR_REGISTRO_INVALIDO;


    elemento_gga->latitud = grados_dec + (minutos_dec / CONSTANTE_A_DECIMAL);

    if(!strcmp(campos[POS_UNIDAD_LATITUD] , UNIDAD_SUR))
        elemento_gga->latitud = -(elemento_gga->latitud);

    memcpy(grados_longitud , campos[POS_LONGITUD] , ANCHO_GRADOS_LON);
	
    memcpy(minutos_longitud , campos[POS_LONGITUD]+ANCHO_GRADOS_LON , ANCHO_MINUTOS);

    grados_dec = strtod(grados_longitud , &temp );
    
    if(*temp)
        return ERROR_REGISTRO_INVALIDO;

    minutos_dec = strtod(minutos_longitud , &temp );
    
    if(*temp)
        return ERROR_REGISTRO_INVALIDO;


    elemento_gga->longitud = grados_dec + (minutos_dec / CONSTANTE_A_DECIMAL);

    if(!strcmp(campos[POS_UNIDAD_LONGITUD] , UNIDAD_OESTE))
        elemento_gga->longitud = -(elemento_gga->longitud);

    elemento_gga->altura_nivel_mar = strtod(campos[POS_ALTURA_NIVEL_MAR] , &temp );

    if(*temp)
        return ERROR_REGISTRO_INVALIDO;

    return OK;

}

status_t suma_de_verificacion(char* registro , bool_t* mensaje_verificado)
{
    unsigned char suma = 0;
    unsigned char suma_de_ver;
    char fin_suma_ver = '*';
    char* temp;
    size_t i;

    if(registro ==NULL || mensaje_verificado == NULL)
        return ERROR_PUNTERO_NULO;

    for(i=0 ; registro[i] != fin_suma_ver ; i++)
    {
	suma = suma^(registro[i]&MASCARA_7BITS);
    }

    suma_de_ver = strtoul(&registro[i+1] , &temp , 16);

    if(suma_de_ver == suma)
        *mensaje_verificado = TRUE;

    else 
	*mensaje_verificado = FALSE;


    return OK;

}
