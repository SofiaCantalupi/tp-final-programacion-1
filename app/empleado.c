#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "empleado.h"


//Funcion aux para ordenar por insercion
void insertarElem (int validos, stEmpleados E[], int u, stEmpleados Em){

    while(u>=0 && (strcmpi(Em.nombre_completo,E[u].nombre_completo)<0)){
        E[u+1] = E[u];
        u--;
    }

    E[u+1] = Em;
}

void ordenamientoInsercion(int validos, stEmpleados E[]){
    int i = 0;

    while(i<validos -1){
        insertarElem(validos,E,i,E[i+1]);
        i++;
    }
}


//Muestra empleado
void mostrarEmpleado(stEmpleados Em){
    printf("=========================\n");
    //printf("ID: %i \n", Em.ID);
    printf("NOMBRE Y APELLIDO: %s \n", Em.nombre_completo);
    printf("DNI: %s \n", Em.DNI);
    printf("ROL: %i \n", Em.rol);
    printf("=========================\n");
}

//Muestra arreglo de empleados
void ArregloMostrarEm(int validos,stEmpleados Em[]){
    int i = 0;

    while(i<validos){
        mostrarEmpleado(Em[i]);
        i++;
    }
}

//Cuenta los registros
int cantidadRegisE(stEmpleados Em){

    long int aux;
    int cantidad;
    FILE * buffer;
    buffer = fopen(NOMBRE_ARCHIVO_EMPLEADOS, "rb");

    if(buffer!=NULL){
    fseek(buffer,0,2);
    aux = ftell(buffer);
    cantidad = aux/sizeof(stEmpleados);
        fclose(buffer);
    }else{
        printf("El archivo no se abrio. ");
}
        return cantidad;
}

//Carga archivo dinamico de empleados
void ArchivoDinamicoE(stEmpleados Em,stEmpleados ArDinE[]){
    FILE*buffer;
    buffer = fopen(NOMBRE_ARCHIVO_EMPLEADOS,"rb");
    int i = 0;

    if(buffer!=NULL){
    while((fread(&Em,sizeof(stEmpleados),1,buffer))>0){
        ArDinE[i] = Em;
        i++;
    }
    fclose(buffer);
    }else{
        printf("No se abrio el archivo");
    }
}

//Crea arreglo dinamico de empleados en el archivo
stEmpleados* CreaDinamicoArchivoE(int registros,stEmpleados Em){
    stEmpleados * ArDinE = (stEmpleados*)malloc(sizeof(stEmpleados)*registros);
    ArchivoDinamicoE(Em,ArDinE);
return ArDinE;
}

//Funcion para verificar que un empleado este inactivo para darle de alta.
int empleado_a_dar_alta(){

    int id_a_dar_alta;

    printf("\nIngrese el ID del empleado que quiere dar de alta:\n");
    fflush(stdin);
    scanf("%d",&id_a_dar_alta);

    while (verificar_ID("empleados.txt",id_a_dar_alta) == 0){
        system("cls");
        printf("ID invalido. Ingrese el ID nuevamente.\n");
        fflush(stdin);
        scanf("%d",&id_a_dar_alta);
    }
    return id_a_dar_alta;
}

//Funcion que cambia de inactivo a activo el rol de empleado
void alta_empleado(){

    int id_a_dar_alta;
    char verificador;
    FILE* buffer;
    stEmpleados empleado;
    buffer=fopen(NOMBRE_ARCHIVO_EMPLEADOS,"r+b");

    int id_alta = empleado_a_dar_alta();
    empleado = retornar_empleado_por_ID(id_alta);

    if(buffer!=NULL){

        fseek(buffer,sizeof(stEmpleados)*(id_alta - 1),0);
        if (empleado.rol == 1){
            printf("El empleado ya es un empleado activo.\n");
        } else {
            printf("El empleado %s va a ser dado de alta, esta seguro? (s/n)\n",empleado.nombre_completo);
            fflush(stdin);
            scanf("%c",&verificador);
            if (verificador == 's'){
                    empleado.rol = 1;
            }
        }
        fwrite(&empleado, sizeof(stEmpleados), 1, buffer);

        fclose(buffer);
    } else {
        printf("\nNo es posible abrir el archivo\n");
    }
}

