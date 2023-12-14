#include "heap.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

/* ******************************************************************
 *                        FUNCIÓN DE COMPARACION
 * *****************************************************************/

int cmp(const void* a, const void* b) {

    if (*(int*) a < *(int*) b) {
        return -1;
    
    } else if (*(int*) a > *(int*) b) {
        return 1;
    }

    return 0;
}

/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/

static void pruebas_crear_heap_vacio() {
    printf("\n~~~ Prueba: CREAR HEAP VACIO ~~~ \n");
    heap_t* heap = heap_crear(cmp);

    print_test("Crear HEAP vacio", heap != NULL);
    print_test("La cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba HEAP ver maximo es NULL", heap_ver_max(heap) == NULL);
    print_test("Prueba HEAP esta vacio devuelve true", heap_esta_vacio(heap));

    heap_destruir(heap, NULL);
    printf("\n");
}

static void pruebas_heap_encolar(){
    printf("~~~ Prueba: HEAP ENCOLAR Y NO BORRAR ~~~ \n");
    heap_t* heap = heap_crear(cmp);

    int n1 = 5;
    int n2 = 9;
    int n3 = 10;
    int n4 = 12;
    int n5 = 11;
    int n6 = 2;

    /* Inserta los 6 valores y no los borra (se destruyen con el HEAP) */
    print_test("Encolar 5", heap_encolar(heap, &n1));
    print_test("La cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba HEAP ver maximo es 5", heap_ver_max(heap) == &n1);
    print_test("Prueba HEAP esta vacio devuelve false", !heap_esta_vacio(heap));

    print_test("Encolar 9", heap_encolar(heap, &n2));
    print_test("La cantidad de elementos es 2", heap_cantidad(heap) == 2);
    print_test("Prueba HEAP ver maximo es 9", heap_ver_max(heap) == &n2);
    print_test("Prueba HEAP esta vacio devuelve false", !heap_esta_vacio(heap));

    print_test("Encolar 10", heap_encolar(heap, &n3));
    print_test("La cantidad de elementos es 3", heap_cantidad(heap) == 3);
    print_test("Prueba HEAP ver maximo es 10", heap_ver_max(heap) == &n3);
    print_test("Prueba HEAP esta vacio devuelve false", !heap_esta_vacio(heap));

    print_test("Encolar 11", heap_encolar(heap, &n5));
    print_test("La cantidad de elementos es 4", heap_cantidad(heap) == 4);
    print_test("Prueba HEAP ver maximo es 11", heap_ver_max(heap) == &n5);
    print_test("Prueba HEAP esta vacio devuelve false", !heap_esta_vacio(heap));

    print_test("Encolar 12", heap_encolar(heap, &n4));
    print_test("La cantidad de elementos es 5", heap_cantidad(heap) == 5);
    print_test("Prueba HEAP ver maximo es 12", heap_ver_max(heap) == &n4);
    print_test("Prueba HEAP esta vacio devuelve false", !heap_esta_vacio(heap));

    print_test("Encolar 2", heap_encolar(heap, &n6));
    print_test("La cantidad de elementos es 6", heap_cantidad(heap) == 6);
    print_test("Prueba HEAP ver maximo es 12", heap_ver_max(heap) == &n4);
    print_test("Prueba HEAP esta vacio devuelve false", !heap_esta_vacio(heap));

    heap_destruir(heap, NULL);
    printf("\n");
}

static void pruebas_crear_heap_alternativo() {
    printf("~~~ Prueba: CREAR HEAP ALTERNATIVO ~~~ \n");
    int v1 = 50, v2 = 1, v3 = 2, v4 = 3, v5 = 30, v6 = 10, v7 = 80;
    int *arr[7] = {&v1, &v2, &v3, &v4, &v5, &v6, &v7};
    size_t n = 7;

    heap_t* heap = heap_crear_arr((void*) arr, n, cmp);

    print_test("El HEAP se creo correctamente", heap != NULL);
    print_test("Prueba HEAP esta vacio devuelve false", !heap_esta_vacio(heap));
    print_test("La cantidad de elementos es 7", heap_cantidad(heap) == 7);
    print_test("Prueba HEAP ver maximo es 80", heap_ver_max(heap) == &v7);

    heap_destruir(heap, NULL);
    printf("\n");
}

