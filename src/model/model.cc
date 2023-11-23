#include <variant>

#include "./model.h"

double s21::Model::Calc(){
  CreateTokenList();
  Validate();
  PolishNotation();
  SetX();
  return FindResult();
}

void s21::Model::MoveTokenFromInputToOutput() {
  token_list_output_orig_.push_back(token_list_input_.front());
  token_list_input_.pop_front();
}

void s21::Model::MoveTokenFromInputToStack() {
  support_stack_.push(token_list_input_.front());
  token_list_input_.pop_front();
}

void s21::Model::MoveTokenFromStackToOutput() {
  token_list_output_orig_.push_back(support_stack_.top());
  support_stack_.pop();
}

void s21::Model::PushPriorityTokenToStack(){
  if(support_stack_.empty()){}
  else if (token_list_input_.front().GetPriority() <= support_stack_.top().GetPriority() && (token_list_input_.front().GetName() != "^" || support_stack_.top().GetName() != "^")) {
      while (token_list_input_.front().GetPriority() <= support_stack_.top().GetPriority()) {
        MoveTokenFromStackToOutput();
          if(support_stack_.empty()) break;
      }
  }
}

void s21::Model::PushUntilOpenBrack(){
  token_list_input_.pop_front();
      while (support_stack_.top().GetType() != s21::LiteralType::kOpenBrack) {
         MoveTokenFromStackToOutput();
      }
      support_stack_.pop();
}

void s21::Model::PolishNotation(){
  token_list_input_.pop_front();
  while (token_list_input_.front().GetType() != s21::LiteralType::kNone) {
    switch (token_list_input_.front().GetType())
    {
    case s21::LiteralType::kX:
      [[fallthrough]];
    case s21::LiteralType::kInt:
      MoveTokenFromInputToOutput();
      break;
    case s21::LiteralType::kOper:
      [[fallthrough]];
    case s21::LiteralType::kFunc:
        PushPriorityTokenToStack();
      [[fallthrough]];
    case s21::LiteralType::kOpenBrack:
        MoveTokenFromInputToStack();
        break;
    case s21::LiteralType::kCloseBrack:
      PushUntilOpenBrack();
        break;
    default:
      break;
    }
  }
  while (!support_stack_.empty()) {
    MoveTokenFromStackToOutput();
  }
};

std::list<s21::Token>::iterator s21::Model::FindOper(){
  auto it = token_list_output_.begin();
  while ((it->GetType() != s21::LiteralType::kFunc) && (it->GetType() != LiteralType::kOper)){
    ++it;
  }
  return it;
};

std::list<s21::Token>::iterator s21::Model::FindPrevNum(std::list<s21::Token>::iterator it){
    --it;
  while ((it->GetType() != s21::LiteralType::kInt) && (it->GetType() != s21::LiteralType::kX)){
    --it;
  }
  return it;
}

void s21::Model::UpdateTokenList(double result, std::list<s21::Token>::iterator it_oper, std::list<s21::Token>::iterator it_num){
  *it_oper = s21::Token(RemoveTrailingZeros(result), 0, s21::LiteralType::kInt,
                    s21::LiteralPriority::kDefault, result);
  token_list_output_.erase(it_num);
}

void s21::Model::UpdateTokenList(double result, std::list<s21::Token>::iterator it_oper, std::list<s21::Token>::iterator it_num1, std::list<s21::Token>::iterator it_num2){
  *it_oper = s21::Token(RemoveTrailingZeros(result), 0, s21::LiteralType::kInt,
                    s21::LiteralPriority::kDefault, result);
                    
  token_list_output_.erase(it_num1);
  if (it_num1 != it_num2 )
    token_list_output_.erase(it_num2);
}
double s21::Model::FindY(double x){
  x_ = x;
  SetX();
  return FindResult();
}

void s21::Model::SetX(){
  token_list_output_ =  token_list_output_orig_;
  for (auto it = token_list_output_.begin(); it != token_list_output_.end(); it++)
  {
    if(it->GetName() == "x" || it->GetType() == s21::LiteralType::kX)
      *it =  s21::Token(RemoveTrailingZeros(x_), 0, s21::LiteralType::kX,
                    s21::LiteralPriority::kDefault, x_);
  }
}

