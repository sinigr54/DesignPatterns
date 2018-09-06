//
// Created by Alexander Chekh on 06.09.2018.
//

#include "behavioral.h"

/*
 * Реализуем алгоритм печати структуры
 * через проверку динамического типа
 * объекта.
 *
 * Мы можем забыть безопасно проверить тип.
 *
 * А что если в иерархии очень много классов?
 * Решение сильно разрастается
 */

#include <iostream>
#include <sstream>

namespace reflective_visitor {

  struct Expression {
      virtual ~Expression() = default;
  };

  struct DoubleExpression : Expression {
      double value;

      explicit DoubleExpression(double value) : value(value) {

      }
  };

  struct AdditionExpression : Expression {
      Expression *left;
      Expression *right;

      AdditionExpression(Expression *left, Expression *right) : left(left), right(right) {

      }

      ~AdditionExpression() override {
          delete left;
          delete right;
      }
  };

  struct ExpressionPrinter {
      std::ostringstream oss;

      void print(Expression *e) {
          if (auto de = dynamic_cast<DoubleExpression*>(e)) {
              oss << de->value;
          } else if (auto ae = dynamic_cast<AdditionExpression*>(e)) {
              oss << "(";
              print(ae->left);
              oss << " + ";
              print(ae->right);
              oss << ")";
          }
      }

      std::string str() const {
          return oss.str();
      }
  };

}

using namespace reflective_visitor;

void reflective_visitor_example() {
    auto e = new AdditionExpression{
            new DoubleExpression{1},
            new AdditionExpression{
                    new DoubleExpression{2},
                    new DoubleExpression{3}
            }
    };

    ExpressionPrinter printer;
    printer.print(e);
    std::cout << printer.str() << std::endl;

    delete e;
}