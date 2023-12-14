#include "cola.h"
#include "testing.h"
#include <stdio.h>
#include "pila.h"
#include <stdlib.h>

/* Pruebas para una cola vacia */
static void prueba_cola_vacia(void) {
    printf("\nINICIO DE PRUEBAS CON COLA VACIA\n");

    /* Creamos la cola */
    cola_t *cola = cola_crear();

    printf("\nVERIFICAMOS QUE EL COMPORTAMIENTO DE UNA COLA VACIA SEA CORRECTO\n");
    /* Vemos si es correcto el comportamiento de una cola vacia */
    print_test("¿Esta vacia la cola?: ", cola_esta_vacia(cola));
    print_test("¿El tope de la pila es NULL?", cola_ver_primero(cola) == NULL);
    print_test("Intentamos desencolar una cola vacia: ", cola_desencolar(cola) == NULL);

    /* Destruimos la cola */
    cola_destruir(cola, NULL);
}

/* Pruebas para encolar y desencolar algunos elementos, tambien para verificar el comportamiento de una cola vaciada */
static void prueba_cola_algunos_elementos(void) {
    printf("\nINICIO DE PRUEBAS CON ALGUNOS ELEMENTOS\n");

    /* Creamos la cola */
    cola_t *cola = cola_crear();

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

    printf("\nENCOLAMOS ALGUNOS ELEMENTOS Y VEMOS QUE EL PRIMERO SEA CORRECTO PASO A PASO\n");
    /* Vemos si es correcto el comportamiento de una cola con elementos de tipo entero */
    /* Verificamos que se encole correctamente, y que el primero corresponda al primer elemento encolado */
    print_test("Encolamos el entero 1: ", cola_encolar(cola, &v1));
    int* primero1 = cola_ver_primero(cola);
    print_test("Vemos el primero de la cola (1): ", *primero1 == v1);

    print_test("Encolamos el entero 2: ", cola_encolar(cola, &v2));
    print_test("Vemos el primero de la cola (1): ", *primero1 == v1);

    print_test("Encolamos el entero 3: ", cola_encolar(cola, &v3));
    print_test("Vemos el primero de la cola (1): ", *primero1 == v1);

    print_test("Encolamos el entero 4: ", cola_encolar(cola, &v4));
    print_test("Vemos el primero de la cola (1): ", *primero1 == v1);

    print_test("Encolamos el entero 5: ", cola_encolar(cola, &v5));
    print_test("Vemos el primero de la cola (1): ", *primero1 == v1);

    print_test("Encolamos el entero 6: ", cola_encolar(cola, &v6));
    print_test("Vemos el primero de la cola (1): ", *primero1 == v1);

    print_test("Encolamos el entero 7: ", cola_encolar(cola, &v7));
    print_test("Vemos el primero de la cola (1): ", *primero1 == v1);

    print_test("Encolamos el entero 8: ", cola_encolar(cola, &v8));
    print_test("Vemos el primero de la cola (1): ", *primero1 == v1);

    print_test("Encolamos el entero 9: ", cola_encolar(cola, &v9));
    print_test("Vemos el primero de la cola (1): ", *primero1 == v1);

    print_test("Encolamos el entero 10: ", cola_encolar(cola, &v10));
    print_test("Vemos el primero de la cola (1): ", *primero1 == v1);

    printf("DESENCOLAMOS TODOS LOS ELEMENTOS Y VEMOS QUE EL PRIMERO SEA CORRECTO PASO A PASO\n");
    /* Vemos si es correcto el comportamiento de una cola desencolando TODOS sus elementos (10) */
    print_test("Vemos el primero de la cola (1): ", *primero1 == v1);
    int* desencolado1 = cola_desencolar(cola);
    print_test("Desencolamos el primero (1): ", *desencolado1 == v1);

    int* primero2 = cola_ver_primero(cola);
    print_test("Vemos el primero de la cola (2): ", *primero2 == v2);
    int* desencolado2 = cola_desencolar(cola);
    print_test("Desencolamos el primero (2): ", *desencolado2 == v2);

    int* primero3 = cola_ver_primero(cola);
    print_test("Vemos el primero de la cola (3): ", *primero3 == v3);
    int* desencolado3 = cola_desencolar(cola);
    print_test("Desencolamos el primero (3): ", *desencolado3 == v3);

    int* primero4 = cola_ver_primero(cola);
    print_test("Vemos el primero de la cola (4): ", *primero4 == v4);
    int* desencolado4 = cola_desencolar(cola);
    print_test("Desencolamos el primero (4): ", *desencolado4 == v4);

    int* primero5 = cola_ver_primero(cola);
    print_test("Vemos el primero de la cola (5): ", *primero5 == v5);
    int* desencolado5 = cola_desencolar(cola);
    print_test("Desencolamos el primero (5): ", *desencolado5 == v5);

    int* primero6 = cola_ver_primero(cola);
    print_test("Vemos el primero de la cola (6): ", *primero6 == v6);
    int* desencolado6 = cola_desencolar(cola);
    print_test("Desencolamos el primero (6): ", *desencolado6 == v6);

    int* primero7 = cola_ver_primero(cola);
    print_test("Vemos el primero de la cola (7): ", *primero7 == v7);
    int* desencolado7 = cola_desencolar(cola);
    print_test("Desencolamos el primero (7): ", *desencolado7 == v7);

    int* primero8 = cola_ver_primero(cola);
    print_test("Vemos el primero de la cola (8): ", *primero8 == v8);
    int* desencolado8 = cola_desencolar(cola);
    print_test("Desencolamos el primero (8): ", *desencolado8 == v8);

    int* primero9 = cola_ver_primero(cola);
    print_test("Vemos el primero de la cola (9): ", *primero9 == v9);
    int* desencolado9 = cola_desencolar(cola);
    print_test("Desencolamos el primero (9): ", *desencolado9 == v9);

    int* primero10 = cola_ver_primero(cola);
    print_test("Vemos el primero de la cola (10): ", *primero10 == v10);
    int* desencolado10 = cola_desencolar(cola);
    print_test("Desencolamos el primero (10): ", *desencolado10 == v10);

    printf("VERIFICAMOS QUE UNA COLA VACIADA SE COMPORTE COMO UNA COLA VACIA\n");
    /* Vemos si es correcto el comportamiento de una cola vacia */
    print_test("¿Esta vacia la cola?: ", cola_esta_vacia(cola));
    print_test("¿El tope de la pila es NULL?", cola_ver_primero(cola) == NULL);
    print_test("Intentamos desencolar una cola vacia: ", cola_desencolar(cola) == NULL);
    
    /* Destruimos la cola */
    /* El segundo parametro sera NULL ya que usamos elementos de tipo entero que 'viven' en la memoria estatica */
    cola_destruir(cola, NULL);
}

