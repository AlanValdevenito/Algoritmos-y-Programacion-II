#include "lista.h"
#include <stdlib.h>

/* Definicion del struct nodo. */

typedef struct nodo {
    void* dato;
    struct nodo* prox;
} nodo_t;

/* Definición del struct lista. */

struct lista {
    nodo_t* prim;
    nodo_t* ult;
    size_t largo;
};

/* Definicion del struct iter. */

struct lista_iter {
    lista_t* lista;
    nodo_t* ant;
    nodo_t* act;
};

/* *****************************************************************
 *                     FUNCIONES AUXILIARES
 * *****************************************************************/

nodo_t* crear_nodo_lista(void* valor) {
    nodo_t* nodo = malloc(sizeof(nodo_t));

    if(nodo == NULL){
        return NULL;
    }

    nodo->dato = valor;
    nodo->prox = NULL;
    return nodo;
}

void destruir_nodo_lista(nodo_t *nodo) {
    free(nodo);
}

/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

lista_t *lista_crear(void) {
    lista_t *lista = malloc(sizeof(lista_t));

    if (lista == NULL) {
        return NULL;
    }

    lista->prim = NULL;
    lista->ult = NULL;
    lista->largo = 0;
    return lista;
}

bool lista_esta_vacia(const lista_t *lista) {
    return lista->largo == 0;
}

bool lista_insertar_primero(lista_t *lista, void *dato) { 
    nodo_t *nodo_nuevo = crear_nodo_lista(dato);

    if (nodo_nuevo == NULL) {
        return false;
    }

    if (lista_esta_vacia(lista)) {
        lista->ult = nodo_nuevo;

    } else {
        nodo_t *mover = lista->prim;
        lista->prim = nodo_nuevo;
        lista->prim->prox = mover;
    }

    lista->prim = nodo_nuevo;
    lista->largo++;
    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {
    nodo_t *nodo_nuevo = crear_nodo_lista(dato);

    if (nodo_nuevo == NULL) return false;

    if (lista_esta_vacia(lista)) {
        lista->prim = nodo_nuevo;

    } else {
        lista->ult->prox = nodo_nuevo;
    }

    lista->ult = nodo_nuevo;
    lista->largo++;
    return true;
}

void *lista_borrar_primero(lista_t *lista) {
    if (lista_esta_vacia(lista)) return NULL;

    nodo_t* primer_nodo = lista->prim;
    void* dato = lista->prim->dato;
    lista->prim = lista->prim->prox;

    if (lista->prim == NULL) {
        lista->ult = NULL;
    }

    destruir_nodo_lista(primer_nodo);
    lista->largo--;
    return dato;
}

void *lista_ver_primero(const lista_t *lista) {
    if (lista_esta_vacia(lista)) {
        return NULL;
    }

    return lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t* lista) {
    if (lista_esta_vacia(lista)) {
        return NULL;
    }

    return lista->ult->dato;
}

size_t lista_largo(const lista_t *lista) {
    return lista->largo;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)) {
    while (!lista_esta_vacia(lista)) {
        
        if (destruir_dato == NULL) {
            lista_borrar_primero(lista);

        } else { 
            destruir_dato(lista_borrar_primero(lista));
        }
    }
    free(lista);
}

/* *****************************************************************
 *                  PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

lista_iter_t *lista_iter_crear(lista_t *lista) {
    lista_iter_t *lista_iter = malloc(sizeof(lista_iter_t));

    if (lista_iter == NULL) {
        return NULL;
    }

    lista_iter->ant = NULL;
    lista_iter->act = lista->prim;
    lista_iter->lista = lista;
    return lista_iter;
}

bool lista_iter_avanzar(lista_iter_t *iter) {
    if (iter->act != NULL) {
        iter->ant = iter->act;
        iter->act = iter->act->prox;
        return true;
    }

    return false;
}

void *lista_iter_ver_actual(const lista_iter_t *iter) {
    if (iter->act == NULL) return NULL;
    return iter->act->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter) {
    return iter->act == NULL;
}

void lista_iter_destruir(lista_iter_t *iter) {
    free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
    nodo_t *nodo_nuevo = crear_nodo_lista(dato);

    if (nodo_nuevo == NULL) {
        return false;
    }

    if (iter->ant == NULL) {
        if (iter->act == NULL) {
            iter->lista->ult = nodo_nuevo;
       
        } else {
            nodo_t *mover = iter->lista->prim;
            iter->lista->prim = nodo_nuevo;
            iter->lista->prim->prox = mover;
        }  

        iter->lista->prim = nodo_nuevo;

    } else if (lista_iter_al_final(iter)) {
        iter->ant->prox = nodo_nuevo;
        iter->lista->ult = nodo_nuevo;

    } else {
        nodo_t* mover = iter->act;
        iter->ant->prox = nodo_nuevo;
        iter->ant->prox->prox = mover;
    }

    iter->act = nodo_nuevo;
    iter->lista->largo++;
    return true;
}

void *lista_iter_borrar(lista_iter_t *iter) {
    if (lista_esta_vacia(iter->lista) || iter->act == NULL) return NULL;
    nodo_t *nodo = iter->act;
    void* dato = nodo->dato;
    
    if (iter->ant == NULL) {
        iter->lista->prim = iter->act->prox;
        iter->act = iter->act->prox;

        if (iter->lista->prim == NULL) {
            iter->lista->ult = NULL;
        }

    } else if (iter->act->prox == NULL) {
        iter->lista->ult = iter->ant;
        iter->ant->prox = iter->act->prox;
        iter->act = iter->act->prox;
    
    } else {
        iter->act = iter->act->prox;
        iter->ant->prox = iter->act;
    }
    
    iter->lista->largo--;
    destruir_nodo_lista(nodo);
    return dato;
}

 /* *****************************************************************
 *                  PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra) {
    nodo_t* nodo_actual = lista->prim;

    for (size_t i = 0; i < lista->largo ; i++) {
        if (!visitar(nodo_actual->dato, extra)) {
            return;
        }
    
        nodo_actual = nodo_actual->prox;
    }
}
