#ifndef MENU_CAJA.h  // Si no est� definido MENU_CAJA.H
#define MENU_CAJA.h  // Define MENU_CAJA.H

// Declaraci�n de la funci�n menu_caja.

void menu_caja();
// Esta es una declaraci�n adelantada de la funci�n que se definir� en otro archivo (.c).

#endif // Fin de la condici�n para MENU_CAJA.H




/**

        EXPLICACION DETALLADA

    --------------------------------------------

    1 - Directivas de preprocesador #ifndef y #define:

            #ifndef MENU_CAJA.H
            #define MENU_CAJA.H

    Estas directivas se utilizan para evitar la inclusi�n m�ltiple del archivo de cabecera.
    Si MENU_GESTION_PRODUCTOS_H no est� definido, se define.
    Esto asegura que el contenido del archivo se incluya solo una vez por compilaci�n, evitando errores de redefinici�n.

    -------------------------------------------

    2 - Declaraci�n de la funci�n:

        void menu_caja();

    Esta declaraci�n indica que hay una funci�n con este nombre que ser� definida en alg�n otro lugar del programa (probablemente en un archivo .c)

    -------------------------------------------

    3 - Fin de la condici�n #ifndef:

    Esta directiva marca el final de la condici�n iniciada por #ifndef.
    Todo el c�digo entre #ifndef y #endif se incluir� solo si MENU_GESTION_PRODUCTOS_H no estaba definido anteriormente.
    Despu�s de esta directiva, MENU_GESTION_PRODUCTOS_H estar� definido, lo que prevendr� que este c�digo se incluya m�s de una vez en la compilaci�n.

    -------------------------------------------

    �C�mo se usa este archivo?

    Este archivo (MENU_CAJA.h) se incluye en los archivos .c que necesiten usar la funci�n menu_caja().
    La implementaci�n de la funci�n menu_caja() estar� en un archivo .c separado.

*/
