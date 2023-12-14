#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include "red_social.h"
#include "abb.h"
#include "pila.h"
#include "hash.h"
#include "vector.h"
#include "heap.h"
#include "lista.h"

#include <stdlib.h>
#include <string.h>

/* Definicion del struct usuario */

typedef struct usuario {
    char* nombre;
    size_t id;
    heap_t* publicaciones_a_ver;
} usuario_t;

/* Definicion del struct post */

typedef struct post  {
    size_t id;
    char* texto;
    char* autor;
    abb_t* usuarios_like;
    size_t cantidad_likes;
} post_t;

/* Definicion del struct que guardaremos en el heap de cada usuario. Guarda informacion sobre la prioridad del post. */

typedef struct post_prioridad {
    post_t* post;
    size_t prioridad;
} post_prioridad_t;

/* Definicion del struct red social */

struct red_social {
    usuario_t* usuario_actual;
    hash_t* usuarios;
    vector_t* posts;
};

/* *****************************************************************
 *                     FUNCIONES AUXILIARES
 * *****************************************************************/

int cmp(const void* a, const void* b) {
    size_t prioridad_p1 = ((post_prioridad_t*) a)->prioridad;
    size_t prioridad_p2 = ((post_prioridad_t*) b)->prioridad;

    if (prioridad_p2 < prioridad_p1) {
        return -1;
    
    } else if (prioridad_p2 > prioridad_p1) {
        return 1;

    } else {
        size_t id_p1 = ((post_prioridad_t*) a)->post->id;
        size_t id_p2 = ((post_prioridad_t*) b)->post->id;

        if (id_p1 < id_p2) {
            return 1;
        }
        
        return -1;
    }

    return 0;
}

usuario_t* crear_usuario(size_t id, char* nombre) {
    usuario_t* usuario = malloc(sizeof(usuario_t));

    if(usuario == NULL){
        return NULL;
    }

    usuario->nombre = strdup(nombre);
    usuario->id = id;
    usuario->publicaciones_a_ver = heap_crear(cmp);
    return usuario;
}

void inicializar_hash_usuarios(hash_t* usuarios, vector_t* nombres) {
    for (size_t i = 0; i < vector_cantidad(nombres); i++) {
        char* usuario = vector_obtener(nombres, i);
        hash_guardar(usuarios, usuario, crear_usuario(i, usuario));
    }
}

void destruir_post_prioridad(void* struct_post_prioridad) {
    post_prioridad_t* post_prioridad = (post_prioridad_t*) struct_post_prioridad;
    free(post_prioridad);
}

void destruir_usuario(void* struct_usuario) {
    usuario_t* usuario = (usuario_t*) struct_usuario;
    heap_destruir(usuario->publicaciones_a_ver, destruir_post_prioridad);
    free(usuario->nombre);
    free(usuario);
}

post_t* crear_post(size_t id, char* texto, char* autor) {
    post_t* post = malloc(sizeof(post_t));

    if(post == NULL){
        return NULL;
    }

    post->id = id;
    post->texto = texto;
    post->autor = autor;
    post->usuarios_like = abb_crear(strcmp, NULL);
    post->cantidad_likes = 0;
    return post;
}

void destruir_post(void* struct_post) {
    post_t* post = (post_t*) struct_post;
    abb_destruir(post->usuarios_like);
    free(post->texto);
    free(post);
}

post_prioridad_t* crear_post_prioridad(post_t* post, size_t prioridad) {
    post_prioridad_t* post_prioridad = malloc(sizeof(post_prioridad_t));

    if(post_prioridad == NULL){
        return NULL;
    }

    post_prioridad->post = post;
    post_prioridad->prioridad = prioridad;
    return post_prioridad;
}

post_t *obtener_post(red_social_t* red_social, size_t id_post) {
    return (post_t*) vector_obtener(red_social->posts, id_post);
}

/* ******************************************************************
 *                  PRIMITIVAS DE LA RED SOCIAL
 * *****************************************************************/

red_social_t* rs_crear(vector_t* usuarios) {
    red_social_t* red_social = malloc(sizeof(red_social_t));

    if(red_social == NULL){
        return NULL;
    }

    red_social->usuario_actual = NULL;
    red_social->usuarios = hash_crear(destruir_usuario);
    red_social->posts = vector_crear();

    inicializar_hash_usuarios(red_social->usuarios, usuarios);
    return red_social;
}

