#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>

#include "../model/model.h"

namespace s21 {
class Controller {
 public:
  Controller() = default;

  Controller(QString input_q_str, QString input_q_x)
      : input_str_(input_q_str.toStdString()),
        x_(std::stod(input_q_x.toStdString())),
        model_(input_str_, x_) {}

  ~Controller() = default;
  QString CalcValue() {
    QString result_q_str_;
    try {
      double result_ = model_.Calc();
      result_q_str_ = QString::number(result_, 'f', 7);
    } catch (...) {
      result_q_str_ = QString::fromStdString("Error");
    }
    return result_q_str_;
  }

  double FindY(double x) { return model_.FindY(x); }

 private:
  std::string input_str_;
  double x_;
  s21::Model model_;
};
}  // namespace s21
#endif