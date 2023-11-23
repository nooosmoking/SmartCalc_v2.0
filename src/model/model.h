#ifndef MODEL_H
#define MODEL_H

#include <cmath>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <string>

#include "./token.h"

namespace s21 {

class Model {
 public:
  Model() = default;
  ~Model() = default;
  Model(std::string input_str_, double x)
      : input_str_(input_str_), size_(input_str_.size()), x_(x) {}
  double Calc();
  double FindY(double x);

 private:
  std::string input_str_;
  size_t size_;
  double x_;
  std::list<s21::Token> token_list_input_;
  std::list<s21::Token> token_list_output_;
  std::list<s21::Token> token_list_output_orig_;
  std::stack<s21::Token> support_stack_;

  std::map<std::string, s21::Token> token_map_ = {
      {{"x"},
       {s21::Token("x", LiteralType::kInt, LiteralPriority::kDefault,
                   (double)0)}},
      {{"("},
       {s21::Token("(", LiteralType::kOpenBrack, LiteralPriority::kDefault,
                   nullptr)}},
      {{")"},
       {s21::Token(")", LiteralType::kCloseBrack, LiteralPriority::kDefault,
                   nullptr)}},
      {{"+"},
       {s21::Token("+", LiteralType::kOper, LiteralPriority::kLow,
                   std::plus<double>())}},
      {{"-"},
       {s21::Token("-", LiteralType::kOper, LiteralPriority::kLow,
                   std::minus<double>())}},
      {{"*"},
       {s21::Token("*", LiteralType::kOper, LiteralPriority::kMedium,
                   std::multiplies<double>())}},
      {{"/"},
       {s21::Token("/", LiteralType::kOper, LiteralPriority::kMedium,
                   std::divides<double>())}},
      {{"^"},
       {s21::Token("^", LiteralType::kOper, LiteralPriority::kHigh, powl)}},
      {{"mod"},
       {s21::Token("mod", LiteralType::kOper, LiteralPriority::kMedium,
                   fmodl)}},
      {{"cos"},
       {s21::Token("cos", LiteralType::kFunc, LiteralPriority::kSuperHigh,
                   cosl)}},
      {{"sin"},
       {s21::Token("sin", LiteralType::kFunc, LiteralPriority::kSuperHigh,
                   sinl)}},
      {{"tan"},
       {s21::Token("tan", LiteralType::kFunc, LiteralPriority::kSuperHigh,
                   tanl)}},
      {{"acos"},
       {s21::Token("acos", LiteralType::kFunc, LiteralPriority::kSuperHigh,
                   acosl)}},
      {{"asin"},
       {s21::Token("asin", LiteralType::kFunc, LiteralPriority::kSuperHigh,
                   asinl)}},
      {{"atan"},
       {s21::Token("atan", LiteralType::kFunc, LiteralPriority::kSuperHigh,
                   atanl)}},
      {{"sqrt"},
       {s21::Token("sqrt", LiteralType::kFunc, LiteralPriority::kSuperHigh,
                   sqrtl)}},
      {{"ln"},
       {s21::Token("ln", LiteralType::kFunc, LiteralPriority::kSuperHigh,
                   logl)}},
      {{"log"},
       {s21::Token("log", LiteralType::kFunc, LiteralPriority::kSuperHigh,
                   log10l)}}};

  bool OrderMatrix_[6][6] = {
      {0, 0, 1, 1, 0, 1},  // None
      {1, 1, 0, 0, 1, 0},  // )
      {0, 0, 1, 1, 0, 1},  // (
      {1, 1, 0, 0, 1, 0},  // Int
      {0, 0, 1, 1, 0, 1},  // Oper
      {0, 0, 1, 1, 0, 1}   // Func
  };

  void ToLowerStr();

  void Parser();

  s21::Token CreateNumberToken(char* input_chr);

  std::string RemoveTrailingZeros(double number);

  s21::Token CompareLiter(char* input_chr);

  void UpdateUnars();

  bool IsFirstToken(std::list<s21::Token>::iterator it);

  bool IsLastToken(std::list<s21::Token>::iterator it);

  void Validate();

  void CreateTokenList();

  void PolishNotation();

  double FindResult();

  void MoveTokenFromInputToOutput();

  void MoveTokenFromInputToStack();

  void MoveTokenFromStackToOutput();

  void PushPriorityTokenToStack();

  void PushUntilOpenBrack();

  std::list<s21::Token>::iterator FindOper();

  std::list<s21::Token>::iterator FindPrevNum(
      std::list<s21::Token>::iterator curr_it);

  void UpdateTokenList(double result, std::list<s21::Token>::iterator it_oper,
                       std::list<s21::Token>::iterator it_num);

  void UpdateTokenList(double result, std::list<s21::Token>::iterator it_oper,
                       std::list<s21::Token>::iterator it_num1,
                       std::list<s21::Token>::iterator it_num2);

  void SetX();
};

};  // namespace s21

#endif  // MODEL_H