static void pruebas_heap_encolar_con_destruir() {
    printf("~~~ Prueba: HEAP ENCOLAR CON DESTRUIR: free() ~~~ \n");
    heap_t* heap = heap_crear(cmp);

    int *v1 = malloc(sizeof(int));
    int *v2 = malloc(sizeof(int));
    int *v3 = malloc(sizeof(int));
    int *v4 = malloc(sizeof(int));
    int *v5 = malloc(sizeof(int));
    int *v6 = malloc(sizeof(int));
    int *v7 = malloc(sizeof(int));

    *v1 = 50;
    *v2 = 1;
    *v3 = 2;
    *v4 = 3;
    *v5 = 30;
    *v6 = 10;
    *v7 = 80;

    /* Inserta los 7 valores y no los borra (se destruyen con el HEAP) */
    print_test("Encolar valor 1", heap_encolar(heap, *&v1));
    print_test("Encolar valor 2", heap_encolar(heap, *&v2));
    print_test("Encolar valor 3", heap_encolar(heap, *&v3));
    print_test("Encolar valor 4", heap_encolar(heap, *&v4));
    print_test("Encolar valor 5", heap_encolar(heap, *&v5));
    print_test("Encolar valor 6", heap_encolar(heap, *&v6));
    print_test("Encolar valor 7", heap_encolar(heap, *&v7));

    heap_destruir(heap, free);
    printf("\n");
}

static void pruebas_heap_desencolar() {
    printf("~~~ Prueba: HEAP DESENCOLAR ~~~ \n");
    heap_t* heap = heap_crear(cmp);
    int n1 = 1, n2 = 2, n3 = 3, n4 = 4, n5 = 5;

    print_test("Encolar 5", heap_encolar(heap, &n5));
    print_test("Encolar 4", heap_encolar(heap, &n4));
    print_test("Encolar 3", heap_encolar(heap, &n3));
    print_test("Encolar 2", heap_encolar(heap, &n2));
    print_test("Encolar 1", heap_encolar(heap, &n1));

    print_test("Prueba HEAP desencolar devuelve 5", heap_desencolar(heap) == &n5);
    print_test("La cantidad de elementos es 4", heap_cantidad(heap) == 4);
    print_test("Prueba HEAP ver maximo es 4", heap_ver_max(heap) == &n4);
    
    print_test("Prueba HEAP desencolar devuelve 4", heap_desencolar(heap) == &n4);
    print_test("La cantidad de elementos es 3", heap_cantidad(heap) == 3);
    print_test("Prueba HEAP ver maximo es 3", heap_ver_max(heap) == &n3);

    print_test("Prueba HEAP desencolar devuelve 3", heap_desencolar(heap) == &n3);
    print_test("La cantidad de elementos es 2", heap_cantidad(heap) == 2);
    print_test("Prueba HEAP ver maximo es 2", heap_ver_max(heap) == &n2);

    print_test("Prueba HEAP desencolar devuelve 2", heap_desencolar(heap) == &n2);
    print_test("La cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba HEAP ver maximo es 1", heap_ver_max(heap) == &n1);

    print_test("Prueba HEAP desencolar devuelve 1", heap_desencolar(heap) == &n1);
    print_test("Prueba HEAP ver maximo es NULL", heap_ver_max(heap) == NULL);
    print_test("Prueba HEAP esta vacio devuelve true", heap_esta_vacio(heap));

    heap_destruir(heap, NULL);
    printf("\n");
}

