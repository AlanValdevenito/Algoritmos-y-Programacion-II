#include "pila.h"
#include "testing.h"
#include <stdio.h>

/* Pruebas para una pila vacia */
static void prueba_pila_vacia(void) {
    printf("\nINICIO DE PRUEBAS CON PILA VACIA\n");

    /* Creamos la pila */
    pila_t *pila = pila_crear();

    printf("\nVERIFICAMOS QUE EL COMPORTAMIENTO DE UNA PILA VACIA SEA CORRECTO\n");
    /* Vemos si es correcto el comportamiento de una pila vacia */
    print_test("¿Esta vacia la pila?: ", pila_esta_vacia(pila));
    print_test("¿El tope de la pila es NULL?", pila_ver_tope(pila) == NULL);
    print_test("Intentamos desapilar una pila vacia: ", pila_desapilar(pila) == NULL);

    /* Destruimos la pila */
    pila_destruir(pila);
}

/* Pruebas para apilar y desapilar algunos elementos de una pila */
static void prueba_pila_algunos_elementos(void) {
    printf("\nINICIO DE PRUEBAS CON ALGUNOS ELEMENTOS\n");

    /* Creamos la pila */
    pila_t *pila = pila_crear();

    /* Definimos los enteros que usaremos */
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    int v4 = 4;
    int v5 = 5;
    int v6 = 6;
    int v7 = 7;
    int v8 = 8;
    int v9 = 9;
    int v10 = 10;

    printf("\nAPILAMOS ALGUNOS ELEMENTOS Y VEMOS QUE EL TOPE SEA CORRECTO PASO A PASO\n");
    /* Vemos si es correcto el comportamiento de una pila con elementos sin sobrepasar su capacidad inicial (10) */
    /* Verificamos que se apile correctamente, y que el tope corresponda al elemento apilado */
    print_test("Apilamos el entero 1: ", pila_apilar(pila, &v1));
    int* tope1 = pila_ver_tope(pila);
    print_test("Vemos el tope de la pila (1): ", *tope1 == v1);

    print_test("Apilamos el entero 2: ", pila_apilar(pila, &v2));
    int* tope2 = pila_ver_tope(pila);
    print_test("Vemos el tope de la pila (2): ", *tope2 == v2);

    print_test("Apilamos el entero 3: ", pila_apilar(pila, &v3));
    int* tope3 = pila_ver_tope(pila);
    print_test("Vemos el tope de la pila (3): ", *tope3 == v3);

    print_test("Apilamos el entero 4: ", pila_apilar(pila, &v4));
    int* tope4 = pila_ver_tope(pila);
    print_test("Vemos el tope de la pila (4): ", *tope4 == v4);

    print_test("Apilamos el entero 5: ", pila_apilar(pila, &v5));
    int* tope5 = pila_ver_tope(pila);
    print_test("Vemos el tope de la pila (5): ", *tope5 == v5);

    print_test("Apilamos el entero 6: ", pila_apilar(pila, &v6));
    int* tope6 = pila_ver_tope(pila);
    print_test("Vemos el tope de la pila (6): ", *tope6 == v6);

    print_test("Apilamos el entero 7: ", pila_apilar(pila, &v7));
    int* tope7 = pila_ver_tope(pila);
    print_test("Vemos el tope de la pila (7): ", *tope7 == v7);

    print_test("Apilamos el entero 8: ", pila_apilar(pila, &v8));
    int* tope8 = pila_ver_tope(pila);
    print_test("Vemos el tope de la pila (8): ", *tope8 == v8);

    print_test("Apilamos el entero 9: ", pila_apilar(pila, &v9));
    int* tope9 = pila_ver_tope(pila);
    print_test("Vemos el tope de la pila (9): ", *tope9 == v9);

    print_test("Apilamos el entero 10: ", pila_apilar(pila, &v10));
    int* tope10 = pila_ver_tope(pila);
    print_test("Vemos el tope de la pila (10): ", *tope10 == v10);

    printf("DESAPILAMOS TODOS LOS ELEMENTOS Y VEMOS QUE EL TOPE SEA CORRECTO PASO A PASO\n");
    /* Vemos si es correcto el comportamiento de una pila desapilando TODOS sus elementos (10) */
    int* desapilado10 = pila_desapilar(pila);
    print_test("Desapilamos el tope (10): ", *desapilado10 == v10);

    int* desapilado9 = pila_desapilar(pila);
    print_test("Desapilamos el tope (9): ", *desapilado9 == v9);

    int* desapilado8 = pila_desapilar(pila);
    print_test("Desapilamos el tope (8): ", *desapilado8 == v8);

    int* desapilado7 = pila_desapilar(pila);
    print_test("Desapilamos el tope (7): ", *desapilado7 == v7);

    int* desapilado6 = pila_desapilar(pila);
    print_test("Desapilamos el tope (6): ", *desapilado6 == v6);

    print_test("Desapilamos el tope (5): ", pila_desapilar(pila) == &v5);
    print_test("Desapilamos el tope (4): ", pila_desapilar(pila) == &v4);

    int* desapilado3 = pila_desapilar(pila);
    print_test("Desapilamos el tope (3): ", *desapilado3 == v3);

    int* desapilado2 = pila_desapilar(pila);
    print_test("Desapilamos el tope (2): ", *desapilado2 == v2);

    print_test("Desapilamos el tope (1): ", pila_desapilar(pila) == &v1);

    printf("VERIFICAMOS QUE UNA PILA VACIADA SE COMPORTE COMO UNA PILA VACIA\n");
    /* Vemos si es correcto el comportamiento de una pila vaciada */
    print_test("¿Esta vacia la pila?: ", pila_esta_vacia(pila));
    print_test("¿El tope de la pila es NULL?", pila_ver_tope(pila) == NULL);
    print_test("Intentamos desapilar una pila vacia: ", pila_desapilar(pila) == NULL);
    
    /* Destruimos la pila */
    pila_destruir(pila);
}

