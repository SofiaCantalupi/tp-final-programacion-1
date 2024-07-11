#ifndef ARTICULOS_H_INCLUDED
#define ARTICULOS_H_INCLUDED

#define NOMBRE_ARCHIVO_ARTICULOS "articulos.BIN"

typedef struct{
    int ID;
    char descripcion[30];
    int precio;
    char talle[10];
    char color[12];
    int cantidad_disponible; // o int stock ??
    char marca[20];
    int estado_activo; // 1:activo 2:inactivo
} stArticulo;

stArticulo buscar_articulo_ID(int num_ID);
int generar_ID_articulo(FILE* buffer);
stArticulo cargar_articulo(FILE* buffer);
void mostrar_articulo(stArticulo);
void mostrar_archivo_articulos();
void cargar_registro_articulo();
void mostrar_detalle_articulos_vendidos(int id_vendidos[], int id_vendidos_validos);
void baja_articulo();
int ingresar_id();
void listar_articulo_descripcion();
void listar_articulo_ID ();
void mostrar_articulo_encabezado(stArticulo);
stArticulo buscar_articulo_xdescrip(char descrip[]);
stArticulo modificar_descripcion_articulo(stArticulo A);
stArticulo modificar_precio_articulo(stArticulo A);
stArticulo modificar_talle_articulo(stArticulo A);
stArticulo modificar_color_articulo(stArticulo A);
stArticulo modificar_marca_articulo(stArticulo A);
stArticulo modificar_cantidad_articulo(stArticulo A);
void modificar_archivo_articulo();
int cantidadRegis(stArticulo Ar);
stArticulo* CreaDinamicoArchivo(int registros,stArticulo Ar);
void ArchivoDinamico(stArticulo Ar,stArticulo ArDin[]);
int buscarMenor(int validos, stArticulo A[],int pos);
void ordeanmientoSeleccion(int validos, stArticulo A[]);
void mostrarArticulo(stArticulo Ar);
void ArregloMostrar(int validos,stArticulo Ar[]);

#endif // ARTICULOS_H_INCLUDED
