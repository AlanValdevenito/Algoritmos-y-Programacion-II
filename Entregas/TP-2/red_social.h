#ifndef RED_SOCIAL_H
#define RED_SOCIAL_H

#include <stdbool.h>  // bool
#include <stddef.h>   // size_t
#include "lista.h"
#include "vector.h"

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* Tipo utilizado para la red social */
typedef struct red_social red_social_t;

/* ******************************************************************
 *                 PRIMITIVAS DE LA RED SOCIAL
 * *****************************************************************/

// Inicializa el TDA. Recibe un vector donde estarán los nombres de cada usuario. 
// El usuario actual (loggeado) sera NULL inicialmente.
red_social_t* rs_crear(vector_t* posts);

// Devuelve true si hay un usuario loggeado actualmente. En caso contrario devuelve false.
bool rs_hay_usuario(red_social_t* red_social);

// Inicia sesión. Recibe el usuario que quiere loggearse y actualiza el usuario actual. 
// En caso de que ya haya un usuario loggeado o no exista devuelve false.
// Complejidad O(1).
bool rs_login(red_social_t* red_social, char* usuario);

// Cierra sesión. El usuario conectado actualmente será NULL. En caso de que no haya usuario loggeado devuelve false.
// Complejidad O(1).
bool rs_logout(red_social_t* red_social); 

// Publica un post. Recibe el texto de la publicación, lo agrega junto a los demás posts y también a los posts que 
// deben ver los usuarios. En caso de que no haya un usuario loggeado devuelve false.
// Complejidad O(u log (p)).
bool rs_publicar_post(red_social_t* red_social, char* post); 

// Devuelve el ID del próximo post que puede ver el usuario actual.
// En caso de que no haya ningún usuario loggeado o no haya ningún post para ver devuelve -1.
// Complejidad O(log p).
size_t rs_obtener_id_siguiente_post(red_social_t* red_social);

// Dado un ID, devuelve el texto del post correspondiente a dicho id.
// Devuelve NULL en caso de que el ID no sea válido.
char* rs_obtener_texto_post(red_social_t* red_social, size_t id_post);

// Dado un id, devuelve el autor del post correspondiente a dicho id.
// Devuelve NULL en caso de que el ID no sea válido.
char* rs_obtener_autor_post(red_social_t* red_social, size_t id_post);

// Likea un post. Recibe el ID del post a likear y actualiza los likes. 
// En caso de no haber un usuario loggeado o no existir el post devuelve false.
// Complejidad O(log u).
bool rs_likear_post(red_social_t* red_social, size_t id_post);

// Muestra los usuarios que dieron like. Recibe el ID del post a mostrar y nos devuelve una lista con los usuarios 
// que dieron like a dicha publicación. En caso de no existir el post devuelve NULL.
// COmplejidad O(u).
lista_t* rs_mostrar_likes_usuarios(red_social_t* red_social, size_t id_post); 

// Muestra la cantidad de likes. Recibe el ID del post a mostrar, y nos devuelve la cantidad de likes de dicha 
// publicación. En caso de no existir el post o no tener likes devuelve NULL.
size_t rs_mostrar_likes_cantidad(red_social_t* red_social, size_t id_post); 

// Destruye la red social liberando toda la memoria pedida (hash y vector).
void rs_destruir_red_social(red_social_t* red_social); 

#endif  // RED_SOCIAL_H
