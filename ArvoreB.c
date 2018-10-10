#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const ORDEM = 2;
  MAX_CHAVES = 2 * ORDEM - 1; //QUANTIDADE MÁXIMA DE CHAVES
  MAX_FILHOS = 2 * ORDEM; // QUANTIDADE MÁXIMA DE FILHOS
  MIN_OCUP = ORDEM - 1; // OCUPAÇÃO MINIMA EM CADA NÓ

typedef struct no_arvoreB {
  struct no_arvoreB *arvoreB;
  int num_chaves; // quantidades de chaves contidas no nó
  int chaves[MAX_CHAVES]; //Chaves armazenadas no nó
  struct no_arvoreB *filhos[MAX_FILHOS]; //Ponteiro para filhos
} arvoreB;
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
    raiz->chaves[k] = raiz->chaves[k-1];
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
      raiz->num_chaves = MIN_OCUP;

      //verifica em qual nó será inserida a nova chave
      if (pos <= MIN_OCUP)
        insere_chave(raiz, *info_retorno,filho_dir);
      else insere_chave(temp,*info_retorno,filho_dir);

      //retorna o mediano para inserí-lo no nó pai e o temp como filho direito do mediano.
      *info_retorno = info_mediano;
      return(temp);
    }
  }


}
arvoreB *insere_arvoreB(arvoreB *raiz,int info)
{
  bool h;
  int info_retorno,i;
  arvoreB *filho_dir,*nova_raiz;

  filho_dir = insere(raiz,info,&h,&info_retorno);
  if (h)
  { //Aumentará a altura da àrvore
  nova_raiz = (arvoreB *)malloc(sizeof(arvoreB));
  nova_raiz->num_chaves = 1;
  nova_raiz->chaves[0] = info_retorno;
  nova_raiz->filhos[0] = raiz;
  nova_raiz->filhos[1] = filho_dir;
  for (i =2; i<= MAX_CHAVES; i++)
    nova_raiz->filhos[i] = NULL;
    return(nova_raiz);
  }
  else return(raiz);
}

int main(void){


  return 0;
}