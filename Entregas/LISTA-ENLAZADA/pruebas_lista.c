#include "lista.h"
#include "testing.h"
#include "pila.h"
#include <stdio.h>
#include <stdlib.h>

/* Pruebas para una lista vacia */
static void pruebas_lista_vacia(void) {
    printf("\nINICIO DE PRUEBAS CON LISTA VACIA\n");
	lista_t *lista = lista_crear();

    printf("\nVERIFICAMOS EL COMPORTAMIENTO DE UNA LISTA VACIA\n");
    print_test("¿Esta vacia la lista?: ", lista_esta_vacia(lista));
    print_test("¿El primero de la lista es NULL?", lista_ver_primero(lista) == NULL);
	print_test("¿El ultimo de la lista es NULL?", lista_ver_ultimo(lista) == NULL);
    print_test("Intentamos borrar el primer elemento de una lista vacia: ", lista_borrar_primero(lista) == NULL);
	print_test("¿El largo de la lista es cero?: ", lista_largo(lista) == 0);
    lista_destruir(lista, NULL);
}

/* Pruebas para insertar algunos elementos, tambien para verificar el comportamiento de una lista vaciada */
static void pruebas_lista_algunos_elementos(void) {
    printf("\nINICIO DE PRUEBAS CON ALGUNOS ELEMENTOS\n");
    lista_t *lista = lista_crear();

	/* Definimos los enteros que usaremos */
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    int v4 = 4;
    int v5 = 5;
	int v6 = 6;

    printf("\nINSERTAMOS ALGUNOS Y VERIFICAMOS PASO A PASO QUE SEA CORRECTO EL COMPORTAMIENTO\n");
    print_test("Insertamos como PRIMERO el 1: ", lista_insertar_primero(lista, &v1));
	print_test("Vemos el primer elemento de la lista (1): ", lista_ver_primero(lista) == &v1);
	print_test("¿El largo es correcto? (1): ", lista_largo(lista) == 1);
	
	print_test("Insertamos como ULTIMO el 2: ", lista_insertar_ultimo(lista, &v2));
	print_test("Vemos el ultimo elemento de la lista (2): ", lista_ver_ultimo(lista) == &v2);
	print_test("¿El largo es correcto? (2): ", lista_largo(lista) == 2);

	print_test("Insertamos como PRIMERO el 3: ", lista_insertar_primero(lista, &v3));
	print_test("Vemos el primer elemento de la lista (3): ", lista_ver_primero(lista) == &v3);
	print_test("¿El largo es correcto? (3): ", lista_largo(lista) == 3);

	print_test("Insertamos como ULTIMO el 4: ", lista_insertar_ultimo(lista, &v4));
	print_test("Vemos el ultimo elemento de la lista (4): ", lista_ver_ultimo(lista) == &v4);
	print_test("¿El largo es correcto? (4): ", lista_largo(lista) == 4);

	print_test("Insertamos como PRIMERO el 5: ", lista_insertar_primero(lista, &v5));
	print_test("Vemos el primer elemento de la lista (5): ", lista_ver_primero(lista) == &v5);
	print_test("¿El largo es correcto? (5): ", lista_largo(lista) == 5);

	print_test("Insertamos como ULTIMO el 6: ", lista_insertar_ultimo(lista, &v6));
	print_test("Vemos el ultimo elemento de la lista (6): ", lista_ver_ultimo(lista) == &v6);
	print_test("¿El largo es correcto? (6): ", lista_largo(lista) == 6);

	// RESULTADO = [5, 3, 1, 2, 4, 6]

    printf("BORRAMOS TODOS LOS ELEMENTOS Y VEMOS QUE EL PRIMERO SEA CORRECTO PASO A PASO\n");
	print_test("Vemos el primer elemento de la lista (5): ", lista_ver_primero(lista) == &v5);
    print_test("Borramos el PRIMER elemento (5): ", lista_borrar_primero(lista));

	print_test("Vemos el primer elemento de la lista (3): ", lista_ver_primero(lista) == &v3);
    print_test("Borramos el PRIMER elemento (3): ", lista_borrar_primero(lista));

	print_test("Vemos el primer elemento de la lista (1): ", lista_ver_primero(lista) == &v1);
    print_test("Borramos el PRIMER elemento (1): ", lista_borrar_primero(lista));

	print_test("Vemos el primer elemento de la lista (2): ", lista_ver_primero(lista) == &v2);
    print_test("Borramos el PRIMER elemento (2): ", lista_borrar_primero(lista));

	print_test("Vemos el primer elemento de la lista (4): ", lista_ver_primero(lista) == &v4);
    print_test("Borramos el PRIMER elemento (4): ", lista_borrar_primero(lista));

	print_test("Vemos el primer elemento de la lista (6): ", lista_ver_primero(lista) == &v6);
    print_test("Borramos el PRIMER elemento (6): ", lista_borrar_primero(lista));

    printf("VERIFICAMOS QUE UNA COLA VACIADA SE COMPORTE COMO UNA COLA VACIA\n");
    print_test("¿Esta vacia la lista?: ", lista_esta_vacia(lista));
    print_test("¿El primero de la lista es NULL?", lista_ver_primero(lista) == NULL);
	print_test("¿El ultimo de la lista es NULL?", lista_ver_ultimo(lista) == NULL);
    print_test("Intentamos borrar el primer elemento de una lista vacia: ", lista_borrar_primero(lista) == NULL);
	print_test("¿El largo de la lista es cero?: ", lista_largo(lista) == 0);
    lista_destruir(lista, NULL);
}

