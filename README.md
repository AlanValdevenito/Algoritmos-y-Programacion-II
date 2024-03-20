# Algoritmos y Programacion II

Algoritmos y Programacion II [2C 2021] - Entregas

## Temas de la materia

- Introduccion general: Punteros y Memoria dinámica. Administración de memoria dinámica. Comparación con memoria estática. Cuestiones adicionales (pasaje de funciones por parámetro, aritmética de punteros, piping y redirección de entrada, salida y errores). Herramientas (Valgrind, GDB, Makefile, uso Unix/Linux). 

- Complejidad algoritmica y recursividad: Complejidad Algorítmica (tiempo, y también espacio). División y Conquista. Teorema Maestro. 

- Tipos de Datos Abstractos: Conceptos de Tipos de Datos Abstractos. TDAs Básicos (TDA Vector, Pila, Cola, Lista enlazada). Implementaciones sobre arreglos y estructuras enlazadas.

- Algoritmos de ordenamiento: Ordenamientos Comparativos. Ordenamientos no comparativos (Counting Sort, Radix Sort, Bucket Sort). Características de ordenamientos (estabilidad, in place).

- TDA Conjunto y Diccionario, Hashing y Hashes: TDA Conjunto y Diccionario. Tablas de Hash. Resolución de colisiones con Hashing Abierto y Cerrado (probing lineal, cuadrático, multiple hashing, etc). Cuckoo Hashing. Hopscotch Hashing. Hashing Perfecto.

- Árboles e Implementación de diccionarios con Árboles: Árboles Binarios. Recorridos sobre árboles. Algoritmos sobre árboles. Árboles Binarios de Búsqueda, como implementación de diccionarios. Árboles auto balanceados (AVL).

- TDA Cola de Prioridad: Implementación con heaps binarios. Operaciones de heaps. Representación en árbol y en arreglo. Construcción de Heap a partir de un arreglo. Heapsort. 

- TDA Grafo: Aplicaciones. Operaciones y Representaciones (matriz de incidencia, matriz de adyacencia, listas de adyacencias, y combinaciones). Recorridos sobre Grafos (BFS, DFS). Ejemplos de uso de BFS y DFS. Orden topológico. Grafos bipartitos. Componentes fuertemente conexas (Algoritmo de Tarjan). Puntos de Articulación, otros.

- Algoritmos sobre grafos: Caminos mínimos (BFS, Algoritmo de Dijkstra y Algoritmo de BellmanFord). Árboles de tendido mínimo (Algoritmos de Prim y Kruskal). Estrategia Backtracking y aplicaciones sobre grafos (Coloreo, Camino Hamiltoniano).

## Compilacion

Ejecutar en una terminal:

```
$ gcc -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -o main *.c *.h
```

## Ejecucion

Ejecutar en una terminal:

```
$ ./main
```

## Valgrind

Ejecutar en una terminal:

```
$ valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./main
```

