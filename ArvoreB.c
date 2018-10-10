#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include<conio.h>

int ORDEM = 2;
int MAX_CHAVES = 2 * ORDEM - 1; //QUANTIDADE MÁXIMA DE CHAVES
int MAX_FILHOS = 2 * ORDEM; // QUANTIDADE MÁXIMA DE FILHOS
int MIN_OCUP = ORDEM - 1; // OCUPAÇÃO MINIMA EM CADA NÓ

/* Estrutura dos nós das árvores */
typedef struct no_arvoreB {
  struct no_arvoreB *arvoreB;
  int num_chaves; // quantidades de chaves contidas no nó
  int chaves[MAX_CHAVES]; //Chaves armazenadas no nó
  struct no_arvoreB *filhos[MAX_FILHOS]; //Ponteiro para filhos
} arvoreB;

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

//insere uma chave e o ponteiro para o filho da direita em um nó
void insere_chave(arvoreB *raiz,int info, arvoreB *filhodir)
{
  int k,pos;
  
  //busca para obter a posição ideal para inserar a nova chave
  pos = busca_binaria(raiz,info);
  k = raiz->num_chaves;

  //realiza o remanejamento para manter as chaves ordenadas
  while (k > pos && info < raiz->chaves[k-1])
  {
    raiz->chaves[k] = raiz->[k-1];
    raiz->filhos[k+1] = raiz->filhos[k];
    k--;
  }
  //insere a chave na posição ideal
  raiz-> chaves[pos] = info;
  raiz-> filhos[pos+1] = filhodir;
  raiz->num_chaves++;
}

//realiza a busca do nó para inserar a chave e faz as subdivisões quando necessárias
arvoreB *insere(arvoreB *raiz,int info,bool *h,int *info_retorno)
{
  int i,j,pos,info_mediano; //auxiliar para armazenar a chave que irá subir para o pai
  arvoreB *temp, *filho_dir; //ponteiro para o filho e direita da chave

  if (raiz == NULL)
  {
    //O nó anterior é o ideal para inserar a nova chave (chegou em um nó folha)
    *h = true;
    *info_retorno = info;
    return(NULL);
  }else{
    pos = busca_binaria(raiz,info);
    if (raiz->num_chaves > pos && raiz->chaves[pos] == info)
    {
      printf("chave ja está contida na arvore");
      *h = false;
    }else{
      //Overflow. Precisa subdividir
      temp = (arvoreB *) malloc(sizeof(arvoreB));
      temp->num_chaves = 0;

      //incializa filhos com NULL
      for (i = 0; i < MAX_FILHOS; i++)
      temp->filhos[i] = NULL;

      //elemento mediano que vai subir para o pai
      info_mediano = raiz->chaves[MIN_OCUP];

      //insere metade do nó raiz no temp(efetua subdivisão)
      temp->filhos[0] = raiz->filhos[MIN_OCUP+1];
      for (i = MIN_OCUP + 1; i < MAX_CHAVES; i++)
        insere_chave(temp,raiz->chaves[i], raiz->filhos[i+1]);

      //atualiza nó raiz.
      for (i = MIN_OCUP; i<MAX_CHAVES; i++)
      {
        raiz->chaves[i] = 0;
        raiz->filhos[i+1] = NULL;
      }
      raiz-
    }
  }


}