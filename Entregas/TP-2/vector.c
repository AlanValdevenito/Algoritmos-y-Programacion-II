#include "vector.h"
#include <stdbool.h>

#define CAPACIDAD_INICIAL 10
#define REDIMENSION 2

/* Definicion del struct vector */

struct vector {
    void **datos;
    size_t tam;
    size_t cant;
};

/* *****************************************************************
 *                     FUNCIONES AUXILIARES
 * *****************************************************************/

bool vector_redimensionar(vector_t *vector, size_t tam_nuevo) {
    void *datos_nuevo = realloc(vector->datos, tam_nuevo * sizeof(void*));

    if (tam_nuevo > 0 && datos_nuevo == NULL) {
        return false;
    }

    vector->datos = datos_nuevo;
    vector->tam = tam_nuevo;
    return true;
}

void ajustar_arreglo(void *arreglo[], size_t n, size_t pos) {
    for (size_t i = pos; i < n; i++) {
        arreglo[i] = arreglo[i + 1];
    }
}

/* ******************************************************************
 *                     PRIMITIVAS DEL VECTOR
 * *****************************************************************/

vector_t *vector_crear(void) {
    vector_t *vector = malloc(sizeof(vector_t));

    if (vector == NULL) {
        return NULL;
    }
    
    vector->datos = malloc(CAPACIDAD_INICIAL * sizeof(void*));

    if (vector->datos == NULL) {
        free(vector);
        return NULL;
    }

    vector->tam = CAPACIDAD_INICIAL;
    vector->cant = 0;
    return vector;
}

void *vector_obtener(vector_t *vector, size_t pos) {
    if (pos >= vector->cant) {
        return NULL;
    }
    
    return vector->datos[pos];
}

bool vector_guardar(vector_t *vector, void* elemento) {
    if (vector->cant == vector->tam) {
        if (!vector_redimensionar(vector, vector->tam * REDIMENSION)) {
            return false;
        }
    }

    vector->datos[vector->cant] = elemento;
    vector->cant++;
    return true;
}

void *vector_reemplazar(vector_t *vector, void *nuevo_elemento, size_t pos) {
    if (pos >= vector->cant) return NULL;

    void *elemento = vector->datos[pos];
    vector->datos[pos] = nuevo_elemento;
    return elemento;
}

void *vector_borrar(vector_t* vector, size_t pos) {
    if (pos >= vector->cant) {
        return NULL;
    }

    vector->cant--;
    void *dato = vector->datos[pos];
    ajustar_arreglo(vector->datos, vector->cant, pos);
    return dato;
}
 
size_t vector_largo(vector_t *vector) {
    return vector->tam;
}

size_t vector_cantidad(vector_t *vector) {
    return vector->cant;
}

void vector_destruir(vector_t *vector, void (*destruir_dato)(void *)) {
    if (destruir_dato != NULL) {
    	for (int i = 0; i < vector->cant; i++) {
    		destruir_dato(vector->datos[i]);
    	}
    }
    
    free(vector->datos);
    free(vector);
}