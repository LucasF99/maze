
#define TAM_MAX 3320 /* número máximo de elementos */

typedef struct fila {
    int n;
    int ini;
    int vet[TAM_MAX];
} Fila;


Fila* fila_cria (void);

void fila_insere (Fila* f, int info);

int fila_retira (Fila* f);

int fila_vazia (Fila* f);

void fila_libera (Fila* f);

void fila_imprime (Fila* f);