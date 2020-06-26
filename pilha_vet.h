#define TAM_MAX 3320

typedef struct pilha {
    int topo;
    int vet[TAM_MAX]; 
} Pilha;

Pilha* pilha_cria (void);
void pilha_push (Pilha* p, int v);
int pilha_pop (Pilha* p);
int pilha_vazia (Pilha* p);
int pilha_tamanho(Pilha * p);
void pilha_libera (Pilha* p);
int pilha_topo(Pilha * p);
void pilha_imprimir(Pilha * p);
