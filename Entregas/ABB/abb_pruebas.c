/*
 * prueba_hash.c
 * Pruebas para el tipo de dato abstracto Tabla de Hash
 * Copyright: (2011) Margarita Manterola, Maximiliano Curia
 * Licencia: CC-BY-SA 2.5 (ar) ó CC-BY-SA 3.0
 */

#include "abb.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

static void prueba_crear_abb_vacio() {
    printf("\n~~~ Prueba: CREAR ABB VACIO ~~~ \n");

    abb_t* abb = abb_crear(NULL, NULL);

    print_test("Crear ABB vacio", abb != NULL);
    print_test("La cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("Prueba abb obtener clave A, es NULL, no existe", abb_obtener(abb, "A") == NULL);
    print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
    print_test("Prueba abb borrar clave A, es NULL, no existe", abb_borrar(abb, "A") == NULL);

    abb_destruir(abb);
    printf("\n");
}

static void prueba_iterar_abb_vacio(){
    printf("~~~ Prueba: ITERAR ABB VACIO (EXTERNO) ~~~ \n");
    abb_t* abb = abb_crear(strcmp, NULL);
    abb_iter_t* iter = abb_iter_in_crear(abb);

    print_test("Crear iterador ABB vacio", iter);
    print_test("Iter esta al final", abb_iter_in_al_final(iter));
    print_test("Iter avanzar ABB vacio devuelve false", !abb_iter_in_avanzar(iter));
    print_test("Iter ver actual ABB vacio es NULL", abb_iter_in_ver_actual(iter) == NULL);

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
    printf("\n");
}

static void prueba_abb_insertar(){
    printf("~~~ Prueba: ABB INSERTAR Y NO BORRAR ~~~ \n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "A", *valor1 = "1";
    char *clave2 = "B", *valor2 = "2";
    char *clave3 = "C", *valor3 = "3";

    /* Inserta los 3 valores y no los borra (se destruyen con el abb) */
    print_test("Insertar clave 2 ", abb_guardar(abb, clave2, valor2));
    print_test("La cantidad de elementos es 2", abb_cantidad(abb) == 1);
    print_test("Obtener clave 2 es valor 2", abb_obtener(abb, clave2) == valor2);
    print_test("Pertenece clave 2, es true", abb_pertenece(abb, clave2));

    print_test("Insertar clave 1", abb_guardar(abb, clave1, valor1));
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 2);
    print_test("Obtener clave 1 es valor 1", abb_obtener(abb, clave1) == valor1);
    print_test("Pertenece clave 1, es true", abb_pertenece(abb, clave1));

    print_test("Insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("La cantidad de elementos es 2", abb_cantidad(abb) == 3);
    print_test("Obtener clave 3 es valor 3", abb_obtener(abb, clave3) == valor3);
    print_test("Pertenece clave 3, es true", abb_pertenece(abb, clave3));

    abb_destruir(abb);
    printf("\n");
}

static void prueba_abb_reemplazar(){
    printf("~~~ Prueba: ABB REEMPLAZAR Y NO BORRAR ~~~ \n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "A", *valor1 = "1";
    char *clave2 = "B", *valor2 = "2";
    char *clave3 = "C", *valor3 = "3";
    char *clave4 = "D", *valor4 = "4";
    char *clave5 = "E", *valor5 = "5";
    char *valor6 = "6";
    char *valor7 = "7";
    char *valor8 = "8";

    /* Inserta 5 valores y luego reemplaza uno de ellos */
    print_test("Insertar clave 3", abb_guardar(abb, clave3, valor3));
    print_test("Obtener clave 3 es valor 3", abb_obtener(abb, clave3) == valor3);
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 1);

    print_test("Insertar clave 1", abb_guardar(abb, clave1, valor1));
    print_test("Obtener clave 1 es valor 1", abb_obtener(abb, clave1) == valor1);
    print_test("La cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Insertar clave 5", abb_guardar(abb, clave5, valor5));
    print_test("Obtener clave 5 es valor 5", abb_obtener(abb, clave5) == valor5);
    print_test("La cantidad de elementos es 3", abb_cantidad(abb) == 3);

    print_test("Insertar clave 2", abb_guardar(abb, clave2, valor2));
    print_test("Obtener clave 2 es valor 2", abb_obtener(abb, clave2) == valor2);
    print_test("La cantidad de elementos es 4", abb_cantidad(abb) == 4);

    print_test("Insertar clave 4", abb_guardar(abb, clave4, valor4));
    print_test("Obtener clave 4 es valor 4", abb_obtener(abb, clave4) == valor4);
    print_test("La cantidad de elementos es 5", abb_cantidad(abb) == 5);

    /* Reemplazo */
    print_test("Reemplazar clave 3", abb_guardar(abb, clave3, valor6));
    print_test("Obtener clave 3 es valor 6", abb_obtener(abb, clave3) == valor6);
    print_test("La cantidad de elementos sigue siendo 5", abb_cantidad(abb) == 5);

    print_test("Reemplazar clave 4", abb_guardar(abb, clave4, valor7));
    print_test("Obtener clave 4 es valor 7", abb_obtener(abb, clave4) == valor7);
    print_test("La cantidad de elementos sigue siendo 5", abb_cantidad(abb) == 5);

    print_test("Reemplazar clave 2", abb_guardar(abb, clave2, valor8));
    print_test("Obtener clave 2 es valor 8", abb_obtener(abb, clave2) == valor8);
    print_test("La cantidad de elementos sigue siendo 5", abb_cantidad(abb) == 5);

    abb_destruir(abb);
    printf("\n");
}

static void prueba_abb_reemplazar_con_destruir() {
    printf("~~~ Prueba: ABB REEMPLAZAR Y DESTRUIR ~~~ \n");
    abb_t* abb = abb_crear(strcmp, free);

    char *clave1 = "A";
    char *clave2 = "B";
    char *clave3 = "C";
    char *clave4 = "D";
    char *clave5 = "E";

    int* valor1 = malloc(sizeof(int));
    *valor1 = 1;
    int* valor2 = malloc(sizeof(int));
    *valor2 = 2;
    int* valor3 = malloc(sizeof(int));
    *valor3 = 3;
    int* valor4 = malloc(sizeof(int));
    *valor4 = 4;
    int* valor5 = malloc(sizeof(int));
    *valor5 = 5;

    int* valor6 = malloc(sizeof(int));
    *valor6 = 9;
    int* valor7 = malloc(sizeof(int));
    *valor7 = 8;

    /* Inserta 5 valores y luego los reemplaza (debe liberar lo que reemplaza) */
    print_test("Insertar clave 3", abb_guardar(abb, clave3, valor3));
    print_test("Obtener clave 3 es valor 3", abb_obtener(abb, clave3) == valor3);
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 1);

    print_test("Insertar clave 1", abb_guardar(abb, clave1, valor1));
    print_test("Obtener clave 1 es valor 1", abb_obtener(abb, clave1) == valor1);
    print_test("La cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Insertar clave 5", abb_guardar(abb, clave5, valor5));
    print_test("Obtener clave 5 es valor 5", abb_obtener(abb, clave5) == valor5);
    print_test("La cantidad de elementos es 3", abb_cantidad(abb) == 3);

    print_test("Insertar clave 2", abb_guardar(abb, clave2, valor2));
    print_test("Obtener clave 2 es valor 2", abb_obtener(abb, clave2) == valor2);
    print_test("La cantidad de elementos es 4", abb_cantidad(abb) == 4);

    print_test("Insertar clave 4", abb_guardar(abb, clave4, valor4));
    print_test("Obtener clave 4 es valor 4", abb_obtener(abb, clave4) == valor4);
    print_test("La cantidad de elementos es 5", abb_cantidad(abb) == 5);

    /* Reemplazo */
    print_test("Reemplazar clave 4", abb_guardar(abb, clave4, valor6));
    print_test("Obtener clave 4 es valor 6", abb_obtener(abb, clave4) == valor6);
    print_test("La cantidad de elementos sigue siendo 5", abb_cantidad(abb) == 5);

    print_test("Reemplazar clave 2", abb_guardar(abb, clave2, valor7));
    print_test("Obtener clave 2 es valor 3", abb_obtener(abb, clave2) == valor7);
    print_test("La cantidad de elementos sigue siendo 5", abb_cantidad(abb) == 5);

    /* Se destruye el abb (se debe liberar lo que quedó dentro) */
    abb_destruir(abb);
    printf("\n");
}

static void prueba_abb_borrar_con_destruir() {
    printf("~~~ Prueba: ABB BORRAR Y DESTRUIR ~~~ \n");
    abb_t* abb = abb_crear(strcmp, free);

    char *clave1 = "A", *valor1;
    char *clave2 = "B", *valor2;
    char *clave3 = "C", *valor3;
    char *clave4 = "D", *valor4;
    char *clave5 = "E", *valor5;

    /* Pide memoria para 4 valores */
    valor1 = malloc(10 * sizeof(char));
    valor2 = malloc(10 * sizeof(char));
    valor3 = malloc(10 * sizeof(char));
    valor4 = malloc(10 * sizeof(char));
    valor5 = malloc(10 * sizeof(char));

    /* Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza) */
    print_test("Insertar clave 3", abb_guardar(abb, clave3, valor3));
    print_test("Insertar clave 1", abb_guardar(abb, clave1, valor1));
    print_test("Insertar clave 5", abb_guardar(abb, clave5, valor5));
    print_test("Insertar clave 4", abb_guardar(abb, clave4, valor4));
    print_test("Insertar clave 2", abb_guardar(abb, clave2, valor2));
    
    print_test("Borrar clave 4 devuelve valor 4", abb_borrar(abb, clave4) == valor4);
    print_test("Borrar clave 2 devuelve valor 2", abb_borrar(abb, clave2) == valor2);
    print_test("Borrar clave 1 devuelve valor 1", abb_borrar(abb, clave1) == valor1);
    print_test("Borrar clave 5 devuelve valor 5", abb_borrar(abb, clave5) == valor5);
    print_test("Borrar clave 3 devuelve valor 3", abb_borrar(abb, clave3) == valor3);

    print_test("La cantidad es 0", abb_cantidad(abb) == 0);

    free(valor1);
    free(valor2);
    free(valor3);
    free(valor4);
    free(valor5);

    abb_destruir(abb);
    printf("\n");
}

static void prueba_abb_borrar() {
    printf("~~~ Prueba: ABB BORRAR ~~~ \n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "A", *valor1 = "1";
    char *clave2 = "B", *valor2 = "2";
    char *clave3 = "C", *valor3 = "3";
    char *clave4 = "D", *valor4 = "4";
    char *clave5 = "E", *valor5 = "5";

    print_test("Insertar clave 3", abb_guardar(abb, clave3, valor3));
    print_test("Insertar clave 1", abb_guardar(abb, clave1, valor1));
    print_test("Insertar clave 5", abb_guardar(abb, clave5, valor5));
    print_test("Insertar clave 4", abb_guardar(abb, clave4, valor4));
    print_test("Insertar clave 2", abb_guardar(abb, clave2, valor2));

    // Borrar con 2 hijos
    print_test("Pertenece clave 3, es true", abb_pertenece(abb, clave3));
    print_test("Borrar clave 3 devuelve valor 3", abb_borrar(abb, clave3) == valor3);
    print_test("Borrar clave 3 devuelve NULL", !abb_borrar(abb, clave3));
    print_test("Pertenece clave 3, es false", !abb_pertenece(abb, clave3));
    print_test("Obtener clave 3 devuelve NULL", !abb_obtener(abb, clave3));
    print_test("La cantidad de elementos es 4", abb_cantidad(abb) == 4);

    // Borrar con 0 hijos
    print_test("Pertenece clave 4, es true", abb_pertenece(abb, clave4));
    print_test("Borrar clave 4 devuelve valor 4", abb_borrar(abb, clave4) == valor4);
    print_test("Borrar clave 4 devuelve NULL", !abb_borrar(abb, clave4));
    print_test("Pertenece clave 4, es false", !abb_pertenece(abb, clave4));
    print_test("Obtener clave 4 devuelve NULL", !abb_obtener(abb, clave4));
    print_test("La cantidad de elementos es 3", abb_cantidad(abb) == 3);

    // Borrar con 1 hijo
    print_test("Pertenece clave 1, es true", abb_pertenece(abb, clave1));
    print_test("Borrar clave 1 devuelve valor 1", abb_borrar(abb, clave1) == valor1);
    print_test("Borrar clave 1 devuelve NULL", !abb_borrar(abb, clave1));
    print_test("Pertenece clave 1, es false", !abb_pertenece(abb, clave1));
    print_test("Obtener clave 1 devuelve NULL", !abb_obtener(abb, clave1));
    print_test("La cantidad de elementos es 2", abb_cantidad(abb) == 2);

    // Borrar con 0 hijos
    print_test("Pertenece clave 5, es true", abb_pertenece(abb, clave5));
    print_test("Borrar clave 5 devuelve valor 5", abb_borrar(abb, clave5) == valor5);
    print_test("Borrar clave 5 devuelve NULL", !abb_borrar(abb, clave5));
    print_test("Pertenece clave 5, es false", !abb_pertenece(abb, clave5));
    print_test("Obtener clave 5 devuelve NULL", !abb_obtener(abb, clave5));
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 1);

    // Borrar la raíz
    print_test("Pertenece clave 2, es true", abb_pertenece(abb, clave2));
    print_test("Borrar clave 2 devuelve valor 2", abb_borrar(abb, clave2) == valor2);
    print_test("Borrar clave 2 devuelve NULL", !abb_borrar(abb, clave2));
    print_test("Pertenece clave 2, es false", !abb_pertenece(abb, clave2));
    print_test("Obtener clave 2 devuelve NULL", !abb_obtener(abb, clave2));
    print_test("La cantidad de elementos es 0", abb_cantidad(abb) == 0);

    // Pruebo insertar luego de vaciar el abb
    print_test("Insertar clave 3", abb_guardar(abb, clave3, valor3));
    print_test("Pertenece clave 3, es true", abb_pertenece(abb, clave3));
    print_test("Borrar clave 3 devuelve valor 3", abb_borrar(abb, clave3) == valor3);

    abb_destruir(abb);
    printf("\n");
}

static void prueba_abb_clave_vacia() {
    printf("~~~ Prueba: ABB CLAVE VACIA ~~~ \n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = "";

    print_test("Insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("La cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
    printf("\n");
}

static void prueba_abb_valor_null() {
    printf("~~~ Prueba: ABB VALOR NULL ~~~ \n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = NULL;

    /* Inserta 1 valor y luego lo borra */
    print_test("Insertar clave vacia con valor NULL", abb_guardar(abb, clave, valor));
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Obtener clave vacia, es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("Pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
    print_test("La cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
    printf("\n");
}

size_t obtener_aleatorio(size_t limite) {
    size_t aleatorio = (size_t) rand();
    return aleatorio % limite;
}

static void prueba_abb_volumen(size_t largo, bool debug){
    printf("~~~ Prueba: ABB VOLUMEN ~~~ \n");
    abb_t* abb = abb_crear(strcmp, free);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);
    unsigned* valores[largo];

    /* Crea 'largo' parejas para guardar en el abb */
    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        sprintf(claves[i], "%08d", i);
        *valores[i] = i;
    }

    /* Utilizando el indice aleatorio vamos guardando elementos en el abb de forma desordenada */
    size_t cantidad_total = 0;
    while (cantidad_total < largo) {
        size_t indice = obtener_aleatorio(largo);

        if (!abb_pertenece(abb, claves[indice])) {
            ok = abb_guardar(abb, claves[indice], valores[indice]);
            if (!ok) break;
            cantidad_total++;
        }
    }

    if (debug) print_test("Almacenar muchos elementos", ok);
    if (debug) print_test("La cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    /* Verifica que devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        ok = abb_pertenece(abb, claves[i]);
        if (!ok) break;
        ok = abb_obtener(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Pertenece y obtener muchos elementos", ok);
    if (debug) print_test("La cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    /* Borra aleatoriamente. Verifica que borre correctamente y devuelva los valores correctos. */
    while (abb_cantidad(abb) > 0) {
        size_t i = obtener_aleatorio(largo);

        if (abb_pertenece(abb, claves[i])) {
            ok = abb_borrar(abb, claves[i]) == valores[i];
            if (!ok) break;
        }
    }

    if (debug) print_test("Borrar muchos elementos", ok);
    if (debug) print_test("La cantidad de elementos es 0", abb_cantidad(abb) == 0);

    /* La memoria pedida para los enteros no se libero, ya que al borrar todos los elementos del abb no se libera memoria */
    /* Destruye el abb y crea uno nuevo que sí libera la memoria dinamica de los enteros */
    abb_destruir(abb);
    abb = abb_crear(strcmp, free);

    /* Inserta 'largo' parejas en el abb */
    ok = true;
    for (size_t i = 0; i < largo; i++) {
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    free(claves);

    /* Destruye el abb (debería liberar los enteros) */
    abb_destruir(abb);
    printf("\n");
}

static void prueba_abb_iterar() {
    printf("~~~ Prueba: ABB ITERAR ~~~ \n");
    abb_t *abb = abb_crear(strcmp, NULL);

    char *clave1 = "A", *valor1 = "1";
    char *clave2 = "B", *valor2 = "2";
    char *clave3 = "C", *valor3 = "3";
    char *clave4 = "D", *valor4 = "4";
    char *clave5 = "E", *valor5 = "5";

    print_test("Insertar clave 3", abb_guardar(abb, clave3, valor3));
    print_test("Insertar clave 1", abb_guardar(abb, clave1, valor1));
    print_test("Insertar clave 4", abb_guardar(abb, clave4, valor4));
    print_test("Insertar clave 2", abb_guardar(abb, clave2, valor2));
    print_test("Insertar clave 5", abb_guardar(abb, clave5, valor5));
    
    abb_iter_t *iter = abb_iter_in_crear(abb);

    print_test("El iterador se creó correctamente", iter != NULL);
    print_test("El iterador no esta al final", !abb_iter_in_al_final(iter));

    /* Primer valor */
    print_test("Ver actual devuelve clave 1", strcmp(abb_iter_in_ver_actual(iter), clave1) == 0);
    print_test("Ver actual no es el mismo puntero que clave 1", abb_iter_in_ver_actual(iter) != clave1);
    print_test("Avanzamos el iterador", abb_iter_in_avanzar(iter));
    print_test("El iterador no esta al final", !abb_iter_in_al_final(iter));

    /* Segundo valor */
    print_test("Ver actual devuelve clave 2", strcmp(abb_iter_in_ver_actual(iter), clave2) == 0);
    print_test("Ver actual no es el mismo puntero que clave 2", abb_iter_in_ver_actual(iter) != clave2);
    print_test("Avanzamos el iterador", abb_iter_in_avanzar(iter));
    print_test("El iterador no esta al final", !abb_iter_in_al_final(iter));

    /* Tercer valor */
    print_test("Ver actual devuelve clave 3", strcmp(abb_iter_in_ver_actual(iter), clave3) == 0);
    print_test("Ver actual no es el mismo puntero que clave 3", abb_iter_in_ver_actual(iter) != clave3);
    print_test("Avanzamos el iterador", abb_iter_in_avanzar(iter));
    print_test("El iterador no esta al final", !abb_iter_in_al_final(iter));

    /* Cuarto valor */
    print_test("Ver actual devuelve clave 4", strcmp(abb_iter_in_ver_actual(iter), clave4) == 0);
    print_test("Ver actual no es el mismo puntero que clave 4", abb_iter_in_ver_actual(iter) != clave4);
    print_test("Avanzamos el iterador", abb_iter_in_avanzar(iter));
    print_test("El iterador no esta al final", !abb_iter_in_al_final(iter));

    /* Quinto valor */
    print_test("Ver actual devuelve clave 5", strcmp(abb_iter_in_ver_actual(iter), clave5) == 0);
    print_test("Ver actual no es el mismo puntero que clave 5", abb_iter_in_ver_actual(iter) != clave5);
    print_test("Avanzamos el iterador", abb_iter_in_avanzar(iter));
    
    print_test("Luego de recorrer todo el abb, el iterador esta al final", abb_iter_in_al_final(iter));
    print_test("Avanzar el iterador devuelve false", !abb_iter_in_avanzar(iter));
    print_test("Ver actual devuelve NULL", !abb_iter_in_ver_actual(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
    printf("\n");
}

static void prueba_abb_iterar_volumen(size_t largo) {
    printf("~~~ Prueba: ABB ITERAR VOLUMEN ~~~ \n");
    abb_t* abb = abb_crear(strcmp, free);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);
    unsigned* valores[largo];

    /* Crea 'largo' parejas para guardar en el abb */
    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        sprintf(claves[i], "%08d", i);
        *valores[i] = i;
    }

    /* Utilizando el indice aleatorio vamos guardando elementos en el abb de forma desordenada */
    size_t cantidad_total = 0;
    while (cantidad_total < largo) {
        size_t indice = obtener_aleatorio(largo);

        if (!abb_pertenece(abb, claves[indice])) {
            ok = abb_guardar(abb, claves[indice], valores[indice]);
            if (!ok) break;
            cantidad_total++;
        }
    }

    print_test("Almacenar muchos elementos", ok);
    print_test("La cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    abb_iter_t *iter = abb_iter_in_crear(abb);
    print_test("El iterador no esta al final", !abb_iter_in_al_final(iter));

    ok = true;
    unsigned i;
    const char *clave;
    bool in_order = true;
    const char *anterior = abb_iter_in_ver_actual(iter);
    abb_iter_in_avanzar(iter);
    
    for (i = 1; i < largo; i++) {
        if (abb_iter_in_al_final(iter) ) {
            ok = false;
            break;
        }
        clave = abb_iter_in_ver_actual(iter);
        if (clave == NULL) {
            ok = false;
            break;
        }
        // Verificamos que cada clave anterior sea menor a la actual
        if (strcmp(anterior, clave) > 0) { 
            in_order = false;
            break;
        }
        anterior = clave;
        abb_iter_in_avanzar(iter);
    }

    print_test("Iteración en volumen", ok);
    print_test("El iterador recorrió el abb de forma in order", in_order);
    print_test("El iterador recorrió todo el abb", i == largo);
    print_test("El iterador está al final", abb_iter_in_al_final(iter));

    free(claves);
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
    printf("\n");
}

bool sumar(const char* clave, void* dato, void* extra) {
    *(int*) extra += *(int*) dato;
    return true;
}

static void prueba_abb_iterador_externo() {
    printf("~~~ Prueba: ITERADOR EXTERNO (SUMAR SUS DATOS) ~~~ \n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "A";
    char *clave2 = "B";
    char *clave3 = "C";
    int valor1 = 1;
    int valor2 = 2;
    int valor3 = 3;

    abb_guardar(abb, clave3, &valor3);
    abb_guardar(abb, clave1, &valor1);
    abb_guardar(abb, clave2, &valor2);

    int suma = 0;
    abb_in_order(abb, sumar, &suma);
    print_test("La suma total de todos los datos es correcta", suma == 6);

    abb_destruir(abb);
}

/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/

void pruebas_abb_estudiante(){
    /* Ejecuta todas las pruebas unitarias. */
    prueba_crear_abb_vacio();
    prueba_iterar_abb_vacio();
    prueba_abb_insertar();
    prueba_abb_reemplazar();
    prueba_abb_reemplazar_con_destruir();
    prueba_abb_borrar_con_destruir(); 
    prueba_abb_borrar();
    prueba_abb_clave_vacia(); 
    prueba_abb_valor_null();
    prueba_abb_volumen(5000, true);
    prueba_abb_iterar();
    prueba_abb_iterar_volumen(5000);
    prueba_abb_iterador_externo();
}

void pruebas_volumen_catedra(size_t largo){
    prueba_abb_volumen(largo, false);
}