/* Pruebas para insertar y borrar el elemento NULL */
static void pruebas_lista_null(void){
    printf("\nINICIO DE PRUEBAS CON EL ELEMENTO NULL\n\n");
    lista_t *lista = lista_crear();

    /* Definimos las variables que usaremos */
    void* valor = NULL;
    print_test("Insertamos NULL como primero: ", lista_insertar_primero(lista, &valor));
    print_test("Vemos el primer elemento de la lista (NULL): ", lista_ver_primero(lista) == &valor);
    print_test("Vemos que después de insertar NULL la lista no está vacía: ", !lista_esta_vacia(lista));
    print_test("¿El largo es correcto? (1): ", lista_largo(lista) == 1);

    print_test("Insertamos NULL pero esta vez como último: ", lista_insertar_ultimo(lista, &valor));
    print_test("Vemos el último elemento de la lista: ", lista_ver_ultimo(lista) == &valor);
    print_test("¿El largo es correcto? (2): ", lista_largo(lista) == 2);

    print_test("Volvemos a insertar NULL como primero: ", lista_insertar_primero(lista, &valor));
    print_test("Vemos el primer elemento de la lista (NULL): ", lista_ver_primero(lista) == &valor);
    print_test("¿El largo es correcto? (3): ", lista_largo(lista) == 3);

    print_test("Borramos el primer elemento de la lista: ", lista_borrar_primero(lista) == &valor);
    print_test("Vemos el primer elemento de la lista: ", lista_ver_primero(lista) == &valor);
    print_test("¿El largo es correcto? (2): ", lista_largo(lista) == 2);

    print_test("Borramos el primer elemento de la lista: ", lista_borrar_primero(lista) == &valor);
    print_test("Vemos el primer elemento de la lista: ", lista_ver_primero(lista) == &valor);
    print_test("¿El largo es correcto? (1): ", lista_largo(lista) == 1);

    print_test("Borramos el primer elemento de la lista: ", lista_borrar_primero(lista) == &valor);

    printf("VERIFICAMOS QUE UNA COLA VACIADA SE COMPORTE COMO UNA COLA VACIA\n");
    print_test("¿Esta vacia la lista?: ", lista_esta_vacia(lista));
    print_test("¿El primero de la lista es NULL?", lista_ver_primero(lista) == NULL);
    print_test("¿El ultimo de la lista es NULL?", lista_ver_ultimo(lista) == NULL);
    print_test("Intentamos borrar el primer elemento de una lista vacia: ", lista_borrar_primero(lista) == NULL);
    print_test("¿El largo de la lista es cero?: ", lista_largo(lista) == 0);
    
    lista_destruir(lista, NULL);
}

