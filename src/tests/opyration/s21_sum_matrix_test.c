#include "../s21_runner.h"

START_TEST(basic_test)
{
    int rows = 3, columns = 4;
    s21_matrix A = {0}, B = {0}, result = {0}, expected_result = {0};
    s21_create_matrix(rows, columns, &A);
    s21_create_matrix(rows, columns, &B);
    s21_create_matrix(rows, columns, &expected_result);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            A.matrix[i][j] = (i + j);
            B.matrix[i][j] = (i + j);
            expected_result.matrix[i][j] = (i + j) * 2;
        }
    }

    int error = s21_sum_matrix(&A, &B, &result);
    int eq = s21_eq_matrix(&A, &B);

    ck_assert_int_eq(error, 0);
    ck_assert_int_eq(eq, SUCCESS);
}
END_TEST

START_TEST(basic_e7_test)
{
    int rows = 3, columns = 4;
    s21_matrix A = {0}, B = {0}, result = {0}, expected_result = {0};
    s21_create_matrix(rows, columns, &A);
    s21_create_matrix(rows, columns, &B);
    s21_create_matrix(rows, columns, &expected_result);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            A.matrix[i][j] = (i + j) + 1e-7;
            B.matrix[i][j] = (i + j) + 1e-7;
            expected_result.matrix[i][j] = (i + j) * 2;
        }
    }

    int error = s21_sum_matrix(&A, &B, &result);
    int eq = s21_eq_matrix(&A, &B);

    ck_assert_int_eq(error, 0);
    ck_assert_int_eq(eq, SUCCESS);
}
END_TEST

START_TEST(different_size_test)
{
    int rowsA = 3, rowsB = 4, columns = 4;
    s21_matrix A = {0}, B = {0}, result = {0};
    s21_create_matrix(rowsA, columns, &A);
    s21_create_matrix(rowsB, columns, &B);

    int error = s21_sum_matrix(&A, &B, &result);

    ck_assert_int_eq(error, 2);
}
END_TEST

START_TEST(null_matrix_test)
{
    int rowsA = 3, rowsB = 4, columns = 4;
    s21_matrix A = {0}, result = {0};
    s21_create_matrix(rowsA, columns, &A);

    int error = s21_sum_matrix(&A, NULL, &result);

    ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(empty_matrix_test)
{
    int rowsA = 3, columns = 4;
    s21_matrix A = {0}, B = {0}, result = {0};
    s21_create_matrix(rowsA, columns, &A);
    B.matrix = NULL;
    B.columns = 4;
    B.rows = 3;

    int error = s21_sum_matrix(&A, &B, &result);

    ck_assert_int_eq(error, 1);
}
END_TEST


Suite *suite_sum_matrix(void)
{
    Suite *s = suite_create("sum_matrix");

    TCase *tcase_basic = tcase_create("basic");
    tcase_add_test(tcase_basic, basic_test);
    tcase_add_test(tcase_basic, basic_e7_test);
    suite_add_tcase(s, tcase_basic);

    TCase *tcase_fail = tcase_create("fail");
    tcase_add_test(tcase_fail, different_size_test);
    tcase_add_test(tcase_fail, null_matrix_test);
    tcase_add_test(tcase_fail, empty_matrix_test);
    suite_add_tcase(s, tcase_fail);

    return s;
}