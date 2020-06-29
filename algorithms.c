#include <stdio.h>
#include <stdlib.h>
#include "algorithms.h"
#include "min_heap.h"

#define SHOW_PROCESSING 0
#define DELAY 5

int dfs(int v, PlayerDef* player, MazeDef* maze, int visited[maze_getGraphV(maze)]){

	int state = 0;
	
	int w;
	visited[v] = 1;

	player->current_vertex = v;
	player->current_y = vertex_to_map_y(player->current_vertex, maze_getFileCols(maze));
	player->current_x = vertex_to_map_x(player->current_vertex, maze_getFileCols(maze));
	player->steps++;
	 
	if(SHOW_PROCESSING) {
		display(player, maze);
		printf(" >> Executando DFS\n");
		
		msleep(DELAY);
	}
	
	if(maze_getFileTile(maze, player->current_y, player->current_x) == 'F')
		return 1;

	for (w = 0; w < maze_getGraphV(maze); w++){
		if (maze_getGraphEdge(maze, v,w) && !visited[w]){
			state = dfs(w, player, maze, visited);
			if(state)
				break;
		}
	}
	
	return state;
}


int pilha_dfs(Pilha* pilha, PlayerDef* player, MazeDef* maze, int visited[maze_getGraphV(maze)]){

	if(pilha_vazia(pilha))
		return 0;

	int state = 0;
	int v = pilha_pop(pilha);
	int w;
	visited[v] = 1;

	player->current_vertex = v;
	player->current_y = vertex_to_map_y(player->current_vertex, maze_getFileCols(maze));
	player->current_x = vertex_to_map_x(player->current_vertex, maze_getFileCols(maze));
	player->steps++;
	 
	if(SHOW_PROCESSING) {
		display(player, maze);
		printf(" >> Executando PILHA_DFS\n");
		
		msleep(DELAY);
	}

	if(maze_getFileTile(maze, player->current_y, player->current_x) == 'F')
		return 1;

	for (w = 0; w < maze_getGraphV(maze); w++){
		if (maze_getGraphEdge(maze, v,w) && !visited[w]){
			pilha_push(pilha, w);
		}
	}

	state = pilha_dfs(pilha, player, maze, visited);
	
	return state;
}


int bfs(Fila* fila,  PlayerDef* player, MazeDef* maze, int visited[maze_getGraphV(maze)]){

	if(fila_vazia(fila))
		return 0;

	int state = 0;
	int v = fila_retira(fila);
	int w;
	visited[v] = 1;

	player->current_vertex = v;
	player->current_y = vertex_to_map_y(player->current_vertex, maze_getFileCols(maze));
	player->current_x = vertex_to_map_x(player->current_vertex, maze_getFileCols(maze));
	player->steps++;
	
	if(SHOW_PROCESSING) {
		display(player, maze);
		printf(" >> Executando BFS\n");
		
		msleep(DELAY);
	}

	if(maze_getFileTile(maze, player->current_y, player->current_x) == 'F')
		return 1;

	for (w = 0; w < maze_getGraphV(maze); w++){
		if (maze_getGraphEdge(maze, v,w) && !visited[w]){
			fila_insere(fila, w);
		}
	}

	state = bfs(fila, player, maze, visited);
	
	return state;
}

int bfs2(Fila* fila,  PlayerDef* player, MazeDef* maze, int visited[maze_getGraphV(maze)]){

	if(fila_vazia(fila))
		return 0;

	int state = 0;
	int v = fila_retira(fila);
	int w;
	visited[v] = 1;

	player->current_vertex = v;
	player->current_y = vertex_to_map_y(player->current_vertex, maze_getFileCols(maze));
	player->current_x = vertex_to_map_x(player->current_vertex, maze_getFileCols(maze));
	player->steps++;
	
	if(SHOW_PROCESSING) {
		display(player, maze);
		printf(" >> Executando BFS2\n");
		
		msleep(DELAY);
	}

	if(maze_getFileTile(maze, player->current_y, player->current_x) == 'F')
		return 1;

	for (w = 0; w < maze_getGraphV(maze); w++){
		if (maze_getGraphEdge(maze, v,w) && !visited[w]){
			fila_insere(fila, w);
			visited[w] = 1; // marca como visitado quando é adicionado à fila
		}
	}

	state = bfs2(fila, player, maze, visited);
	
	return state;
}

