#include <QString>
#include <QFile>
#include <QTextStream>

#include "../ui_mainwindow.h"
#include "../controller/controller.h"
#include "mainwindow.h"

QString s21::MainWindow::ReadFileContent(const QString& filePath) {
  QFile file(filePath);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "Не удалось открыть файл" << filePath;
    return QString();
  }
  QTextStream in(&file);
   QString content = in.readAll();
  file.close();

  return content;
}

s21::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), vector_count_(300) {
  ui->setupUi(this);
  setWindowTitle("SmartCalc");
  SetGraphSettings();
  qApp->setStyleSheet(ReadFileContent("../src/view/style.qss"));
}

s21::MainWindow::~MainWindow() { delete ui;
}

void s21::MainWindow::SetGraphSettings(){
  ui->graphic->hide();

  ui->graphic->setInteraction(QCP::iRangeDrag, true);
  ui->graphic->axisRect()->setRangeDrag(Qt::Vertical);
  ui->graphic->axisRect()->setRangeDrag(Qt::Horizontal);
  ui->graphic->setInteraction(QCP::iRangeZoom, true);
  ui->graphic->axisRect()->setRangeZoom(Qt::Vertical | Qt::Horizontal);

  ui->graphic->xAxis->setTickLabelFont(QFont("Chalkduster", 12));
  ui->graphic->yAxis->setTickLabelFont(QFont("Chalkduster", 12));

  ui->graphic->xAxis->setTickLabelColor(QColor::fromRgb(0, 80, 172));
  ui->graphic->yAxis->setTickLabelColor(QColor::fromRgb(0, 80, 172));

  ui->graphic->setBackground(QBrush(Qt::transparent));
}

void s21::MainWindow::ShowGraph(){
  ui->graphic->clearGraphs();
  ui->graphic->xAxis->setRange(x_min_, x_max_);
  ui->graphic->yAxis->setRange(y_min_, y_max_);

  step_= fabs(x_max_ - x_min_) / vector_count_;
  double curr_y_;
  for (double curr_x_ = x_min_; curr_x_ <= x_max_ ; curr_x_ += step_)
  {
    curr_y_ = controller_->FindY(curr_x_);
    if(curr_y_ >= y_min_ && curr_y_ <= y_max_) {
      x_.push_back(curr_x_);
      y_.push_back(curr_y_);
      }
  }
  ui->graphic->addGraph();

  ui->graphic->graph(0)->addData(x_, y_);
  ui->graphic->graph(0)->setPen(QPen(QColor::fromRgb(250, 120, 230), 2));
  ui->graphic->replot();
  ui->graphic->show();
  x_.clear();
  y_.clear();
}

void s21::MainWindow::on_result_button_clicked() {
  QString input_str = ui->input_text->text();
  QString input_x = ui->input_text_x->text();
  if (!input_str.isEmpty()) {
  controller_ = new Controller(input_str, input_x);
  QString result = controller_->CalcValue();
  ui->result->setText(result);
  x_min_ = ui->x_min_box->value();
  x_max_ = ui->x_max_box->value();
  y_min_ = ui->y_min_box->value();
  y_max_ = ui->y_max_box->value();
    if (result.toStdString() !=  "Error")
    ShowGraph();
    delete controller_;
  }
}