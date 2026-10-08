#include "s21_runner.h"

int main()
{
  SRunner *sr = srunner_create(NULL);

  srunner_add_suite(sr, suite_create_matrix());
  srunner_add_suite(sr, suite_remove_matrix());
  srunner_add_suite(sr, suite_eq_matrix());
  srunner_add_suite(sr, suite_sum_matrix());
  srunner_add_suite(sr, suite_sub_matrix());
  srunner_add_suite(sr, suite_mult_number_matrix());
  srunner_add_suite(sr, suite_mult_matrix());
  srunner_add_suite(sr, suite_transpose_matrix());

  srunner_run_all(sr, CK_NORMAL);

  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (failed == 0) ? 0 : 1;
}