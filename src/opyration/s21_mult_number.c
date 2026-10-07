#include "s21_matrix.h"

int s21_mult_number(s21_matrix *A, double number, s21_matrix *result)
{
    int error = 0;
    if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0 || result == NULL)
        error = 1;
    else
    {
        s21_create_matrix(A->rows, A->columns, result);
        for(int i = 0; i < A->rows; i++)
        {
            for(int j = 0; j < A->columns; j++)
            {
                result->matrix[i][j] = A->matrix[i][j] * number; 
            }
        }
    }
    return error;
}