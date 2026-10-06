#include "../s21_runner.h"

START_TEST(basic_test)
{
  int expected_rows = 3;
  int expected_columns = 4;
  s21_matrix A = {0};
  s21_matrix B = {0};
  s21_create_matrix(expected_rows, expected_columns, &A);
  s21_create_matrix(expected_rows, expected_columns, &B);

  for (int i = 0; i < expected_rows; i++)
  {
    for (int j = 0; j < expected_columns; j++)
    {
      A.matrix[i][j] = i + j;
      B.matrix[i][j] = i + j;
    }
  }

  int eq = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(no_eq_test)
{
  int expected_rows = 3;
  int expected_columns = 4;
  s21_matrix A = {0};
  s21_matrix B = {0};
  s21_create_matrix(expected_rows, expected_columns, &A);
  s21_create_matrix(expected_rows, expected_columns, &B);

  for (int i = 0; i < expected_rows; i++)
  {
    for (int j = 0; j < expected_columns; j++)
    {
      A.matrix[i][j] = i;
      B.matrix[i][j] = j;
    }
  }

  int eq = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(eq, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(different_size_test)
{
  int expected_rows = 3;
  int expected_columnsA = 4;
  int expected_columnsB = 5;
  s21_matrix A = {0};
  s21_matrix B = {0};
  s21_create_matrix(expected_rows, expected_columnsA, &A);
  s21_create_matrix(expected_rows, expected_columnsB, &B);

  for (int i = 0; i < expected_rows; i++)
  {
    for (int j = 0; j < expected_columnsA; j++)
    {
      A.matrix[i][j] = 1;
    }
  }

  for (int i = 0; i < expected_rows; i++)
  {
    for (int j = 0; j < expected_columnsB; j++)
    {
      B.matrix[i][j] = 1;
    }
  }

  int eq = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(eq, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(null_matrix_test)
{
  int expected_rows = 3;
  int expected_columnsA = 4;
  s21_matrix A = {0};
  s21_create_matrix(expected_rows, expected_columnsA, &A);

  int eq = s21_eq_matrix(&A, NULL);

  ck_assert_int_eq(eq, FAILURE);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(empty_matrix_test)
{
  int expected_rows = 3;
  int expected_columns = 4;
  s21_matrix A = {0};
  s21_matrix B = {0};
  s21_create_matrix(expected_rows, expected_columns, &A);
  B.columns = expected_columns;
  B.rows = expected_rows;
  B.matrix = NULL;

  int eq = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(eq, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(double_matrix_test)
{
  int expected_rows = 3;
  int expected_columns = 4;
  s21_matrix A = {0};
  s21_matrix B = {0};
  s21_create_matrix(expected_rows, expected_columns, &A);
  s21_create_matrix(expected_rows, expected_columns, &B);

  for (int i = 0; i < expected_rows; i++)
  {
    for (int j = 0; j < expected_columns; j++)
    {
      A.matrix[i][j] = i + j;
      B.matrix[i][j] = i + j + 1e-7;
    }
  }

  int eq = s21_eq_matrix(&A, &B);

  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *suite_eq_matrix(void)
{
  Suite *s = suite_create("eq_matrix");

  TCase *tcase_basic = tcase_create("basic");
  tcase_add_test(tcase_basic, basic_test);
  tcase_add_test(tcase_basic, double_matrix_test);
  suite_add_tcase(s, tcase_basic);

  TCase *tcase_fail = tcase_create("fail");
  tcase_add_test(tcase_fail, different_size_test);
  tcase_add_test(tcase_fail, null_matrix_test);
  tcase_add_test(tcase_fail, empty_matrix_test);
  tcase_add_test(tcase_fail, no_eq_test);
  suite_add_tcase(s, tcase_fail);

  return s;
}