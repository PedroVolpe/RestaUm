//NOME: ERIC AKIO UCHIYAMADA                 TIA: 42107865
//NOME: PEDRO LOUREIRO MORONE BRANCO VOLPE   TIA: 42131936

#include "pilha.h"

Pilha* create_stack (void) {
	Pilha *p = (Pilha*)malloc(sizeof(Pilha));
	p->topo = NULL;
	return p;
}

void push(Pilha *p, int elem[]) {
	No *n = (No*)malloc(sizeof(No));
  for(int i = 0;i < tam_vet;i++)
	   n->info[i] = elem[i];
	n->next = p->topo;
	p->topo = n;
}

int *pop(Pilha *p){
	if(empty(p)) { return NULL; }
	No *n = p->topo;
  int elem[tam_vet];
  for (int i = 0;i < tam_vet;i++){
    elem[i] = n->info[i];
  }
	p->topo = n->next;
  
	free(n);
  n = NULL;
	return elem;
}

int empty (Pilha *p) {
	return (p->topo == NULL);
}

void print (Pilha *p) {
	No *n;
	for (n=p->topo; n!=NULL; n=n->next) {
    for(int j = 0;j < tam_vet;j++){
      printf("|%d", n->info[j]);
    }
    printf("|\n");
	}
}

void free_stack (Pilha *p) {
	No *n = p->topo;
	while (n != NULL) {
		No *temp = n->next;
		free(n); /*desalocando os nos*/
		n = temp;
	}
	free (p); /*desalocando a pilha*/
}