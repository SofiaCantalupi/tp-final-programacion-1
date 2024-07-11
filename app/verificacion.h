#ifndef VERIFICACION_H_INCLUDED
#define VERIFICACION_H_INCLUDED
#include "empleado.h"

int verificar_ID(int empleado_a_usar);
int verificar_usuario(char ingreso[],int empleado_a_usar);
int verificar_contrasenia(char ingreso[],int empleado_a_usar);
int verificar_rol(int empleado_a_usar);
stEmpleados contrasenia(stEmpleados Em);
int modificarContrasenaAdim(int id);
stEmpleados usuario(stEmpleados Em);
int modificarUsuarioAdmin(int id);

#endif // VERIFICACION_H_INCLUDED
