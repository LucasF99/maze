#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>    
#include <stdlib.h>
#include "maze.h"

#define M_COST 100
#define R_COST 5
#define D_COST 1

// tam: 40x83

typedef struct _mazedef {

   int file_cols;
   int file_rows;

   int maze_cols; 
   int maze_rows;

   int graph_V;

   int start_x;
   int start_y;

   int finish_x;
   int finish_y;
   
   char **maze_file;
   int **maze_graph;

} MazeDef;

int maze_getFileRows(MazeDef* maze) {return maze->file_rows;}
int maze_getFileCols(MazeDef* maze) {return maze->file_cols;}

int maze_getStartX(MazeDef* maze) {return maze->start_x;}
int maze_getStartY(MazeDef* maze) {return maze->start_y;}

int maze_getFinishX(MazeDef* maze) {return maze->finish_x;}
int maze_getFinishY(MazeDef* maze) {return maze->finish_y;}

int maze_getGraphV(MazeDef* maze) {return maze->graph_V;}

char maze_getFileTile(MazeDef* maze, int y, int x){
	return maze->maze_file[y][x];
}

int maze_getGraphEdge(MazeDef* maze, int y, int x){
	return maze->maze_graph[y][x];
}

int msleep(long msec)
{
	struct timespec ts;
	int res;

	if (msec < 0)
	{
		errno = EINVAL;
		return -1;
	}

	ts.tv_sec = msec / 1000;
	ts.tv_nsec = (msec % 1000) * 1000000;

	do {
		res = nanosleep(&ts, &ts);
	} while (res && errno == EINTR);

	return res;
}

int map_to_vertex(int y, int x, int cols){
	return (y * cols) + x;
}
int vertex_to_map_y(int current_vertex, int cols){
	return current_vertex / cols;
}
int vertex_to_map_x(int current_vertex, int cols){
	return current_vertex % cols;
}

void display(PlayerDef *player, MazeDef* maze)
{
	int y, x;

	printf ("\033[H\033[J");  //clear screen go top
	
	for (y = 0; y < maze->file_rows; y++)
	{
		for (x = 0; x < maze->file_cols; x++)
			if(player->current_y == y && player->current_x == x){
				printf ("\033[1;31m"); // bold red
				printf("X");
				printf ("\033[0m");
			}
			else if(maze->maze_file[y][x] == 'M'){
				printf ("\033[1;34m"); // bold blue
				printf("M");
				printf ("\033[0m");
			}
			else if(maze->maze_file[y][x] == 'R'){
				printf ("\033[1;33m"); // bold yellow
				printf("R");
				printf ("\033[0m");
			}
			else if(maze->maze_file[y][x] == '.'){
				printf ("\033[1;32m"); // bold green
				printf(".");
				printf ("\033[0m");
			}
			else
				printf("%c", maze->maze_file[y][x]);
		printf("\n");
	}
	printf("\n");
	printf("current position: %d x %d\n", player->current_y, player->current_x);
	printf("current vertex: %d\n", player->current_vertex);
	printf("visited nodes: %d\n", player->steps);
	fflush(stdout);
}

int free_vertex(char tile){
	return tile !='X'; //tile == '.' || tile == 'I' || tile == 'F';
}

int vertex_cost(char tile) {
	switch (tile) {
		case 'M':
			return M_COST;
		case 'R':
			return R_COST;
		case '.':
			return D_COST;
		case 'I':
			return D_COST;
		case 'F':
			return D_COST;
		default:
			return 0;
	}
}

PlayerDef* maze_criaPlayer(){
	
	PlayerDef* player = (PlayerDef*) malloc(sizeof(PlayerDef));
	player->current_x = 0;
	player->current_y = 0;
	player->current_vertex = 0;
	player->steps = 0;
	return player;
}

