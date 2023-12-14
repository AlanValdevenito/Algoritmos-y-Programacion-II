#include "tp0.h"
#include <stdio.h>

/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap(int *x, int *y){
  int intercambiar = *x;
  *x = *y;
  *y = intercambiar;
}

int maximo(int vector[], int n){
  if(n > 0){
    int pos_max = 0;
    for(int i = 1; i < n; i++){
      if(vector[i] > vector[pos_max]){
        pos_max = i;
      }
    }
    return pos_max;
  }
  else{
    return -1;
  }
}

int _comparar(int vector1[], int n1, int vector2[], int n2, int i){

  if(n1 == 0 || n2 == 0){
    if(n1 == 0 && n2 != 0){
        return -1;
    }
    if(n2 == 0 && n1 != 0){
      return 1;
    }
    return 0;
  }

  if (vector1[i] > vector2[i]){
      return 1;    
  }

  if (vector2[i] > vector1[i]){
      return -1;    
  }

  return _comparar(vector1, n1-1, vector2, n2-1, i+1);
}

int comparar(int vector1[], int n1, int vector2[], int n2){
  return _comparar(vector1, n1, vector2, n2, 0);
}

void seleccion(int vector[], int n){
  int pos_final = n;

  while(pos_final > 0){
    int max = maximo(vector, pos_final);
    pos_final = (pos_final - 1);
    swap(&vector[max], &vector[pos_final]);
  }
}
