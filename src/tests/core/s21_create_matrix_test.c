#include "../s21_runner.h"

START_TEST(basic_test)
{

    int expected_rows = 3;
    int expected_columns = 4;
    s21_matrix matrix = {0};
    int error = s21_create_matrix(expected_rows, expected_columns, &matrix);

    ck_assert_int_eq(error, 0);
    ck_assert_int_eq(expected_rows, matrix.rows);
    ck_assert_int_eq(expected_columns, matrix.columns);
    ck_assert_ptr_nonnull(matrix.matrix);
    for (int i = 0; i < expected_rows; i++)
    {
        ck_assert_ptr_nonnull(matrix.matrix[i]);
    }
}
END_TEST

START_TEST(negative_error_test)
{
    int expected_rows = -3;
    int expected_columns = -4;
    s21_matrix matrix = {0};
    int error = s21_create_matrix(expected_rows, expected_columns, &matrix);

    ck_assert_int_eq(error, 1);
    ck_assert_ptr_null(matrix.matrix);
}
END_TEST

START_TEST(null_error_test)
{
    int expected_rows = -3;
    int expected_columns = -4;
    int error = s21_create_matrix(expected_rows, expected_columns, NULL);

    ck_assert_int_eq(error, 1);
}
END_TEST

Suite *suite_create_matrix(void)
{
    Suite *s = suite_create("create_matrix");

    TCase *tcase_basic = tcase_create("basic");
    tcase_add_test(tcase_basic, basic_test);
    suite_add_tcase(s, tcase_basic);

    TCase *tcase_fail = tcase_create("fail");
    tcase_add_test(tcase_fail, negative_error_test);
    tcase_add_test(tcase_fail, null_error_test);
    suite_add_tcase(s, tcase_fail);

    return s;
}