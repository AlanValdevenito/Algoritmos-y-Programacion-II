#ifndef FUNCIONES_AUX_H
#define FUNCIONES_AUX_H

#include <stdio.h>

/* Devuelve 1 si la cadena es de numeros enteros, en caso contrario devuelve 0. */
int es_numero(char *cadena);

/* Dado un tamaño n en bytes y el nombre de un archivo, divide todas las líneas del archivo en columnas de hasta n 
columnas y las imprime por salida estándar. */
int leer_archivo(FILE *archivo, int bytes);

#endif 