double s21::Model::FindResult(){
  double result = std::get<double>(token_list_output_.front().GetData());
  while(token_list_output_.size() > 1){
    auto it_oper = FindOper();
    auto it_num1 = FindPrevNum(it_oper);
    if (it_oper->GetType() == LiteralType::kFunc) {
      auto un_func = std::get<un_function>(it_oper->GetData());
      result = un_func(std::get<double>(it_num1->GetData()));
      UpdateTokenList(result, it_oper, it_num1);
    } else if (it_oper->GetType() == LiteralType::kOper){
      auto it_num2 = FindPrevNum(it_num1);
      auto bin_func = std::get<bin_function>(it_oper->GetData());
      result = bin_func(std::get<double>(it_num2->GetData()), std::get<double>(it_num1->GetData()));
      UpdateTokenList(result, it_oper, it_num1, it_num2);
    }
  }
  return result;
};

void s21::Model::CreateTokenList(){
  token_list_input_.push_back(Token("", s21::LiteralType::kNone, s21::LiteralPriority::kDefault, nullptr));
  ToLowerStr();
  Parser();
  token_list_input_.push_back(Token("", s21::LiteralType::kNone, s21::LiteralPriority::kDefault, nullptr));
  UpdateUnars();
};

void s21::Model::Validate(){
  int brackets = 0;
  s21::LiteralType type_current;
  s21::LiteralType type_next;
  for (auto it = token_list_input_.begin(); it != --(token_list_input_.end());) {
    type_current = it->GetType();
    if(type_current == s21::LiteralType::kOpenBrack) ++brackets;
    else if (type_current == s21::LiteralType::kCloseBrack) --brackets;
    ++it;
    type_next = it->GetType();
    if(!OrderMatrix_[static_cast<int>(type_current)][static_cast<int>(type_next)]){
          throw std::invalid_argument("Incorrect order of tokens!");
    }
    if (brackets < 0)
      throw std::invalid_argument("Incorrect order of brackets!");
  }
  if (brackets > 0) throw std::invalid_argument("Too much brackets!");
};

void s21::Model::ToLowerStr() {
  for (size_t i = 0; i < size_; i++) {
    input_str_[i] = tolower(input_str_[i]);
  }
};

void s21::Model::Parser() {
  int i = 0;
  s21::Token current_token;
  while (i < size_) {
    if (input_str_[i] == ' ') {
      i++;
      continue;
    } else if (isdigit(input_str_[i])) {
      current_token = CreateNumberToken(&(input_str_[i]));
    } else {
      current_token = CompareLiter(&(input_str_[i]));
    }
    token_list_input_.push_back(current_token);

    i += current_token.GetLength();
  }
};

std::string s21::Model::RemoveTrailingZeros(double number) {
  std::string str = std::to_string(number);
  size_t decimal_pos = str.find(".");
  if (decimal_pos != std::string::npos) {
    size_t last_non_zero_digit = decimal_pos + 1;
    for (size_t i = str.length() - 1; i > decimal_pos; ++i) {
      if (str[i] != '0') break;
      last_non_zero_digit = i - 1;
    }
    if (str[last_non_zero_digit] == '.') {
      str.erase(last_non_zero_digit, std::string::npos);
    } else {
      str.erase(last_non_zero_digit + 1, std::string::npos);
    }
  }
  return str;
}

s21::Token s21::Model::CreateNumberToken(char* input_chr) {
  size_t num_chars_read = 0;
  double data = std::stod(input_chr, &num_chars_read);
  
  s21::Token found_token(RemoveTrailingZeros(data), num_chars_read, s21::LiteralType::kInt,
                    s21::LiteralPriority::kDefault, data);
  return found_token;
}

s21::Token s21::Model::CompareLiter(char* input_chr) {
  std::string tmp_str;
  tmp_str.assign(input_chr);

  auto it = token_map_.begin();
  for (; it != token_map_.end(); ++it) {
    if (tmp_str.substr(0, (*it).first.size()) == (*it).first) {
      break;
    };
  }
  if (it == token_map_.end()) {
    throw std::invalid_argument("Incorrect simbols in string!");
  }
  Token found_token((*it).second);
  return found_token;
}

void s21::Model::UpdateUnars() {
  for (auto it = token_list_input_.begin(); it != token_list_input_.end(); ++it) {
    if (IsFirstToken(it) && (it->GetName() == "-" || it->GetName() == "+")) {
        token_list_input_.insert(it, Token("0", LiteralType::kInt, LiteralPriority::kDefault, (double)0));
    } else if (it->GetName() == "(") {
      ++it;
      if (it->GetName() == "-" || it->GetName() == "+") {
        token_list_input_.insert(it, Token("0", LiteralType::kInt, LiteralPriority::kDefault, (double)0));
      }
      --it;
    }
  }
}

bool s21::Model::IsFirstToken(std::list<Token>::iterator it) {
  bool ok = (it == ++(token_list_input_.begin()));
  return ok;
}