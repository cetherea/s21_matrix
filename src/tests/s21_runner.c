#include "s21_runner.h"


int main()
{
    SRunner *sr = srunner_create(NULL);

    srunner_add_suite(sr, suite_create_matrix());
    srunner_add_suite(sr, suite_remove_matrix());

    srunner_run_all(sr, CK_NORMAL);

    int failed = srunner_ntests_failed(sr);
    return (failed == 0) ? 0 : 1;
}