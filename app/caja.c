#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pila.h"
#include "caja.h"
#include "articulos.h"
#include "ventas.h"
#include "fecha.h"
#include "verificacion.h"

///Funciones cierre de caja////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Funcion que cierra el turno
stCaja cerrar_caja(){

    printf("\n-----------------------CIERRE DE CAJA--------------------\n");
    printf("_________________________________________________________\n\n");

    FILE* buffer_caja = fopen(NOMBRE_ARCHIVO_CAJAS, "a+b");
    FILE* buffer_ventas = fopen(NOMBRE_ARCHIVO_VENTAS, "rb");

    stCaja caja;
    char confirmacion;
    int i = 0;
    long int total_efectivo = 0;
    long int total_debito = 0;
    long int total_credito = 0;
    long int total_transferencia = 0;
    long int efectivo_esperado = 0;
    long int efectivo;
    long int diferencia;

    if(buffer_caja && buffer_ventas){
    caja.ID = generar_ID_caja();
    caja.estado = 0;
    caja.fecha = obtener_fecha_actual();
    caja.ID_empleado = retornar_ID_ultima_caja("cajas.BIN");
    caja.turno = retornar_turno_ultima_caja("cajas.BIN");
    caja.monto_inicial = retornar_monto_inicial_ultima_caja("cajas.BIN");

    total_efectivo = sumar_monto_efectivo(buffer_caja, buffer_ventas);
    caja.resumen_ventas[i] = total_efectivo;
    i++;

    total_debito = sumar_monto_debito(buffer_caja, buffer_ventas);
    caja.resumen_ventas[i] = total_debito;
    i++;

    total_credito = sumar_monto_credito(buffer_caja, buffer_ventas);
    caja.resumen_ventas[i] = total_credito;
    i++;

    total_transferencia = sumar_monto_transferencia(buffer_caja, buffer_ventas);
    caja.resumen_ventas[i] = total_transferencia;
    i++;

    caja.total_caja = sumar_montos_totales(caja.resumen_ventas,VALIDOS_ARREGLO_RESUMEN_STCAJA, 0);

    printf("Ingrese el efectivo que tiene al cerrar la caja:\n");
    fflush(stdin);
    scanf("%ld",&efectivo);

    printf("Desea cargar un gasto? (s/n)\n");
    fflush(stdin);
    scanf("%c",&confirmacion);
    if (confirmacion == 's'){
        caja.gasto = cargar_gasto();
    }else
    {
        caja.gasto.valor = 0;
        strcpy(caja.gasto.nombre,"no se realizaron gastos");
    }

    efectivo_esperado = (caja.monto_inicial + total_efectivo) - caja.gasto.valor; // calcula cuanto efectivo tendria que haber al cerrar la caja

    caja.diferencia = efectivo - efectivo_esperado;

    fseek(buffer_caja, 0,2); // me posiciono al final del archivo para guardar el registro
    fwrite(&caja, sizeof(stCaja), 1, buffer_caja);

    printf("\n********** CIERRE DE CAJA REALIZADO CON EXITO **********\n");
    //mostrar_cierre_caja(caja); //Lo sacaria para que el cierre nom�s cierre y despues mostrarlo aparte
    //printf("\n*****************************************************************************\n");

    fclose(buffer_caja);
    fclose(buffer_ventas);

    } else {
            printf("\nEl archivo no pudo abrirse.\n");
    }

    return caja;
}

//// Funcion que carga el gasto, permite ingresar una descripcion y el importe
stGastoVario cargar_gasto(){

    stGastoVario gasto;

    printf("Ingrese el descripcion del gasto que se ha realizado:\n");
    fflush(stdin);
    gets(gasto.nombre);
    printf("Ingrese el monto total gastado:\n");
    fflush(stdin);
    scanf("%ld",&gasto.valor);

        return gasto;
}

//////// Funcion que suma los montos totales de cada medio de pago
long int sumar_montos_totales(long int monto_totales[], int validos, int i){

    long int total;

    if(i == validos)
        total = 0;
    else
        total = monto_totales[i] + sumar_montos_totales(monto_totales, validos, i+1);

    return total;
}
/////// Funciones que calculan el total segun el medio de pago
long int sumar_monto_efectivo(FILE* buffer_caja, FILE* buffer_ventas) {

    long int resultado = 0;

    stCaja caja;
    stVenta venta;

    fseek(buffer_caja, sizeof(stCaja)*-1, 2); // voy al principio del ultimo registro de la caja y lo leo obtener la fecha
    fread(&caja, sizeof(stCaja), 1, buffer_caja);

    fseek(buffer_ventas, 0, 0); // me posiciono al principio del archivo ventas

    while(fread(&venta, sizeof(stVenta), 1, buffer_ventas) > 0) {
          if((venta.medio_pago == 1) && (venta.estado ==1) && (caja.fecha.tm_year == venta.fecha.tm_year) && (caja.fecha.tm_mon == venta.fecha.tm_mon) && (caja.fecha.tm_mday == venta.fecha.tm_mday) && (caja.ID == venta.ID_caja)){
            resultado += venta.monto_total; // sumo el monto de la venta. Se suma si concide la fecha con la fecha de la caja, el medio de pago es el indicado y si la venta esta activa
          }
    }
    return resultado;
}

