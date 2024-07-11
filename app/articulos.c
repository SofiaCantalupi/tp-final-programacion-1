#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pila.h"
#include "articulos.h"

///ORDEAMIENTO SELECCION ARTICULOS
int buscarMenor(int validos, stArticulo A[],int pos){
    int posmenor = pos;
    char menor[40];
    int i;
    strcpy(menor,A[pos].descripcion);
    i = pos + 1;
    int comparador;

    while(i<validos){
        comparador = strcmpi(menor,A[i].descripcion);
        if(comparador>0){
            strcpy(menor,A[i].descripcion);
            posmenor = i;
        }
    i++;
    }

return posmenor;
}

void ordeanmientoSeleccion(int validos, stArticulo A[]){
    int i = 0;
    int posmenor;
    stArticulo aux;

    while(i<validos){
    posmenor = buscarMenor(validos,A,i);

    aux = A[posmenor];
    A[posmenor] = A[i];
    A[i] = aux;

    i++;
    }

}

int cantidadRegis(stArticulo Ar){

    long int aux;
    int cantidad;
    FILE * buffer;
    buffer = fopen(NOMBRE_ARCHIVO_ARTICULOS, "rb");

    if(buffer!=NULL){
    fseek(buffer,0,2);
    aux = ftell(buffer);
    cantidad = aux/sizeof(stArticulo);
    fclose(buffer);
    }else{
    printf("El archivo no se abrio. ");
}
    return cantidad;
}

///Archivo a Arreglo Dinamico Articulos
stArticulo* CreaDinamicoArchivo(int registros,stArticulo Ar){

    stArticulo * ArDin = (stArticulo*)malloc(sizeof(stArticulo)*registros);

    ArchivoDinamico(Ar,ArDin);

        return ArDin;
}

void ArchivoDinamico(stArticulo Ar,stArticulo ArDin[]){

    FILE* buffer;
    buffer = fopen(NOMBRE_ARCHIVO_ARTICULOS,"rb");
    int i = 0;

    if(buffer!=NULL){
    while((fread(&Ar,sizeof(stArticulo),1,buffer))>0){
    ArDin[i] = Ar;
    i++;
}
fclose(buffer);
}else{
    printf("No se abrio el archivo");
}

}
///Mostrar Arreglo Articulos

void mostrarArticulo(stArticulo Ar){
    printf("=========================\n");
    printf("ID: %i \n", Ar.ID);
    printf("Descripcion: %s \n", Ar.descripcion);
    printf("PRECIO: %i \n", Ar.precio);
    printf("TALLE: %s \n", Ar.talle);
    printf("COLOR: %s \n", Ar.color);
    printf("CANTIDAD: %i \n", Ar.cantidad_disponible);
    printf("MARCA: %s \n", Ar.marca);
    printf("ESTADO: %i \n", Ar.estado_activo);
    printf("=========================\n");
}

void ArregloMostrar(int validos,stArticulo Ar[]){

    int i = 0;

    while(i<validos){
    mostrarArticulo(Ar[i]);
    i++;
}

}





//Busca un articulo por el ID
stArticulo buscar_articulo_ID(int num_ID){

    stArticulo articulo;

    FILE* buffer = fopen(NOMBRE_ARCHIVO_ARTICULOS,"rb");

    if(buffer)
    {
        fseek(buffer, sizeof(stArticulo) * (num_ID-1), 0); // voy al comienzo del registro el cual tendria que tener el mismo ID
        fread(&articulo, sizeof(stArticulo), 1, buffer);

        if(articulo.ID != num_ID)
            articulo.ID = -1; // si el id ingresado no es igual del registro, el ID pasa a ser -1 (es un ID invalido)

        fclose(buffer);
    }
    else
        printf("\nNo pudo abrirse el archivo");

    return articulo;
}

//Hace la busqueda de un articulo por la descripcion
stArticulo buscar_articulo_xdescrip(char descrip[]){
    stArticulo articulo;

    stArticulo articulo_aux;

    articulo_aux.ID=-1;//Le doy el valor -1 a articulo.aux para que si no entra al if del strcmp reciba los datos de articulo y lo retorne

    int flag = 0;

    FILE*buffer=fopen(NOMBRE_ARCHIVO_ARTICULOS,"rb");

    if(buffer!=NULL)
    {
        while(flag==0&&fread(&articulo,sizeof(stArticulo),1,buffer)>0)
        {

            if(strcmpi(articulo.descripcion,descrip) == 0)
            {
                articulo_aux=articulo;
                flag=1;

            }
        }
        fclose(buffer);

    }
    else
        printf("\nNo pudo abrirse el archivo");


    return articulo_aux;//Si nunca entra al bucle, nos retorna el articulo aux con un id invalido
}

