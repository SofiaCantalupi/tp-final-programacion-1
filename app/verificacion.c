#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "empleado.h"

#define NOMBRE_ARCHIVO_EMPLEADOS "ArchivoEmpleados"

int verificar_rol(int empleado_a_usar){

    FILE *buffer;
    int flag = 0;
    int rol;
    stEmpleados empleado;
    buffer = fopen(NOMBRE_ARCHIVO_EMPLEADOS,"rb");
    if (buffer != NULL){

        fseek(buffer,sizeof(stEmpleados)*(empleado_a_usar-1),0);
        fread(&empleado,sizeof(stEmpleados),1,buffer);
        rol = empleado.rol;

    } else {
        printf("El archivo no se pudo abrir\n");
    }
        return rol;
}

int verificar_contrasenia(char ingreso[],int empleado_a_usar){

    FILE *buffer;
    stEmpleados empleado;
    int flag = 0;
    buffer = fopen(NOMBRE_ARCHIVO_EMPLEADOS,"rb");
    if (buffer != NULL){

        fseek(buffer,sizeof(stEmpleados)*(empleado_a_usar-1),0);
        fread(&empleado,sizeof(stEmpleados),1,buffer);
        if (strcmp(ingreso,empleado.contrasenia) == 0){
            flag = 1;
        }

    } else {
        printf("El archivo no se pudo abrir\n");
    }
        return flag;
}

int verificar_usuario(char ingreso[],int empleado_a_usar){

    FILE *buffer;
    stEmpleados empleado;
    int flag = 0;
    buffer = fopen(NOMBRE_ARCHIVO_EMPLEADOS,"rb");
    if (buffer != NULL){

        fseek(buffer,sizeof(stEmpleados)*(empleado_a_usar-1),0);
        fread(&empleado,sizeof(stEmpleados),1,buffer);
        if (strcmp(ingreso,empleado.usuario) == 0){
            flag = 1;
        }

    } else {
        printf("El archivo no se pudo abrir\n");
    }
        return flag;
}

int verificar_ID(int empleado_a_usar){

    FILE *buffer;
    int flag = 0;
    stEmpleados empleado;
    buffer = fopen(NOMBRE_ARCHIVO_EMPLEADOS,"rb");
    if (buffer != NULL){

        while(flag == 0 && fread(&empleado,sizeof(stEmpleados),1,buffer) >0){

        if (empleado_a_usar == empleado.ID){
                    flag = 1;
                }
        }
    fclose(buffer);
    } else {
        printf("El archivo no se pudo abrir\n");
    }
        return flag;
}


///Cambiar contrasena


stEmpleados contrasenia(stEmpleados Em){

    printf("A continuacion, modifique su contrasena: ");
    fflush(stdin);
    gets(&Em.contrasenia);

        return Em;
 }

int modificarContrasenaAdim(int id){

    stEmpleados Em;
    FILE * buffer;
    buffer = fopen(NOMBRE_ARCHIVO_EMPLEADOS,"r+b");
    int flag = 0;
    int i = 0;
    int validos = cantidadRegisE(Em);

    if(buffer!=NULL){
            while(i< validos && flag ==0){
                    fseek(buffer, sizeof(stEmpleados)*(i), SEEK_SET);
                    fread(&Em,sizeof(stEmpleados),1,buffer);
                if(id == Em.ID){
                    Em = contrasenia(Em);
                    fseek(buffer,sizeof(stEmpleados)*(-1),SEEK_CUR);
                    fwrite(&Em,sizeof(stEmpleados),1,buffer);
                flag = 1;
                }
                i++;
            }
        fclose(buffer);
    }else{
        printf("El archivo no se abrio");
    }

return flag;
}

///Retorna flag, en el main la recibe para verificar si se modifico o no exitosamente
///la nueva contrasenia

stEmpleados usuario(stEmpleados Em){

    printf("A continuacion, modifique su usuario: ");
    fflush(stdin);
    gets(&Em.usuario);

        return Em;
 }

int modificarUsuarioAdmin(int id){

    stEmpleados Em;
    FILE * buffer;
    buffer = fopen(NOMBRE_ARCHIVO_EMPLEADOS,"r+b");
    int flag = 0;
    int i = 0;
    int validos = cantidadRegisE(Em);

    if(buffer!=NULL){
            while(i< validos && flag ==0){
                    fseek(buffer, sizeof(stEmpleados)*(i), SEEK_SET);
                    fread(&Em,sizeof(stEmpleados),1,buffer);
                if(id == Em.ID){
                    Em = usuario(Em);
                    fseek(buffer,sizeof(stEmpleados)*(-1),SEEK_CUR);
                    fwrite(&Em,sizeof(stEmpleados),1,buffer);
                flag = 1;
                }
                i++;
            }
        fclose(buffer);
    }else{
        printf("El archivo no se abrio");
    }

return flag;
}
