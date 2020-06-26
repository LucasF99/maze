#include <stdio.h>
#include "algorithms.h"

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