static void pruebas_heap_null() {
    printf("~~~ Prueba: HEAP NULL ~~~ \n");
    heap_t* heap = heap_crear(cmp);

    void *valor = NULL;

    print_test("El HEAP se creó correctamente", heap);
    print_test("El HEAP está vacio", heap_esta_vacio(heap));
    print_test("Encolar NULL", heap_encolar(heap, valor));
    print_test("El HEAP no está vacio", !heap_esta_vacio(heap));
    print_test("La cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Ver maximo devuelve NULL", heap_ver_max(heap) == valor);
    print_test("Desencolar devuelve NULL", heap_desencolar(heap) == valor);
    print_test("El HEAP está vacio", heap_esta_vacio(heap));

    heap_destruir(heap, NULL);
}

static void pruebas_heap_volumen(size_t largo) {
    printf("\n~~~ Prueba: HEAP VOLUMEN (%ld ELEMENTOS)~~~ \n", largo);
    heap_t* heap = heap_crear(cmp);
    bool ok = true;
    int *arr[largo];
    
    for(size_t i = 0; i < largo; i++) {
        arr[i] = malloc(sizeof(int));
        *arr[i] = rand() % (int) largo;
        if (!heap_encolar(heap, &arr[i])) {
            ok = false;
            break;
        }
    }

    print_test("Todos los elementos se encolaron correctamente", ok);

    int anterior = *(int*)heap_desencolar(heap);

    for (size_t i = 1; i < largo; i++) {
        int actual = *(int*)heap_desencolar(heap);
        if (anterior < actual) {
            ok = false;
            break;
        }
        anterior = actual;
    }

    print_test("Todos los elementos se desencolaron correctamente", ok);

    for(size_t i = 0; i < largo; i++) {
        free(arr[i]);
    }

    heap_destruir(heap, NULL);
}

static void pruebas_heap_sort(bool debug) {
    printf("\n~~~ Prueba: HEAP SORT ~~~ \n");
    int v1 = 50, v2 = 1, v3 = 2, v4 = 3, v5 = 30, v6 = 10, v7 = 80;
    int *arr[7] = {&v1, &v2, &v3, &v4, &v5, &v6, &v7};
    size_t n = 7;

    heap_sort((void*) arr, n, cmp);

    bool ok = true;
    for(size_t i = 0; i < n; i++) {
        if((i > 0) && (*arr[i-1] > *arr[i])) ok = false;
        if (!ok) break;
    }

    if (debug) print_test("Prueba ordenar arreglo utilizando Heap Sort", ok);
    printf("\n");
}

static void pruebas_heap_sort_volumen(size_t largo, bool debug) {
    printf("~~~ Prueba: HEAP SORT VOLUMEN %ld ELEMENTOS ~~~ \n", largo);
    int *arr[largo];
    for(size_t i = 0; i < largo; i++) {
        arr[i] = malloc(sizeof(int));
        *arr[i] = rand() % (int) largo;
    }

    heap_sort((void*) arr, largo, cmp);

    bool ok = true;
    for(size_t i = 0; i < largo; i++) {
        if((i > 0) && (*arr[i-1] > *arr[i])) ok = false;
        if (!ok) break;
    }

    if (debug) print_test("Prueba de volumen ordenar arreglo utilizando Heap Sort", ok);

    for(size_t i = 0; i < largo; i++) {
        free(arr[i]);
    }

    printf("\n");
}

void pruebas_heap_estudiante(){
    /* Ejecuta todas las pruebas unitarias. */
    pruebas_crear_heap_vacio();
    pruebas_crear_heap_alternativo(); 
    pruebas_heap_encolar(); 
    pruebas_heap_encolar_con_destruir(); 
    pruebas_heap_desencolar(); 
    pruebas_heap_null(); 
    pruebas_heap_volumen(5000); 
    pruebas_heap_sort(true); 
    pruebas_heap_sort_volumen(5000, true); 
}

