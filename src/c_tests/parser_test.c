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

START_TEST(file_parser_1) {
  char file[256] = "c_tests/cube_first.txt";
  int vert_am = 8;
  int pol_am = 12;
  model_data *data = data_filling(file);
  ck_assert_int_eq(vert_am, data->vertices);
  ck_assert_int_eq(pol_am, data->polygons);
  mem_free(data);
}
END_TEST

START_TEST(file_parser_2) {
  char file[256] = "c_tests/cube_first.txt";
  model_data *data = data_filling(file);
  double correctMin[3] = {-1, -1, -1};
  double correctMax[3] = {1, 1, 1};
  for (int i = 0; i < 2; i++) {
    ck_assert_double_eq(correctMax[i], data->max[i]);
    ck_assert_double_eq(correctMin[i], data->min[i]);
  }
  mem_free(data);
}
END_TEST

START_TEST(file_parser_3) {
  char file[256] = "c_tests/cube_first.txt";
  model_data *data = data_filling(file);
  int poly[12][3] = {{5, 3, 1}, {3, 8, 4}, {7, 6, 8}, {2, 8, 6},
                     {1, 4, 2}, {5, 2, 6}, {5, 7, 3}, {3, 7, 8},
                     {7, 5, 6}, {2, 4, 8}, {1, 3, 4}, {5, 1, 2}};
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_int_eq(poly[i][j], data->polygon[i].v[j]);
    }
  }
  mem_free(data);
}
END_TEST

START_TEST(file_parser_4) {
  char file[256] = "c_tests/cube_first.txt";
  model_data *data = data_filling(file);
  double coord[8][3] = {{1, 1, -1},  {1, -1, -1},  {1, 1, 1},  {1, -1, 1},
                        {-1, 1, -1}, {-1, -1, -1}, {-1, 1, 1}, {-1, -1, 1}};
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      coord[i][j] *= 0.75;  // scaling
    }
  }
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

START_TEST(file_parser_5) {
  char file[256] = "c_tests/pyramid.txt";
  int vert_am = 5;
  int pol_am = 8;
  model_data *data = data_filling(file);
  ck_assert_int_eq(vert_am, data->vertices);
  ck_assert_int_eq(pol_am, data->polygons);
  mem_free(data);
}
END_TEST

START_TEST(file_parser_6) {
  char file[256] = "c_tests/pyramid.txt";
  model_data *data = data_filling(file);
  double correctMin[3] = {-1, 0, -1};
  double correctMax[3] = {1, 1, 1};
  for (int i = 0; i < 2; i++) {
    ck_assert_double_eq(correctMax[i], data->max[i]);
    ck_assert_double_eq(correctMin[i], data->min[i]);
  }
  mem_free(data);
}
END_TEST

// START_TEST(file_parser_7) {
//   char file[256] = "c_tests/pyramid.txt";
//   model_data *data = data_filling(file);
//   int poly[8][3] = {
//     {1, 2, 3},
//     {1, 0, 0},
//     {1, 0, 0},
//     {1, 3, 4},
//     {1, 4, 5},
//     {1, 5, 2},
//     {3, 2, 4},
//     {2, 5, 4}
//   };
//   for (int i = 0; i < 8; i++) {
//     for (int j = 0; j < 3; j++) {
//       ck_assert_int_eq(poly[i][j], data->polygon[i].v[j]);
//     }
//   }
//   mem_free(data);
// }
// END_TEST

START_TEST(file_parser_8) {
  char file[256] = "c_tests/pyramid.txt";
  model_data *data = data_filling(file);
  double coord[5][3] = {{0, 0.375, 0},
                        {-0.75, -0.375, -0.75},
                        {0.75, -0.375, -0.75},
                        {0.75, -0.375, 0.75},
                        {-0.75, -0.375, 0.75}};
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq(coord[i][j], data->matrix[i][j]);
    }
  }
  mem_free(data);
}
END_TEST

Suite *test_file_parser(void) {
  Suite *s = suite_create("\033[36m-=file_parser=-\033[0m");
  TCase *tc = tcase_create("file_parser");

  tcase_add_test(tc, file_parser_1);
  tcase_add_test(tc, file_parser_2);
  tcase_add_test(tc, file_parser_3);
  tcase_add_test(tc, file_parser_4);
  tcase_add_test(tc, file_parser_5);
  tcase_add_test(tc, file_parser_6);
  // tcase_add_test(tc, file_parser_7);
  tcase_add_test(tc, file_parser_8);

  suite_add_tcase(s, tc);
  return s;
}