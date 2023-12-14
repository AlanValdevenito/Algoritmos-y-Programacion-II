#ifndef _VECTOR_H
#define _VECTOR_H

#include <stdbool.h>
#include <stdlib.h>

/* *****************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

struct vector;  // Definición completa en vector.c
typedef struct vector vector_t;

/* *****************************************************************
 *                    PRIMITIVAS DEL VECTOR
 * *****************************************************************/

// Crea un vector vacio.
vector_t *vector_crear(void);

// Devuelve el elemento almacenado en el vector en la posicion pos.
// Devuelve NULL en caso de que pos sea una posición inválida.
// Pre: el vector fue creado.
// Post: Si pos es una posición válida se devolvió el elemento del vector
// almacenado en dicha posición y NULL en caso de que sea invalida.
void *vector_obtener(vector_t *vector, size_t pos);

// Almacena el valor en la posicion siguiente al ultimo elemento.
// Pre: el vector fue creado
// Post: se almacenó el valor. Devuelve false si la posición
// es inválida (fuera del rango del vector, que va de 0 a tamaño-1) y true si
// se guardó el valor con éxito.
bool vector_guardar(vector_t *vector, void* elemento);

// Dada una posición y un nuevo elemento, devuelve el elemento que estaba en dicha
// posición y en su lugar guarda el nuevo.
// Pre: el vector fue creado.
// Post: se reemplazó el elemento y se devolvió el que estaba antes en la posición
// pasada por parámetro. Devuelve NULL en caso de que la posición no sea válida.
void *vector_reemplazar(vector_t *vector, void* nuevo_elemento, size_t pos);

// Borra y devuelve el elemento almacenado en el vector en la posicion pos.
// Devuelve NULL en caso de que pos sea una posición inválida.
// Pre: el vector fue creado.
// Post: Se eliminó y devolvió el elemento almacenado en la posición pos,
// o NULL en caso de que pos no sea una posición válida.
void *vector_borrar(vector_t *vector, size_t pos);

// Devuelve el tamaño del vector
// Pre: el vector fue creado
size_t vector_largo(vector_t *vector);

// Devuelve la cantidad de elementos del vector.
// Pre: el vector fue creado
size_t vector_cantidad(vector_t *vector);

// Destruye el vector. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos del vector llama a destruir_dato.
// Pre: el vector fue creado. destruir_dato es una función capaz de destruir
// los datos del vector, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos del vector.
void vector_destruir(vector_t *vector, void (*destruir_dato)(void *));

#endif  // _VECTOR_H