/* Pruebas para encolar y desencolar el elemento null */
static void pruebas_cola_null(void){
    printf("\nINICIO DE PRUEBAS DEL ELEMENTO NULL\n");

    /* Creamos la cola */
    cola_t *cola = cola_crear();

    /* Definimos los enteros que usaremos */
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    int v4 = 4;
    int v5 = 5;

    printf("\nENCOLAMOS ALGUNOS ELEMENTOS Y ENTRE ELLOS EL ELEMENTO NULL\n");
    /* Probamos que encolar y desencolar el elemento NULL es válido. */
    print_test("Encolamos el entero 1: ", cola_encolar(cola, &v1));
    int* primero1 = cola_ver_primero(cola);
    print_test("Vemos el primero de la cola (1): ", *primero1 == v1);

    print_test("Encolamos el entero 2: ", cola_encolar(cola, &v2));
    print_test("Vemos el primero de la cola (1): ", *primero1 == v1);

    print_test("Encolamos el elemento NULL: ", cola_encolar(cola, NULL));
    print_test("Vemos el primero de la cola (1): ", *primero1 == v1);

    print_test("Encolamos el entero 3: ", cola_encolar(cola, &v3));
    print_test("Vemos el primero de la cola (1): ", *primero1 == v1);

    print_test("Encolamos el entero 4: ", cola_encolar(cola, &v4));
    print_test("Vemos el primero de la cola (1): ", *primero1 == v1);

    print_test("Encolamos el elemento NULL: ", cola_encolar(cola, NULL));
    print_test("Vemos el primero de la cola (1): ", *primero1 == v1);

    print_test("Encolamos el entero 5: ", cola_encolar(cola, &v5));
    print_test("Vemos el primero de la cola (1): ", *primero1 == v1);

    printf("DESENCOLAMOS TODOS LOS ELEMENTOS Y DESTRUIMOS LA COLA\n");
    /* Desencolamos todos los elementos */
    print_test("Vemos el primero de la cola (1): ", *primero1 == v1);
    int* desencolado1 = cola_desencolar(cola);
    print_test("Desencolamos el primero (1): ", *desencolado1 == v1);

    int* primero2 = cola_ver_primero(cola);
    print_test("Vemos el primero de la cola (2): ", *primero2 == v2);
    int* desencolado2 = cola_desencolar(cola);
    print_test("Desencolamos el primero (2): ", *desencolado2 == v2);

    print_test("Vemos el primero de la cola (NULL): ", cola_ver_primero(cola) == NULL);
    print_test("Desencolamos el primero (NULL): ", cola_desencolar(cola) == NULL);

    int* primero3 = cola_ver_primero(cola);
    print_test("Vemos el primero de la cola (3): ", *primero3 == v3);
    int* desencolado3 = cola_desencolar(cola);
    print_test("Desencolamos el primero (3): ", *desencolado3 == v3);

    int* primero4 = cola_ver_primero(cola);
    print_test("Vemos el primero de la cola (4): ", *primero4 == v4);
    int* desencolado4 = cola_desencolar(cola);
    print_test("Desencolamos el primero (4): ", *desencolado4 == v4);

    print_test("Vemos el primero de la cola (NULL): ", cola_ver_primero(cola) == NULL);
    print_test("Desencolamos el primero (NULL): ", cola_desencolar(cola) == NULL);

    int* primero5 = cola_ver_primero(cola);
    print_test("Vemos el primero de la cola (5): ", *primero5 == v5);
    int* desencolado5 = cola_desencolar(cola);
    print_test("Desencolamos el primero (5): ", *desencolado5 == v5);
    
    /* Destruimos la cola */
    /* El segundo parametro sera NULL ya que usamos elementos de tipo entero que 'viven' en la memoria estatica */
    cola_destruir(cola, NULL);
}

