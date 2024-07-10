#ifndef SRC_3DVIEWER_H_
#define SRC_3DVIEWER_H_

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define ERROR 1
#define BUFF 1024

// структура полигона - количество точек в полигоне + массив точек

typedef struct {
  int amount;
  int *v;
} polygon_t;

// Основная структура для хранения данных:
// Количество точек и полигонов;
// массив структур полигонов;
// координатная матрица (переделать - убрать структуру)
// мин и макс значения по трем осям

typedef struct {
  int vertices;
  int polygons;
  polygon_t *polygon;
  // matrix_t coordinates;
  double **matrix;
  double min[3];
  double max[3];
} model_data;

//ПАРСИНГ
int vertices_counter(char *file_name, int *vertices, int *polygons);
model_data *data_filling(char *file_name);
void mem_free(model_data *data);
int file_check(char *filename);
model_data *init_struct(int vert, int poly);
int *add_polygon(int *arr, int amount);
void data_parsing(char *file_name, model_data *Data);
void centering(model_data *data);
void check_minmax(model_data *Data, double x, double y, double z);
void count_vert_on_poly(char *line, model_data *Data, int poly_number);
void vertex_to_polygon(char *line, model_data *Data, int poly_number,
                       int vertices);

// вращение модели
void rotation_ox(model_data *data, double value);
void rotation_oy(model_data *data, double value);
void rotation_oz(model_data *data, double value);
// перемещение модели
void moving(model_data *data, double value, int coordinate);
// масштабирование модели
void scaling(model_data *data, double scale_value);
double max_for_scale(model_data *data);
double scale_rate(double value, double max);
// возвращение модели в центр (для вращения и масштабирования)
void matrix_shift(model_data *data, double x, double y, double z);

#endif  // SRC_3DVIEWER_H_
