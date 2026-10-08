#include "../s21_runner.h"

START_TEST(basic_test)
{
    int rows = 3, columns = 2;
    s21_matrix A = {0}, result = {0}, expected_result = {0};

    s21_create_matrix(rows, columns, &A);
    s21_create_matrix(columns, rows, &expected_result);

    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[1][0] = 3;
    A.matrix[1][1] = 4;
    A.matrix[2][0] = 5;
    A.matrix[2][1] = 6;

    expected_result.matrix[0][0] = 1;
    expected_result.matrix[0][1] = 3;
    expected_result.matrix[0][2] = 5;
    expected_result.matrix[1][0] = 2;
    expected_result.matrix[1][1] = 4;
    expected_result.matrix[1][2] = 6;

    int error = s21_transpose(&A, &result);
    int eq = s21_eq_matrix(&result, &expected_result);
    ck_assert_int_eq(error, 0);
    ck_assert_int_eq(eq, SUCCESS);

    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected_result);
}
END_TEST

START_TEST(basic_e7_test)
{
    int rows = 3, columns = 2;
    s21_matrix A = {0}, result = {0}, expected_result = {0};

    s21_create_matrix(rows, columns, &A);
    s21_create_matrix(columns, rows, &expected_result);

    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[1][0] = 3;
    A.matrix[1][1] = 4;
    A.matrix[2][0] = 5;
    A.matrix[2][1] = 6;

    expected_result.matrix[0][0] = 1 + 1e-7;
    expected_result.matrix[0][1] = 3 + 1e-7;
    expected_result.matrix[0][2] = 5 + 1e-7;
    expected_result.matrix[1][0] = 2 + 1e-7;
    expected_result.matrix[1][1] = 4 + 1e-7;
    expected_result.matrix[1][2] = 6 + 1e-7;

    int error = s21_transpose(&A, &result);
    int eq = s21_eq_matrix(&result, &expected_result);
    ck_assert_int_eq(error, 0);
    ck_assert_int_eq(eq, SUCCESS);

    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected_result);
}
END_TEST

START_TEST(null_matrix_test)
{
    s21_matrix result = {0};

    int error = s21_transpose(NULL, &result);
    ck_assert_int_eq(error, 1);
    ck_assert_ptr_null(result.matrix);

    s21_remove_matrix(&result);
}
END_TEST

START_TEST(empty_matrix_test)
{
    int rows = 3, columns = 2;
    s21_matrix A = {0}, result = {0};
    A.rows = rows;
    A.columns = columns;
    A.matrix = NULL;

    int error = s21_transpose(&A, &result);
    ck_assert_int_eq(error, 1);
    ck_assert_ptr_null(result.matrix);

    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(null_result_matrix_test)
{
    int rows = 3, columns = 2;
    s21_matrix A = {0};
    s21_create_matrix(rows, columns, &A);

    int error = s21_transpose(&A, NULL);
    ck_assert_int_eq(error, 1);

    s21_remove_matrix(&A);
}
END_TEST

START_TEST(invalide_size_test)
{
    int rows = 3, columns = 2;
    s21_matrix A = {0}, result = {0};

    s21_create_matrix(rows, columns, &A);

    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[1][0] = 3;
    A.matrix[1][1] = 4;
    A.matrix[2][0] = 5;
    A.matrix[2][1] = 6;
    A.columns = -3;

    int error = s21_transpose(&A, &result);
    ck_assert_int_eq(error, 1);
    ck_assert_ptr_null(result.matrix);

    A.columns = columns;
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST


Suite *suite_transpose_matrix(void)
{
    Suite *s = suite_create("transpose_matrix");

    TCase *tcase_basic = tcase_create("basic");
    tcase_add_test(tcase_basic, basic_test);
    tcase_add_test(tcase_basic, basic_e7_test);
    suite_add_tcase(s, tcase_basic);

    TCase *tcase_fail = tcase_create("fail");
    tcase_add_test(tcase_fail, invalide_size_test);
    tcase_add_test(tcase_fail, null_matrix_test);
    tcase_add_test(tcase_fail, empty_matrix_test);
    tcase_add_test(tcase_fail, null_result_matrix_test);
    suite_add_tcase(s, tcase_fail);

    return s;
}