#include "mainwindow.h"

#include <QErrorMessage>

#include "cuteviewer.h"
#include "ui_mainwindow.h"

extern "C" {
#include "../3DViewer.h"
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  settingsFile = QApplication::applicationDirPath() + "/settings.conf";
  loadSettings();

  x_angle = 0;
  y_angle = 0;
  z_angle = 0;

  frame_count = 0;
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(create_gif()));
}

MainWindow::~MainWindow() {
  if (ui->widget->Data != NULL) {
    mem_free(ui->widget->Data);
  }
  saveSettings();
  delete timer;
  delete ui;
}

void MainWindow::on_pushButton_file_clicked() {
  ui->doubleSpinBoxMoveX->setValue(0);
  ui->doubleSpinBoxMoveY->setValue(0);
  ui->doubleSpinBoxMoveZ->setValue(0);
  ui->doubleSpinBoxScale->setValue(1.00);
  ui->doubleSpinBoxRotateX->setValue(0);
  ui->doubleSpinBoxRotateY->setValue(0);
  ui->doubleSpinBoxRotateZ->setValue(0);
  ui->label_gif->setText("Ready");
  QString str = NULL;
  str = QFileDialog::getOpenFileName(this, "Open file", ".",
                                     "OBJ Files (*.obj);; All Files (*.*)");
  if (!str.isNull()) {
    ui->label->setText(str.split('/').last());
    QByteArray ba = str.toLocal8Bit();
    char *filename = ba.data();
    get_obj_data(filename);
    ui->widget->update();
  }
}

void MainWindow::get_obj_data(char *filename) {
  int vertices = 0;
  int polygons = 0;
  if (vertices_counter(filename, &vertices, &polygons) == OK) {
    ui->widget->file_correct = true;
    model_data *Data = data_filling(filename);
    ui->widget->Data = Data;
    lines_count = 0;
    for (int i = 0; i < Data->polygons; i++) {
      for (int j = 0; j < Data->polygon[i].amount;) {
        j++;
        lines_count += 1;
      }
    }
    ui->label_poly_numb->setText(QString::number(Data->polygons));
    ui->label_vert_numb->setText(QString::number(Data->vertices));
    ui->label_edge_numb->setText(QString::number(lines_count / 2));
  } else {
    QMessageBox::information(this, "error", "file incorrect");
  }
}

// void MainWindow::get_points(char *str2) {
//   int vert_am = 0;
//   int pol_am = 0;
//   if (count_size_for_init(str2, &vert_am, &pol_am) == 1) {
//     QMessageBox::information(this, "Поломаный файл",
//                                  "Файл имеет неверные данные");
//   } else {

//    ui->widget->is_open = true;
//    view* x = m_viewer(str2);
//    ui->widget->x = x;

//    lines_count = 0;
//    for (unsigned int i = 0; i < x->amount_of_polygons; i++) {
//        for (int j = 0; j < x->poly[i].amount_p - 1;) {
//            j++;
//            lines_count += 1;
//        }
//    }
//    ui->label_Lines_count->setText(QString::number(lines_count / 2));
//    ui->label_vertex_count->setText(QString::number(x->amount_of_vertexes));
//  }
//}

//перемещение
void MainWindow::on_horizontalSliderMoveX_valueChanged(int value) {
  ui->doubleSpinBoxMoveX->setValue((double)value);
}

void MainWindow::on_doubleSpinBoxMoveX_valueChanged(double arg1) {
  if (ui->widget->file_correct == true) {
    double shift = arg1 / 10 - ui->widget->x_shift;
    moving(ui->widget->Data, shift, 0);
    ui->widget->x_shift = arg1 / 10;
    ui->horizontalSliderMoveX->setValue((int)arg1);
    ui->widget->update();
  }
}

void MainWindow::on_horizontalSliderMoveY_valueChanged(int value) {
  ui->doubleSpinBoxMoveY->setValue((double)value);
}

void MainWindow::on_doubleSpinBoxMoveY_valueChanged(double arg1) {
  if (ui->widget->file_correct == true) {
    double shift = arg1 / 10 - ui->widget->y_shift;
    moving(ui->widget->Data, shift, 1);
    ui->widget->y_shift = arg1 / 10;
    ui->horizontalSliderMoveY->setValue((int)arg1);
    ui->widget->update();
  }
}

void MainWindow::on_horizontalSliderMoveZ_valueChanged(int value) {
  ui->doubleSpinBoxMoveZ->setValue((double)value);
}

