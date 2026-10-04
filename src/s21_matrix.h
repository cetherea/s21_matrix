#ifndef S21_MATRIX_H
#define S21_MATRIX_H
#include <stdlib.h>

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} s21_matrix;

int s21_create_matrix(int rows, int columns, s21_matrix *result);


#endif