/* Pruebas de volumen */
static void pruebas_lista_volumen(void){
    printf("\nINICIO DE PRUEBAS DE VOLUMEN: 1000 ELEMENTOS\n");
    lista_t *lista = lista_crear();

    /* Definimos el arreglo de enteros donde guardaremos los elementos y los booleanos que usaremos */
    int arr[1000] = {0};
    bool ok_insertar = true;
    bool ok_primero = true;

    printf("\nINSERTAMOS MUCHOS ELEMENTOS COMO PRIMERO\n");
    for(int i = 0; i < 1000; i++){
        arr[i] = i + 1;

        ok_insertar &= lista_insertar_primero(lista, &arr[i]);
        int* elemento = lista_ver_primero(lista);
        ok_primero &= *elemento == arr[i];
    }

    print_test("¿Se pudieron insertar todos los elementos correctamente?", ok_insertar);
    print_test("¿El primer elemento de la lista es corrrecto paso a paso?", ok_primero);

    printf("BORRAMOS TODOS LOS ELEMENTOS Y COMPROBAMOS QUE EL PRIMERO SEA CORRECTO PASO A PASO\n");
    for(int i = 999; i > -1; i--){

        // Verificamos que el primer elemento de la lista sea el correcto paso a paso
        int* elemento = lista_borrar_primero(lista);
        ok_primero &= *elemento == arr[i];
    }

    print_test("¿El primer elemento de la cola es correcto paso a paso?", ok_primero);

    printf("VERIFICAMOS QUE UNA COLA VACIADA SE COMPORTE COMO UNA COLA VACIA\n");
    print_test("¿Esta vacia la lista?: ", lista_esta_vacia(lista));
    print_test("¿El primero de la lista es NULL?", lista_ver_primero(lista) == NULL);
	print_test("¿El ultimo de la lista es NULL?", lista_ver_ultimo(lista) == NULL);
    print_test("Intentamos borrar el primer elemento de una lista vacia: ", lista_borrar_primero(lista) == NULL);
	print_test("¿El largo de la lista es cero?: ", lista_largo(lista) == 0);
    lista_destruir(lista, NULL);
}

/* Definimos el wrapper */
void pila_destruir_wrapper(void* elem){
    pila_destruir(elem);
}

/* Pruebas de destruccion: con pila_destruir() */
static void pruebas_lista_destruccion_1(void){
    printf("\nINICIO DE PRUEBAS DESTRUIR CON pila_destruir()\n\n");
    printf("DESTRUCCION DE UNA LISTA VACIA CON LA PRIMITIVA pila_destruir()\n");

    /* Definimos las variables a utilizar */
    lista_t *lista = lista_crear();
    pila_t *pila_1 = pila_crear();
    pila_t *pila_2 = pila_crear();
    pila_t *pila_3 = pila_crear();

    print_test("¿La lista se creó correctamente? ", lista != NULL);
    print_test("¿La lista está vacía? ", lista_esta_vacia(lista));
    printf("Destruimos la lista vacía con la función pila_destruir()\n");
    lista_destruir(lista, pila_destruir_wrapper);


    printf("DESTRUCCION DE UNA LISTA CON LA PRIMITIVA pila_destruir()\n");

    /* Volvemos a crear la lista */
    lista_t *lista_2 = lista_crear();

    print_test("Insertamos la primera pila: ", lista_insertar_primero(lista_2, pila_1));
    print_test("La lista ya no está vacía: ", !lista_esta_vacia(lista_2));
    print_test("Insertamos la segunda pila: ", lista_insertar_primero(lista_2, pila_2));
    print_test("Insertamos la tercera pila: ", lista_insertar_primero(lista_2, pila_3));
    printf("Destruimos la lista vacía con la función pila_destruir()\n");
    lista_destruir(lista_2, pila_destruir_wrapper);
}

/* Pruebas de destruccion: con NULL */
static void pruebas_lista_destruccion_2(void){
    printf("\nINICIO DE PRUEBAS DESTRUIR CON NULL\n\n");
    printf("DESTRUCCION DE UNA LISTA VACIA CON NULL\n");

    /* Definimos las variables a utilizar */
    lista_t *lista = lista_crear();
    int v1 = 1, v2 = 2, v3 = 3;

    print_test("¿La lista se creó correctamente? ", lista != NULL);
    print_test("¿La lista está vacía? ", lista_esta_vacia(lista));
    printf("Destruimos la lista vacía pasándole NULL como función\n");
    lista_destruir(lista, NULL);


    printf("DESTRUCCION DE UNA LISTA DE ENTEROS CON NULL\n");

    lista_t *lista_2 = lista_crear();
    
    print_test("Insertamos el primer entero: ", lista_insertar_primero(lista_2, &v1));
    print_test("La lista ya no está vacía: ", !lista_esta_vacia(lista_2));
    print_test("Insertamos el segundo entero: ", lista_insertar_primero(lista_2, &v2));
    print_test("Insertamos el tercer entero: ", lista_insertar_primero(lista_2, &v3));
    printf("Destruimos la lista de enteros pasándole NULL como función\n");
    lista_destruir(lista_2, NULL);
}

/* Funcion para ver el medio de la lista */
void *ver_medio(lista_t *lista) {
    lista_iter_t *iter = lista_iter_crear(lista);
    size_t iterador = 1;

    while (iterador < (lista_largo(lista) / 2)) {
        lista_iter_avanzar(iter);
        iterador++;
    }
    
    void *medio = lista_iter_ver_actual(iter);
    lista_iter_destruir(iter);
    return medio;
}

