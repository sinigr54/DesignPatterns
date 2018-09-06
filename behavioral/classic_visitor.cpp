//
// Created by Alexander Chekh on 06.09.2018.
//

#include "behavioral.h"

/*
 * Classic Visitor (Double Dispatch)
 */

#include <iostream>
#include <sstream>

using namespace std;

namespace classic_visitor {

  struct DoubleExpression;
  struct AdditionExpression;
  struct SubtractionExpression;

  struct ExpressionVisitor {
      virtual void visit(DoubleExpression *de) = 0;

      virtual void visit(AdditionExpression *ae) = 0;

      virtual void visit(SubtractionExpression *se) = 0;
  };

  struct ExpressionPrinter : ExpressionVisitor {
      ostringstream oss;

      void visit(DoubleExpression *de) override;

      void visit(AdditionExpression *ae) override;

      void visit(SubtractionExpression *se) override;

      string str() const {
          return oss.str();
      }
  };

  struct ExpressionEvaluator : ExpressionVisitor {
      double result{0};

      void visit(DoubleExpression *de) override;

      void visit(AdditionExpression *ae) override;

      void visit(SubtractionExpression *se) override;
  };

  struct Expression {
      virtual ~Expression() = default;

      virtual void accept(ExpressionVisitor *visitor) = 0;
  };

  struct DoubleExpression : Expression {
      double value;

      explicit DoubleExpression(double value) : value(value) {

      }

      void accept(ExpressionVisitor *visitor) override {
          visitor->visit(this);
      }
  };

  struct AdditionExpression : Expression {
      Expression *left;
      Expression *right;

      AdditionExpression(Expression *left, Expression *right) : left(left), right(right) {

      }

      void accept(ExpressionVisitor *visitor) override {
          visitor->visit(this);
      }

      ~AdditionExpression() override {
          delete left;
          delete right;
      }
  };

  struct SubtractionExpression : Expression {
      Expression *left;
      Expression *right;

      SubtractionExpression(Expression *left, Expression *right) : left(left), right(right) {

      }

      void accept(ExpressionVisitor *visitor) override {
          visitor->visit(this);
      }

      ~SubtractionExpression() override {
          delete left;
          delete right;
      }
  };

  void ExpressionPrinter::visit(DoubleExpression *de) {
      oss << de->value;
  }

  void ExpressionPrinter::visit(AdditionExpression *ae) {
      bool needBraces = dynamic_cast<SubtractionExpression *>(ae->right);
      ae->left->accept(this);
      oss << " + ";

      if (needBraces) {
          oss << "(";
      }
      ae->right->accept(this);
      if (needBraces) {
          oss << ")";
      }
  }

  void ExpressionPrinter::visit(SubtractionExpression *se) {
      bool needBraces = dynamic_cast<SubtractionExpression *>(se->right);
      if (needBraces) {
          oss << "(";
      }

      se->left->accept(this);
      oss << " - ";
      se->right->accept(this);

      if (needBraces) {
          oss << "(";
      }
  }

  void ExpressionEvaluator::visit(DoubleExpression *de) {
      result = de->value;
  }

  void ExpressionEvaluator::visit(AdditionExpression *ae) {
      ae->left->accept(this);
      auto temp = result;
      ae->right->accept(this);
      result += temp;
  }

  void ExpressionEvaluator::visit(SubtractionExpression *se) {
      se->left->accept(this);
      auto temp = result;
      se->right->accept(this);
      result = temp - result;
  }

}

using namespace classic_visitor;

void classic_visitor_example() {
    auto e = new AdditionExpression{
            new DoubleExpression{1},
            new SubtractionExpression{
                    new DoubleExpression{2},
                    new DoubleExpression{3}
            }
    };

    ExpressionPrinter printer;
    printer.visit(e);

    ExpressionEvaluator evaluator;
    evaluator.visit(e);

    cout << printer.str() << " = " << evaluator.result << endl;

    delete e;
}
