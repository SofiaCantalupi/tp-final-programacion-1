#include <stdio.h>
#include <stdlib.h>
#include "menu_gestion_ventas.h"
#include "caja.h"

void menu_gestion_ventas(){
    int volver = 0;
    int operador;
    int estado_caja;

            while(volver==0)
            {
                system("cls");

                printf("\n\n\n\n\t\t\t\t\t===================V=====================");
                printf("\n\n\t\t\t\t\t--------------->Apparel Ace<-------------");
                printf("\n\t\t\t\t\t===================V=====================");
                printf("\n\t\t\t\t\t|            GESTION DE VENTAS           |");
                printf("\n\t\t\t\t\t=========================================");
                printf("\n\n\t\t\t\t\t(1)CREAR VENTA");
                printf("\n\n\t\t\t\t\t(2)ANULAR VENTA");
                printf("\n\n\t\t\t\t\t(3)VER LISTADO DE VENTAS");
                printf("\n\n\t\t\t\t\t(4)MOSTRAR VENTA");
                printf("\n\n\t\t\t\t\t(0)VOLVER");
                printf("\n\n\t\t\t\t\tIngrese una opcion: ");

                scanf("%d",&operador);

                system("cls");

                switch(operador){

                case 1:
///Funcion crear una venta

                estado_caja = verificar_estado_caja("cajas.BIN");

                if (estado_caja != 1){
                    printf("Para cargar una venta primero tenes que abrir una caja.\n");
                } else {
                system("cls");
                cargar_archivo_ventas();
                system("pause");
                }

                break;

                case 2:
/// Funcion anular venta   // borrar para usuario

                dar_baja_venta();
                system("pause");

                break;

                case 3:
/// Funcion listado de ventas

                mostrar_listado_ventas();
                system("pause");

                break;

                case 4:
/// Funcion ver una venta

                consultar_venta_id();
                system("pause");

                break;

                case 0:
/// Volver al menu principal
                volver = 1;

                break;

                default:
                    system("cls");
                    printf("\nOpcion incorrecta.\n");
                }
            }

}

void menu_gestion_ventas_EMPLEADO(){
    int volver = 0;
    int estado_caja;
    int operador;

            while(volver==0){
                system("cls");

                printf("\n\n\n\n\t\t\t\t\t===================V=====================");
                printf("\n\n\t\t\t\t\t--------------->Apparel Ace<-------------");
                printf("\n\t\t\t\t\t===================V=====================");
                printf("\n\t\t\t\t\t|            GESTION DE VENTAS           |");
                printf("\n\t\t\t\t\t=========================================");
                printf("\n\n\t\t\t\t\t(1)CREAR VENTA");
                printf("\n\n\t\t\t\t\t(2)VER LISTADO DE VENTAS");
                printf("\n\n\t\t\t\t\t(3)MOSTRAR VENTA");
                printf("\n\n\t\t\t\t\t(0)VOLVER");
                printf("\n\n\t\t\t\t\tIngrese una opcion: ");

                scanf("%d",&operador);

                system("cls");

                switch(operador){

                case 1:
///Funcion crear una venta

                estado_caja = verificar_estado_caja("cajas.BIN");

                if (estado_caja != 1){
                    printf("Para cargar una venta primero tenes que abrir una caja.\n");
                } else {
                cargar_archivo_ventas();
                system("pause");
                }

                break;

                case 2:
/// Funcion listado de ventas

                mostrar_listado_ventas();
                system("pause");

                break;

                case 3:
/// Funcion ver una venta

                consultar_venta_id();
                system("pause");

                break;

                case 0:
/// Volver al menu principal
                volver = 1;

                break;

                default:
                    system("cls");
                    printf("\nOpcion incorrecta.\n");
                }
            }

}