/* Pruebas para insertar con el iterador externo */
static void pruebas_externo_insertar(void){
    printf("\nINICIO DE PRUEBAS DEL ITERADOR EXTERNO: INSERTAR PRINCIPIO, MEDIO Y FINAL\n\n");
    lista_t *lista = lista_crear();
    int dato = 0;

    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < 10; i++) {
        lista_insertar_ultimo(lista, (void*) &arr[i]);
    }

    size_t largo_final = lista_largo(lista) + 3;

    printf("PROBAMOS INSERTAR EN EL MEDIO DE LA LISTA\n");
    lista_iter_t *iter = lista_iter_crear(lista);
    size_t iterador = 1;

    while (!lista_iter_al_final(iter)) {

        // Inserta en el medio
        if (iterador == (lista_largo(lista) / 2)) {
            lista_iter_insertar(iter, &dato);
            iterador++;
        }

        lista_iter_avanzar(iter);
        iterador++;
    }

    lista_iter_destruir(iter);
    print_test("¿Se inserto corretamente en el medio?: ", ver_medio(lista) == &dato);

    printf("PROBAMOS INSERTAR AL INICIO Y AL FINAL DE LA LISTA\n");
    lista_iter_t *iter_2 = lista_iter_crear(lista);
    int iterador_2 = 1;

    while (!lista_iter_al_final(iter_2)) {

        // Inserta al principio
        if (iterador_2 == 1) {
            lista_iter_insertar(iter_2, &dato);
        }

        lista_iter_avanzar(iter_2);
        iterador_2++;
    }

    // Inserta al final
    lista_iter_insertar(iter_2, &dato);
    lista_iter_destruir(iter_2);
    print_test("¿Se inserto corretamente al principio?: ", lista_ver_primero(lista) == &dato);
    print_test("¿Se inserto corretamente al final?: ", lista_ver_ultimo(lista) == &dato);

    print_test("¿El largo final es correcto?: ", lista_largo(lista) == largo_final);
    lista_destruir(lista, NULL);
}

/* Pruebas para insertar una lista vacia con el iterador externo */
static void pruebas_externo_insertar_2(void){
    printf("\nINICIO DE PRUEBAS DEL ITERADOR EXTERNO 2: INSERTAR UNA LISTA VACIA\n\n");
    lista_t *lista = lista_crear();
    lista_iter_t *iter = lista_iter_crear(lista);
    int v1 = 1, v2 = 2, v3 = 3;

    printf("INSERTAMOS ELEMENTOS, PASO A PASO COMPROBAMOS QUE EL PRIMERO Y EL ULTIMO.\n");
    lista_iter_insertar(iter, &v1);
    lista_iter_avanzar(iter);
    print_test("¿Es correcto el primer elemento? (1): ", lista_ver_primero(lista) == &v1);
    print_test("¿Es correcto el ultimo elemento? (1): ", lista_ver_ultimo(lista) == &v1);
    lista_iter_insertar(iter, &v2);
    lista_iter_avanzar(iter);
    print_test("¿Es correcto el primer elemento? (1): ", lista_ver_primero(lista) == &v1);
    print_test("¿Es correcto el ultimo elemento? (2): ", lista_ver_ultimo(lista) == &v2);
    lista_iter_insertar(iter, &v3);
    lista_iter_avanzar(iter);
    print_test("¿Es correcto el primer elemento? (1): ", lista_ver_primero(lista) == &v1);
    print_test("¿Es correcto el ultimo elemento? (3): ", lista_ver_ultimo(lista) == &v3);
    lista_iter_destruir(iter);

    printf("BORRAMOS TODOS LOS ELEMENTOS, PASO A PASO COMPROBAMOS QUE EL PRIMERO Y EL ULTIMO.\n");
    lista_iter_t *iter2 = lista_iter_crear(lista);
    lista_iter_borrar(iter2);
    print_test("¿Es correcto el primer elemento? (2): ", lista_ver_primero(lista) == &v2);
    print_test("¿Es correcto el ultimo elemento? (3): ", lista_ver_ultimo(lista) == &v3);
    lista_iter_borrar(iter2);
    print_test("¿Es correcto el primer elemento? (3): ", lista_ver_primero(lista) == &v3);
    print_test("¿Es correcto el ultimo elemento? (3): ", lista_ver_ultimo(lista) == &v3);
    lista_iter_borrar(iter2);
    print_test("¿La lista esta vacia?: ", lista_iter_ver_actual(iter2) == NULL);
    
    lista_iter_destruir(iter2);
    lista_destruir(lista, NULL);
}

