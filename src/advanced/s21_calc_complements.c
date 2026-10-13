#include "../s21_matrix.h"
#include "../helpers/s21_utils.h"

int s21_calc_complements(s21_matrix *A, s21_matrix *result)
{
    int error = 0;
    if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0 || result == NULL)

        error = 1;
    else if (A->rows != A->columns)
        error = 2;

    else if(A->rows == 1)
    {
        s21_create_matrix(A->rows, A->columns, result);
        result->matrix[0][0] = 1;
    }
    else
    {
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < A->rows; i++)
        {
            for (int j = 0; j < A->columns; j++)
            {
                s21_matrix B = get_submatrix(*A, i, j);
                double det = get_det(B);
                result->matrix[i][j] = det * pow(-1, i+j);
;
            }
        }
    }
    return error;
}