MazeDef* maze_criaLabirinto(){
	
	MazeDef* maze = (MazeDef*) malloc(sizeof(MazeDef));
	maze->file_cols = 0;
	maze->file_rows = 1;
	maze->maze_cols = 0;
	maze->maze_rows = 0;
	maze->graph_V = 0;
	   
	maze->start_x = 0;
	maze->start_y = 0;

	maze->finish_x = 0;
	maze->finish_y = 0;
	
	FILE *file;
	int c;
	int i = 0;
	
	file = fopen("maze.txt", "r");
	if (file) {
		while ((c = fgetc(file)) != EOF){
			i++;
			if(maze->file_cols == 0 && c == '\n')
				maze->file_cols = i - 1;
			if(c == '\n')
				(maze->file_rows)++;
		}
		fclose(file);
	}
	else{
		printf("arquivo maze não encontrado!");
		exit(1);
	}
	
	maze->maze_cols = maze->file_cols / 2;
	maze->maze_rows = maze->file_rows - 1;
	
	maze->graph_V = (maze->file_cols) * (maze->file_rows);
	
	printf("Lido %d(rows) x %d (cols)\n", maze->file_rows, maze->file_cols);
	printf("Labirinto Criado de %d(rows) x %d (cols)\n", maze->maze_rows, maze->maze_cols);
	printf("Num Vertices V: %d\n", maze->graph_V);
	
	return maze;
}

MazeDef* maze_carregaLabirinto(MazeDef* maze){
	
	FILE *file;
	int c;
	int i;
	int x = 0;
	int y = 0;

	maze->maze_file = (char **)malloc(maze->file_rows * sizeof(char*));
	for(i = 0; i < maze->file_rows; i++) maze->maze_file[i] = (char *)malloc(maze->file_cols * sizeof(char));

	// carregar labirinto
	file = fopen("maze.txt", "r");
	if (file) {
		while ((c = fgetc(file)) != EOF){
			
			 if(c == '\n'){
				x = 0;
				y++;
			 }
			 else{
				maze->maze_file[y][x] = c;
				
				if(c == 'I')
				{
					
				 maze->start_x = x;
				 maze->start_y = y;
				 
				}
				else if(c == 'F')
				{
				 maze->finish_x = x;
				 maze->finish_y = y;
				}
				x++;
			 }
		}
		fclose(file);
	}
	else{
		printf("arquivo maze não encontrado!");
		exit(1);
	}
		
	printf("Start %d(row) x %d (col)\n", maze->start_y, maze->start_x);
	printf("Finish %d(row) x %d (col)\n", maze->finish_y, maze->finish_x);
	return maze;
}