long int sumar_monto_debito(FILE* buffer_caja, FILE* buffer_ventas){

    long int resultado = 0;

    stCaja caja;
    stVenta venta;

    fseek(buffer_caja, sizeof(stCaja)*-1, 2); // voy al principio del ultimo registro de la caja y lo leo obtener la fecha
    fread(&caja, sizeof(stCaja), 1, buffer_caja);

    fseek(buffer_ventas, 0, 0); // me posiciono al principio del archivo ventas

    while(fread(&venta, sizeof(stVenta), 1, buffer_ventas) > 0) {
          if((venta.medio_pago == 2) && (venta.estado ==1) && (caja.fecha.tm_year == venta.fecha.tm_year) && (caja.fecha.tm_mon == venta.fecha.tm_mon) && (caja.fecha.tm_mday == venta.fecha.tm_mday) && (caja.ID == venta.ID_caja)){
            resultado += venta.monto_total; // sumo el monto de la venta. Se suma si concide la fecha con la fecha de la caja, el medio de pago es el indicado y si la venta esta activa
          }
    }
    return resultado;
}

long int sumar_monto_credito(FILE* buffer_caja, FILE* buffer_ventas){

    long int resultado = 0;

    stCaja caja;
    stVenta venta;

    fseek(buffer_caja, sizeof(stCaja)*-1, 2); // voy al principio del ultimo registro de la caja y lo leo obtener la fecha
    fread(&caja, sizeof(stCaja), 1, buffer_caja);

    fseek(buffer_ventas, 0, 0); // me posiciono al principio del archivo ventas

    while(fread(&venta, sizeof(stVenta), 1, buffer_ventas) > 0) {
          if((venta.medio_pago == 3) && (venta.estado ==1) && (caja.fecha.tm_year == venta.fecha.tm_year) && (caja.fecha.tm_mon == venta.fecha.tm_mon) && (caja.fecha.tm_mday == venta.fecha.tm_mday) && (caja.ID == venta.ID_caja)){
            resultado += venta.monto_total; // sumo el monto de la venta. Se suma si concide la fecha con la fecha de la caja, el medio de pago es el indicado y si la venta esta activa
          }
    }
    return resultado;
}

