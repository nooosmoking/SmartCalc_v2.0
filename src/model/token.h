#ifndef TOKEN_H
#define TOKEN_H

#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <variant>

namespace s21 {
enum class LiteralType {
  kNone,
  kCloseBrack,
  kOpenBrack,
  kInt,
  kOper,
  kFunc,
  kX
};

enum LiteralPriority {
  kDefault,   // ( & other
  kLow,       // +-
  kMedium,    // * / m
  kHigh,      // ^
  kSuperHigh  // func
};

using un_function = std::function<double(double)>;
using bin_function = std::function<double(double, double)>;
using function_variant =
    std::variant<double, un_function, bin_function, nullptr_t>;

class Token {
 public:
  Token() = default;
  Token(const std::string& name, LiteralType type, LiteralPriority priority,
        function_variant data)
      : name_(name),
        length_(name.size()),
        type_(type),
        priority_(priority),
        data_(data){};
  Token(const std::string& name, size_t length, LiteralType type,
        LiteralPriority priority, function_variant data)
      : name_(name),
        length_(length),
        type_(type),
        priority_(priority),
        data_(data){};
  ~Token() = default;

  void PrintToken() {
    std::cout << name_ << " " << (int)type_ << " ";
    std::cout << "\n";
  }

  size_t GetLength() const { return length_; }
  std::string GetName() const { return name_; }
  LiteralType GetType() const { return type_; }
  int GetPriority() const { return static_cast<int>(priority_); }
  function_variant GetData() const { return data_; }

  void SetType(LiteralType type) { type_ = type; }

 private:
  std::string name_;
  size_t length_;
  LiteralType type_;
  LiteralPriority priority_;
  function_variant data_;
};
}  // namespace s21
#endif  // TOKEN_H