//Le genera el ID a un articulo
int generar_ID_articulo(FILE* buffer){
    int num_ID = 0;

    stArticulo articulo;
    stArticulo ultimo;

    if(buffer != NULL)
    {
        fseek(buffer, 0, 0);

        if (fread(&articulo, sizeof(stArticulo), 1, buffer) > 0)
        {
            fseek(buffer, (sizeof(stArticulo)*-1), 2);  //lo uso para leer el ID del ultimo articulo y le sumo 1

            fread(&ultimo, sizeof(stArticulo), 1, buffer);

            num_ID = ultimo.ID + 1;
        }
        else if(fread(&articulo, sizeof(stArticulo), 1, buffer) == 0)    //retorna 0 porque no hay ningun registro, no pudo leerlo
            num_ID = 1;//el primer articulo creado recibe 1 como ID
    }
    else
        printf("\nNo puedo abrirse el archivo\n");

    return num_ID;
}

//Carga un articulo
stArticulo cargar_articulo(FILE* buffer){

    system("cls");
    printf("\n-----------------------Esta por crear un nuevo ARTICULO--------------------\n");
    printf("___________________________________________________________________________");

    stArticulo articulo;

    int num_ID = 0;

    num_ID = generar_ID_articulo(buffer);
    articulo.ID = num_ID;

    printf("\n\nDescripcion:\n");
    fflush(stdin);
    gets(articulo.descripcion);

    printf("\nMarca:\n");
    fflush(stdin);
    gets(articulo.marca);

    printf("\nTalle:\n");
    fflush(stdin);
    gets(articulo.talle);

    printf("\nColor:\n");
    fflush(stdin);
    gets(articulo.color);

    printf("\nCantidad disponible:\n");
    scanf("%d",&articulo.cantidad_disponible);

    printf("\nPrecio:\n");
    scanf("%d",&articulo.precio);

    articulo.estado_activo = 1;

    return articulo;
}


