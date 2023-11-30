#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "../include/digger.h"

// Function to create a new graph node
struct Node *create_node(int vertex)
{
    struct Node *node = (struct Node *)calloc(1, sizeof(struct Node));
    if (!node)
    {
        fprintf(stderr, "Can't allocate memory: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    node->vertex = vertex;
    node->next = NULL;
    return node;
}

struct Graph *create_graph(int vertices)
{
    struct Graph *graph = (struct Graph *)calloc(1, sizeof(struct Graph));
    if (!graph)
    {
        fprintf(stderr, "Can't allocate memory: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    graph->vertices = vertices;
    graph->adjLists = (struct Node **)calloc(vertices, sizeof(struct Node *));
    if (!graph->adjLists)
    {
        fprintf(stderr, "Can't allocate memory: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;
    return graph;
}

void add_edge(struct Graph *graph, int src, int dest)
{
    struct Node *node = create_node(dest);
    node->next = graph->adjLists[src];
    graph->adjLists[src] = node;
}

// Depth first search
bool DFS(struct Graph *graph, int vertex, bool *visited)
{
    // Mark the current vertex as visited
    visited[vertex] = true;

    // Traverse the adjacent vertices
    struct Node *adjList = graph->adjLists[vertex];
    while (adjList)
    {
        int connectedVertex = adjList->vertex;

        if (!visited[connectedVertex])
            // Recursive call for unvisited adjacent vertices
            if (DFS(graph, connectedVertex, visited))
                return true; // Exit found

        adjList = adjList->next;
    }

    return false; // No exit found
}

bool can_find_way_list(struct Graph *graph, int startVertex)
{
    // Create an array to keep track of visited vertices
    bool *visited = (bool *)calloc(graph->vertices, sizeof(bool));
    if (!visited)
    {
        fprintf(stderr, "Can't allocate memory: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Call the recursive DFS function
    bool result = DFS(graph, startVertex, visited);

    free(visited);
    visited = NULL;

    return result;
}
