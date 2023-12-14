#include "pila.h"
#include <stdlib.h>

#define CAPACIDAD_INICIAL 10
#define REDIMENSION 2

/* Definición del struct pila proporcionado por la cátedra. */

struct pila{
    void **datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad; // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                     FUNCIONES AUXILIARES
 * *****************************************************************/

bool pila_redimensionar(pila_t *pila, size_t tam_nuevo){

    void **datos_nuevo = realloc(pila->datos, tam_nuevo * sizeof(void*));

    if(datos_nuevo == NULL){
        return false;
    }

    pila->datos = datos_nuevo;
    pila->capacidad = tam_nuevo;
    return true;
}

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t *pila_crear(void){
    pila_t *pila = malloc(sizeof(pila_t));

    if (pila == NULL){
        return NULL;
    }

    pila->capacidad = CAPACIDAD_INICIAL;
    pila->cantidad = 0;

    pila->datos = malloc(pila->capacidad * sizeof(void*));

    if (pila->datos == NULL){
        free(pila);
        return NULL;
    }

    return pila;
}

void pila_destruir(pila_t *pila){
    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
    return pila->cantidad == 0;
}

bool pila_apilar(pila_t *pila, void *valor){

    if(pila->cantidad == pila->capacidad){
        bool funciono = pila_redimensionar(pila, pila->capacidad * REDIMENSION);

        if(!funciono){
            return false;
        }
    }

    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    return true;
}

void *pila_ver_tope(const pila_t *pila){

    if (pila_esta_vacia(pila)){
        return NULL;
    }

    return pila->datos[pila->cantidad - 1];
}

void *pila_desapilar(pila_t *pila){

    if (pila_esta_vacia(pila)){
        return NULL;
    }

    if((pila->cantidad * 4) >= CAPACIDAD_INICIAL && (pila->cantidad * 4) <= pila->capacidad){
        pila_redimensionar(pila, pila->capacidad / REDIMENSION);
    }

    pila->cantidad--;
    return pila->datos[pila->cantidad];
}
