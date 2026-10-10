#include "../s21_matrix.h"
#include "../helpers/s21_utils.h"

int s21_determinant(s21_matrix *A, double *result)
{
    int error = 0;
    if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0 || result == NULL)

        error = 1;

    else if (A->rows != A->columns)
        error = 2;
    else
        *result = get_det(*A);
    return error;
}