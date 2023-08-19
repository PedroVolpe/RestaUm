//NOME: ERIC AKIO UCHIYAMADA                 TIA: 42107865
//NOME: PEDRO LOUREIRO MORONE BRANCO VOLPE   TIA: 42131936

#include <stdlib.h>
#include <stdio.h>

#define tam_vet 6

typedef struct node {
	int info[tam_vet];
	struct node* next;
} No;

typedef struct pilha {
	No *topo;
} Pilha;

Pilha* create_stack (void);
void push(Pilha *p, int elem[]);
int *pop(Pilha *p);
int empty (Pilha *p);
void print (Pilha *p);
void free_stack (Pilha *p);