int* dijkstra(PlayerDef* player, MazeDef* maze, int start,
				int visited[maze_getGraphV(maze)]) {

	int i;
	int v, w;
	int node_n = maze_getGraphV(maze);
	int dist[maze_getGraphV(maze)];
	int* prev = malloc(maze_getGraphV(maze) * sizeof(int));

	//visited[v] = 1;

	MinHeap* heap = heap_create(node_n);

	dist[start] = 0;
	prev[start] = -1;
	for (i = 0; i < node_n; i++) {
		if (i != start) {
			dist[i] = (node_n + 1) * 100;
			prev[i] = -1;
		}
		min_heap_insert(heap, i, dist);
	}

	printf("Heap inicializada\n");

	v = min_heap_remove(heap, dist);
	while (v > -1) {

		player->current_vertex = v;
		player->current_y = vertex_to_map_y(player->current_vertex, maze_getFileCols(maze));
		player->current_x = vertex_to_map_x(player->current_vertex, maze_getFileCols(maze));
		player->steps++;

		if(SHOW_PROCESSING) {
			display(player, maze);
			printf(" >> Executando Dijkstra\n");
			
			msleep(DELAY);
		}

		if(maze_getFileTile(maze, player->current_y, player->current_x) == 'F')
			return prev;

		for (w = 0; w < node_n; w++){
			if (maze_getGraphEdge(maze, v, w) && !visited[w]){
				int new_dist = dist[v] + maze_getGraphEdge(maze, v, w);
				if (new_dist < dist[w]) {
					dist[w] = new_dist;
					prev[w] = v;
					min_heap_find_and_update(heap, w, dist);
				}
			}
		}

		visited[v] = 1;
		v = min_heap_remove(heap, dist);
	}
	return NULL;
}

int* a_star(PlayerDef* player, MazeDef* maze, int start, int finish,
				int visited[maze_getGraphV(maze)]) {

	int i;
	int v, w;
	int node_n = maze_getGraphV(maze);
	int dist[maze_getGraphV(maze)];
	int heur[maze_getGraphV(maze)];
	int func[maze_getGraphV(maze)];
	int* prev = malloc(maze_getGraphV(maze) * sizeof(int));

	//visited[v] = 1;

	MinHeap* heap = heap_create(node_n);

	dist[start] = 0;
	prev[start] = -1;
	for (i = 0; i < node_n; i++) {
		if (i != start) {
			dist[i] = (node_n + 1) * 100;
			heur[i] = -1;
			func[i] = dist[i];
			prev[i] = -1;
		}
		min_heap_insert(heap, i, func);
	}

	printf("Heap inicializada\n");

	v = min_heap_remove(heap, dist);
	while (v > -1) {

		player->current_vertex = v;
		player->current_y = vertex_to_map_y(player->current_vertex, maze_getFileCols(maze));
		player->current_x = vertex_to_map_x(player->current_vertex, maze_getFileCols(maze));
		player->steps++;

		if(SHOW_PROCESSING) {
			display(player, maze);
			printf(" >> Executando Dijkstra\n");
			
			msleep(DELAY);
		}

		if(maze_getFileTile(maze, player->current_y, player->current_x) == 'F')
			return prev;

		for (w = 0; w < node_n; w++){
			if (maze_getGraphEdge(maze, v, w) && !visited[w]){
				if (heur[w] == -1)
					heur[w] = heuristic(maze, w, finish);
				int new_dist = dist[v] + maze_getGraphEdge(maze, v, w);
				if (new_dist < dist[w]) {
					dist[w] = new_dist;
					func[w] = dist[w] + heur[w];
					prev[w] = v;
					min_heap_find_and_update(heap, w, func);
				}
			}
		}

		visited[v] = 1;
		v = min_heap_remove(heap, func);
	}
	return NULL;
}

void dijkstra_draw_path(MazeDef* maze, int* prev) {
	int i;
	int in_path[maze_getGraphV(maze)];

	int f_x = maze_getFinishX(maze);
	int f_y = maze_getFinishY(maze);

	int f = map_to_vertex(f_y, f_x, maze_getFileCols(maze));

	int v = prev[f];

	for (i = 0; i < maze_getGraphV(maze); i++) {
		in_path[i] = 0;
	}

	while (v != -1) {
		in_path[v] = 1;
		v = prev[v];
	}

	for (i = 0; i < maze_getGraphV(maze); i++) {
		if (in_path[i]) {
			maze_print_path(maze, i);
		}
	}
	maze_print_path(maze, f);
}

