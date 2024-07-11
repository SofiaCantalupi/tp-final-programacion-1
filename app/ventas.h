#ifndef VENTAS_H_INCLUDED
#define VENTAS_H_INCLUDED

#define NOMBRE_ARCHIVO_VENTAS "ventas.BIN"
#define DIMENSION_ARREGLO_ID_STVENTAS 30


typedef struct{
    int estado; // 1 = activa 0 = cancelada
    int ID;
    int caja_ID;
    int id_vendidos[30];
    int id_vendidos_validos;
    struct tm fecha;                                                                     // es un tipo de struct ya definido en time.h. Guarda la info de fecha y hora en sus componentes individuales
    int monto_total;
    int medio_pago; // 1 = efectivo 2 = debito 3 = credito 4 = transferencia
    int cantidad_cuotas; // usado solo para pago con credito
    int porcentaje_a_descontar;
    int ID_caja;
} stVenta;

/// VENTAS
void mostrar_listado_ventas();
int generar_ID_venta(FILE* buffer);
void  disminuir_cantidad_articulo(int num_ID);
int sumar_precio_vendidos(stArticulo arreglo_articulos_vendidos[],int validos);
int agregar_articulos_vendidos(int id_vendidos[], int** id_vendidos_validos);
int ingresar_validar_medio_pago_venta();

void mostrar_venta_comprobante(stVenta venta);
void mostrar_venta_modo_listado(stVenta venta);

stVenta cargar_struct_venta(FILE* buffer);
void cargar_archivo_ventas();

void listado_ventas_fecha();
stVenta cambiar_estado_venta(int id_venta);
void  aumentar_cantidad_disponible_articulo(FILE* buffer, int num_ID);
stVenta buscar_venta_ID(int num_ID);
void dar_baja_venta();
void consultar_venta_id();

#endif // VENTAS_H_INCLUDED
