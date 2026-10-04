#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, s21_matrix *result)
{
    int error = 0;
    if (rows <= 0 || columns <= 0 || result == NULL)
        error = 1;
    else
    {
        result->rows = rows;
        result->columns = columns;
        result->matrix = (double **)malloc(rows * sizeof(double*));
        if (result->matrix == NULL) error = 1;
        for(int i = 0; i < rows && !error; i++)
        {
            result->matrix[i] = (double*)malloc(columns * sizeof(double));
            
        }
    }
    return error;
}