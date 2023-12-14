#include "heap.h"
#include <stdlib.h>
#include <string.h>

#define CAPACIDAD_INICIAL 10
#define REDIMENSION 2
#define MINIMO_REDIMENSION 1/4

/* Definicion del struct heap */

struct heap {
    void** datos;
    size_t cant;
    size_t tam;
    cmp_func_t cmp;
};

/* *****************************************************************
 *                     FUNCIONES AUXILIARES
 * *****************************************************************/

bool heap_redimensionar(heap_t* heap, size_t tam_nuevo) {
    void** datos_nuevo = realloc(heap->datos, tam_nuevo * sizeof(void*));

    if (datos_nuevo == NULL) {
        return false;
    }

    heap->datos = datos_nuevo;
    heap->tam = tam_nuevo;
    return true;
}

size_t buscar_padre(size_t pos_hijo) {
    return (pos_hijo - 1) / 2;
}

size_t buscar_hijo_izquierdo(size_t pos_padre) {
    return 2 * (pos_padre) + 1;
}

size_t buscar_hijo_derecho(size_t pos_padre) {
    return 2 * (pos_padre) + 2;
}

size_t buscar_hijo_mayor(void* arreglo[], size_t pos_padre, size_t cant, cmp_func_t cmp) {
    size_t pos_hijo_izq = buscar_hijo_izquierdo(pos_padre);
    size_t pos_hijo_der = buscar_hijo_derecho(pos_padre);
    
    if (pos_hijo_izq >= cant) return (size_t) -1;
    
    else if (pos_hijo_der >= cant) return pos_hijo_izq;

    if (cmp(arreglo[pos_hijo_izq], arreglo[pos_hijo_der]) < 0) return pos_hijo_der;
    else return pos_hijo_izq;
}

void swap(void *arreglo[], size_t pos_padre, size_t pos_hijo) {
    void *aux = arreglo[pos_padre];
    arreglo[pos_padre] = arreglo[pos_hijo];
    arreglo[pos_hijo] = aux;
}

void upheap(void* arreglo[], size_t pos_hijo, cmp_func_t cmp) {
    if (pos_hijo == 0) {
        return;
    }

    size_t pos_padre = buscar_padre(pos_hijo);
    if (cmp(arreglo[pos_padre], arreglo[pos_hijo]) < 0) {
        swap(arreglo, pos_padre, pos_hijo);
        upheap(arreglo, pos_padre, cmp);
    }
}

void downheap(void* arreglo[], size_t pos_padre, size_t cant, cmp_func_t cmp) {
    if (pos_padre == cant - 1) {
        return;
    }

    size_t pos_hijo = buscar_hijo_mayor(arreglo, pos_padre, cant, cmp);

    if (pos_hijo == -1) {
        return;
    }
    
    if (cmp(arreglo[pos_padre], arreglo[pos_hijo]) < 0) {
        swap(arreglo, pos_padre, pos_hijo);
        downheap(arreglo, pos_hijo, cant, cmp);    
    }
}

void heapify(void *arreglo[], size_t largo, cmp_func_t cmp) {
    for (size_t i = 0; i < largo/2 + 1; i++) {
        downheap(arreglo, largo/2 - i, largo, cmp);
    }
}

void copiar_arreglo(void *arreglo[], void *original[], size_t largo) {
    for (size_t i = 0; i < largo; i++) {
        arreglo[i] = original[i];
    }
}

/* ******************************************************************
 *                    PRIMITIVAS DEL HEAP
 * *****************************************************************/

heap_t *heap_crear(cmp_func_t cmp) {
    heap_t* heap = malloc(sizeof(heap_t));

    if (heap == NULL) {
        return NULL;
    }

    heap->datos = malloc(CAPACIDAD_INICIAL * sizeof(void*));

    if (heap->datos == NULL) {
        free(heap);
        return NULL;
    }

    heap->cmp = cmp;
    heap->cant = 0;
    heap->tam = CAPACIDAD_INICIAL;
    return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp) {
    heap_t* heap = malloc(sizeof(heap_t));

    if (heap == NULL) {
        return NULL;
    }

    heap->tam = CAPACIDAD_INICIAL;

    while (heap->tam < n) {
        heap->tam = heap->tam * REDIMENSION;
    }

    heap->datos = malloc(heap->tam * sizeof(void*));

    if (heap->datos == NULL) {
        free(heap);
        return NULL;
    }

    copiar_arreglo(heap->datos, arreglo, n);
    heapify(heap->datos, n,cmp);
    heap->cmp = cmp;
    heap->cant = n;
    return heap;
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)) {
    if (destruir_elemento) {
        for (int i = 0; i < heap->cant; i++) {
            destruir_elemento(heap->datos[i]);
        }
    }

    free(heap->datos);
    free(heap);
}

size_t heap_cantidad(const heap_t *heap) {
    return heap->cant;
}

bool heap_esta_vacio(const heap_t *heap) {
    return heap->cant == 0;
}

bool heap_encolar(heap_t *heap, void *elem) {

    if (heap->cant == heap->tam) {
        if (!heap_redimensionar(heap, REDIMENSION * heap->tam)) {
            return false;
        }
    }

    heap->datos[heap->cant] = elem;
    upheap(heap->datos, heap->cant, heap->cmp);
    heap->cant++;
    return true;
}

void *heap_ver_max(const heap_t *heap) {
    if (heap_esta_vacio(heap)) return NULL;
    return heap->datos[0];
}

void *heap_desencolar(heap_t *heap) {
    if (heap_esta_vacio(heap)) return NULL;
    
    void *max = heap_ver_max(heap);
    heap->cant--;
    swap(heap->datos, 0, heap->cant);
    downheap(heap->datos, 0, heap->cant, heap->cmp);

    if (heap->cant <= heap->tam*MINIMO_REDIMENSION && heap->tam / REDIMENSION >= CAPACIDAD_INICIAL) {
        heap_redimensionar(heap, heap->tam / REDIMENSION);
    }

    return max;
}

/* ******************************************************************
 *                    METODO DE ORDENAMIENTO
 * *****************************************************************/

void heap_sort_wrapper(void *elementos[], size_t cant, cmp_func_t cmp) {
    if(cant == 0) {
        return;
    }

    swap(elementos, 0, cant - 1);
    cant--;
    downheap(elementos, 0, cant, cmp);
    heap_sort_wrapper(elementos, cant, cmp);
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp) {
    heapify(elementos, cant, cmp);
    heap_sort_wrapper(elementos, cant, cmp);
}
