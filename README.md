# Algoritmos y Programacion II

Algoritmos y Programacion II [2C 2021] - Entregas

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