/* Pruebas de la cola al trabajar con un volumen grande de elementos */
static void pruebas_cola_volumen(void){
    printf("\nINICIO DE PRUEBAS DE VOLUMEN: 1000 ELEMENTOS\n");

    /* Creamos la cola */
    cola_t *cola = cola_crear();

    /* Definimos el arreglo de enteros donde guardaremos los elementos y los booleanos que usaremos */
    int arr[1000] = {0};
    bool ok_apilar = true;
    bool ok_primero = true;

    printf("\nENCOLAMOS MUCHOS ELEMENTOS\n");
    /* Pruebo encolar 1000 elementos */
    for(int i = 0; i < 1000; i++){
        arr[i] = i + 1;

        // Si algun elemento fallo en apilarse, ok_apilar sera false
        ok_apilar &= cola_encolar(cola, &arr[i]);

        // Verificamos que se encole correctamente, y que el primero corresponda al primer elemento encolado 
        int* elemento = cola_ver_primero(cola);
        ok_primero &= *elemento == arr[0];
    }

    print_test("Se pudieron encolar todos los elementos", ok_apilar);
    print_test("El primer elemento de la cola es corrrecto paso a paso", ok_primero);

    printf("DESENCOLAMOS TODOS LOS ELEMENTOS Y DESTRUIMOS LA COLA\n");
    /* Pruebo desencolar todos los elementos */
    for(int i = 0; i < 1000; i++){

        // Verificamos que el primer elemento de la cola sea el correcto paso a paso
        int* elemento = cola_desencolar(cola);
        ok_primero &= *elemento == arr[i];
    }

    print_test("El primer elemento de la cola es correcto paso a paso", ok_primero);
    print_test("¿Esta vacia la cola?", cola_esta_vacia(cola));
    print_test("¿El primero de la cola es NULL?", cola_ver_primero(cola) == NULL);

    /* Destruimos la cola */
    cola_destruir(cola, NULL);  
}