MazeDef* maze_carregaMatrizAdjacencias(MazeDef* maze){
	
	int i = 0;
	int x = 0;
	int y = 0;

	maze->maze_graph = (int**)malloc(maze->graph_V * sizeof(int *));
	for(i = 0; i < maze->graph_V; i++) maze->maze_graph[i] = (int *)malloc(maze->graph_V * sizeof(int));
	
	for(y = 0; y < maze->graph_V; y++)
		for(x = 0; x < maze->graph_V; x++)
		maze->maze_graph[y][x] = 0;

	for(y = 0; y < maze->file_rows; y++){
		for(x = 0; x < maze->file_cols; x++){

			int i = map_to_vertex(y, x, maze->file_cols);
			int j = i;
			
			//Verificar vizinhos e cadastrar arestas i->j e j->i quando possivel

			// if(free_vertex(maze->maze_file[y][x])){
				
			// 	if(free_vertex(maze->maze_file[y][x+1]) && x < maze->file_cols-1){ // dir
				
			// 		j = map_to_vertex(y, x+1, maze->file_cols);
			// 		if(i != j && i >=0 && j>=0 && i <maze->graph_V && j<maze->graph_V){
			// 			maze->maze_graph[i][j] = 1;
			// 			maze->maze_graph[j][i] = 1;
			// 		}
					
			// 	} 
				
			// 	if(free_vertex(maze->maze_file[y][x-1]) && x > 1){ // esq
				
			// 		j = map_to_vertex(y, x-1, maze->file_cols);
			// 		if(i != j && i >=0 && j>=0 && i <maze->graph_V && j<maze->graph_V){
			// 			maze->maze_graph[i][j] = 1;
			// 			maze->maze_graph[j][i] = 1;
			// 		}
					
			// 	}
			// 	if(free_vertex(maze->maze_file[y+1][x]) && y < maze->file_rows-1){ // baixo
			// 		j = map_to_vertex(y+1, x, maze->file_cols);
			// 		if(i != j && i >=0 && j>=0 && i <maze->graph_V && j<maze->graph_V){
			// 			maze->maze_graph[i][j] = 1;
			// 			maze->maze_graph[j][i] = 1;
			// 		}
			// 	}
			// 	if(free_vertex(maze->maze_file[y-1][x]) && y > 1){ // cima
			// 		j = map_to_vertex(y-1, x, maze->file_cols);
			// 		if(i != j && i >=0 && j>=0 && i <maze->graph_V && j<maze->graph_V){
			// 			maze->maze_graph[i][j] = 1;
			// 			maze->maze_graph[j][i] = 1;
			// 		}
			// 	}
			// }

			if (y > 0) {
				j = map_to_vertex(y-1, x, maze->file_cols);
				maze->maze_graph[i][j] = vertex_cost(maze->maze_file[y-1][x]);
			}
			if (y < maze->file_rows-1) {
				j = map_to_vertex(y+1, x, maze->file_cols);
				maze->maze_graph[i][j] = vertex_cost(maze->maze_file[y+1][x]);
			}
			if (x > 0) {
				j = map_to_vertex(y, x-1, maze->file_cols);
				maze->maze_graph[i][j] = vertex_cost(maze->maze_file[y][x-1]);
			}
			if (x < maze->file_cols-1) {
				j = map_to_vertex(y, x+1, maze->file_cols);
				maze->maze_graph[i][j] = vertex_cost(maze->maze_file[y][x+1]);
			}
		}
	}

	printf("Matriz de adjacências carregada.\n");
	
	return maze;
}

void maze_printListaVizinhanca(int v, MazeDef* maze){
	
	int w;
	printf("Lista de vizinhos vertice: %d (row:%d col:%d)\n", v, vertex_to_map_y(v, maze->file_cols), vertex_to_map_x(v, maze->file_cols));
	
	for (w = 0; w < maze->graph_V; w++)
	if (maze->maze_graph[v][w])
		printf("Aresta %d -> %d ou (row:%d col:%d) -> (row:%d col:%d)\n", v, w,vertex_to_map_y(v, maze->file_cols), vertex_to_map_x(v, maze->file_cols), vertex_to_map_y(w, maze->file_cols), vertex_to_map_x(w, maze->file_cols));
}

void maze_print_path(MazeDef *maze, int u){
	int v_start = map_to_vertex(maze_getStartY(maze), maze_getStartX(maze), maze_getFileCols(maze));
	int v_finish = map_to_vertex(maze_getFinishY(maze), maze_getFinishX(maze), maze_getFileCols(maze));
	
	printf ("\033[H");
	if(u == v_start || u == v_finish) //ref colors peguei em http://web.theurbanpenguin.com/adding-color-to-your-output-from-c/
		printf ("\033[1;31m"); // bold green 
	else
		printf ("\033[1;32m"); // bold red
	int y = vertex_to_map_y(u, maze_getFileCols(maze));
	int x = vertex_to_map_x(u, maze_getFileCols(maze));
	
	printf("\033[%dB", y);
	printf("\033[%dC", x);
	printf("◘\r");
	printf ("\033[0m");
}

// pra debug: printa parte da matriz de adjacencia,
// limites definidos por ini e fim
void print_matrix(MazeDef* m, int ini, int fim) {
	int i, j;

	printf("    ");
	for (i = ini; i < fim; i++) {
		printf("%3d ", i);
	}
	printf("\n");

	for (i = ini; i < fim; i++) { // linha
		printf("%3d ", i);
		for (j = ini; j < fim; j++) { // col
			printf("%3d ", m->maze_graph[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}