#include <stdio.h>
#include <stdlib.h>
#include "funciones_aux.h"

int main(int argc, char* argv[]){

    if(argc < 2 || es_numero(argv[1]) == 0){
        fprintf(stderr, "%s\n", "Error: Cantidad erronea de parametros");
        return -1;
    }

    int cant_bytes = atoi(argv[1]);

    if(argc == 3){
        FILE *mi_archivo = fopen(argv[2], "r");

        if(mi_archivo == NULL){
            fprintf(stderr, "%s\n", "Error: archivo fuente inaccesible");
            return -1;
        }

        leer_archivo(mi_archivo, cant_bytes);
    }

    if(argc == 2){
        leer_archivo(stdin, cant_bytes);
    }

    return 0;
}