long int sumar_monto_transferencia(FILE* buffer_caja, FILE* buffer_ventas){

    long int resultado = 0;

    stCaja caja;
    stVenta venta;

    fseek(buffer_caja, sizeof(stCaja)*-1, 2); // voy al principio del ultimo registro de la caja y lo leo obtener la fecha
    fread(&caja, sizeof(stCaja), 1, buffer_caja);

    fseek(buffer_ventas, 0, 0); // me posiciono al principio del archivo ventas

    while(fread(&venta, sizeof(stVenta), 1, buffer_ventas) > 0) {
          if((venta.medio_pago == 4) && (venta.estado ==1) && (caja.fecha.tm_year == venta.fecha.tm_year) && (caja.fecha.tm_mon == venta.fecha.tm_mon) && (caja.fecha.tm_mday == venta.fecha.tm_mday) && (caja.ID == venta.ID_caja)){
            resultado += venta.monto_total; // sumo el monto de la venta. Se suma si concide la fecha con la fecha de la caja, el medio de pago es el indicado y si la venta esta activa
          }
    }
    return resultado;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Funciones para retornar info
int retornar_ID_ultima_caja(){

    FILE *buffer;
    stCaja caja;
    int ID;
    buffer = fopen(NOMBRE_ARCHIVO_CAJAS,"rb");
    if (buffer != NULL){

        fseek(buffer,sizeof(stCaja)*(-1),2);
        fread(&caja,sizeof(stCaja),1,buffer);
        ID = caja.ID_empleado;

    fclose(buffer);
    } else {
            printf("\nEl archivo no pudo abrirse.\n");
    }
            return ID;
}

int retornar_turno_ultima_caja(){

    FILE *buffer;
    stCaja caja;
    int turno;
    buffer = fopen(NOMBRE_ARCHIVO_CAJAS,"rb");
    if (buffer != NULL){

        fseek(buffer,sizeof(stCaja)*(-1),2);
        fread(&caja,sizeof(stCaja),1,buffer);
        turno = caja.turno;

    fclose(buffer);
    } else {
            printf("\nEl archivo no pudo abrirse.\n");
    }
            return turno;
}

int retornar_monto_inicial_ultima_caja(){

    FILE *buffer;
    stCaja caja;
    int monto_inicial;
    buffer = fopen(NOMBRE_ARCHIVO_CAJAS,"rb");
    if (buffer != NULL){

        fseek(buffer,sizeof(stCaja)*(-1),2);
        fread(&caja,sizeof(stCaja),1,buffer);
        monto_inicial = caja.monto_inicial;

    fclose(buffer);
    } else {
            printf("\nEl archivo no pudo abrirse.\n");
    }
            return monto_inicial;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///Funcion para mostrar el cierre
void mostrar_cierre_caja(stCaja caja){

    int i = 0;

    mostrar_fecha(caja.fecha);

    printf("| Cierre de caja N. %d |",caja.ID);
    printf("| ID empleado: %d |",caja.ID_empleado);
    if (caja.turno == 1){
    printf("| Turno maniana |\n");
    } else if (caja.turno == 2){
    printf("| Turno noche |\n");
    }
    printf("\n| Monto inicial: $%ld |\n", caja.monto_inicial);
    printf("| Gastos -> Descripcion: %s Monto: $%ld |", caja.gasto.nombre, caja.gasto.valor);

    printf("\n| Total EFECTIVO: $%ld|",caja.resumen_ventas[i]);
    printf("\n| Total DEBITO: $%ld|",caja.resumen_ventas[i+1]);
    printf("\n| Total CREDITO: $%ld|",caja.resumen_ventas[i+2]);
    printf("\n| Total TRANSFERENCIA: $%ld|\n",caja.resumen_ventas[i+3]);

    printf("\n| TOTAL: $%ld |", caja.total_caja);
    printf("\n* monto total de todos los medios de pago");

    printf("\n\n| Arqueo final: %ld |\n", caja.diferencia);

}

void mostrar_archivo_ultimo_cierre(){

    FILE *buffer;
    stCaja caja;
    int estado;
    buffer = fopen(NOMBRE_ARCHIVO_CAJAS,"rb");
    if (buffer != NULL){

        fseek(buffer,sizeof(stCaja)*(-1),2);
        fread(&caja,sizeof(stCaja),1,buffer);
        estado = caja.estado;
        if (estado == 0){
        mostrar_cierre_caja(caja);
        } else if (estado == 1){
        fseek(buffer,sizeof(stCaja)*(-2),2);
        fread(&caja,sizeof(stCaja),1,buffer);
        mostrar_cierre_caja(caja);
        }

        fclose(buffer);
    } else {
            printf("\nEl archivo no pudo abrirse.\n");
    }
}
/// Funcion para mostrar el archivo de cajas, depende el tipo de caja (cierre o apertura) llama a la funcion correspondiente
void mostrar_archivo_cajas(){

    FILE *buffer;
    stCaja caja;
    buffer = fopen(NOMBRE_ARCHIVO_CAJAS,"rb");
    if (buffer != NULL){

        while(fread(&caja, sizeof(stCaja), 1, buffer) > 0){
                if (caja.estado == 1){
                mostrar_apertura_caja(caja);
printf("\n*****************************************************************************\n");

                printf("\n");
                } else if(caja.estado == 0) {
                mostrar_cierre_caja(caja);
    printf("\n*****************************************************************************\n");
                printf("\n");
                }
    }
        fclose(buffer);
    } else {
            printf("\nEl archivo no pudo abrirse.\n");
    }
}

///Funciones apertura////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Abre el turno de la caja
stCaja abrir_caja(){

    stCaja caja;
    int ID;
    int turno;
    char verificador;
    int monto_inicial = 5000;
    int flag;

    FILE*buffer;
    buffer=fopen(NOMBRE_ARCHIVO_CAJAS,"ab");
    if(buffer!=NULL){

    caja.ID = generar_ID_caja();
    caja.estado = 1;
    caja.fecha = obtener_fecha_actual();

    do{
        printf("Ingresa tu ID.\n"); //validador de ID de empleados.
        fflush(stdin);
        scanf("%d",&ID);
        flag = verificar_ID(ID);

            if (flag == 1){
                caja.ID_empleado = ID;
                } else {
                    printf("ID invalido.\n");
                    }
    } while (flag == 0);

    do {
    printf("Ingresa tu turno.\n1) Turno maniana.\n2) Turno noche.\n");
    fflush(stdin);
    scanf("%d",&turno);
    if (turno != 1 && turno != 2){
        printf("Numero invalido. \n(!) Recorda que solo tenes la opcion 1 para turno maniana y 2 para turno noche.\n\n");
    }} while (turno != 1 && turno != 2);
    caja.turno = turno;

    printf("Queres modificar tu monto inicial? por defecto son $%d. (s/n)\n",monto_inicial);
    fflush(stdin);
    scanf("%c",&verificador);

    if (verificador != 's'){
        caja.monto_inicial = monto_inicial;
    } else {
        printf("Ingresa tu monto inicial.\n");
        fflush(stdin);
        scanf("%d",&monto_inicial);
        caja.monto_inicial = monto_inicial;
    }

        fwrite(&caja,sizeof(stCaja),1,buffer);

            fclose(buffer);
    }else{
        printf("\nNo puedo abrirse el archivo\n");
    }
    return caja;
}
//// Muestra stCaja modo apertura
void mostrar_apertura_caja(stCaja caja){

    mostrar_fecha(caja.fecha);
    printf("| Apertura de caja N. %d |\n",caja.ID);
    printf("| ID empleado: %d |\n",caja.ID_empleado);
    if (caja.turno == 1){
    printf("| Turno maniana |\n");
    } else if (caja.turno == 2){
    printf("| Turno noche |\n");
    }
    printf("| Monto inicial: $%d |\n",caja.monto_inicial);
}

void mostrar_archivo_ultima_apertura(){

    FILE *buffer;
    stCaja caja;
    int estado;
    buffer = fopen(NOMBRE_ARCHIVO_CAJAS,"rb");
    if (buffer != NULL){

        fseek(buffer,sizeof(stCaja)*(-1),2);
        fread(&caja,sizeof(stCaja),1,buffer);
        estado = caja.estado;
        if (estado == 1){
            mostrar_apertura_caja(caja);
        } else if (estado == 0){
        fseek(buffer,sizeof(stCaja)*(-2),2);
        fread(&caja,sizeof(stCaja),1,buffer);
            mostrar_apertura_caja(caja);
        }

        fclose(buffer);
    } else {
            printf("\nEl archivo no pudo abrirse.\n");
    }
}
///*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// Muestra cierre de caja modo listado
void mostrar_cierre_caja_listado(stCaja caja){

    int i = 0;
    mostrar_fecha(caja.fecha);
    printf("| ID empleado: %d |",caja.ID_empleado);
    if (caja.turno == 1){
    printf("| TM |");
    } else if (caja.turno == 2){
    printf("| TN |");
    }
    printf("\n| Monto inicial: $%ld |\n", caja.monto_inicial);
    printf("| Gastos $%ld |", caja.gasto.valor);

    printf("| Total EFECTIVO: $%ld|",caja.resumen_ventas[i]);
    printf("| Total DEBITO: $%ld|",caja.resumen_ventas[i+1]);
    printf("| Total CREDITO: $%ld|",caja.resumen_ventas[i+2]);
    printf("| Total TRANSFERENCIA: $%ld|",caja.resumen_ventas[i+3]);

    printf("| TOTAL CAJA: $%ld |", caja.total_caja);

    printf("| Arqueo final: %ld |", caja.diferencia);

}


///Funciones sueltas////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int verificar_estado_caja(){

    FILE *buffer;
    stCaja caja;
    int estado;
    buffer = fopen(NOMBRE_ARCHIVO_CAJAS,"rb");
    if (buffer != NULL){

        fseek(buffer,sizeof(stCaja)*(-1),2);
        fread(&caja,sizeof(stCaja),1,buffer);
        estado = caja.estado;

    fclose(buffer);
    } else {
            printf("\nNo hay cajas cargadas, carga una.\n");
    }
            return estado;
}
//// Generar ID
int generar_ID_caja(){

    int num_ID = 0;
    stCaja caja;
    long int cantidad;
    int registros;
    FILE*buffer;

    buffer=fopen(NOMBRE_ARCHIVO_CAJAS,"rb");

        if(buffer != NULL){

        fseek(buffer, 0, 2);

        cantidad = ftell(buffer);
        registros = (cantidad) / (sizeof(stCaja));
        num_ID = registros + 1;

        fclose(buffer);
  }
    else
        printf("\nNo puedo abrirse el archivo\n");

    return num_ID;
}

///Funciones que obtienen y muestrar la fecha actual
struct tm obtener_fecha_actual(){
    time_t tiempo_crudo; //tipo de dato que guarda un entero, que representa la cantidad de segundos desde las 00:00 hs del 1/1/1970 hasta la actualidad
    struct tm* tiempo;

    time(&tiempo_crudo); // funcion que devuelve la cantidad de segundos comentados arriba
    tiempo = localtime(&tiempo_crudo); // local timbre convierte la cantidad de segundos en datos que representan la hora local

    return *tiempo;
}

void mostrar_fecha(struct tm tiempo){

    printf ("\n| %02d:%02d %d/%d/%d |\n",tiempo.tm_hour,tiempo.tm_min,tiempo.tm_mday,tiempo.tm_mon+1,tiempo.tm_year+1900);
    //tm_mon+1 ya que devuelve valores del 0 al 11. tm_year+1900 ya que devuelve los anios a partir de 1900
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
