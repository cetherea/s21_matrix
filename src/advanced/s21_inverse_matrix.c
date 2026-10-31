#include "../s21_matrix.h"

int s21_inverse_matrix(s21_matrix *A, s21_matrix *result) {
  int error = 0;
  if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0 ||
      result == NULL)

    error = 1;

  else if (A->rows != A->columns)
    error = 2;
  else {
    s21_matrix tMatrix = {0};
    s21_matrix detMatrix = {0};
    double det = 0;
    s21_determinant(A, &det);
    if (det != 0) {
      s21_calc_complements(A, &detMatrix);
      s21_transpose(&detMatrix, &tMatrix);

      s21_mult_number(&tMatrix, 1.0 / det, result);

      s21_remove_matrix(&tMatrix);
      s21_remove_matrix(&detMatrix);
    } else
      error = 2;
  }
  return error;
}