void MainWindow::on_doubleSpinBoxMoveZ_valueChanged(double arg1) {
  if (ui->widget->file_correct == true) {
    double shift = arg1 / 10 - ui->widget->z_shift;
    moving(ui->widget->Data, shift, 2);
    ui->widget->z_shift = arg1 / 10;
    ui->horizontalSliderMoveZ->setValue((int)arg1);
    ui->widget->update();
  }
}

// масштаб
void MainWindow::on_horizontalSliderScale_valueChanged(int value) {
  ui->doubleSpinBoxScale->setValue((double)value / 100);
}

void MainWindow::on_doubleSpinBoxScale_valueChanged(double arg1) {
  if (ui->widget->file_correct == true) {
    double scale = (arg1 / ui->widget->scale_val);
    matrix_shift(ui->widget->Data, -ui->widget->x_shift, -ui->widget->y_shift,
                 -ui->widget->z_shift);
    scaling(ui->widget->Data, scale);
    matrix_shift(ui->widget->Data, ui->widget->x_shift, ui->widget->y_shift,
                 ui->widget->z_shift);
    ui->widget->scale_val = arg1;
    ui->widget->update();
    ui->horizontalSliderScale->setValue((int)(arg1 * 100));
  }
}

//вращение
void MainWindow::on_horizontalSliderRotateX_valueChanged(int value) {
  ui->doubleSpinBoxRotateX->setValue(value);
}

void MainWindow::on_doubleSpinBoxRotateX_valueChanged(double arg1) {
  ui->horizontalSliderRotateX->setValue(arg1);
  if (ui->widget->file_correct == true) {
    double valueR = (x_angle - arg1) * M_PI / 180;
    x_angle = arg1;
    ui->doubleSpinBoxRotateX->setValue(arg1);
    matrix_shift(ui->widget->Data, -ui->widget->x_shift, -ui->widget->y_shift,
                 -ui->widget->z_shift);
    rotation_ox(ui->widget->Data, valueR);
    matrix_shift(ui->widget->Data, ui->widget->x_shift, ui->widget->y_shift,
                 ui->widget->z_shift);
    ui->widget->update();
  }
}

void MainWindow::on_horizontalSliderRotateY_valueChanged(int value) {
  ui->doubleSpinBoxRotateY->setValue(value);
}

void MainWindow::on_doubleSpinBoxRotateY_valueChanged(double arg1) {
  ui->horizontalSliderRotateY->setValue(arg1);
  if (ui->widget->file_correct == true) {
    double valueR = (y_angle - arg1) * M_PI / 180;
    y_angle = arg1;
    ui->doubleSpinBoxRotateY->setValue(arg1);
    matrix_shift(ui->widget->Data, -ui->widget->x_shift, -ui->widget->y_shift,
                 -ui->widget->z_shift);
    rotation_oy(ui->widget->Data, valueR);
    matrix_shift(ui->widget->Data, ui->widget->x_shift, ui->widget->y_shift,
                 ui->widget->z_shift);
    ui->widget->update();
  }
}

void MainWindow::on_horizontalSliderRotateZ_valueChanged(int value) {
  ui->doubleSpinBoxRotateZ->setValue(value);
}

void MainWindow::on_doubleSpinBoxRotateZ_valueChanged(double arg1) {
  ui->horizontalSliderRotateZ->setValue(arg1);
  if (ui->widget->file_correct == true) {
    double valueR = (z_angle - arg1) * M_PI / 180;
    z_angle = arg1;
    ui->doubleSpinBoxRotateZ->setValue(arg1);
    matrix_shift(ui->widget->Data, -ui->widget->x_shift, -ui->widget->y_shift,
                 -ui->widget->z_shift);
    rotation_oz(ui->widget->Data, valueR);
    matrix_shift(ui->widget->Data, ui->widget->x_shift, ui->widget->y_shift,
                 ui->widget->z_shift);
    ui->widget->update();
  }
}

void MainWindow::on_radioButton_toggled(bool checked) {
  if (checked == true) ui->widget->projection = true;
}

void MainWindow::on_radioButton_2_toggled(bool checked) {
  if (checked == true) ui->widget->projection = false;
}

void MainWindow::on_radioButton_2_clicked() { ui->widget->update(); }

void MainWindow::on_radioButton_clicked() { ui->widget->update(); }

