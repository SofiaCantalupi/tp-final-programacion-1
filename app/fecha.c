#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/////////// agregar Y MOSTRAR fecha venta
struct tm* obtener_fecha_actual_venta()
{
    time_t tiempo_crudo; //tipo de dato que guarda un entero que representa la cantidad de segundos desde las 00:00 hs del 1/1/1970 hasta la actualidad
    struct tm* tiempo;

    time(&tiempo_crudo); // funcion que devuelve la cantidad de segundos comentados arriba
    tiempo = localtime(&tiempo_crudo); // local timbre convierte la cantidad de segundos en datos que representan la hora local

    return tiempo;
}
/////////// mostrar fecha
void mostrar_fecha_ventas(struct tm tiempo)
{

    printf("|%02d:%02d:%02d %d/%d/%d|",tiempo.tm_hour,tiempo.tm_min,tiempo.tm_sec,tiempo.tm_mday,tiempo.tm_mon+1,tiempo.tm_year+1900);
    //tm_mon+1 ya que devuelve valores del 0 al 11.tm_year+1900 ya q devuelve los anios apartir de 1900.
}
