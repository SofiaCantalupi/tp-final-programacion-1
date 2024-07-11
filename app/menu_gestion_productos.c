#include <stdio.h>
#include <stdlib.h>
#include "menu_gestion_productos.h"
#include "articulos.h"


void menu_gestion_productos(char ArchivoArticulos[]){

            int volver = 0;
            int operador;
            stArticulo Ar;
            int validos;



            while(volver==0)
            {
                system("cls");
                printf("\n\n\n\n\t\t\t\t\t===================V=====================");
                printf("\n\n\t\t\t\t\t--------------->Apparel Ace<-------------");
                printf("\n\t\t\t\t\t===================V=====================");
                printf("\n\t\t\t\t\t|           GESTION DE ARTICULOS         |");
                printf("\n\t\t\t\t\t=========================================");
                printf("\n\n\t\t\t\t\t(1)STOCK");
                printf("\n\n\t\t\t\t\t(2)ALTA DE ARTICULOS");
                printf("\n\n\t\t\t\t\t(3)BAJA DE ARTICULOS");
                printf("\n\n\t\t\t\t\t(4)MODIFICACION DE ARTICULOS");
                printf("\n\n\t\t\t\t\t(5)MOSTRAR LISTADO ORDENADO POR ORDEN ALFABETICO");
                printf("\n\n\t\t\t\t\t(0)VOLVER");
                printf("\n\n\t\t\t\t\tIngrese una opcion: ");

                fflush(stdin);
                scanf("%d",&operador);

                switch(operador)
                {
                case 1: ///Funcion menu Stock
                menu_gestion_productos_Stock();
                     break;
                case 2:
/// Funcion Alta de ARTICULOS
                cargar_registro_articulo();
                    break;
                case 3:
/// Funcion Baja de ARTICULOS
                baja_articulo();
                    break;
                case 4:
/// Funcion modificacion de ARTICULOS
                modificar_archivo_articulo();
                break;

                case 5:
/// Funcion ordenamiento por seleccion

            validos = cantidadRegis(Ar);
            stArticulo * ArDin = CreaDinamicoArchivo(validos,Ar);
            ordeanmientoSeleccion(validos,ArDin);
            ArregloMostrar(validos,ArDin);
            system("pause");

                break;

                case 0:
/// VOLVER
                    volver = 1;
                    break;

                default:
                    system("cls");
                    printf("\nOpcion incorrecta.\n");
                }

            }
            }
