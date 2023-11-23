#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../controller/controller.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  void on_result_button_clicked();

 private:
  Ui::MainWindow* ui;
  s21::Controller* controller_;
  double step_, x_max_, y_max_, x_min_, y_min_;
  int vector_count_;
  QVector<double> x_, y_;

  void SetGraphSettings();
  void ShowGraph();
  QString ReadFileContent(const QString& filePath);
};
}  // namespace s21

#endif  // MAINWINDOW_H
