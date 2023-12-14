#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif
#include "abb.h"
#include "pila.h"
#include <stdlib.h>
#include <string.h>

/* Definicion del struct campo. */

typedef struct abb_nodo {
    struct abb_nodo* izq;
    struct abb_nodo* der;
    char* clave;
    void* dato;
} abb_nodo_t;

/* Definición del struct abb. */

struct abb {
    abb_nodo_t* raiz;
    abb_comparar_clave_t comparar;
    abb_destruir_dato_t destruir;
    size_t cantidad;
};

/* Definicion del struct iter. */

struct abb_iter {
    pila_t* pila;
};

/* *****************************************************************
 *                     FUNCIONES AUXILIARES
 * *****************************************************************/

abb_nodo_t* crear_nodo(char* clave, void* dato) {
    abb_nodo_t* nodo = malloc(sizeof(abb_nodo_t));

    if(nodo == NULL){
        return NULL;
    }

    nodo->clave = clave;
    nodo->dato = dato;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

void destruir_nodo(abb_nodo_t* nodo, abb_destruir_dato_t destruir_dato) {
    if (destruir_dato != NULL) {
        destruir_dato(nodo->dato);
    }

    free(nodo->clave);
    free(nodo);
}

void reemplazar_dato(abb_nodo_t* nodo, void* dato, abb_destruir_dato_t destruir_dato) {
    if (destruir_dato != NULL) {
        destruir_dato(nodo->dato);
    }

    nodo->dato = dato;
}

void asignar_nodo(abb_t* arbol, abb_nodo_t* padre, abb_nodo_t* nodo_nuevo) {
    int comparacion = arbol->comparar(padre->clave, nodo_nuevo->clave);

    if (comparacion > 0) {
        padre->izq = nodo_nuevo;
        arbol->cantidad++;
    
    } else if (comparacion < 0) {
        padre->der = nodo_nuevo;
        arbol->cantidad++;
    }
}

abb_nodo_t* obtener_hijo(abb_nodo_t* padre) {
    abb_nodo_t* hijo = NULL;

    if (padre->der != NULL) {
        hijo = padre->der;
        
    } else if (padre->izq != NULL) {
        hijo = padre->izq;
    }

    return hijo;
}

abb_nodo_t* buscar_nodo(abb_nodo_t* actual, const char* clave, abb_comparar_clave_t comparar) {
    if (actual == NULL) {
        return NULL;
    }

    int comparacion = comparar(actual->clave, clave);
    if (comparacion == 0) {
        return actual;
    }

    return (comparacion > 0) ? buscar_nodo(actual->izq, clave, comparar) : buscar_nodo(actual->der, clave, comparar); 
}

void borrar_cero_h(abb_t* arbol, abb_nodo_t* actual, abb_nodo_t* padre) {

    if (actual == padre) {
        arbol->raiz = NULL;
    
    } else if (padre->izq == actual) {
        padre->izq = NULL;
        
    } else if (padre->der == actual) {
        padre->der = NULL;
    }

    destruir_nodo(actual, NULL);
    arbol->cantidad--;
}

void borrar_un_h(abb_t* arbol, abb_nodo_t* actual, abb_nodo_t* padre) {
    abb_nodo_t* nieto = obtener_hijo(actual);

    if (actual == padre) {
        arbol->raiz = nieto;
    
    } else if (padre->izq == actual) {
        padre->izq = nieto;
        
    } else if (padre->der == actual) {
        padre->der = nieto;
    }

    destruir_nodo(actual, NULL);
    arbol->cantidad--;
}

abb_nodo_t* buscar_reemplazante(abb_nodo_t* actual, abb_nodo_t* padre) {
    if (actual == NULL) {
        return padre;
    }

    return buscar_reemplazante(actual->der, actual);
}

void borrar_dos_h(abb_t* arbol, abb_nodo_t* actual) {
    abb_nodo_t* borrar = actual;
    abb_nodo_t* reemplazante = buscar_reemplazante(actual->izq, actual);
    char* clave_reemplazante = strdup(reemplazante->clave);
    void* dato_reemplazante = abb_borrar(arbol, reemplazante->clave);
    free(borrar->clave);
    borrar->clave = clave_reemplazante;
    borrar->dato = dato_reemplazante;
}

/* ******************************************************************
 *                        WRAPPERS
 * *****************************************************************/

bool abb_guardar_wrapper(abb_t* arbol, abb_nodo_t* actual, abb_nodo_t* padre, abb_nodo_t* nodo_nuevo) {

    if (actual == NULL) {
        asignar_nodo(arbol, padre, nodo_nuevo);
        return true;
    }

    int comparacion = arbol->comparar(actual->clave, nodo_nuevo->clave);
    if (comparacion == 0) {
        reemplazar_dato(actual, nodo_nuevo->dato, arbol->destruir);
        destruir_nodo(nodo_nuevo, NULL);
        return true;
    }

    return (arbol->comparar(actual->clave, nodo_nuevo->clave) > 0) ? abb_guardar_wrapper(arbol, actual->izq, actual, nodo_nuevo) : abb_guardar_wrapper(arbol, actual->der, actual, nodo_nuevo); 
}

void *abb_borrar_wrapper(abb_t* arbol, abb_nodo_t* actual, abb_nodo_t* padre, const char *clave) {
    if (actual == NULL) {
        return NULL;
    }

    int comparacion = arbol->comparar(actual->clave, clave);
    if (comparacion == 0) {
        void* dato_asociado = actual->dato;

        if (actual->izq == NULL && actual->der == NULL) {
            borrar_cero_h(arbol, actual, padre);
    
        } else if ((actual->izq == NULL && actual->der != NULL) || (actual->izq != NULL && actual->der == NULL)) {
            borrar_un_h(arbol, actual, padre);
    
        } else if (actual->izq != NULL && actual->der != NULL) {
            borrar_dos_h(arbol, actual);
        }

        return dato_asociado;
    }
    
    return (comparacion > 0) ? abb_borrar_wrapper(arbol, actual->izq, actual, clave) : abb_borrar_wrapper(arbol, actual->der, actual, clave); 
}

void abb_destruir_wrapper(abb_nodo_t* nodo, void (*destruir_dato)(void *)) {
    if (nodo == NULL) return;

    abb_destruir_wrapper(nodo->izq, destruir_dato);
    abb_destruir_wrapper(nodo->der, destruir_dato);
    destruir_nodo(nodo, destruir_dato);
}

/* ******************************************************************
 *                    PRIMITIVAS DEL ABB
 * *****************************************************************/

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato) {
    abb_t *abb = malloc(sizeof(abb_t));
    
    if (abb == NULL) {
        return NULL;
    }
    
    abb->cantidad = 0;
    abb->comparar = cmp;
    abb->destruir = destruir_dato;
    
    abb->raiz = NULL;
    return abb;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato) {
    char *clave_copia = strdup(clave);
   abb_nodo_t* nodo_nuevo = crear_nodo(clave_copia, dato);

    if (nodo_nuevo == NULL) {
        free(clave_copia);
        return false;
    }

    if (arbol->raiz == NULL) {
        arbol->raiz = nodo_nuevo;
        arbol->cantidad++;
        return true;
    }

    return abb_guardar_wrapper(arbol, arbol->raiz, arbol->raiz, nodo_nuevo);
}

