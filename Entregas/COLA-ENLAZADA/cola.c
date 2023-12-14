#include "cola.h"
#include <stdlib.h>

/* Definicion del struct nodo. */

typedef struct nodo{
    void* dato;
    struct nodo* prox;
} nodo_t;

/* Definición del struct cola. */

struct cola{
    nodo_t* prim;
    nodo_t* ulti;  
};

/* *****************************************************************
 *                     FUNCIONES AUXILIARES
 * *****************************************************************/

nodo_t* crear_nodo(void* valor){
    nodo_t* nodo = malloc(sizeof(nodo_t));

    if(nodo == NULL){
        return NULL;
    }

    nodo->dato = valor;
    nodo->prox = NULL;
    return nodo;
}

void destruir_nodo(nodo_t *nodo){
    free(nodo);
}

/* *****************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

cola_t *cola_crear(void){
    cola_t *cola = malloc(sizeof(cola_t));

    if(cola == NULL){
        return NULL;
    }

    cola->prim = NULL;
    cola->ulti = NULL;
    return cola;
}

void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)){

    while(!cola_esta_vacia(cola)){
        
        if(destruir_dato == NULL){
            cola_desencolar(cola);
        }

        else{
            destruir_dato(cola_desencolar(cola));
        }
    }

    free(cola);
}

bool cola_esta_vacia(const cola_t *cola){
    return cola->prim == NULL;
}

bool cola_encolar(cola_t *cola, void *valor){
    nodo_t *nodo_nuevo = crear_nodo(valor);

    if(nodo_nuevo == NULL){
        return false;
    }

    if(cola_esta_vacia(cola)){
        cola->prim = nodo_nuevo;
    }
    else{
        cola->ulti->prox = nodo_nuevo;
    }

    cola->ulti = nodo_nuevo;
    return true;
}

void *cola_ver_primero(const cola_t *cola){

    if(cola_esta_vacia(cola)){
        return NULL;
    }

    return cola->prim->dato;
}

void *cola_desencolar(cola_t *cola){

    if(cola_esta_vacia(cola)){ 
        return NULL;
    }

    void* dato = cola->prim->dato;
    nodo_t *nodo_destruir = cola->prim;
    cola->prim = cola->prim->prox;

    if(cola->prim == NULL){
        cola->ulti = NULL;
    }

    destruir_nodo(nodo_destruir);
    return dato;
}
