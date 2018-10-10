#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORDEM 6

typedef struct no{
    int num_chaves;
    int *chaves[ORDEM - 1];
    struct no *filhos[ORDEM];
} No;

int ORDEM = 2;
int MAX_CHAVES = 2 * ORDEM - 1; //QUANTIDADE MÁXIMA DE CHAVES
int MAX_FILHOS = 2 * ORDEM; // QUANTIDADE MÁXIMA DE FILHOS
int MIN_OCUP = ORDEM - 1; // OCUPAÇÃO MINIMA EM CADA NÓ

typedef struct no_arvoreB {
  struct no_arvoreB *arvoreB;
  int num_chaves; // quantidades de chaves contidas no nó
  int chaves[MAX_CHAVES]; //Chaves armazenadas no nó
  struct no_arvoreB *filhos[MAX_FILHOS]; //Ponteiro para filhos
} arvoreB;


void splitARV(arvoreB x, int i) {

  int z = (arvoreB *) malloc(sizeof(arvoreB)), t = ORDEM / 2;
  arvoreB y = x.chaves[i];
  y.chaves = z.chaves;
  z.num_chaves = t - 1;
  for (int j = 0; j < (t - 1); j++) {
    z.chaves[j] = y.chaves[j + t];
  }

  if (y.filhos != NULL) {
    for (int j = 0; j < (t - 1); j++) {
      z.filhos[j] = y.filhos[j + t];
    }
    y.num_chaves = t - 1;
  }

  for (int j = x.num_chaves + 1; j >= i + 1; j--) {
    x.filhos[j + 1] = x.filhos[j];

  }

  x.chave[i + 1] = z;

  for (int j = x.num_chaves; j >= i; j--) {
    x.chaves[j + 1] = x.chaves[j];
  }

  x.chaves[i] = y.chaves[t];

  x.num_chaves = x.num_chaves + 1;

}

int main(void){


  return 0;
}
