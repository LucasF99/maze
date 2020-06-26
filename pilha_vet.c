
#include <stdio.h>
#include <stdlib.h>
#include "pilha_vet.h"

Pilha* pilha_cria ()
{
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    if (p==NULL) exit (1);
    p->topo = 0;
    return p;
}

void pilha_push (Pilha* p, int v)
{
    if (p->topo == TAM_MAX) {
        printf("Capacidade da pilha estourou.\n");
        exit(1); 
    }
    
    p->vet[p->topo] = v;
    p->topo++;
}

int pilha_pop (Pilha* p)
{
    int v;
    if (pilha_vazia(p))
    {
        printf("Pilha vazia.\n");
        exit(1); 
    }
    
    v = p->vet[p->topo-1];
    p->topo--;
    return v;
}

int pilha_vazia (Pilha* p)
{
    if(p->topo == 0)
        return 1;
    return 0;
}

int pilha_tamanho(Pilha * p) {
	return p->topo;
}


void pilha_libera (Pilha* p)
{
    int i;
    //for(i=0; i < p->topo; i++)
    //    free(p->vet[i]);
    free(p);
}



int pilha_topo(Pilha * p) {
	if (p->topo == 0) {
		//printf("Pilha vazia");
		return -1;
	}
	return p->vet[p->topo-1];
}

void pilha_imprimir(Pilha * p) {
	int i;
	printf("[ ");
	for(i=0; i<p->topo; i++) {
		printf("%d ", p->vet[i]);
	}
	printf("]\n");
}

