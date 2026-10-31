#include "../s21_runner.h"

START_TEST(basic_test_1x1) {
  s21_matrix A = {0}, result = {0}, expected_result = {0};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &expected_result);

  A.matrix[0][0] = 5;
  expected_result.matrix[0][0] = 0.2;

  int error = s21_inverse_matrix(&A, &result);
  int eq = s21_eq_matrix(&result, &expected_result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
}
END_TEST

START_TEST(basic_test_1x1_negative) {
  s21_matrix A = {0}, result = {0}, expected_result = {0};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &expected_result);

  A.matrix[0][0] = -4;
  expected_result.matrix[0][0] = -0.25;

  int error = s21_inverse_matrix(&A, &result);
  int eq = s21_eq_matrix(&result, &expected_result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
}
END_TEST

START_TEST(basic_test_2x2) {
  s21_matrix A = {0}, result = {0}, expected_result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected_result);

  A.matrix[0][0] = 4;
  A.matrix[0][1] = 7;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 6;

  expected_result.matrix[0][0] = 0.6;
  expected_result.matrix[0][1] = -0.7;
  expected_result.matrix[1][0] = -0.2;
  expected_result.matrix[1][1] = 0.4;

  int error = s21_inverse_matrix(&A, &result);
  int eq = s21_eq_matrix(&result, &expected_result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
}
END_TEST

START_TEST(basic_test_3x3) {
  s21_matrix A = {0}, result = {0}, expected_result = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &expected_result);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  expected_result.matrix[0][0] = 1;
  expected_result.matrix[0][1] = -1;
  expected_result.matrix[0][2] = 1;
  expected_result.matrix[1][0] = -38;
  expected_result.matrix[1][1] = 41;
  expected_result.matrix[1][2] = -34;
  expected_result.matrix[2][0] = 27;
  expected_result.matrix[2][1] = -29;
  expected_result.matrix[2][2] = 24;

  int error = s21_inverse_matrix(&A, &result);
  int eq = s21_eq_matrix(&result, &expected_result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
}
END_TEST

START_TEST(basic_e7_test) {
  s21_matrix A = {0}, result = {0}, expected_result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected_result);

  A.matrix[0][0] = 4;
  A.matrix[0][1] = 7;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 6;

  expected_result.matrix[0][0] = 0.6 + 1e-8;
  expected_result.matrix[0][1] = -0.7 + 1e-8;
  expected_result.matrix[1][0] = -0.2 + 1e-8;
  expected_result.matrix[1][1] = 0.4 + 1e-8;

  int error = s21_inverse_matrix(&A, &result);
  int eq = s21_eq_matrix(&result, &expected_result);

  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
}
END_TEST

START_TEST(extended_test_4x4_identity_product) {
  s21_matrix A = {0}, result = {0}, product = {0}, identity = {0};
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &identity);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 0;
  A.matrix[0][3] = 0;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 1;
  A.matrix[1][3] = 0;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = 1;
  A.matrix[2][2] = 4;
  A.matrix[2][3] = 1;
  A.matrix[3][0] = 0;
  A.matrix[3][1] = 0;
  A.matrix[3][2] = 1;
  A.matrix[3][3] = 5;

  for (int i = 0; i < 4; i++) identity.matrix[i][i] = 1;

  int error = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(error, 0);

  int mult_error = s21_mult_matrix(&A, &result, &product);
  int eq = s21_eq_matrix(&product, &identity);

  ck_assert_int_eq(mult_error, 0);
  ck_assert_int_eq(eq, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&product);
  s21_remove_matrix(&identity);
}
END_TEST

START_TEST(zero_1x1_test) {
  s21_matrix A = {0}, result = {0};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 0;

  int error = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(error, 2);
  ck_assert_ptr_null(result.matrix);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(singular_3x3_test) {
  s21_matrix A = {0}, result = {0};
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  int error = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(error, 2);
  ck_assert_ptr_null(result.matrix);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(singular_4x4_test) {
  s21_matrix A = {0}, result = {0};
  s21_create_matrix(4, 4, &A);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 3;
  A.matrix[0][2] = 4;
  A.matrix[0][3] = 5;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 3;
  A.matrix[1][3] = 4;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = 1;
  A.matrix[2][2] = 2;
  A.matrix[2][3] = 3;
  A.matrix[3][0] = 0;
  A.matrix[3][1] = 0;
  A.matrix[3][2] = 1;
  A.matrix[3][3] = 2;

  int error = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(error, 2);
  ck_assert_ptr_null(result.matrix);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(incorrect_size_test) {
  s21_matrix A = {0}, result = {0};
  s21_create_matrix(3, 4, &A);

  int error = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(error, 2);
  ck_assert_ptr_null(result.matrix);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(null_matrix_test) {
  s21_matrix result = {0};

  int error = s21_inverse_matrix(NULL, &result);

  ck_assert_int_eq(error, 1);
  ck_assert_ptr_null(result.matrix);

  s21_remove_matrix(&result);
}
END_TEST

START_TEST(empty_matrix_test) {
  s21_matrix A = {0}, result = {0};
  A.rows = 3;
  A.columns = 3;
  A.matrix = NULL;

  int error = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(error, 1);
  ck_assert_ptr_null(result.matrix);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(null_result_matrix_test) {
  s21_matrix A = {0};
  s21_create_matrix(3, 3, &A);

  int error = s21_inverse_matrix(&A, NULL);

  ck_assert_int_eq(error, 1);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(invalide_size_test) {
  int rows = 3, columns = 3;
  s21_matrix A = {0}, result = {0};
  s21_create_matrix(rows, columns, &A);
  A.columns = -3;

  int error = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(error, 1);
  ck_assert_ptr_null(result.matrix);

  A.columns = columns;
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite *suite_inverse_matrix(void) {
  Suite *s = suite_create("inverse_matrix");

  TCase *tcase_basic = tcase_create("basic");
  tcase_add_test(tcase_basic, basic_test_1x1);
  tcase_add_test(tcase_basic, basic_test_1x1_negative);
  tcase_add_test(tcase_basic, basic_test_2x2);
  tcase_add_test(tcase_basic, basic_test_3x3);
  tcase_add_test(tcase_basic, basic_e7_test);
  tcase_add_test(tcase_basic, extended_test_4x4_identity_product);
  suite_add_tcase(s, tcase_basic);

  TCase *tcase_fail = tcase_create("fail");
  tcase_add_test(tcase_fail, zero_1x1_test);
  tcase_add_test(tcase_fail, singular_3x3_test);
  tcase_add_test(tcase_fail, singular_4x4_test);
  tcase_add_test(tcase_fail, incorrect_size_test);
  tcase_add_test(tcase_fail, null_matrix_test);
  tcase_add_test(tcase_fail, empty_matrix_test);
  tcase_add_test(tcase_fail, null_result_matrix_test);
  tcase_add_test(tcase_fail, invalide_size_test);
  suite_add_tcase(s, tcase_fail);

  return s;
}