#ifndef ABB_H
#define ABB_H

#include <stdbool.h>
#include <stddef.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct abb abb_t;

typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);

typedef struct abb_iter abb_iter_t;

/* ******************************************************************
 *                    PRIMITIVAS DEL ABB
 * *****************************************************************/

// Crea el ABB.
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

// Guarda un elemento en el arbol, si la clave ya se encuentra en la
// estructura, la reemplaza. De no poder guardarlo devuelve false.
// Pre: La estructura ABB fue inicializada.
// Post: Se almacenó el par (clave, dato).
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

// Borra un elemento del ABB y devuelve el dato asociado. Devuelve
// NULL si el dato no estaba.
// Pre: La estructura ABB fue inicializada.
// Post: El elemento fue borrado de la estructura y se lo devolvió,
// en el caso de que estuviera guardado.
void *abb_borrar(abb_t *arbol, const char *clave);

// Dada una clave, devuelve el dato asociado. Si la clave no se
// encuentra en el ABB devuelve NULL.
// Pre: La estructura ABB fue inicializada.
// Post: Se devolvió el dato asociado a la clave, en el caso de
// que se encuentre la clave.
void *abb_obtener(const abb_t *arbol, const char *clave);

// Devuelve true si la clave se encuentra en el ABB, false en caso contrario.
// Pre: La estructura ABB fue inicializada.
bool abb_pertenece(const abb_t *arbol, const char *clave);

// Devuelve la cantidad de elementos del ABB.
// Pre: La estructura ABB fue inicializada.
size_t abb_cantidad(const abb_t *arbol);

void abb_destruir(abb_t *arbol);

/* ******************************************************************
 *                   PRIMITIVAS DEL EXTERNO
 * *****************************************************************/

// Crea un iterador externo.
// Pre: el abb fue creado.
// Post: devuelve un iterador.
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

// Avanza de a un elemento del abb inorder. Si el elemento actual es NULL devuelve false ya que no se puede seguir 
// iterando, en caso contrario devuelve true y se avanza al siguiente elemento.
// Pre: el ABB fue creado y el iterador fue creado.
// Post: avanza un elemento.
bool abb_iter_in_avanzar(abb_iter_t *iter);

// Obtiene el valor actual al que apunta el iterador. Si el ABB está vacio devuelve NULL.
// Pre: el ABB fue creado y el iterador fue creado.
// Post: devuelve el valor al que apunta el iterador, en caso de que el ABB esté vacío devuelve NULL.
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

// Si se encuentra al final del ABB el iterador apunta a NULL ya que itero todos los elementos, en este caso 
// devuelve true. En caso contrario false.
// Pre: el ABB fue creado y el iterador fue creado.
bool abb_iter_in_al_final(const abb_iter_t *iter);

// Destruye el iterador externo.
// Pre: el ABB fue creado y el iterador fue creado.
// Post: el iterador fue destruido.
void abb_iter_in_destruir(abb_iter_t* iter);

/* ******************************************************************
 *                   PRIMITIVAS DEL INTERNO
 * *****************************************************************/

// Itera el ABB inorder y a cada nodo de la misma le aplica la funcion visitar() que recibe la clave, el dato y 
// un extra. La funcion visitar() devuelve true si se debe seguir iterando y false en caso contrario.
// Pre: el ABB fue creado.
// Post: el ABB se itero inorder y a cada nodo se le aplico la funcion visitar().
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

#endif  // ABB_H