void *abb_borrar(abb_t *arbol, const char *clave) {
    if (arbol == NULL) {
        return NULL;
    } 
    
    return abb_borrar_wrapper(arbol, arbol->raiz, arbol->raiz, clave);
}

void *abb_obtener(const abb_t *arbol, const char *clave) {
    if (arbol == NULL) return NULL;
    abb_nodo_t* act = buscar_nodo(arbol->raiz, clave, arbol->comparar);
    if (act == NULL) return NULL;
    return act->dato;
}

bool abb_pertenece(const abb_t *arbol, const char *clave) {
    if (arbol == NULL) return false;
    abb_nodo_t* act = buscar_nodo(arbol->raiz, clave, arbol->comparar);
    if (act == NULL) return false;
    return true;
}

size_t abb_cantidad(const abb_t *arbol) {
    return arbol->cantidad;
}

void abb_destruir(abb_t *arbol) {
    if (arbol != NULL) abb_destruir_wrapper(arbol->raiz, arbol->destruir);
    free(arbol);
}

/* ******************************************************************
 *                 PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

abb_iter_t *abb_iter_in_crear(const abb_t *arbol) {
    abb_iter_t *iter = malloc(sizeof(abb_iter_t));

    if (iter == NULL) {
        return NULL;
    }

    pila_t* pila = pila_crear();

    if (pila == NULL) {
        return NULL;
    }

    iter->pila = pila;
    abb_nodo_t* act = arbol->raiz;
    while (act != NULL) {
        pila_apilar(pila, act);
        act = act->izq;
    }

    return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter) {
    if (abb_iter_in_al_final(iter)) return false;
    abb_nodo_t* desapilado = (abb_nodo_t*) pila_desapilar(iter->pila);   
    
    if (desapilado->der != NULL) {
        abb_nodo_t *act = desapilado->der;
        pila_apilar(iter->pila, act);
        while (act->izq != NULL) {
            act = act->izq;
            pila_apilar(iter->pila, act);
        }
    }
    return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter) {
    if (abb_iter_in_al_final(iter)) return NULL;
    abb_nodo_t* actual = pila_ver_tope(iter->pila);
    return actual->clave;
}

bool abb_iter_in_al_final(const abb_iter_t *iter) {
    return pila_esta_vacia(iter->pila);
}

void abb_iter_in_destruir(abb_iter_t* iter) {
    pila_destruir(iter->pila);
    free(iter);
}

/* ******************************************************************
 *                 PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

bool _abb_in_order(abb_nodo_t* nodo, bool visitar(const char *, void *, void *), void *extra) {

    if (nodo == NULL) {
        return true;
    }

    if (!_abb_in_order(nodo->izq, visitar, extra)) {
        return false;
    }

    if (!visitar(nodo->clave, nodo->dato, extra)) {
        return false;
    }

    if (!_abb_in_order(nodo->der, visitar, extra)) {
        return false;
    }

    return true;
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra) {
    _abb_in_order(arbol->raiz, visitar, extra);
}
