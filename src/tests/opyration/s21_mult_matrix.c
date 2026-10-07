#include "../s21_runner.h"

START_TEST(basic_test)
{
    int rowsA = 2, columnsA = 3, rowsB = 3, columnsB = 2;
    s21_matrix A = {0}, B = {0}, result = {0}, expected_result = {0};
    s21_create_matrix(rowsA, columnsA, &A);
    s21_create_matrix(rowsB, columnsB, &B);
    s21_create_matrix(rowsA, columnsB, &expected_result);

    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[0][2] = 3;
    A.matrix[1][0] = 0;
    A.matrix[1][1] = 4;
    A.matrix[1][2] = 5;

    B.matrix[0][0] = 2;
    B.matrix[0][1] = 1;
    B.matrix[1][0] = 1;
    B.matrix[1][1] = 2;
    B.matrix[2][0] = 0;
    B.matrix[2][1] = 3;

    expected_result.matrix[0][0] = 4;
    expected_result.matrix[0][1] = 14;
    expected_result.matrix[1][0] = 4;
    expected_result.matrix[1][1] = 23;

    int error = s21_mult_matrix(&A, &B, &result);
    int eq = s21_eq_matrix(&result, &expected_result);

    ck_assert_int_eq(error, 0);
    ck_assert_int_eq(eq, SUCCESS);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected_result);
}
END_TEST

START_TEST(basic_e7_test)
{
    int rowsA = 2, columnsA = 3, rowsB = 3, columnsB = 2;
    s21_matrix A = {0}, B = {0}, result = {0}, expected_result = {0};
    s21_create_matrix(rowsA, columnsA, &A);
    s21_create_matrix(rowsB, columnsB, &B);
    s21_create_matrix(rowsA, columnsB, &expected_result);

    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[0][2] = 3;
    A.matrix[1][0] = 0;
    A.matrix[1][1] = 4;
    A.matrix[1][2] = 5;

    B.matrix[0][0] = 2;
    B.matrix[0][1] = 1;
    B.matrix[1][0] = 1;
    B.matrix[1][1] = 2;
    B.matrix[2][0] = 0;
    B.matrix[2][1] = 3;

    expected_result.matrix[0][0] = 4 + 1e-7;
    expected_result.matrix[0][1] = 14 + 1e-7;
    expected_result.matrix[1][0] = 4 + 1e-7;
    expected_result.matrix[1][1] = 23 + 1e-7;

    int error = s21_mult_matrix(&A, &B, &result);
    int eq = s21_eq_matrix(&result, &expected_result);

    ck_assert_int_eq(error, 0);
    ck_assert_int_eq(eq, SUCCESS);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected_result);
}
END_TEST

START_TEST(incorrect_size_test)
{
    int rowsA = 2, columnsA = 2, rowsB = 3, columnsB = 2;
    s21_matrix A = {0}, B = {0}, result = {0};
    s21_create_matrix(rowsA, columnsA, &A);
    s21_create_matrix(rowsB, columnsB, &B);

    int error = s21_mult_matrix(&A, &B, &result);

    ck_assert_int_eq(error, 2);
    ck_assert_ptr_null(result.matrix);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(null_matrix_test)
{
    int rowsA = 2, columnsA = 2;
    s21_matrix A = {0}, result = {0};
    s21_create_matrix(rowsA, columnsA, &A);

    int error = s21_mult_matrix(&A, NULL, &result);

    ck_assert_int_eq(error, 1);
    ck_assert_ptr_null(result.matrix);

    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(empty_matrix_test)
{
    int rowsA = 2, columnsA = 2, rowsB = 3, columnsB = 2;
    s21_matrix A = {0}, B = {0}, result = {0};
    s21_create_matrix(rowsA, columnsA, &A);
    B.columns = columnsB;
    B.rows = rowsB;
    B.matrix = NULL;

    int error = s21_mult_matrix(&A, &B, &result);

    ck_assert_int_eq(error, 1);
    ck_assert_ptr_null(result.matrix);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(null_result_matrix_test)
{
    int rowsA = 2, columnsA = 3, rowsB = 3, columnsB = 2;
    s21_matrix A = {0}, B = {0};
    s21_create_matrix(rowsA, columnsA, &A);
    s21_create_matrix(rowsB, columnsB, &B);

    int error = s21_mult_matrix(&A, &B, NULL);

    ck_assert_int_eq(error, 1);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

Suite *suite_mult_matrix(void)
{
    Suite *s = suite_create("mul_matrix");

    TCase *tcase_basic = tcase_create("basic");
    tcase_add_test(tcase_basic, basic_test);
    tcase_add_test(tcase_basic, basic_e7_test);
    suite_add_tcase(s, tcase_basic);

    TCase *tcase_fail = tcase_create("fail");
    tcase_add_test(tcase_fail, incorrect_size_test);
    tcase_add_test(tcase_fail, null_matrix_test);
    tcase_add_test(tcase_fail, empty_matrix_test);
    tcase_add_test(tcase_fail, null_result_matrix_test);
    suite_add_tcase(s, tcase_fail);

    return s;
}