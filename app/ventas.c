#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pila.h"
#include "articulos.h"
#include "ventas.h"
#include "caja.h"

const char tipos_medios_de_pago[4][15] = {"Efectivo","Debito","Credito","Transferencia"};
const char estado_venta[2][12]= {"CANCELADA","Activa"};

///////////////////// MOSTRAR ARCHIVO VENTAS  //////////////////////////////
void mostrar_listado_ventas()
{
    FILE* buffer= fopen(NOMBRE_ARCHIVO_VENTAS, "rb");

    stVenta venta;

    if(buffer)
    {
        while(fread(&venta, sizeof(stVenta), 1, buffer) > 0)
        {
           mostrar_venta_modo_listado(venta);
           printf("\n");
        }
        fclose(buffer);
    }
    else
        printf("\nNo se pudo abrir el archivo\n");
}

///////////////////// calcular total suma precios //////////////////
int calcular_suma_precios(Pila pila_a)
{

    int suma = 0;

    while(!pilavacia(&pila_a))
    {
        suma += tope(&pila_a);
        desapilar(&pila_a);
    }
    return suma;
}
///////////////////// GENERAR ID VENTAS ////////////////////////////////
int generar_ID_venta(FILE* buffer)
{

    int num_ID = 0;
    stVenta venta;
    stVenta ultimo;

    if(buffer != NULL)
    {
        fseek(buffer, 0, 0);

        if (fread(&venta, sizeof(stVenta), 1, buffer) == 1)
        {
            fseek(buffer, (sizeof(stVenta)*-1), 2);  //lo uso para leer el ID de la ultima venta
            fread(&ultimo, sizeof(stVenta), 1, buffer);

            num_ID = ultimo.ID + 1;

        }
        else if(fread(&venta,sizeof(stVenta), 1, buffer) == 0)    //retorna 0 porque no hay ningun registro
            num_ID = 1;//la primera venta creada recibe 1 como ID

    }
    else
        printf("\nNo puedo abrirse el archivo\n");

    return num_ID;
}

///////////////////// agregar articulos vendidos /////////////////////////
int agregar_articulos_vendidos(int id_vendidos[], int** id_vendidos_validos)  // retorna un entero que es el monto total a pagar de la venta
{
    char control = 's';

    stArticulo articulo;

    int ID_articulo_vendido = 0;

    Pila suma_precios;
    inicpila(&suma_precios);

    int i = 0;

    **id_vendidos_validos = 0;

    while(control =='s' && (i < DIMENSION_ARREGLO_ID_STVENTAS))        // permite cargar varios articulos a la venta
    {
        do
        {
            printf("\n\nIngrese ID del articulo vendido\n");
            scanf("%d",&ID_articulo_vendido);

            articulo = buscar_articulo_ID(ID_articulo_vendido); // si existe el ID, retorna una copia de la estructura. si no existe retorna ID == -1

            if(articulo.ID == -1) // info al usuario que el ID es invalido para que lo reingrese
                printf("\nNo se encontraron articulos con ese ID. Intente nuevamente\n");
            if(articulo.estado_activo == 0)
                printf("\nEse articulo se encuentra INACTIVO\n");
            if(articulo.cantidad_disponible <= 0)
                printf("\nNo hay stock del articulo ingresado\n");

        }
        while((articulo.ID == -1) || (articulo.estado_activo == 0) || (articulo.cantidad_disponible <= 0));  // valida que exista el ID

        printf("\nArticulo:%s\n", articulo.descripcion);

        apilar(&suma_precios, articulo.precio); //apila el precio del articulo vendido

        id_vendidos[i] = articulo.ID; // carga en el arreglo, los id de los articulos vendidos
        i++;

        disminuir_cantidad_articulo(articulo.ID); // disminuye en 1 el stock de ese articulo

        printf("\nQuiere agregrar otro articulo a la venta? s/n\n");
        fflush(stdin);
        scanf("%c",&control);

    }

    **id_vendidos_validos = i; // guardo i en los validos del arreglo de ids

    int monto_total = calcular_suma_precios(suma_precios); //le paso la pila con los precios de los articulos

    return monto_total;
}

