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

START_TEST(scaling_1) {
  char file[256] = "c_tests/cube_first.txt";
  double coord[8][3] = {{1.5, 1.5, -1.5}, {1.5, -1.5, -1.5}, {1.5, 1.5, 1.5},
                        {1.5, -1.5, 1.5}, {-1.5, 1.5, -1.5}, {-1.5, -1.5, -1.5},
                        {-1.5, 1.5, 1.5}, {-1.5, -1.5, 1.5}};
  model_data *data = data_filling(file);
  scaling(data, 2);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq(coord[i][j], data->matrix[i][j]);
    }
  }
  mem_free(data);
}
END_TEST

START_TEST(scaling_2) {
  char file[256] = "c_tests/cube_first.txt";
  double coord[8][3] = {{-1.5, -1.5, 1.5}, {-1.5, 1.5, 1.5}, {-1.5, -1.5, -1.5},
                        {-1.5, 1.5, -1.5}, {1.5, -1.5, 1.5}, {1.5, 1.5, 1.5},
                        {1.5, -1.5, -1.5}, {1.5, 1.5, -1.5}};
  model_data *data = data_filling(file);
  scaling(data, -2);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq(coord[i][j], data->matrix[i][j]);
    }
  }
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

START_TEST(scaling_3) {
  char file[256] = "c_tests/pyramid.txt";
  double coord[5][3] = {{0.0, 0.75, 0.0},
                        {-1.5, -0.75, -1.5},
                        {1.5, -0.75, -1.5},
                        {1.5, -0.75, 1.5},
                        {-1.5, -0.75, 1.5}};
  model_data *data = data_filling(file);
  scaling(data, 2);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq(coord[i][j], data->matrix[i][j]);
    }
  }
  mem_free(data);
}
END_TEST

START_TEST(scaling_4) {
  char file[256] = "c_tests/pyramid.txt";
  double coord[5][3] = {{0.0, -0.75, 0.0},
                        {1.5, 0.75, 1.5},
                        {-1.5, 0.75, 1.5},
                        {-1.5, 0.75, -1.5},
                        {1.5, 0.75, -1.5}};
  model_data *data = data_filling(file);
  scaling(data, -2);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq(coord[i][j], data->matrix[i][j]);
    }
  }
  mem_free(data);
}
END_TEST

Suite *test_scaling(void) {
  Suite *s = suite_create("\033[36m-=scaling=-\033[0m");
  TCase *tc = tcase_create("scaling");

  tcase_add_test(tc, scaling_1);
  tcase_add_test(tc, scaling_2);
  tcase_add_test(tc, scaling_3);
  tcase_add_test(tc, scaling_4);

  suite_add_tcase(s, tc);
  return s;
}