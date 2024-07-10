#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QSettings>
#include <QTimer>

#include "qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  int lines_count = 0;
  double scale = 1.0f;
  double move_x = 0.0f;
  double move_y = 0.0f;
  double move_z = 0.0f;

  void loadSettings();
  void saveSettings();

  QTimer *timer;
  QImage image;
  QGifImage *gif;
  int frame_count;
  // int i = 0;

 private slots:
  void on_pushButton_file_clicked();
  void get_obj_data(char *filename);

  void on_doubleSpinBoxMoveX_valueChanged(double arg1);

  void on_doubleSpinBoxMoveY_valueChanged(double arg1);

  void on_doubleSpinBoxMoveZ_valueChanged(double arg1);

  void on_horizontalSliderMoveX_valueChanged(int value);

  void on_horizontalSliderMoveY_valueChanged(int value);

  void on_horizontalSliderMoveZ_valueChanged(int value);

  void on_horizontalSliderScale_valueChanged(int value);

  void on_doubleSpinBoxScale_valueChanged(double arg1);

  void on_horizontalSliderRotateX_valueChanged(int value);

  void on_doubleSpinBoxRotateX_valueChanged(double arg1);

  void on_horizontalSliderRotateY_valueChanged(int value);

  void on_doubleSpinBoxRotateY_valueChanged(double arg1);

  void on_horizontalSliderRotateZ_valueChanged(int value);

  void on_doubleSpinBoxRotateZ_valueChanged(double arg1);

  void on_radioButton_toggled(bool checked);

  void on_radioButton_2_toggled(bool checked);

  void on_radioButton_2_clicked();

  void on_radioButton_clicked();

  void on_comboBox_vertextype_activated(int index);

  void on_spinBox_vertexsize_valueChanged(int arg1);

  void on_pushButton_vertexColor_clicked();

  void on_pushButton_edgeColor_clicked();

  void on_pushButton_backgroundColor_clicked();

  void on_comboBox_edgetype_activated(int index);

  void on_spinBox_edgewidth_valueChanged(int arg1);

  void on_pushButton_screenshot_clicked();

  void on_pushButton_screencast_clicked();

  void create_gif();

 private:
  Ui::MainWindow *ui;
  double x_angle;
  double y_angle;
  double z_angle;
  QString settingsFile;
};
#endif  // MAINWINDOW_H
