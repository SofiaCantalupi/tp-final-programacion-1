#ifndef CAJA_H_INCLUDED
#define CAJA_H_INCLUDED
#include "time.h"

#define NOMBRE_ARCHIVO_CAJAS "cajas.BIN"
#define VALIDOS_ARREGLO_RESUMEN_STCAJA 4

typedef struct{
    char nombre[50];
    long int valor;
}stGastoVario;

typedef struct{
    int ID;
    int estado; //1 abierto 0 cerrado.
    struct tm fecha; // es un tipo de struct ya definido en time.h. Guarda la info de fecha y hora
    int ID_empleado;
    int turno;
    int monto_inicial;
    long int resumen_ventas[4]; //total de todas las ventas.
    stGastoVario gasto;
    long int diferencia;
    long int total_caja;
}stCaja;

struct tm obtener_fecha_actual();
void mostrar_fecha(struct tm tiempo);
stCaja abrir_caja();
int generar_ID_caja();
void mostrar_apertura_caja(stCaja caja);
void mostrar_archivo_cajas();
int verificar_estado_caja();
int retornar_ID_ultima_caja();
int retornar_monto_inicial_ultima_caja();
int retornar_turno_ultima_caja();
void cargar_arreglo_cierre_caja(long int arreglo[]);
void mostrar_arreglo_cierre_caja(long int arreglo[]);
stGastoVario cargar_gasto();
stCaja cerrar_caja();
void mostrar_archivo_ultimo_cierre();
void mostrar_cierre_caja_listado(stCaja caja);
long int sumar_montos_totales(long int monto_totales[], int validos, int i);
long int sumar_monto_efectivo(FILE* buffer_caja, FILE* buffer_ventas);
long int sumar_monto_debito(FILE* buffer_caja, FILE* buffer_ventas);
long int sumar_monto_credito(FILE* buffer_caja, FILE* buffer_ventas);
long int sumar_monto_transferencia(FILE* buffer_caja, FILE* buffer_ventas);
void mostrar_archivo_ultima_apertura();


#endif // CAJA_H_INCLUDED
