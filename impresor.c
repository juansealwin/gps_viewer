#include <stdio.h>
#include <stdlib.h>
#include "impresor.h"
#include "types.h"
#include "registros_gps.h"
#include "TDA_vector.h"

status_t imprimir_TDA_vector(t_TDA_vector** vector , t_formato formato , FILE* fo)
{
    if(vector == NULL)
        return ERROR_PUNTERO_NULO;

    switch(formato)
    {
        case FMT_SALIDA_CSV:

            imprimir_formato_csv((*vector)->elementos , (*vector)->cant_elementos ,  fo);

        break;

        case FMT_SALIDA_KML:


            imprimir_formato_kml((*vector)->elementos , (*vector)->cant_elementos ,  fo);


        break;
    }

    return OK;
}

status_t imprimir_formato_csv(void** elementos , size_t cant_elementos , FILE* fo)
{
    size_t i;
    t_registro_gga** registros = (t_registro_gga**) elementos;

    if(elementos == NULL || fo == NULL)
        return ERROR_PUNTERO_NULO;

    for (i=0 ; i < cant_elementos ; i++)
    {
        if(registros[i] == NULL)
            continue;

        fprintf(fo , "%.4f%s%.4f%s%.4f\n" , registros[i]->longitud , DELIMIT_CSV , registros[i]->latitud , DELIMIT_CSV , registros[i]->altura_nivel_mar);
    }

    return OK;
}

status_t imprimir_formato_kml(void** elementos , size_t cant_elementos , FILE* fo)
{
    size_t i;
    t_registro_gga** registros = (t_registro_gga**) elementos;

    if(elementos == NULL || fo == NULL)
        return ERROR_PUNTERO_NULO;

    fprintf(fo , "%s\n" , KML_ENCABEZADO);
    fprintf(fo , "\t<Document>\n");
    fprintf(fo , "\t\t<name>%s</name> \n" , KML_NOMBRE);
    fprintf(fo , "\t\t<description>%s</description>\n" , KML_DESCRIPCION);
    fprintf(fo , "\t\t<Style id=\"%s\"> \n" , KML_ESTILO_ID);
    fprintf(fo , "\t\t\t<LineStyle>\n");
    fprintf(fo , "\t\t\t\t<color>%s</color>\n" , KML_COLOR);
    fprintf(fo , "\t\t\t\t<width>%i</width>\n" , KML_ANCHO);
    fprintf(fo , "\t\t\t</LineStyle>\n");
    fprintf(fo , "\t\t\t<PolyStyle>\n");
    fprintf(fo , "\t\t\t\t<color>%s</color> \n" , KML_COLOR2);
    fprintf(fo , "\t\t\t</PolyStyle>\n");
    fprintf(fo , "\t\t</Style>\n");
    fprintf(fo , "\t\t<Placemark>\n");
    fprintf(fo , "\t\t\t<name>%s</name>\n" , KML_NOMBRE_LUGAR);
    fprintf(fo , "\t\t\t<description>%s</description>\n" , KML_DESCRIPCION_LUGAR);
    fprintf(fo , "\t\t\t<styleUrl>%s</styleUrl>\n" , KML_ESTILO_URL);
    fprintf(fo , "\t\t\t<LineString>\n");
    fprintf(fo , "\t\t\t\t<extrude>%i</extrude>\n" , KML_EXTRUDE);
    fprintf(fo , "\t\t\t\t<tessellate>%i</tessellate>\n" , KML_TESSELLATE);
    fprintf(fo , "\t\t\t\t <altitudeMode>%s</altitudeMode>\n" , KML_ALTITUD_MODO);
    fprintf(fo , "\t\t\t\t<coordinates>");

    for (i=0 ; i < cant_elementos ; i++)
    {
        if(registros[i] == NULL)
            continue;

        fprintf(fo ,"%.6f,%.6f,%.6f\n", registros[i]->longitud , registros[i]->latitud , registros[i]->altura_nivel_mar);
    }

    fprintf(fo , "\t\t\t\t</coordinates>");
    fprintf(fo , "\t\t\t</LineString>");
    fprintf(fo , "\t\t</Placemark>");
    fprintf(fo , "\t</Document>");
    fprintf(fo , "</kml>");

    return OK;
}
