#include "fila_vet.h"
#include "pilha_vet.h"
#include "maze.h"

int dfs(int v, PlayerDef* player, MazeDef* maze, int visited[maze_getGraphV(maze)]);

int pilha_dfs(Pilha* pilha, PlayerDef* player, MazeDef* maze, int visited[maze_getGraphV(maze)]);

int bfs(Fila* fila,  PlayerDef* player, MazeDef* maze, int visited[maze_getGraphV(maze)]);

int bfs2(Fila* fila,  PlayerDef* player, MazeDef* maze, int visited[maze_getGraphV(maze)]);

int* dijkstra(PlayerDef* player, MazeDef* maze, int start, int visited[maze_getGraphV(maze)]);

void dijkstra_draw_path(MazeDef* maze, int* prev);

int* a_star(PlayerDef* player, MazeDef* maze, int start, int finish, int visited[maze_getGraphV(maze)]);

int heuristic(MazeDef* maze, int v, int w);

int** floyd_warshall(PlayerDef* player, MazeDef* maze, int visited[maze_getGraphV(maze)], int** prox);

void floyd_warshall_draw_path(MazeDef* maze, int** prox, int i, int f);