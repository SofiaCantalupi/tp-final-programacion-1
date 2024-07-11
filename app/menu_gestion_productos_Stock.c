#include <stdio.h>
#include <stdlib.h>
#include "menu_gestion_productos_Stock.h"
#include "articulos.h"
#include "menu_gestion_productos.h"

void menu_gestion_productos_Stock()
{

    int operador;
    int volver = 0;

    while(volver==0)
    {


        system("cls");

            printf("\n\n\n\n\t\t\t\t\t===================V=====================");
            printf("\n\n\t\t\t\t\t--------------->Apparel Ace<-------------");
            printf("\n\t\t\t\t\t===================V=====================");
            printf("\n\t\t\t\t\t|             GESTION DE STOCK           |");
            printf("\n\t\t\t\t\t=========================================");
            printf("\n\n\t\t\t\t\t(1)LISTA DE ARTICULOS");
            printf("\n\n\t\t\t\t\t(2)BUSCAR UN ARTICULO POR ID");
            printf("\n\n\t\t\t\t\t(3)BUSCAR UN ARTICULO POR DESCRIPCION");
            printf("\n\n\t\t\t\t\t(0)VOLVER");
            printf("\n\n\t\t\t\t\tIngrese una opcion: ");

        scanf("%d",&operador);

        switch(operador)
        {
        case 1:
            system("cls");
            printf("\n-----------------------------LISTA DE ARTICULOS-----------------------------\n");
            mostrar_archivo_articulos();
            system("pause");
            break;
        case 2:
/// Funciones BUSCAR UN ARTICULO por ID
            system("cls");
            listar_articulo_ID ();
            system("pause");
            break;
        case 3:
///Funcion BUSCAR ARTICULO por DESCRIPCION
            system("cls");
            listar_articulo_descripcion();
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
