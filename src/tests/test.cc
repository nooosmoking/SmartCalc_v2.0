#include <gtest/gtest.h>

#include "../model/model.h"

TEST(TestSmartCalc, SmartCalc1) {
    s21::Model model("((cos(x)+0.853))", 1);
    ASSERT_NEAR(model.Calc(), 1.3933023058681397, 1e-7l);
}

TEST(TestSmartCalc, SmartCalc2) {
    s21::Model model("((cos(x)+0.853))", -100);
  ASSERT_NEAR(model.Calc(), 1.7153188, 1e-7l);
} 

TEST(TestSmartCalc, SmartCalc3) {
    s21::Model model("", 1);
  ASSERT_ANY_THROW(model.Calc());
}

TEST(TestSmartCalc, SmartCalc4) {
    s21::Model model("((css(1)+0.853))", 1);
  ASSERT_ANY_THROW(model.Calc());
}

TEST(TestSmartCalc, SmartCalc5) {
    s21::Model model("((cos(1)+0,.853)))", 1);
  ASSERT_ANY_THROW(model.Calc());
}

TEST(TestSmartCalc, SmartCalc6) {
    s21::Model model("sqrt((6^atan())*9)", 1);
  ASSERT_ANY_THROW(model.Calc());
}

TEST(TestSmartCalc, SmartCalc7) {
    s21::Model model(" +( (cos(log(-1 / 0.777,.777 )+0.853) - 865.))", 1);
  ASSERT_ANY_THROW(model.Calc());
}

TEST(TestSmartCalc, SmartCalc8) {
    s21::Model model("( (sin(1) + 0.853) )", 1);
    ASSERT_NEAR(model.Calc(), 1.6944709848078965, 1e-7l);
}

TEST(TestSmartCalc, SmartCalc9) {
    s21::Model model(" +( (cos(log(-1 + 777.777 )+0.853) - 865.))", -100);
  ASSERT_NEAR(model.Calc(), -865.824372433783, 1e-7l);
} 

TEST(TestSmartCalc, SmartCalc10) {
    s21::Model model(" +( (asin((ln(+0.1 ^ 0.777777 ) + 5)mod 2-1) - 865.))", 1);
ASSERT_NEAR(model.Calc(), -864.7893431503167, 1e-7l);}

TEST(TestSmartCalc, SmartCalc11) {
    s21::Model model("sqrt((6^atan(9))*9)", 1);
    ASSERT_NEAR(model.Calc(), 11.097516262125971, 1e-7l);
}

TEST(TestSmartCalc, SmartCalc12) {
    s21::Model model("((css(1)+  0.853))", 1);
  ASSERT_ANY_THROW(model.Calc());
}

TEST(TestSmartCalc, SmartCalc13) {
    s21::Model model("(6+3)(7-9)", -100);
  ASSERT_ANY_THROW(model.Calc());
} 

TEST(TestSmartCalc, SmartCalc14) {
    s21::Model model("tan (6)", 1);
    ASSERT_NEAR(model.Calc(), -0.29100619138474915, 1e-7l);
}

TEST(TestSmartCalc, SmartCalc15) {
    s21::Model model("sqrt )6)", -100);
  ASSERT_ANY_THROW(model.Calc());
} 

TEST(TestSmartCalc, SmartCalc16) {
    s21::Model model("*sqrt(6)", 1);
  ASSERT_ANY_THROW(model.Calc());
}

TEST(TestSmartCalc, SmartCalc17) {
    s21::Model model("sqrt(6)mod", 1);
  ASSERT_ANY_THROW(model.Calc());
}

TEST(TestSmartCalc, SmartCalc18) {
    s21::Model model("((-acos(sin(3))))", 1);
    ASSERT_NEAR(model.Calc(), -1.4292036732051034, 1e-7l);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}