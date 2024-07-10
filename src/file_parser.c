#include "3DViewer.h"

// Заполнение структуры данных и первоначальное положение модели
model_data *data_filling(char *filename) {
  int vertices = 0;
  int polygons = 0;
  model_data *data;
  vertices_counter(filename, &vertices, &polygons);
  data = init_struct(vertices, polygons);
  data_parsing(filename, data);
  centering(data);
  scaling(data, scale_rate(0.75, max_for_scale(data)));
  return data;
}

// определение количества вершин и полигонов и проверка файла
int vertices_counter(char *file_name, int *vertices, int *polygons) {
  int status = OK;
  if (file_check(file_name) == ERROR) {
    status = ERROR;
  } else {
    FILE *obj_file = fopen(file_name, "r");
    char str[BUFF] = "";
    while (fgets(str, BUFF, obj_file) != NULL) {
      if (str[0] == 'v' && str[1] == ' ') *vertices += 1;
      if (str[0] == 'f' && str[1] == ' ') *polygons += 1;
    }
    fclose(obj_file);
    if (*vertices < 1 || *polygons < 1) status = ERROR;
  }
  return status;
}

// инициализация структуры данных
model_data *init_struct(int vert, int poly) {
  model_data *data = calloc(1, sizeof(model_data));
  data->polygon = calloc(poly, sizeof(polygon_t));
  data->matrix = NULL;
  data->matrix =
      (double **)malloc(vert * sizeof(double *) + vert * 3 * sizeof(double));
  data->matrix[0] = (double *)(data->matrix + vert);
  for (int i = 1; i < vert; i++) {
    data->matrix[i] = data->matrix[0] + i * 3;
  }
  data->min[0] = 0;
  data->min[1] = 0;
  data->min[2] = 0;
  data->max[0] = 0;
  data->max[1] = 0;
  data->max[2] = 0;
  return data;
}

// поиск минимальных и максимальных координат по трем осям
void check_minmax(model_data *Data, double x, double y, double z) {
  if (x < Data->min[0]) Data->min[0] = x;
  if (x > Data->max[0]) Data->max[0] = x;
  if (y < Data->min[1]) Data->min[1] = y;
  if (y > Data->max[1]) Data->max[1] = y;
  if (z < Data->min[2]) Data->min[2] = z;
  if (z > Data->max[2]) Data->max[2] = z;
}

// выделение памяти под массив вершин в структуре полигона
int *add_polygon(int *arr, int amount) {
  arr = calloc(amount, sizeof(int));
  return arr;
}

//  центрирование модели
void centering(model_data *Data) {
  double x = Data->min[0] + (Data->max[0] - Data->min[0]) / 2;
  double y = Data->min[1] + (Data->max[1] - Data->min[1]) / 2;
  double z = Data->min[2] + (Data->max[2] - Data->min[2]) / 2;
  for (int i = 0; i < Data->vertices; i++) {
    Data->matrix[i][0] -= x;
    Data->matrix[i][1] -= y;
    Data->matrix[i][2] -= z;
  }
}

// освобождение памяти, выделенной под данные модели
void mem_free(model_data *Data) {
  for (int i = 0; i < Data->polygons; i++) {
    free(Data->polygon[i].v);
  }
  free(Data->polygon);
  free(Data->matrix);
  free(Data);
}

// проверка файла на корректность
int file_check(char *filename) {
  int status = OK;
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    status = ERROR;
  } else {
    fclose(f);
  }
  return status;
}

// парсинг данных из .obj файла
void data_parsing(char *file_name, model_data *Data) {
  FILE *f_file = fopen(file_name, "r");
  char str[BUFF] = "";
  int v_num = 0;  // количество вершин
  int p_num = 0;  // количество полигонов
  while (fgets(str, BUFF, f_file) != NULL) {
    if (str[0] == 'v' && str[1] == ' ') {
      sscanf(str, "%*s %lf %lf %lf", &Data->matrix[v_num][0],
             &Data->matrix[v_num][1], &Data->matrix[v_num][2]);
      check_minmax(Data, Data->matrix[v_num][0], Data->matrix[v_num][1],
                   Data->matrix[v_num][2]);
      v_num++;
      Data->vertices++;
    }
    if (str[0] == 'f' && str[1] == ' ') {
      count_vert_on_poly(str, Data, p_num);
      vertex_to_polygon(str, Data, p_num, v_num);
      p_num++;
      Data->polygons++;
    }
  }
  fclose(f_file);
}

// определение количества вершин в полигоне
void count_vert_on_poly(char *line, model_data *Data, int poly_number) {
  int vert_amount = 0;  // количество вершин в полигоне
  int index = 1;
  while (line[index] != '\0') {
    if (line[index] == ' ' && isdigit(line[index + 1])) {
      vert_amount++;
    }
    index++;
  }
  Data->polygon[poly_number].v =
      add_polygon(Data->polygon[poly_number].v, vert_amount);
  Data->polygon[poly_number].amount = vert_amount;
}

// заполнение массива вершин в полигоне
void vertex_to_polygon(char *line, model_data *Data, int poly_number,
                       int vertices) {
  int index = 0;
  int v_p_num = 0;  // индекс вершины в полигоне
  while (line[index] != '\0') {
    if (line[index] == ' ' && isdigit(line[index + 1])) {
      index++;
      char number[12] = {0};
      for (int i = 0; isdigit(line[index]); i++) {
        number[i] = line[index];
        index++;
      }
      Data->polygon[poly_number].v[v_p_num] = atoi(number);
      v_p_num++;
      index--;
    }
    if (line[index] == ' ' && line[index + 1] == '-' &&
        isdigit(line[index + 2])) {
      index += 2;
      char number[12] = {0};
      for (int i = 0; isdigit(line[index]); i++) {
        number[i] = line[index];
        index++;
      }
      int numb = atoi(number);
      Data->polygon[poly_number].v[v_p_num] = vertices + 1 - numb;
      v_p_num++;
      index--;
    }
    Data->polygon[poly_number].amount = v_p_num;
    index++;
  }
}

// определение максимального расстояния по трем осям для первоначального
// масштабирования
double max_for_scale(model_data *figure) {
  double max = 0;
  double x = figure->max[0] - figure->min[0];
  double y = figure->max[1] - figure->min[1];
  double z = figure->max[2] - figure->min[2];
  if (x > y)
    max = x;
  else
    max = y;
  if (z > max) max = z;
  return max;
}

// коэффициент масштабирования
double scale_rate(double value, double max) {
  double scal = 0;
  scal = (value - (value * (-1))) / max;
  return scal;
}
