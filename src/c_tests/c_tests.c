#include "c_tests.h"

int main(void) {
  int failed = 0;
  Suite *s21_3dviewer_test[] = {test_file_check(), test_file_parser(),
                                test_moving(),     test_rotation(),
                                test_scaling(),    NULL};
  printf("\033[92m============= UNIT TESTS: =============\033[0m\n");
  for (int i = 0; s21_3dviewer_test[i] != NULL; i++) {
    SRunner *sr = srunner_create(s21_3dviewer_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("\033[92m============== FAILED: %d ==============\033[0m\n", failed);

  return failed == 0 ? 0 : 1;
}