#include "../s21_runner.h"

START_TEST(basic_test_3x3) {
  int rows = 3, columns = 3;
  s21_matrix A = {0};
  s21_matrix result = {0};
  s21_matrix expected_matrix = {0};

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &expected_matrix);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  expected_matrix.matrix[0][0] = 0;
  expected_matrix.matrix[0][1] = 10;
  expected_matrix.matrix[0][2] = -20;
  expected_matrix.matrix[1][0] = 4;
  expected_matrix.matrix[1][1] = -14;
  expected_matrix.matrix[1][2] = 8;
  expected_matrix.matrix[2][0] = -8;
  expected_matrix.matrix[2][1] = -2;
  expected_matrix.matrix[2][2] = 4;

  int error = s21_calc_complements(&A, &result);

  int eq = s21_eq_matrix(&result, &expected_matrix);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&expected_matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(basic_test_1x1) {
  int rows = 1, columns = 1;
  s21_matrix A = {0};
  s21_matrix result = {0};
  s21_matrix expected_matrix = {0};

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &expected_matrix);

  A.matrix[0][0] = 5;

  expected_matrix.matrix[0][0] = 1;

  int error = s21_calc_complements(&A, &result);

  int eq = s21_eq_matrix(&result, &expected_matrix);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&expected_matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(error_not_square_test) {
  int rows = 3, columns = 2;
  s21_matrix A = {0};
  s21_matrix result = {0};

  s21_create_matrix(rows, columns, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  result.matrix = NULL;

  int error = s21_calc_complements(&A, &result);
  ck_assert_int_eq(error, 2);
  ck_assert_ptr_null(result.matrix);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(null_matrix_test) {
  s21_matrix result = {0};
  result.matrix = NULL;

  int error = s21_calc_complements(NULL, &result);
  ck_assert_int_eq(error, 1);
  ck_assert_ptr_null(result.matrix);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(empty_matrix_test) {
  int rows = 3, columns = 3;
  s21_matrix result = {0}, A = {0};
  result.matrix = NULL;
  A.matrix = NULL;
  A.rows = rows;
  A.columns = columns;

  int error = s21_calc_complements(&A, &result);
  ck_assert_int_eq(error, 1);
  ck_assert_ptr_null(result.matrix);
  s21_remove_matrix(&result);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(null_result_matrix_test) {
  int rows = 3, columns = 3;
  s21_matrix A = {0};

  s21_create_matrix(rows, columns, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  int error = s21_calc_complements(&A, NULL);
  ck_assert_int_eq(error, 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(invalid_size_test) {
  int rows = 3, columns = 3;
  s21_matrix A = {0};
  s21_matrix result = {0};
  result.matrix = NULL;

  s21_create_matrix(rows, columns, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  A.rows = -3;
  A.columns = -3;

  int error = s21_calc_complements(&A, &result);

  ck_assert_int_eq(error, 1);
  ck_assert_ptr_null(result.matrix);

  A.rows = rows;
  A.columns = columns;

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite *suite_complements_matrix(void) {
  Suite *s = suite_create("complements_matrix");

  TCase *tcase_basic = tcase_create("basic");
  tcase_add_test(tcase_basic, basic_test_1x1);
  tcase_add_test(tcase_basic, basic_test_3x3);
  suite_add_tcase(s, tcase_basic);

  TCase *tcase_fail = tcase_create("fail");
  tcase_add_test(tcase_fail, error_not_square_test);
  tcase_add_test(tcase_fail, null_matrix_test);
  tcase_add_test(tcase_fail, empty_matrix_test);
  tcase_add_test(tcase_fail, null_result_matrix_test);
  tcase_add_test(tcase_fail, invalid_size_test);
  suite_add_tcase(s, tcase_fail);

  return s;
}
