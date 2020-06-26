#include "fila_vet.h"
#include "pilha_vet.h"
#include "maze.h"

int dfs(int v, PlayerDef* player, MazeDef* maze, int visited[maze_getGraphV(maze)]);

int pilha_dfs(Pilha* pilha, PlayerDef* player, MazeDef* maze, int visited[maze_getGraphV(maze)]);

int bfs(Fila* fila,  PlayerDef* player, MazeDef* maze, int visited[maze_getGraphV(maze)]);

int bfs2(Fila* fila,  PlayerDef* player, MazeDef* maze, int visited[maze_getGraphV(maze)]);

int dijkstra(PlayerDef* player, MazeDef* maze, int start, int visited[maze_getGraphV(maze)]);