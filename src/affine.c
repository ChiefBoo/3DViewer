#include "3DViewer.h"

void scaling(model_data *data, double scale_value) {
  for (int i = 0; i < data->vertices; i++) {
    data->matrix[i][0] *= scale_value;
    data->matrix[i][1] *= scale_value;
    data->matrix[i][2] *= scale_value;
  }
}

void moving(model_data *data, double shift, int coordinate) {
  for (int i = 0; i < data->vertices; i++) {
    data->matrix[i][coordinate] += shift;
  }
}

void matrix_shift(model_data *data, double x, double y, double z) {
  for (int i = 0; i < data->vertices; i++) {
    data->matrix[i][0] += x;
    data->matrix[i][1] += y;
    data->matrix[i][2] += z;
  }
}

void rotation_ox(model_data *data, double value) {
  for (int i = 0; i < data->vertices; i++) {
    double Y = data->matrix[i][1];
    double Z = data->matrix[i][2];
    data->matrix[i][1] = Y * cos(value) + Z * sin(value);
    data->matrix[i][2] = Y * (-sin(value)) + Z * cos(value);
  }
}

void rotation_oy(model_data *data, double value) {
  for (int i = 0; i < data->vertices; i++) {
    double X = data->matrix[i][0];
    double Z = data->matrix[i][2];
    data->matrix[i][0] = X * cos(value) + Z * sin(value);
    data->matrix[i][2] = X * (-sin(value)) + Z * cos(value);
  }
}

void rotation_oz(model_data *data, double value) {
  for (int i = 0; i < data->vertices; i++) {
    double X = data->matrix[i][0];
    double Y = data->matrix[i][1];
    data->matrix[i][0] = X * cos(value) - Y * sin(value);
    data->matrix[i][1] = X * sin(value) + Y * cos(value);
  }
}