//Retorna el empleado con el ID buscado
stEmpleados retornar_empleado_por_ID(int ID){

    stEmpleados empleado;

    FILE*buffer=fopen(NOMBRE_ARCHIVO_EMPLEADOS,"rb");

        if(buffer)
        {
            fseek(buffer,sizeof(stEmpleados)*(ID-1),0); // voy al comienzo del registro el cual tendria que tener el mismo ID
            fread(&empleado,sizeof(stEmpleados),1,buffer);

            fclose(buffer);

        }else
        printf("\nNo pudo abrirse el archivo");

    return empleado;
}

//Da de baja un empleado por el ID
int empleado_a_eliminar(){

    int id_a_eliminar;

    printf("\nIngrese el ID del empleado que quiere dar de baja:\n");
    fflush(stdin);
    scanf("%d",&id_a_eliminar);

    while (verificar_ID(id_a_eliminar) == 0){
        system("cls");
        printf("ID invalido. Ingrese el ID nuevamente.\n");
        fflush(stdin);
        scanf("%d",&id_a_eliminar);
    }
    return id_a_eliminar;
}

//Se le da de baja a un empleado
void baja_empleado(){

    int id_a_eliminar;
    char verificador;
    FILE* buffer;
    stEmpleados empleado;
    buffer=fopen(NOMBRE_ARCHIVO_EMPLEADOS,"r+b");

    int id_baja = empleado_a_eliminar();
    empleado = retornar_empleado_por_ID(id_baja);

    if(buffer!=NULL){

        fseek(buffer,sizeof(stEmpleados)*(id_baja - 1),0);
        if (empleado.rol == 0){
            printf("El empleado ya estaba dado de baja.\n");
        } else {
            printf("El empleado %s va a ser dado de baja, esta seguro? (s/n)\n",empleado.nombre_completo);
            fflush(stdin);
            scanf("%c",&verificador);
            if (verificador == 's'){
                    empleado.rol = 0;
            }
        }
        fwrite(&empleado, sizeof(stEmpleados), 1, buffer);

        fclose(buffer);
    } else {
        printf("\nNo es posible abrir el archivo\n");
    }
}

//Devuelve un empleado por el DNI
stEmpleados retornar_empleado_buscado(char DNI_buscado[]){

    stEmpleados empleado;
    stEmpleados empleado2;
    int flag = 0;
    FILE*buffer;
    buffer = fopen(NOMBRE_ARCHIVO_EMPLEADOS,"rb");
        if(buffer != NULL){

        while(flag == 0 && fread(&empleado,sizeof(stEmpleados),1,buffer)>0){

            if (strcmpi(empleado.DNI,DNI_buscado) == 0){

                empleado2.ID = empleado.ID;
                strcpy(empleado2.nombre_completo,empleado.nombre_completo);
                strcpy(empleado2.DNI,empleado.DNI);
                empleado2.rol = empleado.rol;
                flag = 1;
        }}
                if (flag == 0){
                    empleado2.ID=-1; // si no entra en el if, el ID pasa a ser -1 (es un ID invalido)
                    }
            fclose(buffer);
        } else{
        printf("\nNo pudo abrirse el archivo");
        }
    return empleado2;
}

//Muestra el archivo de empleados
void mostrar_archivo_empleados(){

    FILE *buffer;
    stEmpleados empleado;
    buffer = fopen(NOMBRE_ARCHIVO_EMPLEADOS,"rb");
    if (buffer != NULL){

        while (fread(&empleado,sizeof(stEmpleados),1,buffer) > 0){
                mostrar_empleado(empleado);
        }
        fclose(buffer);
    } else {
            printf("\nEl archivo no pudo abrirse.\n");
    }
}

