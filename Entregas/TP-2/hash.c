#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif
#include "hash.h"
#include <stdlib.h>
#include <string.h>

#define VACIO 0
#define OCUPADO 1
#define BORRADO 2

#define CAPACIDAD_INICIAL 10
#define FACTOR_CARGA 0.7
#define FACTOR_CARGA_MINIMO 0.1
#define REDIMENSION 2

/* Definicion del struct estado. */

typedef struct estado {
    int estado_actual;
} estado_t;

/* Definicion del struct campo. */

typedef struct campo {
    char* clave;
    void* dato;
    estado_t estado;
} campo_t;

/* Definición del struct hash. */

struct hash {
    campo_t* tabla;
    hash_destruir_dato_t destruir;
    size_t cantidad;
    size_t largo;
};

/* Definicion del struct iter. */

struct hash_iter {
    const hash_t* hash;
    campo_t* act;
    size_t pos_actual;
};

/* *****************************************************************
 *                     FUNCIONES AUXILIARES
 * *****************************************************************/

// La funcion de hashing la conseguimos del siguiente link: https://softwareengineering.stackexchange.com/questions/49550/which-hashing-algorithm-is-best-for-uniqueness-and-speed
size_t hashing(const char* clave, size_t largo_arreglo) {
    int pos = 5381;
    int c;
        
    while ((c = *clave++)){
        pos = ((pos << 5) + pos) + c;
    }
    return (size_t) pos % largo_arreglo;
}

void inicializar_campo(campo_t* campo, char* clave, void* dato, int estado) {
    campo->clave = clave;
    campo->dato = dato;
    campo->estado.estado_actual = estado;
}

void destruir_campo(campo_t *campo, hash_destruir_dato_t destruir) {
    if (destruir != NULL) {
        destruir(campo->dato);
    
    } 

    free(campo->clave);
}

bool son_iguales(const char* clave_1, const char* clave_2) {
    if (clave_1 == NULL || clave_2 == NULL) return false;
    size_t largo_1 = strlen(clave_1);
    size_t largo_2 = strlen(clave_2);
    if (largo_1 != largo_2) return false;

    for (size_t i = 0; i < largo_1; i++) {
        if (clave_1[i] != clave_2[i]) return false;
    }
    return true;

}

campo_t *obtener_campo(const hash_t *hash, const char* clave) {
    if (clave == NULL) return NULL;
    char *clave_copia = strdup(clave);
    size_t pos = hashing(clave_copia, hash->largo);
    free(clave_copia);
    size_t contador = 0;
    while (!son_iguales(clave, hash->tabla[pos].clave) && hash->tabla[pos].estado.estado_actual != VACIO) {
        pos++;
        contador++;
        if (contador >= hash->largo - 1) {
            break;
        }
        if (pos > hash->largo - 1) {
            pos = 0;
        }   
    }

    if (hash->tabla[pos].estado.estado_actual == VACIO || !son_iguales(clave, hash->tabla[pos].clave)) return NULL;
    return &hash->tabla[pos];
}

size_t campo_avanzar(campo_t* tabla, size_t largo, size_t pos) {
    while (tabla[pos].estado.estado_actual == OCUPADO) {
        if (pos >= (largo - 1)) {
            pos = 0;
        
        } else {
            pos++;
        }
    }
    return pos;
}

bool redimensionar(hash_t* hash, size_t tam_nuevo){
    campo_t* tabla_nueva = malloc(tam_nuevo * sizeof(campo_t));

    if (tabla_nueva == NULL) {
        free(tabla_nueva);
        return false;
    }

    for (size_t i = 0; i < tam_nuevo; i++) {
        inicializar_campo(&tabla_nueva[i], NULL, NULL, VACIO);
    }

    for (size_t i = 0; i < hash->largo; i++) {
        if (hash->tabla[i].estado.estado_actual == OCUPADO) {
            size_t pos_nueva = hashing(hash->tabla[i].clave, tam_nuevo);
            
            if (tabla_nueva[pos_nueva].estado.estado_actual == OCUPADO) {
                pos_nueva = campo_avanzar(tabla_nueva, tam_nuevo, pos_nueva);
            }

            inicializar_campo(&tabla_nueva[pos_nueva], hash->tabla[i].clave, hash->tabla[i].dato, hash->tabla[i].estado.estado_actual);
        }
    }

    free(hash->tabla);
    hash->largo = tam_nuevo;
    hash->tabla = tabla_nueva;
    return true;
}

/* ******************************************************************
 *                    PRIMITIVAS DEL HASH
 * *****************************************************************/