int heuristic(MazeDef* maze, int v, int w) {

	int v_x, v_y, w_x, w_y;
	int cols = maze_getFileCols(maze);

	v_x = vertex_to_map_x(v, cols);
	v_y = vertex_to_map_y(v, cols);

	w_x = vertex_to_map_x(w, cols);
	w_y = vertex_to_map_y(w, cols);

	return abs(v_x - w_x) + abs(v_y - w_y);
}

static int** cria_matriz (int rows, int cols) { // creates dynamic matrix with rows x cols entries
	int **m = (int**) malloc(rows * sizeof(int*));
	for (int i=0; i<rows; i++) {
		m[i] = (int*)malloc(cols * sizeof(int));
	}
	return m;
}

static void libera_matriz (int** m, int rows) { // frees dynamic matrix
	for (int i=0; i<rows; i++) {
		free(m[i]);
	}
	free(m);
}

static void floyd_warshall_alg (PlayerDef* player, MazeDef* maze, int** dist, int** prox, 
																	int visited[maze_getGraphV(maze)]) {
	int node_n = maze_getGraphV(maze);

	// initializing dist with infinity
	for (int i=0; i<node_n; i++) {
		for (int j=0; j<node_n; j++) {
			if (i == j) // same vertex, distance to itself is zero
				dist[i][j] = 0;
			else 
				dist[i][j] = 1073741773; // big number used as 'infinity'
		}
	}

	// initializing prox with -1 (NULL)
	for (int i=0; i<node_n; i++) {
		for (int j=0; j<node_n; j++) {
			if (i == j)
				prox[i][j] = i;
			else
				prox[i][j] = -1;
		}
	}

	// filling dist and prox with graph edges
	for (int i=0; i<node_n; i++) {
		for (int j=0; j<node_n; j++) {
			int edge = maze_getGraphEdge(maze, i, j);
			if (edge) { // edge exists, fills tables with its value
				dist[i][j] = edge;
				prox[i][j] = j;
			}
		}
	}

	// running Floyd Warshall
	for (int k=0; k<node_n; k++) {
		visited[k] = 1;
		player->current_vertex = k;
		player->current_y = vertex_to_map_y(player->current_vertex, maze_getFileCols(maze));
		player->current_x = vertex_to_map_x(player->current_vertex, maze_getFileCols(maze));
		player->steps++;

		if(SHOW_PROCESSING) {
			display(player, maze);
			printf(" >> Executando Floyd-Warshall\n");
			
			msleep(DELAY);
		}

		for (int i=0; i<node_n; i++) {
			for (int j=0; j<node_n; j++) {
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					prox[i][j] = prox[i][k];
				}
			}
		}
	}
}

int** floyd_warshall(PlayerDef* player, MazeDef* maze, int visited[maze_getGraphV(maze)], int** prox) {
	// Returns and displays for shortest path between 'I' and 'F'
	int node_n = maze_getGraphV(maze);
	int** dist = cria_matriz(node_n, node_n);	
	prox = cria_matriz(node_n, node_n);	

	floyd_warshall_alg(player, maze, dist, prox, visited); // calculates shortest path from all nodes to all nodes

	libera_matriz(dist, node_n);

	return prox;
}

void floyd_warshall_draw_path(MazeDef* maze, int** prox, int start, int finish) { 
	// retrieving path from start to finish
	int node_n = maze_getGraphV(maze);
	
	int* in_path = (int*) malloc(node_n*sizeof(int)); // flag vector for nodes in shortest path
	for (int i = 0; i < node_n; i++) {
		in_path[i] = 0;
	}

	while (start != finish) {
		start = prox[start][finish];
		in_path[start] = 1; // node 'start' is in path
	}

	for (int i = 0; i < node_n; i++) {
		if (in_path[i]) {
			maze_print_path(maze, i);
		}
	}
	maze_print_path(maze, finish);

	free(in_path);
	libera_matriz(prox, node_n);
	prox = NULL;
}