//Muestra 1 solo empleado
void mostrar_empleado(stEmpleados empleado){

        printf("| %d |",empleado.ID);
        printf("| %s |",empleado.nombre_completo);
        printf("| %s |",empleado.DNI);
        if (empleado.rol == 0){
            printf("| Inactivo |");
        } else if (empleado.rol == 2){
            printf("| Activo |");
        }else if (empleado.rol == 1) {
            printf("| Administrador |");
        }
        printf("\n");
}

//Carga varios empleados al archivo
void cargar_empleados(){

    FILE *buffer;
    stEmpleados empleado;
    char control = 's';

            while (control == 's'){

    buffer = fopen(NOMBRE_ARCHIVO_EMPLEADOS,"ab");
    if (buffer != NULL){

                system("cls");
                printf("-------------------------------------------");
                empleado = cargarUnEmpleado();
                printf("-------------------------------------------");

                fwrite(&empleado,sizeof(stEmpleados),1,buffer);

    fclose(buffer);
    } else {
            printf("\nEl archivo no pudo abrirse.\n");
    }
        printf("\nDesea agregar mas? (s/n)\n");
        fflush(stdin);
        scanf("%c",&control);
}
}

//Carga un empleado solo.
stEmpleados cargarUnEmpleado(){

    stEmpleados empleado;

    empleado.ID = generar_ID();
    printf("\nEscribi el nombre del empleado a cargar:\n");
    fflush(stdin);
    gets(empleado.nombre_completo);
    printf("\nEscribi el DNI de %s:\n",empleado.nombre_completo);
    fflush(stdin);
    gets(empleado.DNI);
    empleado.rol = 2;

        return empleado;
}

//Funcion que genera el ID para el empleado.
int generar_ID(){

    int num_ID = 0;
    stEmpleados empleado;
    stEmpleados ultimo;

    FILE*buffer;

    buffer=fopen(NOMBRE_ARCHIVO_EMPLEADOS,"rb");
    if(buffer!=NULL)
    {
        if (fread(&empleado,sizeof(stEmpleados),1,buffer)==1)
        {
            fseek(buffer,(sizeof(stEmpleados)*-1),2); //lo uso para leer el ID del ultimo empleado y le sumo 1
            fread(&ultimo,sizeof(stEmpleados),1,buffer);

            num_ID=ultimo.ID+1;
        }
        else if(fread(&empleado,sizeof(stEmpleados),1,buffer)==0)  //retorna 0 porque no hay ningun registro, no pudo leerlo
            num_ID=1;//el primer articulo creado recibe 1 como ID

        fclose(buffer);
    }
    else
        printf("\nNo puedo abrirse el archivo\n");

    return num_ID;
}

/// LOG IN ////////////////////////
//Funcion usada en el inicio del programa para iniciar sesion
void log_in (){
   // printf("Lista de empleados:\n");
  //  mostrar_archivo_empleados();

    char DNI_buscado[15];
    stEmpleados empleado_buscado;
    stEmpleados empleado;
    stEmpleados * Em;
    int validos;
    int empleado_a_usar;
    char validador = 's';
    char ingreso[15];


    do {
        printf("\n\n\n\n\t\t\t\t\t===================V=====================");
        printf("\n\n\t\t\t\t\t--------------->Apparel Ace<-------------");
        printf("\n\t\t\t\t\t===================V=====================");
        printf("\n\t\t\t\t\t|         BIENVENIDO DE NUEVO!           |");
        printf("\n\t\t\t\t\t=========================================\n\n");


        printf("\n\t\t\t\t\tIngrese su ID: ");
        fflush(stdin);
        scanf("%d",&empleado_a_usar);
            while (verificar_ID(empleado_a_usar) == 0){
                system("cls");
                printf("\n\t\t\t\t\tID invalido. Ingrese su ID nuevamente.\n");
                fflush(stdin);
                scanf("%d",&empleado_a_usar);
                } if (verificar_rol(empleado_a_usar) == 1){

                        do {
                        printf("\n\t\t\t\t\tIngrese el usuario: ");
                        fflush(stdin);
                        gets(ingreso); ///admin123
                        if (verificar_usuario(ingreso,empleado_a_usar) == 0){
                            system("cls");
                            printf("\n\t\t\t\t\tUsuario invalido. ");
                            validador = 'n';
                        } else {
                            do {
                            printf("\n\t\t\t\t\tIngrese la contrasenia: ");
                            fflush(stdin);
                            gets(ingreso); ///utn2024
                            if (verificar_contrasenia(ingreso,empleado_a_usar) == 0){
                            system("cls");
                            printf("\n\t\t\t\t\tContrasenia invalido. ");
                            validador = 'n';
                            } else {
                                printf("\n\t\t\t\t\tIngreso exitoso, admin.");
                                menu_principal_ADMIN();
                                validador = 's';
                            }} while (validador == 'n');
                        }
                        } while (validador == 'n');
    } else {
        printf("\n\t\t\t\t\tIngreso correctamente.\n");
        menu_principal_USUARIO();

    }
} while (validador == 'n');
}


