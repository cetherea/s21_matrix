#include "../s21_matrix.h"

int s21_transpose(s21_matrix *A, s21_matrix *result)
{
    int error = 0;
    if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0 || result == NULL)
        error = 1;
    else
    {
        s21_create_matrix(A->columns, A->rows, result);
        for(int i = 0; i < A->columns; i++)
        {
            for(int j = 0; j < A->rows; j++)
            {
                result->matrix[i][j] = A->matrix[j][i];
            }
        }

    }
    return error;
}