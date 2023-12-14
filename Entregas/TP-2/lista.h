#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

struct lista;
typedef struct lista lista_t;

struct lista_iter;
typedef struct lista_iter lista_iter_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Devuelve verdadero si la lista no tiene elementos, false en caso contrario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento a la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, dato se encuentra primero en la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento al final de la lista. Devuelve false en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento en la última posición de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Elimina el primer elemento de la lista. Si la lista tiene elementos, se quita 
// el primer elemento y se devuelve su valor. Si la lista está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: si la lista no estaba vacía, se quita y se devuelve el valor del primer
// elemento. En caso contrario devuelve NULL.
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del último elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del último, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del último elemento de la lista, cuando la lista
// no está vacía, NULL en caso contrario.
void *lista_ver_ultimo(const lista_t* lista);

// Obtiene el largo de la lista.
// Pre: la lista fue creada.
// Post: se devolvio el largo de la lista.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

/* ******************************************************************
 *                   PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

// Crea un iterador externo.
// Pre: la lista fue creada.
// Post: devuelve un iterador.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza de a un elemento la lista. Si el elemento actual es NULL devuelve false ya que no se puede seguir iterando, en
// caso contrario devuelve true y se avanza al siguiente elemento.
// Pre: la lista fue creada y el iterador fue creado.
// Post: avanza un elemento.
bool lista_iter_avanzar(lista_iter_t *iter);

// Obtiene el valor actual al que apunta el iterador. Si la lista está vacía devuelve NULL.
// Pre: la lista fue creada y el iterador fue creado.
// Post: devuelve el valor al que apunta el iterador, en caso de que la lista esté vacía devuelve NULL.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Si se encuentra al final de la lista el iterador apunta a NULL ya que itero todos los elementos, en este caso 
// devuelve true. En caso contrario false.
// Pre: la lista fue creada y el iterador fue creado.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador externo.
// Pre: la lista fue creada y el iterador fue creado.
// Post: el iterador fue destruido.
void lista_iter_destruir(lista_iter_t *iter);

// Inserta un elemento en la lista. Devuelve true si se pudo hacer la insercion y en caso contrario devuelve false.
// El elemento insertado va a tomar la posicion del elemento al que se apunta.
// Pre: la lista fue creada y el iterador fue creado.
// Post: luego de una insercion, el iterador va a apuntar al nuevo elemento.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Obtiene el elemento actual al cual apunta el iterador y lo borra de la lista. Si la lista está vacía devuelve NULL.
// Pre: la lista fue creada y el iterador fue creado.
// Post: se devolvió el elemento al cual apunta el iterador y se lo eliminó de la lista. En caso de que la lista esté
// vacía, devolvió NULL.
void *lista_iter_borrar(lista_iter_t *iter);

/* ******************************************************************
 *                   PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

// Itera la lista y a cada nodo de la misma le aplica la funcion visitar() que recibe el dato del nodo actual y 
// un extra. La funcion visitar() devuelve true si se debe seguir iterando y false en caso contrario.
// Pre: la lista fue creada.
// Post: la lista se itero y a cada nodo se le aplico la funcion visitar()
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación realizada.
void pruebas_lista_estudiante(void);

#endif  // LISTA_H
