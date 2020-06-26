typedef struct heap MinHeap;

MinHeap* heap_create(int max);

void swap(int i, int j, int *v);

void heap_free(MinHeap* h);

void fix_above(MinHeap* h, int pos, int* dist);

void min_heap_insert(MinHeap* h, int i, int* dist);

void fix_below(MinHeap* h, int* dist);

int min_heap_remove(MinHeap* h, int* dist);