bool rs_hay_usuario(red_social_t* red_social) {
    return red_social->usuario_actual != NULL;
}

bool rs_login(red_social_t* red_social, char* usuario) {
    if (rs_hay_usuario(red_social)) {
        return false;
    }

    if (!hash_pertenece(red_social->usuarios, usuario)) {
        return false;
    }

    red_social->usuario_actual = hash_obtener(red_social->usuarios, usuario);
    return true;
}

bool rs_logout(red_social_t* red_social) {
    if (!rs_hay_usuario(red_social)) {
		return false;
	}

	red_social->usuario_actual = NULL;
	return true;
}

bool rs_publicar_post(red_social_t* red_social, char* post_texto) {
    if (!rs_hay_usuario(red_social)) {
        return false;
    }

    size_t post_id = vector_cantidad(red_social->posts);
    char* post_texto_copia = strdup(post_texto);
    char* post_autor = red_social->usuario_actual->nombre;
    post_t* post_nuevo = crear_post(post_id, post_texto_copia, post_autor);
    vector_guardar(red_social->posts, post_nuevo);

    hash_iter_t* iter = hash_iter_crear(red_social->usuarios);
    while (!hash_iter_al_final(iter)) {
        usuario_t* actual = hash_obtener(red_social->usuarios, hash_iter_ver_actual(iter));
    
        if(red_social->usuario_actual->id != actual->id) {
            size_t afinidad = (size_t) abs((int) red_social->usuario_actual->id - (int) actual->id);
            post_prioridad_t* post_prioridad = crear_post_prioridad(post_nuevo, afinidad); 
            heap_encolar(actual->publicaciones_a_ver, post_prioridad);
        }

        hash_iter_avanzar(iter);
    }

    hash_iter_destruir(iter);
    return true;
}

size_t rs_obtener_id_siguiente_post(red_social_t* red_social) {
    if (!rs_hay_usuario(red_social)) return (size_t) -1;

    heap_t* publicaciones = red_social->usuario_actual->publicaciones_a_ver;
    post_prioridad_t* post_prioridad = (post_prioridad_t*) heap_desencolar(publicaciones);

    if (!post_prioridad) return (size_t) -1;
    
    size_t id = post_prioridad->post->id;
    free(post_prioridad);
    return id;
}

char *rs_obtener_texto_post(red_social_t* red_social, size_t id_post) {
    post_t* post = obtener_post(red_social, id_post);
    return post->texto;
}

char *rs_obtener_autor_post(red_social_t* red_social, size_t id_post) {
    post_t* post = obtener_post(red_social, id_post);
    return post->autor;
}

bool rs_likear_post(red_social_t* red_social, size_t id_post) {
    if (!rs_hay_usuario(red_social)) {
        return false;
    }

    post_t* post = vector_obtener(red_social->posts, id_post);

    if (post == NULL) {
        return false;
    }

    if (!abb_pertenece(post->usuarios_like, red_social->usuario_actual->nombre)) {
        char* usuario_nombre = red_social->usuario_actual->nombre;
        abb_guardar(post->usuarios_like, usuario_nombre, NULL);
        post->cantidad_likes++;
    }

    return true;
}

lista_t* rs_mostrar_likes_usuarios(red_social_t* red_social, size_t id_post) {
    post_t* post = (post_t*) vector_obtener(red_social->posts, id_post);
	if (!post) return NULL;

	abb_t* usuarios_like = post->usuarios_like;
	lista_t* lista = lista_crear();
	
    abb_iter_t* iter = abb_iter_in_crear(usuarios_like);
	while (!abb_iter_in_al_final(iter)) {
        char* usuario_nombre = (char*) abb_iter_in_ver_actual(iter);
		lista_insertar_ultimo(lista, (void*) usuario_nombre);
        abb_iter_in_avanzar(iter);
	}

	abb_iter_in_destruir(iter);
	return lista;
}

size_t rs_mostrar_likes_cantidad(red_social_t* red_social, size_t id_post) {
    post_t* post = (post_t*) vector_obtener(red_social->posts, id_post);
	if (!post) return (size_t )-1;

	return post->cantidad_likes;
}

void rs_destruir_red_social(red_social_t* red_social) {
    hash_destruir(red_social->usuarios);
    vector_destruir(red_social->posts, destruir_post);
	free(red_social);
}