#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"




trie *nova_trie() {

  trie*t = malloc(sizeof(trie));
  t->father = NULL;
  t->existe =0; 

  int j; 
  for (j=0; j <Nel; j++){
    t->prox[j] = NULL; 
  }

  return t;
}

void insere_trie(trie *t, char *chave)
{

  int i;

  if (*chave==0) {
    t->existe =1;
  }
  else {

    if (t->prox[*chave - Minel]==NULL) {

      t->prox[*chave - Minel]= malloc(sizeof(trie));
      t->prox[*chave - Minel]->existe=0;
      t->prox[*chave-Minel]->father = t;

      for (i=0;i<Nel;i++) {
        t->prox[*chave - Minel]->prox[i]=NULL; 
      }
    }
    insere_trie(t->prox[*chave-Minel],chave+1);
  }
}

int existe_trie (trie *t, char *chave){
  
  if (!*chave){
    return t->existe;  
  }

  else if (t->prox[*chave - Minel]==NULL){
    return 0;
  }

  else {
    return existe_trie(t->prox[*chave - Minel], chave+1);
  }

}

void remover_trie(trie *t, char *chave)
{
  trie *no = t;
  int x = 0;
  
  while (no != NULL && chave[x])   
  {
    
    no = no->prox[chave[x] - Minel];
    x++;
  }

  if (no != NULL && no->existe)
  {
    no->existe = 0;

    int empty = 1;
    do
    {
      x--;
      
      int j;
      for (j = 0; j < Nel; j++)
      {
        if (no->prox[j] != NULL)
          empty = 0;
      }

      if (empty)
      {
        trie *f = no->father;

        if (f != NULL)
        {
          int x = chave[x] - Minel;
          f->prox[x] = NULL;
        }

        free(no);
        no= f;
      }

    } while (no != NULL && empty && !no->existe);
  }
}

void destroy_trie(trie *t){

  int i;
  for (i=0; i<Nel; i++){
    if (t->prox[i]== NULL){
      destroy_trie(t->prox[i]);
    }
  }

  free(t);
}
