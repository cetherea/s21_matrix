#include "../s21_matrix.h"

void s21_remove_matrix(s21_matrix *A)
{
    if (A != NULL)
    {
        if (A->matrix != NULL)
        {
            for (int i = 0; i < A->rows; i++)
            {
                free(A->matrix[i]);
            }
            free(A->matrix);
            A->matrix = NULL;
        }

        A->columns = 0;
        A->rows = 0;
    }
}