static void pruebas_pila_null(void){
    printf("\nINICIO DE PRUEBAS DEL ELEMENTO NULL\n");

    /* Creamos la pila */
    pila_t *pila = pila_crear();

    /* Definimos los enteros que usaremos */
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    int v4 = 4;
    int v5 = 5;

    printf("\nAPILAMOS ALGUNOS ELEMENTOS Y ENTRE ELLOS EL ELEMENTO NULL\n");
    /* Probamos que el apilamiento y desapilamiento del elemento NULL es válido. */
    print_test("Apilamos el entero 1: ", pila_apilar(pila, &v1));
    print_test("Vemos el tope de la pila (1): ", pila_ver_tope(pila) == &v1);
    print_test("Apilamos el elemento NULL: ", pila_apilar(pila, NULL));
    print_test("Vemos el tope de la pila (NULL): ", pila_ver_tope(pila) == NULL);
    print_test("Apilamos el entero 2: ", pila_apilar(pila, &v2));
    print_test("Vemos el tope de la pila (2): ", pila_ver_tope(pila) == &v2);
    print_test("Apilamos el entero 3: ", pila_apilar(pila, &v3));
    print_test("Vemos el tope de la pila (3): ", pila_ver_tope(pila) == &v3);
    print_test("Apilamos el elemento NULL: ", pila_apilar(pila, NULL));
    print_test("Vemos el tope de la pila (NULL): ", pila_ver_tope(pila) == NULL);
    print_test("Apilamos el entero 4: ", pila_apilar(pila, &v4));
    print_test("Vemos el tope de la pila (4): ", pila_ver_tope(pila) == &v4);
    print_test("Apilamos el entero 5: ", pila_apilar(pila, &v5));
    print_test("Vemos el tope de la pila (5): ", pila_ver_tope(pila) == &v5);

    printf("DESAPILAMOS TODOS LOS ELEMENTOS Y DESTRUIMOS LA PILA\n");
    /* Desapilamos todos los elementos */
    print_test("Desapilamos el tope (5): ", pila_desapilar(pila) == &v5);
    print_test("Desapilamos el tope (4): ", pila_desapilar(pila) == &v4);
    print_test("Desapilamos el tope (NULL): ", pila_desapilar(pila) == NULL);
    print_test("Desapilamos el tope (3): ", pila_desapilar(pila) == &v3);
    print_test("Desapilamos el tope (2): ", pila_desapilar(pila) == &v2);
    print_test("Desapilamos el tope (NULL): ", pila_desapilar(pila) == NULL);
    print_test("Desapilamos el tope (1): ", pila_desapilar(pila) == &v1);
    print_test("¿Esta vacia la pila?: ", pila_esta_vacia(pila));
    print_test("¿El tope de la pila es NULL?", pila_ver_tope(pila) == NULL);

    /* Destruimos la pila */
    pila_destruir(pila);
}

/* Pruebas de la pila al trabajar con un volumen grande de elementos */
static void pruebas_pila_volumen(void){
    printf("\nINICIO DE PRUEBAS DE VOLUMEN: 1000 ELEMENTOS\n");

    /* Creamos la pila */
    pila_t *pila = pila_crear();

    /* Definimos el arreglo de enteros donde guardaremos los elementos y los booleanos que usaremos */
    int arr[1000] = {0};
    bool ok_apilar = true;
    bool ok_tope = true;

    printf("\nAPILAMOS MUCHOS ELEMENTOS\n");
    /* Pruebo apilar 100 elementos */
    for(int i = 0; i < 1000; i++){
        arr[i] = i + 1;

        // Si algun elemento fallo en apilarse, ok_apilar sera false
        ok_apilar &= pila_apilar(pila, &arr[i]);

        // Si algun elemento no coincide con el tope de la pila, ok_tope sera false
        int* elemento = pila_ver_tope(pila);

        if(*elemento == arr[i]){
            ok_tope &= true;
        }

        else{
            ok_tope &= false;
        }
    }

    print_test("Se pudieron apilar todos los elementos", ok_apilar);
    print_test("El tope de la lista es corrrecto paso a paso", ok_tope);

    printf("DESAPILAMOS TODOS LOS ELEMENTOS Y DESTRUIMOS LA PILA\n");
    /* Pruebo desapilar todos los elementos */
    for(int i = 999; i > -1; i--){

        // Si algun elemento no coincide con el tope de la pila, ok_tope sera false
        int* elemento = pila_desapilar(pila);

        if(*elemento == arr[i]){
            ok_tope &= true;
        }

        else{
            ok_tope &= false;
        }
    }

    print_test("El tope de la lista es correcto paso a paso", ok_tope);
    print_test("¿Esta vacia la pila?", pila_esta_vacia(pila));
    print_test("¿El tope de la pila es NULL?", pila_ver_tope(pila) == NULL);

    /* Destruimos la pila */
    pila_destruir(pila);   
}

void pruebas_pila_estudiante() {
    prueba_pila_vacia();
    prueba_pila_algunos_elementos();
    pruebas_pila_null();
    pruebas_pila_volumen();
}

/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
