#include "c_tests.h"

START_TEST(file_check_1) {
  char file[256] = "nofile.txt";
  int status = file_check(file);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

START_TEST(file_check_2) {
  char file[256] = "c_tests/cube_first.txt";
  int status = file_check(file);
  ck_assert_int_eq(status, OK);
}
END_TEST

START_TEST(file_check_3) {
  int v = 0;
  int p = 0;
  char file[256] = "c_tests/trash.txt";
  int status = vertices_counter(file, &v, &p);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

Suite *test_file_check(void) {
  Suite *s = suite_create("\033[36m-=file_check=-\033[0m");
  TCase *tc = tcase_create("file_check");

  tcase_add_test(tc, file_check_1);
  tcase_add_test(tc, file_check_2);
  tcase_add_test(tc, file_check_3);

  suite_add_tcase(s, tc);
  return s;
}