void cargar_empleado(){
    cargar_empleados();

    system("pause");
    system("cls");

    printf("Lista de empleados:\n");
    mostrar_archivo_empleados();
}
/// //////////////////////////////
void baja_de_empleado(){

    printf("Lista de empleados:\n");
    mostrar_archivo_empleados();
    baja_empleado();
  ///  alta_empleado(); ///PREGUNTAR A FRANCO POR QUE ACA ESTA LA ALTA
}


///MODIFICAR EMPLEADO
void modificar_archivo_empleados()
{
    char DNI_buscado[15];
    printf("\nIngrese el DNI de la persona que quiere modificar: ");
    fflush(stdin);
    gets(DNI_buscado);

        int pos = 0;
        stEmpleados A = retornar_empleado_buscado(DNI_buscado);///CORREGIDO &POS
        mostrar_empleado(A);
        pos = A.ID; ///La posicion en el archivo, va a ser el ID del empleado
if(pos > 1){
        FILE *archi = fopen(NOMBRE_ARCHIVO_EMPLEADOS, "r+b");
        if (archi) {
            fseek(archi, sizeof(stEmpleados) * (pos -1), SEEK_SET);///

            int control = 0;
            do {
                printf("---------------------------------------\n");
                printf("||     Elija que desea modificar     ||\n");
                printf("---------------------------------------\n");
                printf("||1- Modificar nombre.               ||\n");
                printf("||2- Modificar D.N.I.                ||\n");
                printf("||3- <-Volver Atras.                 ||\n");
                printf("---------------------------------------\n");
                printf("\nIngrese una opcion:");
                scanf("%d", &control);

                switch (control) {
                    case 1:
                        A = modificar_nombre_empleado(A);
                        break;
                    case 2:
                        A = modificar_DNI_empleado(A);
                        break;
                    case 3:
                        // Salir del bucle
                        break;
                    default:
                        printf("Opcion no valida.\\n");
                }

                fseek(archi, sizeof(stEmpleados) * (pos-1), SEEK_SET);///
                fwrite(&A, sizeof(stEmpleados), 1, archi);
            } while (control != 3);
            fclose(archi);
        } else {
            printf("No se pudo abrir el archivo.\\n");
        }
}else{
      printf("\nNo hay un empleado con ese DNI."); ///No muestra esta parte del codigo.
}

        mostrar_empleado(A);
}
/// FUNCION MODIFICAR NOMBRE EMPLEADO
stEmpleados modificar_nombre_empleado(stEmpleados A)
{
        printf("\nIngrese el nuevo nombre del empleado:");
        fflush(stdin);
        gets(A.nombre_completo);
        return A;
}
/// FUNCION MODIFICAR DNI EMPLEADO
stEmpleados modificar_DNI_empleado(stEmpleados A)
{
        printf("\nIngrese el nuevo D.N.I. del empleado");
        fflush(stdin);
        gets(A.DNI);

        return A;
}

