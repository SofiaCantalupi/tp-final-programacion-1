#ifndef MENU_CAJA.h  // Si no está definido MENU_CAJA.H
#define MENU_CAJA.h  // Define MENU_CAJA.H

// Declaración de la función menu_caja.

void menu_caja();
// Esta es una declaración adelantada de la función que se definirá en otro archivo (.c).

#endif // Fin de la condición para MENU_CAJA.H




/**

        EXPLICACION DETALLADA

    --------------------------------------------

    1 - Directivas de preprocesador #ifndef y #define:

            #ifndef MENU_CAJA.H
            #define MENU_CAJA.H

    Estas directivas se utilizan para evitar la inclusión múltiple del archivo de cabecera.
    Si MENU_GESTION_PRODUCTOS_H no está definido, se define.
    Esto asegura que el contenido del archivo se incluya solo una vez por compilación, evitando errores de redefinición.

    -------------------------------------------

    2 - Declaración de la función:

        void menu_caja();

    Esta declaración indica que hay una función con este nombre que será definida en algún otro lugar del programa (probablemente en un archivo .c)

    -------------------------------------------

    3 - Fin de la condición #ifndef:

    Esta directiva marca el final de la condición iniciada por #ifndef.
    Todo el código entre #ifndef y #endif se incluirá solo si MENU_GESTION_PRODUCTOS_H no estaba definido anteriormente.
    Después de esta directiva, MENU_GESTION_PRODUCTOS_H estará definido, lo que prevendrá que este código se incluya más de una vez en la compilación.

    -------------------------------------------

    ¿Cómo se usa este archivo?

    Este archivo (MENU_CAJA.h) se incluye en los archivos .c que necesiten usar la función menu_caja().
    La implementación de la función menu_caja() estará en un archivo .c separado.

*/
