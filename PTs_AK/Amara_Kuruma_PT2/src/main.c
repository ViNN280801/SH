#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "../include/digger.h"

void print_matrix(char **matrix, int rows, int cols)
{
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
            printf("%c ", matrix[row][col]);
        printf("\n");
    }
}

int main()
{
    srand((unsigned)time(NULL));

    // Read cave size and cave description
    int rows = 0, cols = 0;
    char **cave; // Change to a dynamic array

    printf("Enter the number of rows of the matrix: ");
    scanf("%d", &rows);
    printf("Enter the number of columns of the matrix: ");
    scanf("%d", &cols);

    // Allocate memory for the dynamic 2D array
    cave = (char **)malloc(rows * sizeof(char *));
    if (!cave)
    {
        fprintf(stderr, "Can't allocate memory: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < rows; i++)
    {
        cave[i] = (char *)malloc(cols * sizeof(char));
        if (!cave[i])
        {
            fprintf(stderr, "Can't allocate memory: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int value = rand() % 2;
            switch (value)
            {
            case 0:
                cave[i][j] = 'w'; // Wall
                break;
            case 1:
                cave[i][j] = 'p'; // Path
                break;
            default:
                break;
            }
        }
    }

    // Generating exit from the cave
    int exitRow = rand() % rows,
        exitCol = rand() % cols;
    cave[exitRow][exitCol] = 'e';

    printf("Cave sheme:\n");
    print_matrix(cave, rows, cols);

    int startRow = 0, startCol = 0;
    printf("Enter the starting row and column in format \"<num1> <num2>\": ");
    scanf("%d %d", &startRow, &startCol);
    cave[startRow][startCol] = 's';

    // Check using adjacency matrix
    can_find_way_matrix(cave, rows, cols, startRow, startCol)
        ? printf("Using adjacency matrix: The digger \033[1;32mfound\033[0m\033[1m a way out!\n")
        : printf("Using adjacency matrix: The digger \033[1;31mcannot find\033[0m\033[1m a way out.\n");

    // Create and check using adjacency list
    struct Graph *graph = create_graph(rows * cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int vertex = i * cols + j;
            if (cave[i][j] != 'w')
            {
                if (i > 0 && cave[i - 1][j] != 'w')
                    add_edge(graph, vertex, vertex - cols);
                if (i < rows - 1 && cave[i + 1][j] != 'w')
                    add_edge(graph, vertex, vertex + cols);
                if (j > 0 && cave[i][j - 1] != 'w')
                    add_edge(graph, vertex, vertex - 1);
                if (j < cols - 1 && cave[i][j + 1] != 'w')
                    add_edge(graph, vertex, vertex + 1);
            }
        }
    }

    (can_find_way_list(graph, startRow * cols + startCol))
        ? printf("Using adjacency list: The digger \033[1;32mfound\033[0m\033[1m a way out!\n")
        : printf("Using adjacency list: The digger \033[1;31mcannot find\033[0m\033[1m a way out.\n");

    free(graph);
    graph = NULL;

    // Free the dynamically allocated memory for the cave
    for (int i = 0; i < rows; i++)
    {
        free(cave[i]);
        cave[i] = NULL;
    }
    free(cave);
    cave = NULL;

    return EXIT_SUCCESS;
}
