#include <stdio.h>
#include <stdlib.h>
#include "menu_usuarios.h"
#include "empleado.h"

void menu_usuarios(){
    int volver = 0;
    int operador;
    int flag;
    int ID;
    int rol;
    int registros_empleados;
    stEmpleados Em;
    stEmpleados* E =  CreaDinamicoArchivoE(registros_empleados,Em);
            while(volver==0)
            {
                system("cls");

                printf("\n\n\n\n\t\t\t\t\t===================V=====================");
                printf("\n\n\t\t\t\t\t--------------->Apparel Ace<-------------");
                printf("\n\t\t\t\t\t===================V=====================");
                printf("\n\t\t\t\t\t|                USUARIOS               |");
                printf("\n\t\t\t\t\t=========================================");
                printf("\n\n\t\t\t\t\t(1)CREAR EMPLEADO");
                printf("\n\n\t\t\t\t\t(2)MODIFICAR EMPLEADO");
                printf("\n\n\t\t\t\t\t(3)ANULAR EMPLEADO");
                printf("\n\n\t\t\t\t\t(4)LISTADO DE EMPLEADOS");
                printf("\n\n\t\t\t\t\t(5)ORDENAR LISTADO POR ORDEN ALFABETICO");
                printf("\n\n\t\t\t\t\t(6)CAMBIAR CONTRASENIA ADMIN");
                printf("\n\n\t\t\t\t\t(7)CAMBIAR USUARIO ADMIN");
                printf("\n\n\t\t\t\t\t(0)VOLVER");
                printf("\n\n\t\t\t\t\tIngrese una opcion: ");

                scanf("%d",&operador);

                system("cls");

                switch(operador)
                {
                case 1:
///Funcion crear usuario
      cargar_empleado();
                    break;
                case 2:
///Funcion modificar usuario
      modificar_archivo_empleados();

                    break;
                case 3:
///Funcion anular usuario
    baja_de_empleado();
    system("pause");
                    break;
                case 4:
///Funcion LISTAR EMPLEADOS
            mostrar_archivo_empleados();
            system("pause");

                    break;

                case 5:
///Funcion Ordenar por insercion
            registros_empleados = cantidadRegisE(Em);
            ordenamientoInsercion(registros_empleados,E);
            ArregloMostrarEm(registros_empleados,E);

            system("pause");

                    break;

                case 6:
///Funcion CAMBIAR CONTRASENIA
            printf("Ingresa tu ID.\n");
            fflush(stdin);
            scanf("%d",&ID);
            rol = verificar_rol(ID);
            if (rol != 1){
                printf("El ID ingresado no es el de un administrador.\n");
            } else {

            flag = modificarContrasenaAdim(ID);
            if (flag == 1) {
                printf("Cambio de contrasenia exitoso.\n");
            } else if (flag == 0){
                printf("Error al cambiar la contrasenia.\n");
            }
            }
            system("pause");

                    break;

                case 7:
///Funcion CAMBIAR USUARIO
            printf("Ingresa tu ID.\n");
            fflush(stdin);
            scanf("%d",&ID);
            rol = verificar_rol(ID);
            if (rol != 1){
                printf("El ID ingresado no es el de un administrador.\n");
            } else {

            flag = modificarUsuarioAdmin(ID);
            if (flag == 1) {
                printf("Cambio de usuario exitoso.\n");
            } else if (flag == 0){
                printf("Error al cambiar el usuario.\n");
            }
            }
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
