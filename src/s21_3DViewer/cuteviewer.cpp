#include "cuteviewer.h"

CuteViewer::CuteViewer(QWidget *parent) : QOpenGLWidget{parent} {}

void CuteViewer::initializeGL() {
  initializeOpenGLFunctions();
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
}

void CuteViewer::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void CuteViewer::paintGL() {
  if (!edgeType) {
    glEnable(GL_LINES);
  } else {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  }
  glLineWidth(edgeWidth);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projection == true) {
    glFrustum(-1, 1, -1, 1, 1, 5);
  } else {
    glOrtho(-1, 1, -1, 1, 1, 5);
  }
  glTranslatef(0, 0, -2);
  glMatrixMode(GL_MODELVIEW);
  glClearColor(backColor.redF(), backColor.greenF(), backColor.blueF(), 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3d(edgeColor.redF(), edgeColor.greenF(), edgeColor.blueF());
  if (file_correct == true) {
    for (int i = 0; i < Data->polygons; i++) {
      glBegin(GL_LINE_LOOP);
      for (int j = 0; j < Data->polygon[i].amount; j++) {
        glVertex3d(Data->matrix[(Data->polygon[i].v[j] - 1)][0],
                   Data->matrix[(Data->polygon[i].v[j] - 1)][1],
                   Data->matrix[(Data->polygon[i].v[j] - 1)][2]);
      }
      glEnd();
    }
  }
  if (!edgeType) {
    glDisable(GL_LINES);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  if (vertex_type) {
    if (vertex_type == 1) glEnable(GL_POINT_SMOOTH);
    if (vertex_type == 2) glEnable(GL_POINT_BIT);
    glPointSize(vertex_size);
    glColor3f(vertColor.redF(), vertColor.greenF(), vertColor.blueF());
    glBegin(GL_POINTS);
    if (file_correct == true) {
      for (int i = 0; i < Data->polygons; i++) {
        for (int j = 0; j < Data->polygon[i].amount;) {
          glVertex3d(Data->matrix[Data->polygon[i].v[j] - 1][0],
                     Data->matrix[Data->polygon[i].v[j] - 1][1],
                     Data->matrix[Data->polygon[i].v[j] - 1][2]);
          j++;
        }
      }
    }
    glEnd();
    if (vertex_type == 1) glDisable(GL_POINT_SMOOTH);
    if (vertex_type == 2) glDisable(GL_POINT_BIT);
  }
}
