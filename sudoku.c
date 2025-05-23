#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int i, j, k, p;
  for (i = 0; i < 9; i++)
  {
    int bandera[10] = {0};
    for (k = 0; k < 9; k++)
    {
      int aux = n->sudo[i][k];
      if (aux != 0)
      {
        if (bandera[aux]) return 0;
        bandera[aux] = 1;
      }
    }
  }

  for (i = 0; i < 9; i++)
  {
    int bandera[10] = {0};
    for (k = 0; k < 9; k++)
    {
      int aux = n->sudo[k][i];
      if (aux != 0)
      {
        if (bandera[aux]) return 0;
        bandera[aux] = 1;
      }
    }
  }

  for (i = 0; i < 9; i++) 
  {
    int bandera[10] = {0};
    for (k = 0; k < 9; k++) 
    {
      p = 3 * (i / 3) + (k / 3);
      j = 3 * (i % 3) + (k % 3);
      int val = n->sudo[p][j];
      if (val != 0) 
      {
        if (bandera[val]) return 0;
        bandera[val] = 1;
      }
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n)
{
  List* lista = createList();
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0 ; j < 9; j++)
    {
      if(n->sudo[i][j]==0)
      {
        for(int k = 1; k <= 9; k++)
        {
          Node* nuevo = copy(n);
          nuevo->sudo[i][j] = k;
          if(is_valid(nuevo))
          {
            pushBack(lista, nuevo);
          }
        }
        return lista;
      }
    }
  }
  return lista;
}


int is_final(Node* n){
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      if (n->sudo[i][j] == 0)
        return 0;
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* pila = createStack();
  push(pila, initial);
  while(!is_empty(pila))
  {
    Node* nodo = top(pila);
    pop(pila);
    (*cont)++;
    if(is_final(nodo)) return nodo;
    List* adj = get_adj_nodes(nodo);
    for(Node* node = first(adj); node != NULL; node = next(adj))
    {
      push(pila, node);
    }
    clean(adj);
  }

  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/