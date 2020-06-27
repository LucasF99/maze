/******************************************************************************

MAZE SOLVER
INF1010 Estrutura de Dados Avançadas
Prof. Augusto Baffa

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "min_heap.h"
#include "algorithms.h"

#define ALG 4   // 0 DFS, 1 PILHA_DFS, 2 BFS, 3 BFS alterado, 4 Dijkstra

int main() {
	clock_t t;
	int v,w;
	
	MazeDef* maze = maze_criaLabirinto();
	
	maze = maze_carregaLabirinto(maze);

	maze = maze_carregaMatrizAdjacencias(maze);
	
	//print_matrix(maze, 2000, 2020);

	PlayerDef* player = maze_criaPlayer();

	player->current_x = maze_getStartX(maze);
	player->current_y = maze_getStartY(maze);

	player->current_vertex = map_to_vertex(player->current_y, player->current_x, maze_getFileCols(maze));

	display(player, maze);
	
	int visited[maze_getGraphV(maze)];

	for (w = 0; w < maze_getGraphV(maze); w++) // inicializa visitados    
		visited[w] = 0;

	if(ALG == 0){

		///////////////////////////////////////////////////////
		// chamar DFS
		
		t = clock(); 
		if(dfs(player->current_vertex, player, maze, visited))
		{
			t = clock() - t; 
			display(player, maze);
			printf("Final encontrado c/ DFS em %f segundos\n", ((double)t)/CLOCKS_PER_SEC);
			
			for(w = 0; w < maze_getGraphV(maze); w++)
				if(visited[w])
					maze_print_path(maze, w);
		}
		else{
			t = clock() - t; 
			display(player, maze);
			printf("Não encontrado c/ DFS em %f segundos\n", ((double)t)/CLOCKS_PER_SEC);
		}

	}
	else if(ALG == 1){

		///////////////////////////////////////////////////////
		// chamar PILHA_DFS
		Pilha* pilha = pilha_cria ();
		pilha_push(pilha, player->current_vertex);
		
		t = clock(); 
		if(pilha_dfs(pilha, player, maze, visited)){
			t = clock() - t; 
			display(player, maze);
			printf("Final encontrado c/ DFS em %f segundos\n", ((double)t)/CLOCKS_PER_SEC);
			
			for(w = 0; w < maze_getGraphV(maze); w++)
				if(visited[w])
					maze_print_path(maze, w);
		}
		else{
			t = clock() - t; 
			display(player, maze);
			printf("Não encontrado c/ DFS em %f segundos\n", ((double)t)/CLOCKS_PER_SEC);
		}
	}
	else if(ALG == 2){

		///////////////////////////////////////////////////////
		// chamar BFS
		Fila* fila = fila_cria ();
		fila_insere(fila, player->current_vertex);
		
		t = clock(); 
		if(bfs(fila, player, maze, visited)){
			t = clock() - t; 
			display(player, maze);
			printf("Final encontrado c/ BFS em %f segundos\n", ((double)t)/CLOCKS_PER_SEC);
	
			for(w = 0; w < maze_getGraphV(maze); w++)
				if(visited[w])
					maze_print_path(maze, w);        
		}
		else{
			t = clock() - t; 
			display(player, maze);
			printf("Não encontrado c/ BFS em %f segundos\n", ((double)t)/CLOCKS_PER_SEC);
		}
	}
	else if(ALG == 3){

		///////////////////////////////////////////////////////
		// chamar BFS
		Fila* fila = fila_cria ();
		fila_insere(fila, player->current_vertex);
		
		t = clock(); 
		if(bfs2(fila, player, maze, visited)){
			t = clock() - t; 
			display(player, maze);
			printf("Final encontrado c/ BFS2 em %f segundos\n", ((double)t)/CLOCKS_PER_SEC);
	
			for(w = 0; w < maze_getGraphV(maze); w++)
				if(visited[w])
					maze_print_path(maze, w);        
		}
		else{
			t = clock() - t; 
			display(player, maze);
			printf("Não encontrado c/ BFS2 em %f segundos\n", ((double)t)/CLOCKS_PER_SEC);
		}
	} else if(ALG == 4){

		///////////////////////////////////////////////////////
		// chamar Dijkstra
		int* prev;

		t = clock();
		prev = dijkstra(player, maze, player->current_vertex, visited);
		if(prev){
			t = clock() - t; 
			display(player, maze);
			printf("Final encontrado c/ Dijkstra em %f segundos\n", ((double)t)/CLOCKS_PER_SEC);
	
			dijkstra_draw_path(maze, prev);       
		}
		else{
			t = clock() - t; 
			display(player, maze);
			printf("Não encontrado c/ Dijkstra em %f segundos\n", ((double)t)/CLOCKS_PER_SEC);
		}
	}

	printf ("\033[H");
	printf("\033[%dB", maze_getFileRows(maze)+6);
	
	return 0;
}
