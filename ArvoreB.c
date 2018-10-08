#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORDEM 4

typedef struct no{
    int num_chaves;
    int *chaves[ORDEM - 1];
    struct no *filhos[ORDEM];
} No;

int main(void){


  return 0;
}