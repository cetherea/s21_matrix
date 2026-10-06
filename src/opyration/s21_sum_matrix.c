#include "../s21_matrix.h"
int s21_sum_matrix(s21_matrix *A, s21_matrix *B, s21_matrix *result)
{
    int error = 0;
    if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL)
    {
        error = 1;
    }
    else if (A->columns <= 0 || A->rows <= 0 || A->columns != B->columns || A->rows != B->rows)
    {
        error = 2;
    }
    else
    {
        s21_remove_matrix(result);
        s21_create_matrix(A->rows, A->columns, result);
        for(int i = 0; i < A->rows; i++)
        {
            for(int j = 0; j < A->columns; j++)
            {
                result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
            }
        }
    }
    return error;
}