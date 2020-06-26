#include <stdio.h>
#include <stdlib.h>
#include "fila_vet.h"


Fila* fila_cria (void)
{
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->n = 0; /* inicializa fila como vazia */
    f->ini = 0; /* escolhe uma posição inicial */
    return f;
}


void fila_insere (Fila* f, int info){
    int fim;
    if (f->n == TAM_MAX) { /* fila cheia: capacidade esgotada */
        printf("Capacidade da fila estourou.\n");
        exit(1); /* aborta programa */
    }

    /* insere elemento na próxima posição livre */
    fim = (f->ini + f->n) % TAM_MAX;
    f->vet[fim] = info;
    f->n++;
}

int fila_retira (Fila* f){
    int v;
    if (fila_vazia(f)) {
        printf("Fila vazia.\n");
        exit(1); /* aborta programa */
    }

    /* retira elemento do início */
    v = f->vet[f->ini];
    f->ini = (f->ini + 1) % TAM_MAX;
    f->n--;
    return v;
}


int fila_vazia (Fila* f)
{
    if(f->n == 0)
        return 1;
    return 0;
}


void fila_libera (Fila* f)
{
    free(f);
}


void fila_imprime (Fila* f){
    
    int i;
    int ini = (f->ini) % TAM_MAX;
    int fim = (f->ini + f->n) % TAM_MAX;
    
    for(i = ini; i < TAM_MAX && i < ini + f->n; i++)
        printf("%d", f->vet[i]);
    
    if(fim < ini)
        for(i = 0; i < fim; i++)
            printf("%d", f->vet[i]);
}
