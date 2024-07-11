#ifndef EMPLEADO_H_INCLUDED
#define EMPLEADO_H_INCLUDED

#define NOMBRE_ARCHIVO_EMPLEADOS "ArchivoEmpleados"

typedef struct {
    int ID;
    char nombre_completo[30];
    char DNI[15];
    int rol; //fucionarla con estado. 0 Inactivo 1 admin 2 usuario.
    char usuario[15]; ///admin123
    char contrasenia[15]; ///utn2024
}stEmpleados;

///Prototipados///
int generar_ID();
stEmpleados cargarUnEmpleado();
void cargar_empleados();
void mostrar_empleado(stEmpleados empleado);
void mostrar_archivo_empleados();
stEmpleados retornar_empleado_buscado(char DNI_buscado[]);
int empleado_a_eliminar();
void baja_empleado();
stEmpleados retornar_empleado_por_ID(int ID);
void alta_empleado();
int empleado_a_dar_alta();
void ordenamientoInsercion(int validos, stEmpleados E[]);
void insertarElem (int validos, stEmpleados E[], int u, stEmpleados Em);
void ArregloMostrarEm(int validos,stEmpleados Em[]);
int cantidadRegisE(stEmpleados Em);
void ArchivoDinamicoE(stEmpleados Em,stEmpleados ArDinE[]);
stEmpleados* CreaDinamicoArchivoE(int registros,stEmpleados Em);
void mostrarEmpleado(stEmpleados Em);
void log_in ();
void cargar_empleado();
void baja_de_empleado();
stEmpleados modificar_DNI_empleado(stEmpleados A);
stEmpleados modificar_nombre_empleado(stEmpleados A);
void modificar_archivo_empleados();


#endif // EMPLEADO_H_INCLUDED
