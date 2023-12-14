#ifndef FUNCIONES_AUX_H
#define FUNCIONES_AUX_H

#include <stdio.h>

#include "red_social.h"

// Recibe una linea de texto y reemplaza su ultimo caracter '\n' por un '\0'.
void reemplazar_caracter(char* linea);

// Recibe un archivo y lee su contenido. Devuelve un vector con lo que guardaba dicho archivo.
// En caso de error devuelve NULL.
vector_t* leer_archivo(FILE* mi_archivo);

// Funcion encargada de conectar al usuario. 
// Recibe como parametros la red social y el usuario que desea conectarse.
// En caso de error se le informara al usuario.
void login(red_social_t* red_social, char* usuario);

// Funcion encargada de desconectar al usuario actual, si es que existe. 
// Recibe como parametros la red social.
// En caso de error se le informara al usuario.
void logout(red_social_t* red_social);

// Funcion encargada de publicar un nuevo post. 
// Recibe como parametros la red social y el texto del nuevo post.
// En caso de error se le informara al usuario.
void publicar(red_social_t* red_social, char* post_texto);

// Funcion encargada de mostrar posts en el feed.
// Recibe como parametros la red social.
// En caso de error se le informara al usuario.
void ver_proximo_post(red_social_t* red_social);

// Funcion encargada de actualizar los likes de un post.
// Recibe como parametros la red social y el ID del post a likear.
// En caso de error se le informara al usuario.
void actualizar_likes(red_social_t* red_social, size_t id);

// Funcion encargada de mostrar los likes de un post (cantidad y que usuarios le dieron like).
// Recibe como parametros la red social y el ID del post en cuestion.
// En caso de error se le informara al usuario.
void mostrar_likes(red_social_t* red_social, size_t id);

// Funcion encargada de comprobar si los parametros son validos o no.
// Recibe un numero entero y si este es distinto de 2 la funcion devolvera false.
// En caso de que el numero entero sea exactamente igual a 2 la funcion devolvera true.
bool son_parametros_validos(int argc);

// Se encaga de leer lo que el usuario ingresa en la terminal para interactuar con la red social AlgoGram.
void leer_entrada(red_social_t* red_social);

// Funcion encargada de inicializar la red social.
void algogram(char* argv[]);

#endif 