///////////////////// validacion medio pago //////////////////////////
int ingresar_validar_medio_pago_venta()
{

    int opcion = 0;

    printf("\nMEDIO DE PAGO:\n");
    printf("\nIngresa el numero de la opcion correspondiente:\n1:Efectivo 2:Debito 3:Credito 4:Transferencia\n");
    scanf("%d",&opcion);


    while((opcion != 1) && (opcion != 2) && (opcion != 3) && (opcion != 4)) //valida el dato ingresado
    {
        printf("\nOpcion invalida\n");
        printf("\nVuelva a ingresar la opcion correspondiente al medio de pago:");
        printf("1:Efectivo \n2:Debito \n3:Credito \n4:Transferencia\n");
        scanf("%d",&opcion);
    }

    return opcion;
}
///////////////////// AGREGAR DESCUENTO ////////////////
int agregar_descuento(int * monto_total)
{

    char control = 's';
    int porcentaje_descuento = 0;

    printf("\nDesea aplicar un descuento en la venta?\n");
    fflush(stdin);
    scanf("%c", &control);

    if (control == 's')  // se ejecuta solo si el usuario quiere agregar un descuento
    {

        printf("\nIngrese el porcentaje a descontar (sin el %%):\n");
        scanf("%d", &porcentaje_descuento);

        *monto_total = *monto_total - ((*monto_total*porcentaje_descuento)/ 100);
    }

    return porcentaje_descuento;
}
///////////////////// mostrar venta /////////////////////
void mostrar_venta_comprobante(stVenta venta)
{

    printf("\n------------------------------VENTA------------------------------\n");
    printf("\n");

    mostrar_fecha_ventas(venta.fecha);
    printf("\nID venta: N%d", venta.ID);

    mostrar_detalle_articulos_vendidos(venta.id_vendidos, venta.id_vendidos_validos);

    printf("\n.................................................................\n");


    printf("\n|SUBTOTAL:$%d \n",venta.monto_total); // si no hay descuento el subtotal es igual al total. si hay descuento el subtotal es el monto total

    if ( venta.porcentaje_a_descontar > 0) //si se aplico con descuento
    {
        printf("\n|Descuento:%%%d\n",venta.porcentaje_a_descontar);
        printf("\n|TOTAL:$%d\n",venta.monto_total-((venta.porcentaje_a_descontar*venta.monto_total)/100)); // el total es menos que el subtotal porque hay un descuento aplicado
    }
    else
        printf("\n|TOTAL: $%d\n",venta.monto_total);

    printf("\nMedio de pago: %s",tipos_medios_de_pago[venta.medio_pago - 1]);

    if( venta.medio_pago == 3) //si es credito
        printf("\n|Cantidad cuotas: %d\n",venta.cantidad_cuotas);

    printf("\nEstado de venta: %s\n",estado_venta[venta.estado]);

    printf("\nID de la caja: %d\n",venta.ID_caja);

    printf("\n------------------------------------------------------------------\n");
}
///////////////////// carga stVenta ////////////////////
stVenta cargar_struct_venta(FILE* buffer)  // el buffer abierto que recibe es el del archivo ventas
{
    system("cls");
    printf("\n-----------------------Esta por crear un nueva VENTA-----------------------\n");
    printf("___________________________________________________________________________");

    stVenta venta;
    stCaja caja;

    int aux_validos = 0;
    int* puntero_aux = &aux_validos;

    struct tm* fecha_actual = obtener_fecha_actual_venta();
    venta.fecha = *fecha_actual;

    venta.ID = generar_ID_venta(buffer);

    int monto_total = agregar_articulos_vendidos(venta.id_vendidos, &puntero_aux);// retorna el monto resultante de sumar todos los precios de los articulos vendidos.

    venta.id_vendidos_validos = aux_validos;

    venta.porcentaje_a_descontar = agregar_descuento(&monto_total); // si se agrega un descuento se guarda el descuento aplicado

    venta.monto_total = monto_total; //guardo el monto total. si hubo descuento la f(x)agregar descuento ya modifico el monto total con el monto con el descuento aplicado. si no hay descuento, el monto total es el mismo que el retornado por agregar articulos

    venta.medio_pago = ingresar_validar_medio_pago_venta();

    if( venta.medio_pago == 3)
    {
        printf("\nIngrese la cantidad de cuotas:\n");
        scanf("%d",&venta.cantidad_cuotas);
    }

    venta.estado = 1; // 1 es igual a activa

    FILE* buffer_caja = fopen(NOMBRE_ARCHIVO_CAJAS, "rb");
    if (buffer_caja){

    fseek(buffer_caja,sizeof(stCaja)*-1,2);
    fread(&caja, sizeof(stCaja), 1, buffer_caja);

    venta.ID_caja = caja.ID;

    fclose(buffer_caja);
} else {
    printf("El archivo no pudo abrirse.\n");
}

    return venta;
}
///////////////////// cargar archivo ventas //////////////////
void cargar_archivo_ventas()
{
    char control = 's';

    FILE* buffer = fopen(NOMBRE_ARCHIVO_VENTAS, "a+b");

    stVenta venta;

    if(buffer)
    {
        while(control == 's')
        {

            venta = cargar_struct_venta(buffer);

            mostrar_venta_comprobante(venta);

            fseek(buffer, 0, 2); // me posiciono al final para agregar el registro
            fwrite(&venta, sizeof(stVenta), 1, buffer);

            printf("\nDesea cargar una NUEVA venta? s/n\n");
            fflush(stdin);
            scanf("%c",&control);
        }

        fclose(buffer);
    }
    else
        printf("\nEl archivo no pudo ser abierto\n");
}

