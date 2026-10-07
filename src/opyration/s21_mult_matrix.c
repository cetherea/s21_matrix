#include "../s21_matrix.h"

int s21_mult_matrix(s21_matrix *A, s21_matrix *B, s21_matrix *result)
{
    int error = 0;
    if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL ||
        result == NULL || A->columns <= 0 || A->rows <= 0 || B->columns <= 0 ||
        B->rows <= 0)
    {
        error = 1;
    }
    else if (A->columns != B->rows)
    {
        error = 2;
    }
    else
    {
        s21_create_matrix(A->rows, B->columns, result);
        for(int i = 0; i < A->rows; i++)
        {
            for(int j = 0; j < B->columns; j++)
            {
                double s = 0;
                for(int t = 0; t < A->columns; t++) s+= A->matrix[i][t] * B->matrix[t][j];

                result->matrix[i][j] = s;

            }
        }

    }
    return error;
}