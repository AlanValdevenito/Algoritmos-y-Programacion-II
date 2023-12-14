#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fun_aux.h"

/* ******************************************************************
 *                             MAIN
 * *****************************************************************/

int main(int argc, char* argv[]) {
    if (son_parametros_validos(argc)) {
        algogram(argv);
        return 0;
    }

    printf("%s\n", "Error: Cantidad erronea de parametros");
    return -1;
}