/* Pruebas para borrar con el iterador externo */
static void pruebas_externo_remover(void){
    printf("\nINICIO DE PRUEBAS DEL ITERADOR EXTERNO: BORRAR PRINCIPIO, MEDIO Y FINAL\n\n");
    lista_t *lista = lista_crear();

    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < 10; i++) {
        lista_insertar_ultimo(lista, (void*) &arr[i]);
    }

    size_t largo_final = lista_largo(lista) - 3;

    printf("PROBAMOS BORRAR EN EL MEDIO DE LA LISTA\n");
    lista_iter_t *iter = lista_iter_crear(lista);
    size_t iterador = 1;

    while (!lista_iter_al_final(iter)) {

        // Borra en el medio
        if (iterador == (lista_largo(lista) / 2)) {
            lista_iter_borrar(iter);
            iterador++;
        }

        lista_iter_avanzar(iter);
        iterador++;
    }

    lista_iter_destruir(iter);
    print_test("¿Se borro correctamente en el medio?: ", ver_medio(lista) == &arr[3]);

    printf("PROBAMOS BORRAR AL INICIO Y AL FINAL DE LA LISTA\n");
    lista_iter_t *iter_2 = lista_iter_crear(lista);
    size_t iterador_2 = 1;

    while (!lista_iter_al_final(iter_2)) {

        // Borra al principio
        if (iterador_2 == 1) {
            lista_iter_borrar(iter_2);
        }

        // Borra el ultimo elemento
        if (iterador_2 == lista_largo(lista)) {
            lista_iter_borrar(iter_2);
            iterador_2++;
        }

        lista_iter_avanzar(iter_2);
        iterador_2++;
    }

    lista_iter_destruir(iter_2);
    print_test("¿Se borro correctamente al principio?: ", lista_ver_primero(lista) == &arr[1]);
    print_test("¿Se borro correctamente al final?: ", lista_ver_ultimo(lista) == &arr[8]);

    print_test("¿El largo final es correcto?: ", lista_largo(lista) == largo_final);
    lista_destruir(lista, NULL);
}

/* Funcion para sumar elementos usando el iterador interno */
bool sumar(void* dato, void* extra) {
    *(int*) extra += *(int*) dato;
    return true;
}

/* Pruebas del iterador interno sin condicion de corte */
static void pruebas_interno_sin_condicion_corte(void){
    printf("\nINICIO DE PRUEBAS DEL ITERADOR INTERNO: EXTRA, SIN CONDICION DE CORTE\n");
    lista_t *lista1 = lista_crear();
    int suma = 0;
    int arr1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 10; i++) {
        suma += arr1[i];
        lista_insertar_ultimo(lista1, (void*) &arr1[i]);
    }

    printf("\nCALCULAMOS LA SUMA DE TODOS LOS ELEMENTOS DE LA LISTA\n");
    int suma_interno = 0;
    lista_iterar(lista1, sumar, &suma_interno);
    print_test("¿La suma de todos los elementos es correcta?: ", suma == suma_interno);

    lista_destruir(lista1, NULL);
}

/* Funcion para imprimir los primeros 5 elementos usando el iterador interno */
bool imprimir_primeros_5(void* dato, void* extra) {
    if (*(size_t*)extra >= 5) return false;
    printf("%d, ", *(int*)dato);
    *(size_t*)extra+= 1;
    return true;
}

/* Pruebas del iterador interno con condicion de corte */
static void pruebas_interno_condicion_corte(void){
    printf("\nINICIO DE PRUEBAS DEL ITERADOR INTERNO: EXTRA, CON CONDICION DE CORTE\n\n");
    printf("IMPRIMIMOS TODOS LOS ELEMENTOS DE LA LISTA\n");
    lista_t *lista = lista_crear();
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    printf("Lista: [");
    for (int i = 0; i < 10; i++) {
        lista_insertar_ultimo(lista, (void*) &arr[i]);
        printf("%d, ", arr[i]);
    }
    printf("]\n");

    size_t contador = 0;
    printf("IMPRIMIMOS LOS PRIMEROS 5 ELEMENTOS DE LA LISTA\n");
    printf("Resultado: [");
    lista_iterar(lista, imprimir_primeros_5, &contador);
    printf("]\n");
    lista_destruir(lista, NULL);
}

void pruebas_lista_estudiante() {
	pruebas_lista_vacia();
    pruebas_lista_algunos_elementos();
    pruebas_lista_null();
    pruebas_lista_volumen();
    pruebas_lista_destruccion_1();
    pruebas_lista_destruccion_2();
    pruebas_externo_insertar();
    pruebas_externo_insertar_2();
    pruebas_externo_remover();
    pruebas_interno_sin_condicion_corte();
    pruebas_interno_condicion_corte();
}

/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
