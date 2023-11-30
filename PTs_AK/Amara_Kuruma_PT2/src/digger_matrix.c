#include "../include/digger.h"

bool can_find_way_matrix(char **cave, int rows, int cols, int startRow, int startCol)
{
    // Base cases
    if (startRow < 0 || startRow >= rows || startCol < 0 || startCol >= cols)
        return true; // Exit found

    if (cave[startRow][startCol] == 'w')
        return false; // Wall

    if (cave[startRow][startCol] == 'v')
        return false; // Visited

    // Mark as visited
    cave[startRow][startCol] = 'v';

    // Recursive calls for adjacent cells
    if (can_find_way_matrix(cave, rows, cols, startRow - 1, startCol) ||
        can_find_way_matrix(cave, rows, cols, startRow + 1, startCol) ||
        can_find_way_matrix(cave, rows, cols, startRow, startCol - 1) ||
        can_find_way_matrix(cave, rows, cols, startRow, startCol + 1))
        return true;

    return false;
}