hash_t *hash_crear(hash_destruir_dato_t destruir_dato) {
    hash_t *hash = malloc(sizeof(hash_t));

    if (hash == NULL) {
        return NULL;
    }

    hash->tabla = malloc(CAPACIDAD_INICIAL * sizeof(campo_t));

    if (hash->tabla == NULL) {
        free(hash);
        return NULL;
    }

    for (int i = 0; i < CAPACIDAD_INICIAL; i++) {
        inicializar_campo(&hash->tabla[i], NULL, NULL, VACIO);
    }

    hash->destruir = destruir_dato;
    hash->cantidad = 0;
    hash->largo = CAPACIDAD_INICIAL;
    return hash;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato) {
    if (hash_pertenece(hash, clave)) {
        char *clave_copia_1 = strdup(clave);
        size_t pos = hashing(clave_copia_1, hash->largo);
        free(clave_copia_1);

        if (hash->destruir != NULL) {
            hash->destruir(hash->tabla[pos].dato);
        } 

        hash->tabla[pos].dato = dato;
        return true;
    }

    if (((double) hash->cantidad / (double) hash->largo) > FACTOR_CARGA) {
        if (!redimensionar(hash, REDIMENSION * hash->largo)) {
            return false;
        }
    }

    char *clave_copia = strdup(clave);
    size_t pos = hashing(clave_copia, hash->largo);

    if (hash->tabla[pos].estado.estado_actual == OCUPADO) {
        pos = campo_avanzar(hash->tabla, hash->largo, pos);
    }

    inicializar_campo(&hash->tabla[pos], clave_copia, dato, OCUPADO);
    hash->cantidad++;
    return true;
}

void *hash_borrar(hash_t *hash, const char *clave) {
    campo_t *campo = obtener_campo(hash, clave);
    if (campo == NULL) return NULL;
    if (campo->estado.estado_actual == VACIO) return NULL;  
    void *valor = campo->dato;
    destruir_campo(campo, NULL);
    inicializar_campo(campo, NULL, NULL, BORRADO);
    hash->cantidad--;

    if (((double) hash->cantidad / (double) hash->largo) <= FACTOR_CARGA_MINIMO && hash->largo / REDIMENSION >= CAPACIDAD_INICIAL) {
        redimensionar(hash, hash->largo / REDIMENSION);
    }
    return valor;
}

void *hash_obtener(const hash_t *hash, const char *clave) {
    campo_t* campo = obtener_campo(hash, clave);
    if (campo == NULL) return NULL;
    if (campo->estado.estado_actual == VACIO) return NULL;
    return campo->dato;
}

bool hash_pertenece(const hash_t *hash, const char *clave) {
    campo_t *campo = obtener_campo(hash, clave);
    if (campo == NULL) return false;
    if (campo->estado.estado_actual != OCUPADO || !(strcmp(campo->clave, clave) == 0)) return false;
    return true;
}

size_t hash_cantidad(const hash_t *hash) {
    return hash->cantidad;
}

void hash_destruir(hash_t *hash) {
    for (size_t i = 0; i < hash->largo; i++) {
        if (hash->tabla[i].estado.estado_actual == OCUPADO) {
            destruir_campo(&hash->tabla[i], hash->destruir);
        } 
    }
    free(hash->tabla);
    free(hash);
}

/* ******************************************************************
 *                   PRIMITIVAS DEL ITERADOR
 * *****************************************************************/

hash_iter_t *hash_iter_crear(const hash_t *hash) {
    hash_iter_t *iter = malloc(sizeof(hash_iter_t));

    if (iter == NULL) return NULL;

    iter->hash = hash;

    size_t pos = 0;
    while (iter->hash->tabla[pos].estado.estado_actual == VACIO) {
        pos++;
        if (pos > hash->largo - 1) break;
    }
    
    iter->pos_actual = pos;
    iter->act = &iter->hash->tabla[pos];
    return iter;
}

bool hash_iter_avanzar(hash_iter_t *iter) {
    if (hash_iter_al_final(iter)) {
        return false;
    
    } else {
        iter->pos_actual++;
    }

    while (!hash_iter_al_final(iter) && iter->hash->tabla[iter->pos_actual].estado.estado_actual != OCUPADO) {
        iter->pos_actual++;
    }

    iter->act = &iter->hash->tabla[iter->pos_actual];
    return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter) {
    if (!hash_iter_al_final(iter) && iter->hash->cantidad > 0) return iter->act->clave;
    return NULL;
}

bool hash_iter_al_final(const hash_iter_t *iter) {
    if (iter->hash->cantidad == 0) return true;
    return iter->pos_actual == iter->hash->largo;
}

void hash_iter_destruir(hash_iter_t *iter) {
    free(iter);
}
