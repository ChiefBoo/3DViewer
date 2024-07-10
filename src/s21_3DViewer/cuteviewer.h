#ifndef CUTEVIEWER_H
#define CUTEVIEWER_H

#define GL_SILENCE_DEPRECATION

#include <QColor>
#include <QColorDialog>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QSettings>
#include <QtOpenGL>

extern "C" {
#include "../3DViewer.h"
}

class CuteViewer : public QOpenGLWidget, public QOpenGLFunctions {
 public:
  CuteViewer(QWidget *parent = nullptr);
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

  model_data *Data;
  bool file_correct = false;

  double scale_val = 1.0f;
  double x_shift = 0.0f;
  double y_shift = 0.0f;
  double z_shift = 0.0f;

  bool projection = true;

  QColor backColor = Qt::black;

  int vertex_type = 0;
  int vertex_size = 5;
  QColor vertColor = Qt::red;

  int edgeType = 0;
  int edgeWidth = 1;
  QColor edgeColor = Qt::green;
};

#endif  // CUTEVIEWER_H
