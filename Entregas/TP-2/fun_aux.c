#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdlib.h>
#include <string.h>
#include "fun_aux.h"

/* ******************************************************************
 *                     FUNCIONES AUXILIARES
 * *****************************************************************/

void reemplazar_caracter(char* linea) {
    if(linea[strlen(linea) - 1] == '\n'){
        linea[strlen(linea) - 1] = '\0';
    }
}

vector_t* leer_archivo(FILE* mi_archivo) {
    if (mi_archivo == NULL) {
        printf("%s\n", "Error: archivo fuente inaccesible");
        return NULL;
    }

    vector_t* usuarios = vector_crear();
    char* linea = NULL;
    size_t tam;
    
    while ((getline(&linea, &tam, mi_archivo)) != EOF) {
        reemplazar_caracter(linea);
        char* usuario = strdup(linea);
        vector_guardar(usuarios, usuario);
    }

    free(linea);
    fclose(mi_archivo);
    return usuarios;
}

void login(red_social_t* red_social, char* usuario) {
    if (rs_hay_usuario(red_social)) {
        printf("%s\n", "Error: Ya habia un usuario loggeado");
        return;
    }

    if (!rs_login(red_social, usuario)) {
        printf("%s\n", "Error: usuario no existente");
        return;
    }

    printf("Hola %s\n", usuario);
}

void logout(red_social_t* red_social) {
    if (!rs_logout(red_social)) {
        printf("%s\n", "Error: no habia usuario loggeado");
        return;
    }

    printf("Adios\n");
}

void publicar(red_social_t* red_social, char* post_texto) {

    if (!rs_publicar_post(red_social, post_texto)) {
        printf("%s\n", "Error: no habia usuario loggeado");
        return;
    }

    printf("%s\n", "Post publicado");
}

void ver_proximo_post(red_social_t* red_social) {
    size_t id_post = rs_obtener_id_siguiente_post(red_social);

    if (id_post == -1) {
        printf("%s\n", "Usuario no loggeado o no hay mas posts para ver");
        return;
    }

    char* texto = rs_obtener_texto_post(red_social, id_post);
    char* autor = rs_obtener_autor_post(red_social, id_post);
    size_t cantidad_likes = rs_mostrar_likes_cantidad(red_social, id_post);

    printf("Post ID %ld\n", id_post);
    printf("%s dijo: %s\n", autor, texto);
    printf("Likes: %ld\n", cantidad_likes);
}

void actualizar_likes(red_social_t* red_social, size_t id) {
    if (!rs_likear_post(red_social, id)) {
        printf("%s\n", "Error: Usuario no loggeado o Post inexistente");
        return;
    }

    printf("%s\n", "Post likeado");
}

void mostrar_likes(red_social_t* red_social, size_t id) {
    lista_t* usuarios_like = rs_mostrar_likes_usuarios(red_social, id);
    size_t cantidad_likes = rs_mostrar_likes_cantidad(red_social, id);
    
    if (!usuarios_like || cantidad_likes == 0) {
        printf("%s\n", "Error: Post inexistente o sin likes");

        if (cantidad_likes == 0) {
            lista_destruir(usuarios_like, NULL);
        }
        
        return;
    }

    printf("El post tiene %ld likes:\n", cantidad_likes);

    lista_iter_t* iter = lista_iter_crear(usuarios_like);
    while (!lista_iter_al_final(iter)) {
        printf("	%s\n", (char*) lista_iter_ver_actual(iter));
        lista_iter_avanzar(iter);
    }
    
    lista_iter_destruir(iter);
    lista_destruir(usuarios_like, NULL);
}

bool son_parametros_validos(int argc) {
    if (argc != 2) {
        return false;
    }
    return true;
}

void leer_entrada(red_social_t* red_social) {
    char* comandos[6] = {"login", "logout", "publicar", "ver_siguiente_feed", "likear_post", "mostrar_likes"}; 
    char* linea = NULL;
    size_t tam;
    while(getline(&linea, &tam, stdin) != EOF) {
        reemplazar_caracter(linea);

        if(strcmp(linea, comandos[0]) == 0) {
            if (getline(&linea, &tam, stdin) != EOF) {
                reemplazar_caracter(linea);
                login(red_social, linea);
            }
            
        } else if(strcmp(linea, comandos[1]) == 0) {
            logout(red_social);
        
        } else if(strcmp(linea, comandos[2]) == 0) {
            if (getline(&linea, &tam, stdin) != EOF) {
                reemplazar_caracter(linea);
                publicar(red_social, linea);
            }
        
        } else if(strcmp(linea, comandos[3]) == 0) {
            ver_proximo_post(red_social);
        
        } else if(strcmp(linea, comandos[4]) == 0) {
            if (getline(&linea, &tam, stdin) != EOF) {
                reemplazar_caracter(linea);
                size_t id = (size_t) atoi(linea);
                actualizar_likes(red_social, id);
            }
        
        } else if(strcmp(linea, comandos[5]) == 0) {
            if (getline(&linea, &tam, stdin) != EOF) {
                reemplazar_caracter(linea);
                size_t id = (size_t) atoi(linea);
                mostrar_likes(red_social, id);
            }

        } else {
            printf("%s\n", "Error: Comando no valido");
        }
    }

    free(linea);
}

void algogram(char* argv[]) {
    FILE* mi_archivo = fopen(argv[1], "r");
    vector_t* usuarios = leer_archivo(mi_archivo);
    red_social_t* algogram = rs_crear(usuarios);
    vector_destruir(usuarios, free);

    leer_entrada(algogram);
    rs_destruir_red_social(algogram);
}
