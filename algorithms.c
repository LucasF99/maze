#include <stdio.h>
#include <stdlib.h>
#include "algorithms.h"
#include "min_heap.h"

#define SHOW_PROCESSING 1
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

int dijkstra(PlayerDef* player, MazeDef* maze, int start,
				int visited[maze_getGraphV(maze)]) {

	int state = 0;
	int i;
	int v, w;
	int node_n = maze_getGraphV(maze);
	int dist[maze_getGraphV(maze)];
	int prev[maze_getGraphV(maze)];

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
			return 1;

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
	return 0;
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