/////////////////////////// MOSTRAR ART ////////////////////////////////////
void mostrar_articulo(stArticulo articulo)
{

    printf("\n|ID: %d",articulo.ID);
    printf("|Descripcion: %s",articulo.descripcion);
    printf("|Marca: %s",articulo.marca);
    printf("|Talle: %s",articulo.talle);
    printf("|Color: %s",articulo.color);
    printf("|Cantidad disponible: %d",articulo.cantidad_disponible);
    printf("|Precio: $%d",articulo.precio);

    if(articulo.estado_activo == 1)
        printf("|Activo|\n");
    else
        printf("|Inactivo|\n");
}
///////////////////////////// CARGAR REGISTRO ART //////////////////////////////////////////
void cargar_registro_articulo()
{
    char control = 's';
    stArticulo articulo;

    FILE* buffer = fopen(NOMBRE_ARCHIVO_ARTICULOS, "a+b");

    if(buffer != NULL)
    {
        while(control == 's')
        {

            articulo = cargar_articulo(buffer);

            fseek(buffer, 0, 2); // pongo el cursor a lo ultimo del archivo

            fwrite(&articulo, sizeof(stArticulo), 1, buffer);

            printf("\n______________________________________________________________________________\n");
            printf("\n--------------------Su articulo ha sido cargado con exito!----------------------");
            printf("\n______________________________________________________________________________\n");

            mostrar_articulo(articulo);

            printf("\nDesea cargar otro nuevo articulo? s/n\n");
            fflush(stdin);
            scanf("%c",&control);

        }

        fclose(buffer);
    }
    else
        printf("\nNo puedo abrirse el archivo\n");

}
///////////////////////////// MOSTRAR ARCHIVO ARTICULOS ///////////////////////////////////
void mostrar_archivo_articulos()
{
    FILE* buffer;
    stArticulo A;

    buffer = fopen(NOMBRE_ARCHIVO_ARTICULOS,"rb");
    if(buffer)
    {
        while(fread(&A,sizeof(stArticulo),1,buffer)>0)
        {
            mostrar_articulo(A);
        }
        fclose(buffer);
    }
    else
        printf("\nNo se pudo abrir el archivo\n");
}
void mostrar_articulo_detalles(stArticulo articulo)//MUESTRA SOLO LOS DATOS DEL MISMO ARTICULO QUE NO SE REPITEN
{
    printf("\n------------\n");
    printf("|| ID: %d ||",articulo.ID);
    printf("\n------------\n");
    printf("\n| Talle: %s ",articulo.talle);
    printf("| Color: %s ",articulo.color);
    printf("| Cantidad disponible: %d ",articulo.cantidad_disponible);
    printf("| Marca: %s | Precio: $%d |",articulo.marca,articulo.precio);

    if(articulo.estado_activo==1)
        printf(" Estado: activo |");
    else
        printf(" Estado: inactivo |");

    printf("\n_________________________________________________________________________________\n");
}
/// LISTAR ARTICULO POR DESCRIPCION
void listar_articulo_descripcion()
{
    char descrip[20];

    printf("\nIngrese la descripcion del articulo que quiere ver (nombre completo del mismo):\n");
    fflush(stdin);
    scanf("%s",&descrip);
    system("cls");
    stArticulo articulo;
    articulo = buscar_articulo_xdescrip(descrip);

    mostrar_articulo_encabezado(articulo);

    FILE* buffer = fopen(NOMBRE_ARCHIVO_ARTICULOS,"rb");

    if(buffer!=NULL)
    {
        while(fread(&articulo,sizeof(stArticulo),1,buffer))
        {
            if(articulo.ID>-1&&strcmpi(articulo.descripcion,descrip)==0)
            {
                mostrar_articulo_detalles(articulo);
            }
        }
     fclose(buffer);

    }


}
/// LISTAR ARTICULO POR ID
void listar_articulo_ID (){
    int id = ingresar_id();

    stArticulo articulo;
    articulo = buscar_articulo_ID(id);
    char descripcion[15];
    strcpy(descripcion,articulo.descripcion);

    system("cls");

    mostrar_articulo_encabezado(articulo);

    FILE* buffer = fopen(NOMBRE_ARCHIVO_ARTICULOS,"rb");

    if(buffer!=NULL){
          while(fread(&articulo,sizeof(stArticulo),1,buffer)>0)
            {
               if(articulo.ID>-1&&strcmpi(articulo.descripcion,descripcion)==0){
                mostrar_articulo_detalles(articulo);
            }
        }

     fclose(buffer);
    } else {
        printf("El archivo no se pudo abrir.\n");
    }

}
///FUNCION ENCABEZADO
void mostrar_articulo_encabezado(stArticulo articulo)
{
  if(articulo.ID==-1)
    {
        printf("\nEse articulo no existe.\n");
    }
    if(articulo.ID>-1){

    printf("\n-------------------------------------------------------------------------------------\n");
    printf("|| Descripcion: %s ||",articulo.descripcion,articulo.ID);
    printf("\n-------------------------------------------------------------------------------------\n");
    }
}
//Disminuye el stock de un articulo en 1
void  disminuir_cantidad_articulo(int num_ID){

    stArticulo articulo;
    FILE* buffer;
    buffer = fopen(NOMBRE_ARCHIVO_ARTICULOS, "r+b");

    if(buffer)
    {
        fseek(buffer, sizeof(stArticulo) * (num_ID - 1), 0); // voy al principio del registro al que tengo que disminuir el stock
        fread(&articulo, sizeof(stArticulo), 1, buffer);

        articulo.cantidad_disponible = articulo.cantidad_disponible - 1;

        fseek(buffer, sizeof(stArticulo) * (num_ID-1), 0);
        fwrite(&articulo,sizeof(stArticulo),1,buffer);//copio articulo con el dato modificado

        fclose(buffer);
    }
}

///////// mostrar articulos vendidos venta
void mostrar_detalle_articulos_vendidos(int id_vendidos[], int id_vendidos_validos)
{

    stArticulo articulo_vendido;
    int i = 0;

    while(i < id_vendidos_validos)
    {

        articulo_vendido = buscar_articulo_ID(id_vendidos[i]);
        i++;

        printf("\n\nART. N%d:%s                     ", i+1, articulo_vendido.descripcion);
        printf("$%d\n", articulo_vendido.precio);
    }

}

/////////////////////// aumentar cantidad disponible articulo //////////////////////////////////////////
void  aumentar_cantidad_disponible_articulo(FILE* buffer, int num_ID)
{
    stArticulo articulo;

    if(buffer)
    {
        fseek(buffer, sizeof(stArticulo) * (num_ID - 1), 0); // voy al principio del registro al que tengo que disminuir el stock
        fread(&articulo, sizeof(stArticulo), 1, buffer);

        articulo.cantidad_disponible = articulo.cantidad_disponible + 1;

        fseek(buffer, sizeof(stArticulo) * (num_ID-1), 0);
        fwrite(&articulo,sizeof(stArticulo),1,buffer);//copio articulo con el dato modificado

    }
}

/////////////////////Eliminar un articulo /////////////////////////////////////////////////////////////

///Ingresar id
int ingresar_id(){
    int id;
    printf("\nIngrese el ID correspondiente al articulo:\n");
    fflush(stdin);
    scanf("%d",&id);

    return id;
}

