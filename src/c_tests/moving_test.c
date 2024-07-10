#include "c_tests.h"

/* cube_first.obj (scaled)
      x        y        z
v    0.75     0.75    -0.75
v    0.75    -0.75    -0.75
v    0.75     0.75     0.75
v    0.75    -0.75     0.75
v   -0.75     0.75    -0.75
v   -0.75    -0.75    -0.75
v   -0.75     0.75     0.75
v   -0.75    -0.75     0.75
*/

START_TEST(moving_1) {
  char file[256] = "c_tests/cube_first.txt";
  double x1 = 1;
  double y1 = 1.25;
  double z1 = 0.25;
  model_data *data = data_filling(file);
  moving(data, 0.25, 0);
  moving(data, 0.5, 1);
  moving(data, 1, 2);
  ck_assert_double_eq(x1, data->matrix[0][0]);
  ck_assert_double_eq(y1, data->matrix[0][1]);
  ck_assert_double_eq(z1, data->matrix[0][2]);
  mem_free(data);
}
END_TEST

START_TEST(moving_2) {
  char file[256] = "c_tests/cube_first.txt";
  double x8 = -1;
  double y8 = -1.25;
  double z8 = -0.25;
  model_data *data = data_filling(file);
  moving(data, -0.25, 0);
  moving(data, -0.5, 1);
  moving(data, -1, 2);
  ck_assert_double_eq(x8, data->matrix[7][0]);
  ck_assert_double_eq(y8, data->matrix[7][1]);
  ck_assert_double_eq(z8, data->matrix[7][2]);
  mem_free(data);
}
END_TEST

START_TEST(moving_3) {
  char file[256] = "c_tests/cube_first.txt";
  double x1 = 1;
  double y1 = 1;
  double z1 = -0.5;
  model_data *data = data_filling(file);
  matrix_shift(data, 0.25, 0.25, 0.25);
  ck_assert_double_eq(x1, data->matrix[0][0]);
  ck_assert_double_eq(y1, data->matrix[0][1]);
  ck_assert_double_eq(z1, data->matrix[0][2]);
  mem_free(data);
}
END_TEST

/* pyramid.txt (centered & scaled)
      x        y        z
v    0.0      0.375    0.0
v   -0.75    -0.375   -0.75
v    0.75    -0.375   -0.75
v    0.75    -0.375    0.75
v   -0.75    -0.375    0.75
*/

START_TEST(moving_4) {
  char file[256] = "c_tests/pyramid.txt";
  double x1 = 0.25;
  double y1 = 0.875;
  double z1 = 1;
  model_data *data = data_filling(file);
  moving(data, 0.25, 0);
  moving(data, 0.5, 1);
  moving(data, 1, 2);
  ck_assert_double_eq(x1, data->matrix[0][0]);
  ck_assert_double_eq(y1, data->matrix[0][1]);
  ck_assert_double_eq(z1, data->matrix[0][2]);
  mem_free(data);
}
END_TEST

START_TEST(moving_5) {
  char file[256] = "c_tests/pyramid.txt";
  double x5 = -1;
  double y5 = -0.875;
  double z5 = -0.25;
  model_data *data = data_filling(file);
  moving(data, -0.25, 0);
  moving(data, -0.5, 1);
  moving(data, -1, 2);
  ck_assert_double_eq(x5, data->matrix[4][0]);
  ck_assert_double_eq(y5, data->matrix[4][1]);
  ck_assert_double_eq(z5, data->matrix[4][2]);
  mem_free(data);
}
END_TEST

START_TEST(moving_6) {
  char file[256] = "c_tests/pyramid.txt";
  double x1 = 0.25;
  double y1 = 0.625;
  double z1 = 0.25;
  model_data *data = data_filling(file);
  matrix_shift(data, 0.25, 0.25, 0.25);
  ck_assert_double_eq(x1, data->matrix[0][0]);
  ck_assert_double_eq(y1, data->matrix[0][1]);
  ck_assert_double_eq(z1, data->matrix[0][2]);
  mem_free(data);
}
END_TEST

Suite *test_moving(void) {
  Suite *s = suite_create("\033[36m-=moving=-\033[0m");
  TCase *tc = tcase_create("moving");

  tcase_add_test(tc, moving_1);
  tcase_add_test(tc, moving_2);
  tcase_add_test(tc, moving_3);
  tcase_add_test(tc, moving_4);
  tcase_add_test(tc, moving_5);
  tcase_add_test(tc, moving_6);

  suite_add_tcase(s, tc);
  return s;
}