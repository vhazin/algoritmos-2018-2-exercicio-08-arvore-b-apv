#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define ORDEM 2

/* Estrutura dos nós das árvores */
typedef struct no_arvoreB {
  int isLeaf;
  int num_chaves; // quantidades de chaves contidas no nó
  int chaves[2 * ORDEM - 1]; //Chaves armazenadas no nó
  struct no_arvoreB *filhos[2 * ORDEM]; //Ponteiro para filhos
} arvoreB;

/* Protótiopos das funções */
arvoreB *insertArv(arvoreB *raiz, int chave);
void printArv(arvoreB *raiz);

int main(void){
  int val, ch;
  arvoreB *raiz;
      while (1) {
              printf("1. Inserir um nó na Árvore B\n");
              printf("2. Imprimir a Árvore B\n");
              printf("3. Sair\n");
              scanf("%d", &ch);
              switch (ch) {
                      case 1:
                              printf("Digite sua chave:");
                              scanf("%d", &val);
                              insertArv(raiz, val);
                              break;
                      case 2:
                              printf("%d", raiz->chaves[0]);
                              //printArv(raiz);
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

arvoreB* criarArvore(void)
{
  arvoreB raiz; 
  arvoreB *b = (arvoreB *)malloc(sizeof(raiz));
  b->isLeaf = 1;
  b->num_chaves = (2 * ORDEM - 1);
  return b;
}
 

//insere uma chave e o ponteiro para o filho da direita em um nó
arvoreB insere_chave(arvoreB *raiz,int info, arvoreB *filhodir)
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

  return *raiz;
}

//realiza a busca do nó para inserar a chave e faz as subdivisões quando necessárias
arvoreB *insere(arvoreB *raiz,int info,int *info_retorno)
{
  int i,j,pos,info_mediano; //auxiliar para armazenar a chave que irá subir para o pai
  arvoreB *temp, *filho_dir; //ponteiro para o filho e direita da chave

  if (raiz == NULL)
  {
    //O nó anterior é o ideal para inserar a nova chave (chegou em um nó folha)
    raiz->isLeaf = 1;
    *info_retorno = info;
    return(NULL);
  }else{
    pos = busca_binaria(raiz,info);
    if (raiz->num_chaves > pos && raiz->chaves[pos] == info)
    {
      printf("chave ja está contida na arvore");
      raiz->isLeaf = 0;
    }else{
      //Overflow. Precisa subdividir
      temp = (arvoreB *) malloc(sizeof(arvoreB));
      temp->num_chaves = 0;

      //incializa filhos com NULL
      for (i = 0; i < 2 * ORDEM; i++)
      temp->filhos[i] = NULL;

      //elemento mediano que vai subir para o pai
      info_mediano = raiz->chaves[ORDEM - 1];

      //insere metade do nó raiz no temp(efetua subdivisão)
      temp->filhos[0] = raiz->filhos[ORDEM - 1+1];
      for (i = ORDEM - 1 + 1; i < (2 * ORDEM - 1); i++)
        insere_chave(temp,raiz->chaves[i], raiz->filhos[i+1]);

      //atualiza nó raiz.
      for (i = ORDEM - 1; i<(2 * ORDEM - 1); i++)
      {
        raiz->chaves[i] = 0;
        raiz->filhos[i+1] = NULL;
      }
      raiz->num_chaves = ORDEM - 1;

      //verifica em qual nó será inserida a nova chave
      if (pos <= ORDEM - 1)
        insere_chave(raiz, *info_retorno,filho_dir);
      else insere_chave(temp,*info_retorno,filho_dir);

      //retorna o mediano para inserí-lo no nó pai e o temp como filho direito do mediano.
      *info_retorno = info_mediano;
      return temp;
    }
  }
}

arvoreB *insertArv(arvoreB *raiz,int info)
{
  int info_retorno,i;
  arvoreB *filho_dir,*nova_raiz;

  filho_dir = insere(raiz,info,&info_retorno);
  printf("f");
  if (raiz->isLeaf)
  { //Aumentará a altura da àrvore
  nova_raiz = (arvoreB *)malloc(sizeof(arvoreB));
  nova_raiz->num_chaves = 1;
  nova_raiz->chaves[0] = info_retorno;
  nova_raiz->filhos[0] = raiz;
  nova_raiz->filhos[1] = filho_dir;
  for (i =2; i<= (2 * ORDEM - 1); i++){
    nova_raiz->filhos[i] = NULL;
    }
    return(nova_raiz);
  }
  else return(raiz);
}

int busca_binaria(arvoreB *no,int info){
  int meio,i,f;
  
  i = 0;
  f = no->num_chaves-1;

  while (i <= f)
  {
    meio = (i + f) /2;
    if(no->chaves[meio] == info)
      return(meio); //encontrou. retorna a posição em que a chave está.
    else if (no->chaves[meio] > info)
      f = meio - 1;
      else i = meio + 1;
  }
  return (i); // não encontrou. retorna a posição do ponteiro para o filho.

}
bool busca(arvoreB *raiz,int info)
{
  arvoreB *no;
  int pos; //posição retornada pelo busca binaria.

  no = raiz;
  while (no != NULL)
  {
    pos = busca_binaria(no,info);
    if (pos < no->num_chaves && no->chaves[pos] == info)
      return(true);
    else no = no->filhos[pos];
  }
  return(false);

}

//Algoritmo de varredura em ordem
void em_ordem(arvoreB *raiz)
{
  int i;
  if (raiz != NULL)
  {
    for (i = 0; i < raiz->num_chaves; i++)
    {
      em_ordem(raiz->filhos[i]);
      printf("\n%d", raiz->chaves[i]);
    }
    em_ordem(raiz->filhos[i]);
  }
}

void printArv(arvoreB *raiz){
  for(int interacao = 0; interacao < raiz->num_chaves; interacao++){
    printf("%d", raiz->chaves[interacao]);
  }
  for(int i=0; i<= raiz->num_chaves; i++){
    printArv(raiz->filhos[i]);
  }
    /*for(int interacaoFilho = 0; interacaoFilho < 2 * ORDEM; interacaoFilho++){
      printf("%d |", raiz->chaves[interacaoFilho]);
    }
    printf(")");
  }*/
}