/* Definimos el wrapper */
void pila_destruir_wrapper(void* elem){
    pila_destruir(elem);
}

/* Pruebas de destruccion: con pila_destruir() */
static void pruebas_cola_destruccion_1(void){
    printf("\nINICIO DE PRUEBAS DE DESTRUCCION 1: PILA_DESTRUIR\n");

    /* Creamos la cola */
    cola_t *cola = cola_crear();

    /* Definimos las estructuras que usaremos */
    pila_t *pila1 = pila_crear();
    pila_t *pila2 = pila_crear();
    pila_t *pila3 = pila_crear();

    printf("\nENCOLAMOS LAS ESTRUCTURAS Y VEMOS QUE EL PRIMERO SEA CORRECTO PASO A PASO\n");
    /* Vemos si es correcto el comportamiento de una cola con pilas */
    /* Verificamos que se encole correctamente, y que el primero corresponda al primer elemento encolado */
    print_test("Encolamos la pila 1: ", cola_encolar(cola, pila1));
    print_test("Vemos el primero de la cola (pila 1): ", cola_ver_primero(cola) == pila1);

    print_test("Encolamos la pila 2: ", cola_encolar(cola, pila2));
    print_test("Vemos el primero de la cola (pila 1): ", cola_ver_primero(cola) == pila1);

    print_test("Encolamos la pila 3: ", cola_encolar(cola, pila3));
    print_test("Vemos el primero de la cola (pila 1): ", cola_ver_primero(cola) == pila1);

    /* Destruimos la cola */
    /* El segundo parametro sera pila_destruir */
    cola_destruir(cola, pila_destruir_wrapper);
}

/* Pruebas de destruccion: con free() */
static void pruebas_cola_destruccion_2(void){
    printf("\nINICIO DE PRUEBAS DE DESTRUCCION 2: FREE\n");

    /* Creamos la cola */
    cola_t *cola = cola_crear();

    /* Definimos los punteros a memoria dinamica de enteros que usaremos */
    int* v1 = malloc(sizeof(int));
    *v1 = 1;
    int* v2 = malloc(sizeof(int));
    *v2 = 1;
    int* v3 = malloc(sizeof(int));
    *v3 = 1;

    printf("\nENCOLAMOS LOS ENTEROS Y VEMOS QUE EL PRIMERO SEA CORRECTO PASO A PASO\n");
    /* Vemos si es correcto el comportamiento de una cola con elementos de tipo entero */
    /* Verificamos que se encole correctamente, y que el primero corresponda al primer elemento encolado */
    print_test("Encolamos el entero 1: ", cola_encolar(cola, *&v1));
    int* primero1 = cola_ver_primero(cola);
    print_test("Vemos el primero de la cola (1): ", *primero1 == *v1);

    print_test("Encolamos el entero 2: ", cola_encolar(cola, *&v2));
    print_test("Vemos el primero de la cola (1): ", *primero1 == *v1);

    print_test("Encolamos el entero 3: ", cola_encolar(cola, *&v3));
    print_test("Vemos el primero de la cola (1): ", *primero1 == *v1);

    /* Destruimos la cola */
    /* El segundo parametro sera free */
    cola_destruir(cola, free);
}

void pruebas_cola_estudiante() {
    prueba_cola_vacia();
    prueba_cola_algunos_elementos();
    pruebas_cola_null();
    pruebas_cola_volumen();
    pruebas_cola_destruccion_1();
    pruebas_cola_destruccion_2();
}

/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_cola_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
