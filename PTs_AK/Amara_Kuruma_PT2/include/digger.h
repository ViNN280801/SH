#ifndef DIGGER_H
#define DIGGER_H

#include <stdbool.h>

#define MAX_CAVE_SIZE 100

struct Node
{
    int vertex;
    struct Node *next;
};

struct Graph
{
    int vertices;
    struct Node **adjLists;
};

// Function to create a new graph
struct Graph *create_graph(int vertices);

// Add an edge to the graph
void add_edge(struct Graph *graph, int src, int dest);

bool can_find_way_matrix(char **cave, int rows, int cols, int startRow, int startCol);
bool can_find_way_list(struct Graph *graph, int startVertex);

#endif //! DIGGER_H
