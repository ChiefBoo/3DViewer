#include "c_tests.h"

START_TEST(rotation_1) {
  char file[256] = "c_tests/cube_first.txt";
  double x1 = 0.75;
  model_data *data = data_filling(file);
  rotation_ox(data, 10);
  ck_assert_double_eq(x1, data->matrix[0][0]);
  mem_free(data);
}
END_TEST

START_TEST(rotation_2) {
  char file[256] = "c_tests/cube_first.txt";
  double y1 = 0.75;
  model_data *data = data_filling(file);
  rotation_oy(data, 10);
  ck_assert_double_eq(y1, data->matrix[0][1]);
  mem_free(data);
}
END_TEST

START_TEST(rotation_3) {
  char file[256] = "c_tests/cube_first.txt";
  double z1 = -0.75;
  model_data *data = data_filling(file);
  rotation_oz(data, 10);
  ck_assert_double_eq(z1, data->matrix[0][2]);
  mem_free(data);
}
END_TEST

/* cube_first.txt (scaled)
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

START_TEST(rotation_4) {
  char file[256] = "c_tests/cube_first.txt";
  model_data *data = data_filling(file);
  rotation_ox(data, 90);
  double coord[8][3] = {{0.75, -1.00655, -0.33444},  {0.75, -0.33444, 1.00655},
                        {0.75, 0.33444, -1.00655},   {0.75, 1.00655, 0.33444},
                        {-0.75, -1.00655, -0.33444}, {-0.75, -0.33444, 1.00655},
                        {-0.75, 0.33444, -1.00655},  {-0.75, 1.00655, 0.33444}};
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(coord[i][j], data->matrix[i][j], 1e-05);
    }
  }
  mem_free(data);
}
END_TEST

Suite *test_rotation(void) {
  Suite *s = suite_create("\033[36m-=rotation=-\033[0m");
  TCase *tc = tcase_create("rotation");

  tcase_add_test(tc, rotation_1);
  tcase_add_test(tc, rotation_2);
  tcase_add_test(tc, rotation_3);
  tcase_add_test(tc, rotation_4);

  suite_add_tcase(s, tc);
  return s;
}