#include <stdio.h>
#include <stdlib.h>

#include "min_heap.h"

struct heap {
	int *v;
	int max;
	int pos;
};

MinHeap* heap_create(int max) {
	MinHeap* h = malloc(sizeof(MinHeap));
	h->max = max;
	h->pos = 0;
	h->v = malloc(max * sizeof(int));
}

void swap(int i, int j, int *v) {
	int aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

void heap_free(MinHeap* h) {
	free(h->v);
	free(h);
}

void fix_above(MinHeap* h, int pos, int* dist) {
	int parent;
	while (pos > 0) {
		parent = (pos-1)/2;
		if (dist[h->v[parent]] > dist[h->v[pos]])
			swap(pos, parent, h->v);
		else
			break;
		pos = parent;
	}
}

void min_heap_insert(MinHeap* h, int i, int* dist) {
	if (h->pos < h->max) {
		h->v[h->pos] = dist[i];
		fix_above(h, h->pos, dist);
		h->pos++;
	} else {
		printf("MinHeap cheio\n");
		exit(1);
	}
}

void fix_below(MinHeap* h, int* dist) {
	int parent = 0;
	int child_l, child_r, child;

	while(2 * parent+1 < h->pos) {
		child_l = (2 * parent) + 1;
		child_r = (2 * parent) + 2;

		if (child_r >= h->pos)
			child_r = child_l;

		if (dist[h->v[child_l]] < dist[h->v[child_r]])
			child = child_l;
		else
			child = child_r;

		if (dist[h->v[parent]] > dist[h->v[child]])
			swap(child, parent, h->v);
		else
			break;

		parent = child;
	}
}

int min_heap_remove(MinHeap* h, int* dist) {
	if (h->pos > 0) {
		int top = h->v[0];
		h->v[0] = h->v[h->pos-1];
		h->pos--;
		fix_below(h, dist);
		return top;
	} else {
		printf("MinHeap vazio!\n");
		return -1;
	}
}