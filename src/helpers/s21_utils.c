#include "s21_utils.h"

s21_matrix get_submatrix(s21_matrix matrix, int row, int col)
{
    int new_row = matrix.rows - 1, new_col = matrix.columns - 1;

    s21_matrix A;
    s21_create_matrix(new_row, new_col, &A);
    for (int Ar = 0; Ar < A.rows; Ar++)
    {
        int orig_r = (Ar >= row) ? Ar + 1 : Ar;
        for (int Ac = 0; Ac < A.columns; Ac++)
        {
            int orig_c = (Ac >= col) ? Ac + 1 : Ac;

            A.matrix[Ar][Ac] = matrix.matrix[orig_r][orig_c];
        }
    }
    return A;
}

double get_det(s21_matrix matrix)
{
    double result = 0;

    if (matrix.columns == 1)
        result = matrix.matrix[0][0];
    else
    {
        int sign = 1;
        for (int i = 0; i < matrix.columns; i++)
        {
            s21_matrix sub_matrix = get_submatrix(matrix, 0, i);
            result += sign * matrix.matrix[0][i] * get_det(sub_matrix);
            s21_remove_matrix(&sub_matrix);

            sign = -sign;
        }
    }

    return result;
}
