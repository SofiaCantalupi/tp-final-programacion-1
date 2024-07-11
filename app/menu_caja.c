#include <stdio.h>
#include <stdlib.h>
#include "menu_caja.h"
#include "caja.h"

void menu_caja(){
 int volver = 0;
 int operador;
 stCaja caja;
 int ultimo_estado = -1;
            while(volver==0){

                system("cls");

                printf("\n\n\n\n\t\t\t\t\t===================V=====================");
                printf("\n\n\t\t\t\t\t--------------->Apparel Ace<-------------");
                printf("\n\t\t\t\t\t===================V=====================");
                printf("\n\t\t\t\t\t|            GESTION DE CAJAS            |");
                printf("\n\t\t\t\t\t=========================================");
                printf("\n\n\t\t\t\t\t(1)ABRIR CAJA");
                printf("\n\n\t\t\t\t\t(2)CERRAR CAJA");
                printf("\n\n\t\t\t\t\t(3)LISTADO CAJAS");
                printf("\n\n\t\t\t\t\t(0)VOLVER");
                printf("\n\n\t\t\t\t\tIngrese una opcion: ");
                scanf("%d",&operador);

                system("cls");

                switch(operador){

                case 1:
///Funcion abrir caja
                    ultimo_estado = verificar_estado_caja("cajas.BIN");
                    if (ultimo_estado == 1){
                        printf("Ya hay una caja abierta. Cerrala para despues abrir otra.\n");
                        system("pause");
                    } else {
                        caja = abrir_caja("cajas.BIN");
                        printf("Ultima caja abierta:\n");
                        mostrar_archivo_ultima_apertura("cajas.BIN");
                        system("pause");
                    }

                break;

                case 2:
///Funcion cerrar caja

                    ultimo_estado = verificar_estado_caja("cajas.BIN");
                    if (ultimo_estado == 1){

                    caja = cerrar_caja("cajas.BIN");
                    system("pause");
                    printf("Ultima caja cerrada:.\n");
                    mostrar_archivo_ultimo_cierre("cajas.BIN");

                } else if (ultimo_estado == 0) {
                    printf("No hay una caja abierta para realizar el cierre.\n");
                }
                system("pause");

                break;

                case 3:
///Funcion ver registro cajas


                    printf("\n------------------------Registro completo de cajas------------------------\n");
                    printf("____________________________________________________________________________");
                    mostrar_archivo_cajas("cajas.BIN");
                    system("pause");

                break;

                case 0:
///Volver
                volver = 1;

                break;

                default:
                    //system("cls");
                    printf("\nOpcion incorrecta.\n");
}

            }
}
