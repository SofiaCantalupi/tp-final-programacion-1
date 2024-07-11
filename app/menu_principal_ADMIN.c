#include <stdio.h>
#include <stdlib.h>
#include "menu_principal_ADMIN.h"

 void menu_principal_ADMIN(char ArchivoEmpleado[]){
    char control='s';
    int operador;


    while(control=='s')

    {
        int volver = 0;

        system("cls");
        printf("\n\n\n\n\t\t\t\t\t===================V=====================");
        printf("\n\n\t\t\t\t\t--------------->Apparel Ace<-------------");
        printf("\n\t\t\t\t\t===================V=====================");
        printf("\n\t\t\t\t\t|       (1) GESTION DE ARTICULOS         |");
        printf("\n\t\t\t\t\t=========================================");
        printf("\n\t\t\t\t\t|       (2) GESTION DE VENTAS            |");
        printf("\n\t\t\t\t\t=========================================");
        printf("\n\t\t\t\t\t|       (3) CAJA                         |");
        printf("\n\t\t\t\t\t=========================================");
        printf("\n\t\t\t\t\t|       (4) USUARIOS                     |");
        printf("\n\t\t\t\t\t=========================================\n");
        printf("\n\t\t\t\t\tIngrese una opcion: ");
        scanf("%d",&operador);

        switch(operador){

        case 1:
        //Abre el menu de gestion de productos
        menu_gestion_productos();

        break;

        case 2:
        //Abre el menu de gestion de ventas
        menu_gestion_ventas();

        break;

        case 3:
        //Abre el menu de caja
        menu_caja();

        break;

        case 4:
        //Abre el menu de usuarios
        menu_usuarios(ArchivoEmpleado);

        break;

        default:
            system("cls");
            printf("Opcion incorrecta\n");
        }
        system("cls");
        printf("\nDesea volver al menu principal? Presione s/n: ");
        fflush(stdin);
        scanf("%c",&control);
    }
 }
