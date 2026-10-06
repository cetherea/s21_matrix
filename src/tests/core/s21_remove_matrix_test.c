#include "../s21_runner.h"

START_TEST(basic_test) {
  int expected_rows = 3;
  int expected_columns = 4;
  s21_matrix matrix = {0};
  s21_create_matrix(expected_rows, expected_columns, &matrix);

  s21_remove_matrix(&matrix);
  ck_assert_ptr_null(matrix.matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}
END_TEST

START_TEST(null_ptr_test) {
  s21_matrix matrix = {0};
  matrix.matrix = NULL;

  s21_remove_matrix(&matrix);
  ck_assert_ptr_null(matrix.matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}

Suite *suite_remove_matrix(void) {
  Suite *s = suite_create("remove_matrix");

  TCase *tcase_basic = tcase_create("basic");
  tcase_add_test(tcase_basic, basic_test);
  tcase_add_test(tcase_basic, null_ptr_test);
  suite_add_tcase(s, tcase_basic);
  return s;
}