///////////////////// mostrar ventas listado //////////////////
void mostrar_venta_modo_listado(stVenta venta)
{

    mostrar_fecha_ventas(venta.fecha);
    printf("|ID: %d|", venta.ID);
    printf("|ID de la caja: %d|", venta.ID_caja);
    printf("|Monto total: %d|", venta.monto_total);
    printf("|Medio de pago: %s|",tipos_medios_de_pago[venta.medio_pago - 1]);
    printf("|Estado: %s|",estado_venta[venta.estado]);
}
///////////////////// buscar venta por ID ///////////////////////
stVenta buscar_venta_ID(int num_ID)
{
    stVenta venta;

    FILE* buffer = fopen(NOMBRE_ARCHIVO_VENTAS, "rb");

    if(buffer)
    {
        fseek(buffer, sizeof(stVenta) * (num_ID - 1), 0); // voy al comienzo del registro el cual tendria que tener el mismo ID
        fread(&venta, sizeof(stVenta), 1, buffer);

        if(venta.ID != num_ID)
            venta.ID = -1; // si no entra en el if, el ID pasa a ser -1 (es un ID invalido)

        fclose(buffer);
    }
    else
        printf("\nNo pudo abrirse el archivo");

    return venta;
}
///////////////////// cambiar estado venta a inactivo ==0 /////////////////////////////
stVenta cambiar_estado_venta(int id_venta)
{
    FILE* buffer = fopen(NOMBRE_ARCHIVO_VENTAS, "r+b");
    stVenta venta;

    if(buffer){

        fseek(buffer, sizeof(stVenta) * (id_venta - 1), 0);
        fread(&venta, sizeof(stVenta), 1, buffer);

        venta.estado = 0; // cambio el estado a 0 = cancelada

        fseek(buffer, sizeof(stVenta) * (id_venta - 1), 0);
        fwrite(&venta, sizeof(stVenta), 1, buffer);

        fclose(buffer);
    }
    else
        printf("\nNo pudo abrirse el archivo");

    return venta;

}

///////////////////// dar de baja venta //////////////////////
void dar_baja_venta()
{
    int id_venta = 0;
    char control = 's';
    int i = 0;

    stVenta venta_a_cancelar;
    stVenta venta_cancelada; // recibe el retorno de la funcion que cambia el estado a cancelado

    do
    {
        printf("\nIngrese el ID de la venta que desea CANCELAR:\n");
        scanf("%d", &id_venta);

        venta_a_cancelar = buscar_venta_ID(id_venta);

        if(venta_a_cancelar.ID == -1)
            printf("\nNo se encontro una venta con ese ID. Intente nuevamente\n");

    }
    while(venta_a_cancelar.ID == -1);

    if(venta_a_cancelar.estado == 0){

        printf("\nLA VENTA BUSCADA YA SE ENCUENTRA CANCELADA\n");
    }else
    {
    printf("\n------------------------------------------------------------");
    printf("\nLA VENTA QUE ESTA POR CANCELAR ES:\n");

    mostrar_venta_comprobante(venta_a_cancelar);

    printf("\nEsta seguro que quiere cancelar la venta? s/n\n"); // solicita confirmacion para cancelar la venta
    fflush(stdin);
    scanf("%c", &control);

    if(control == 's')
    {
        venta_cancelada = cambiar_estado_venta(id_venta);

        FILE* buffer = fopen(NOMBRE_ARCHIVO_ARTICULOS, "r+b"); // abro el archivo de articulos

        if(buffer){

                while(i < venta_a_cancelar.id_vendidos_validos){

                aumentar_cantidad_disponible_articulo(buffer, venta_a_cancelar.id_vendidos[i]);
                i++;
        }

            fclose(buffer);
        }else
        printf("\nNo se pudo abrir el archivo");
    }

    if(venta_cancelada.estado == 0)
        printf("\n***************La venta fue CANCELADA con exito ****************\n         No se tendra en cuenta para el arqueo de caja\n");
    }
}
///////////////////// consultar venta por ID //////////////////////////
void consultar_venta_id()
{
    int id_venta = 0;
    stVenta venta;

    do
    {
        printf("\nIngrese el ID de la venta:\n");
        scanf("%d", &id_venta);

        venta = buscar_venta_ID(id_venta);

        if(venta.ID == -1)
            printf("\nNo se encontro una venta con ese ID. Intente nuevamente\n");

    }
    while(venta.ID == -1);

    printf("\nVENTA CONSULTADA:\n");
    mostrar_venta_comprobante(venta);
}