//Pone en inactivo un articulo
void baja_articulo(){
    system("cls");

    printf("\n-----------------------Esta por dar de baja ARTICULO--------------------\n");
    printf("________________________________________________________________________");

    FILE* buffer;
    stArticulo articulo;
    buffer=fopen(NOMBRE_ARCHIVO_ARTICULOS,"r+b");

    int id_baja = ingresar_id();//Esta funcion retorna el id que se quiera buscar, el print esta en esa misma funcion para no ponerlo en el main

    articulo = buscar_articulo_ID(id_baja);

    int pos = articulo.ID;//Le asigno el ID como la posicion, pero cuando la uso en fseek le resto 1

    if(buffer!=NULL)
    {
        if(articulo.ID>-1)
        {

            articulo.estado_activo=2;

            printf("\nArticulo dado de baja exitosamente.\n");
            mostrar_articulo(articulo);

            system("pause");
        }

        else if (pos == -1)//Si la funcion de buscar ID me retorna -1 en articulo.ID significa que no hay tal ID
        {
            printf("\nArticulo no encontrado.\n");
        }

        fseek(buffer,sizeof(stArticulo)*pos-1, SEEK_SET);//Me posiciono un lugar antes de donde esta el articulo que se retorno de la funcion de buscar ID
        fwrite(&articulo, sizeof(stArticulo), 1, buffer);
        fclose(buffer);

    }
    else
    {
        printf("\nNo es posible abrir el archivo\n");
    }
}



/////////////////////////Modificar Articulo ///////////////////////////////////////////////

///Funciones para Modificar campos de un articulo

void modificar_archivo_articulo(){

int num_ID = ingresar_id();

stArticulo A = buscar_articulo_ID(num_ID);

mostrar_articulo(A);

FILE* archi = fopen(NOMBRE_ARCHIVO_ARTICULOS, "r+b");

    if (archi)
        {
    fseek(archi, sizeof(stArticulo) * (num_ID - 1), SEEK_SET);

    if (fread(&A, sizeof(stArticulo), 1, archi) == 1){

        int control = 0;

        do {
            printf("---------------------------------------\n");
            printf("||     Elija que desea modificar     ||\n");
            printf("---------------------------------------\n");
            printf("||1- Modificar descripcion.          ||\n");
            printf("||2- Modificar precio.               ||\n");
            printf("||3- Modificar talle.                ||\n");
            printf("||4- Modificar color.                ||\n");
            printf("||5- Modificar cantidad.             ||\n");
            printf("||6- Modificar marca.                ||\n");
            printf("||7- <-Volver Atras.                 ||\n");
            printf("---------------------------------------\n");
            printf("\nIngrese una opcion:");
            scanf("%d", &control);

            switch (control)
            {
            case 1:
                A = modificar_descripcion_articulo(A);
                break;
            case 2:
                A = modificar_precio_articulo(A);
                break;
            case 3:
                A = modificar_talle_articulo(A);
                break;
            case 4:
                A = modificar_color_articulo(A);
                break;
            case 5:
                A = modificar_cantidad_articulo(A);
                break;
            case 6:
                A = modificar_marca_articulo(A);
                break;
            case 7:
                // Salir del bucle
                break;
            default:
                printf("Opción no valida.\\n");
            }

            fseek(archi, sizeof(stArticulo) * (num_ID - 1), SEEK_SET);
            fwrite(&A, sizeof(stArticulo), 1, archi);
        }
        while (control != 7); // Corrección de la condición del bucle
    }
    else
    {
        printf("No se pudo leer el artículo.\\n");
    }

    fclose(archi);
}
else
{
    printf("No se pudo abrir el archivo.\\n");
}

mostrar_articulo(A);  //para mostrar el articulo modificado presionar 7 para salir

}

stArticulo modificar_descripcion_articulo(stArticulo A){

    printf("\nIngrese la nueva descripcion:");
    fflush(stdin);
    gets(A.descripcion);

    return A;
}

stArticulo modificar_precio_articulo(stArticulo A){

    printf("\nIngrese el nuevo precio:");
    scanf("%d",&A.precio);

    return A;
}

stArticulo modificar_talle_articulo(stArticulo A){

    printf("\nIngrese el nuevo talle:");
    fflush(stdin);
    gets(A.talle);

    return A;
}

stArticulo modificar_color_articulo(stArticulo A){

    printf("\nIngrese el nuevo color:");
    fflush(stdin);
    gets(A.color);

    return A;
}

stArticulo modificar_marca_articulo(stArticulo A){

    printf("\nIngrese la nueva marca:");
    fflush(stdin);
    gets(A.marca);

    return A;
}

stArticulo modificar_cantidad_articulo(stArticulo A){

    printf("\nIngrese la nueva cantidad:");
    scanf("%d",&A.cantidad_disponible);

    return A;
}
