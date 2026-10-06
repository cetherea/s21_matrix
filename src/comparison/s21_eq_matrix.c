#include "../s21_matrix.h"
int s21_eq_matrix(s21_matrix *A, s21_matrix *B) {
  int eq = SUCCESS;
  if (A == NULL || B == NULL || A->columns != B->columns ||
      A->rows != B->rows || A->rows <= 0 || A->columns <= 0 ||
      A->matrix == NULL || B->matrix == NULL)
    eq = FAILURE;
  else {
    for (int i = 0; i < A->rows && eq; i++) {
      for (int j = 0; j < A->columns && eq; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= 1e-6)
          eq = FAILURE;
      }
    }
  }
  return eq;
}