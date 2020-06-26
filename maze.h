typedef struct _mazedef MazeDef;

typedef struct _playerdef {
    int current_x;
    int current_y;
    int current_vertex;
    int steps;
} PlayerDef;


int msleep(long msec);

int map_to_vertex(int y, int x, int cols);
int vertex_to_map_y(int current_vertex, int cols);
int vertex_to_map_x(int current_vertex, int cols);
int free_vertex(char tile);
int vertex_cost(char tile);

PlayerDef* maze_criaPlayer();

MazeDef* maze_criaLabirinto();
MazeDef* maze_carregaLabirinto(MazeDef* maze);
MazeDef* maze_carregaMatrizAdjacencias(MazeDef* maze);
void maze_printListaVizinhanca(int v, MazeDef* maze);


void display(PlayerDef *player, MazeDef* maze);


int maze_getFileRows(MazeDef* maze);
int maze_getFileCols(MazeDef* maze);

int maze_getStartX(MazeDef* maze);
int maze_getStartY(MazeDef* maze);

int maze_getFinishX(MazeDef* maze);
int maze_getFinishY(MazeDef* maze);

int maze_getGraphV(MazeDef* maze);

char maze_getFileTile(MazeDef* maze, int y, int x);
void maze_setFileTile(MazeDef* maze, int y, int x, char c);

int maze_getGraphEdge(MazeDef* maze, int y, int x);

void maze_print_path(MazeDef *maze, int u);

void print_matrix(MazeDef* m, int ini, int fim);