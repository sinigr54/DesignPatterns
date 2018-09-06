//
// Created by Alexander Chekh on 06.09.2018.
//

#include "behavioral.h"

#include <sstream>
#include <iostream>

/*
 * Intrusive Visitor
 * Заходим в каждый класс в иерархии
 * и добавляем необходимую функциональность.
 * В нашем случае - print.
 *
 * Нарушает принцип единственности ответственности,
 * нарушает принцип открыт - закрыт.
 *
 * Что если в иерархии очень много классов?
 * Придется редактировать каждый из них.
 */

namespace intrusive_visitor {
  struct Expression {
      virtual ~Expression() = default;

      virtual void print(std::ostringstream &oss) = 0;
  };

  struct DoubleExpression : Expression {
      double value;

      explicit DoubleExpression(double value) : value(value) {

      }

      void print(std::ostringstream &oss) override {
          oss << value;
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

      void print(std::ostringstream &oss) override {
          oss << "(";
          left->print(oss);
          oss << " + ";
          right->print(oss);
          oss << ")";
      }
  };
}

using namespace intrusive_visitor;

void intrusive_visitor_example() {
    auto e = new AdditionExpression{
            new DoubleExpression{1},
            new AdditionExpression{
                    new DoubleExpression{2},
                    new DoubleExpression{3}
            }
    };

    std::ostringstream oss;
    e->print(oss);

    std::cout << oss.str() << std::endl;

    delete e;
}
