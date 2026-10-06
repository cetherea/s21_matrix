#ifndef S21_MATRIX_H
#define S21_MATRIX_H
#include <stdlib.h>
#include <math.h>

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} s21_matrix;

int s21_create_matrix(int rows, int columns, s21_matrix *result);
void s21_remove_matrix(s21_matrix *A);
int s21_eq_matrix(s21_matrix *A, s21_matrix *B);
int s21_sum_matrix(s21_matrix *A, s21_matrix *B, s21_matrix *result);
int s21_sub_matrix(s21_matrix *A, s21_matrix *B, s21_matrix *result);
#endif