void MainWindow::on_comboBox_vertextype_activated(int index) {
  ui->widget->vertex_type = index;
  ui->widget->update();
}

void MainWindow::on_spinBox_vertexsize_valueChanged(int arg1) {
  ui->widget->vertex_size = arg1;
  ui->widget->update();
}

void MainWindow::on_pushButton_vertexColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select color");
  ui->widget->vertColor = color;
  ui->widget->update();
}

void MainWindow::on_pushButton_edgeColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select color");
  ui->widget->edgeColor = color;
  ui->widget->update();
}

void MainWindow::on_pushButton_backgroundColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select color");
  ui->widget->backColor = color;
  ui->widget->update();
}

void MainWindow::on_comboBox_edgetype_activated(int index) {
  ui->widget->edgeType = index;
  ui->widget->update();
}

void MainWindow::on_spinBox_edgewidth_valueChanged(int arg1) {
  ui->widget->edgeWidth = arg1;
  ui->widget->update();
}

void MainWindow::saveSettings() {
  QSettings settings(settingsFile, QSettings::IniFormat);
  settings.setValue("edgeType", ui->widget->edgeType);
  settings.setValue("edgeWidth", ui->widget->edgeWidth);
  settings.setValue("edgeColor", ui->widget->edgeColor);
  settings.setValue("vertexType", ui->widget->vertex_type);
  settings.setValue("vertexSize", ui->widget->vertex_size);
  settings.setValue("vertexColor", ui->widget->vertColor);
  settings.setValue("backgroundColor", ui->widget->backColor);
  settings.setValue("projection", ui->widget->projection);
}

void MainWindow::loadSettings() {
  QFile file(settingsFile);
  if (file.exists()) {
    QSettings settings(settingsFile, QSettings::IniFormat);
    ui->widget->edgeType = settings.value("edgeType").toInt();
    ui->widget->edgeWidth = settings.value("edgeWidth").toInt();
    ui->widget->vertex_type = settings.value("vertexType").toInt();
    ui->widget->vertex_size = settings.value("vertexSize").toInt();
    ui->widget->projection = settings.value("projection").toBool();
    ui->widget->edgeColor = settings.value("edgeColor").value<QColor>();
    ui->widget->vertColor = settings.value("vertexColor").value<QColor>();
    ui->widget->backColor = settings.value("backgroundColor").value<QColor>();

    ui->comboBox_edgetype->setCurrentIndex(ui->widget->edgeType);
    ui->spinBox_edgewidth->setValue(ui->widget->edgeWidth);
    ui->comboBox_vertextype->setCurrentIndex(ui->widget->vertex_type);
    ui->spinBox_vertexsize->setValue(ui->widget->vertex_size);
    if (ui->widget->projection) {
      ui->radioButton->setChecked(true);
    } else {
      ui->radioButton_2->setChecked(true);
    }
  }
}

void MainWindow::on_pushButton_screenshot_clicked() {
  QFileDialog file_dialog_img(this);
  QString screen_name = file_dialog_img.getSaveFileName(
      this, tr("Save a screenshot"), "", tr("images (*.bmp *.jpeg)"));
  QImage img = ui->widget->grabFramebuffer();
  if (!screen_name.isNull()) {
    int saved = img.save(screen_name);
    if (!saved) {
      (new QErrorMessage(this))
          ->showMessage("Incorrect file extension. Only jpeg or bmp.");
    }
  }
}

void MainWindow::on_pushButton_screencast_clicked() {
  gif = new QGifImage(QSize(640, 480));
  // QGifImage gif(QSize(640, 480));
  this->ui->pushButton_screencast->setEnabled(false);
  this->ui->label_gif->setText("Recording a GIF file");
  gif->setDefaultDelay(100);
  timer->start(100);
}

void MainWindow::create_gif() {
  if (frame_count < 50) {
    image = ui->widget->grabFramebuffer().scaled(640, 480);
    gif->addFrame(image);
    frame_count++;
  } else {
    frame_count = 0;
    timer->stop();
    QFileDialog file_dialog_gif(this);
    QString gif_name = file_dialog_gif.getSaveFileName(this, tr("Save a gif"),
                                                       "", tr("gif (*.gif)"));
    if (gif_name.isNull()) {
      ui->label_gif->setText("GIF creation canceled");
    } else {
      gif->save(gif_name);
      ui->label_gif->setText("GIF file created");
    }
    ui->pushButton_screencast->setEnabled(true);
    delete gif;
  }
}
