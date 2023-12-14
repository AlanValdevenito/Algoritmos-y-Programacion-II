#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funciones_aux.h"

int es_numero(char *cadena){

    for(int i = 0; cadena[i] != '\0'; i++){
        if(isdigit(cadena[i]) == 0){
            return 0;
        }
    }
    return 1;
}

int leer_archivo(FILE *archivo, int bytes){

    int tam_buffer = bytes + 1; 
    char cadena[tam_buffer];

    while((fgets(cadena, tam_buffer, archivo)) != NULL){

        if(cadena[strlen(cadena) - 1] == '\n'){
            cadena[strlen(cadena) - 1] = '\0';
        }

        if(cadena[0] != '\0'){
            fprintf(stdout, "%s\n", cadena);
        }
    }

    fclose(archivo);
    return 0;
}
