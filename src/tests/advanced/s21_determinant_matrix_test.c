#include "../s21_runner.h"

START_TEST(basic_test_1x1)
{
    s21_matrix A = {0};
    double result;
    int rows = 1, columns = 1;
    s21_create_matrix(rows, columns, &A);
    A.matrix[0][0] = 1;

    int error = s21_determinant(&A, &result);
    ck_assert_int_eq(error, 0);
    ck_assert_double_eq(result, 1.0);
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(extended_test_4x4)
{
    s21_matrix A = {0};
    double result;
    int rows = 4, columns = 4;
    s21_create_matrix(rows, columns, &A);
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

    int error = s21_determinant(&A, &result);
    ck_assert_int_eq(error, 0);
    ck_assert_double_eq(result, 0.0);
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(error_test_not_square)
{
    s21_matrix A = {0};
    double result = 0;
    int rows = 3, columns = 4;
    s21_create_matrix(rows, columns, &A);

    int error = s21_determinant(&A, &result);
    ck_assert_int_eq(error, 2);
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(null_matrix_test)
{
    double result;

    int error = s21_determinant(NULL, &result);
    ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(empty_matrix_test)
{
    int rows = 3, columns = 3;
    double result;
    s21_matrix A = {0};
    A.rows = rows;
    A.columns = columns;
    A.matrix = NULL;

    int error = s21_determinant(&A, &result);
    ck_assert_int_eq(error, 1);

    s21_remove_matrix(&A);
}
END_TEST

START_TEST(null_result_matrix_test)
{
    int rows = 3, columns = 3;
    s21_matrix A = {0};
    s21_create_matrix(rows, columns, &A);

    int error = s21_determinant(&A, NULL);
    ck_assert_int_eq(error, 1);

    s21_remove_matrix(&A);
}
END_TEST

START_TEST(invalide_size_test)
{
    int rows = 4, columns = 4;
    s21_matrix A = {0};
    double result;

    s21_create_matrix(rows, columns, &A);

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
    A.columns = -4;

    int error = s21_determinant(&A, &result);
    ck_assert_int_eq(error, 1);

    A.columns = columns;
    s21_remove_matrix(&A);
}
END_TEST



Suite *suite_determinant_matrix(void)
{
    Suite *s = suite_create("determinant_matrix");

    TCase *tcase_basic = tcase_create("basic");
    tcase_add_test(tcase_basic, basic_test_1x1);
    tcase_add_test(tcase_basic, extended_test_4x4);
    suite_add_tcase(s, tcase_basic);

    TCase *tcase_fail = tcase_create("fail");
    tcase_add_test(tcase_fail, error_test_not_square);
    tcase_add_test(tcase_fail, null_matrix_test);
    tcase_add_test(tcase_fail, empty_matrix_test);
    tcase_add_test(tcase_fail, null_result_matrix_test);
    tcase_add_test(tcase_fail, invalide_size_test);
    suite_add_tcase(s, tcase_fail);

    return s;
}