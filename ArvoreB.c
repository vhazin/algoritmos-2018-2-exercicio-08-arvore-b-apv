#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>

#define ORDEM 6

/* Estrutura dos nós das árvores */
typedef struct no{
    int num_chaves;
    int *chaves[ORDEM - 1];
    struct no *filhos[ORDEM];
} No;

/* Protótiopos das funções */
insertArv(no raiz, int chave);
printArv(no raiz);


int main(void){
  clrscr();
  int val, ch;
      while (1) {
              printf("1. Inserir um nó na Árvore B\n");
              printf("2. Imprimir a Árvore B\n");
              printf("3. Sair\n");
              scanf("%d", &ch);
              switch (ch) {
                      case 1:
                              printf("Digite sua chave:");
                              scanf("%d", &val);
                              insertArv(*raiz, val);
                              break;
                      case 2:
                              printArv(*raiz);
                              break;
                      case 3:
                              exit(0);
                      default:
                              printf("Você escolheu uma opção inválida!!\n");
                              break;
              }
              printf("\n");
      }

  return 0;
}