//
// Created by Alexander Chekh on 29.04.2018.
//

#include "structural.h"

#include <iostream>

using std::cout;
using std::endl;

namespace structural {

  struct Square {
      int side{0};

      explicit Square(int side) : side(side) {

      }
  };

  struct Rectangle {
      virtual ~Rectangle() = default;

      virtual int width() const = 0;

      virtual int height() const = 0;

      int area() const {
          return width() * height();
      }
  };

  class SquareToRectangleAdapter : public Rectangle {
  public:

      Square &square;

      explicit SquareToRectangleAdapter(Square &square) : square(square) {

      }

      int width() const override {
          return square.side;
      }

      int height() const override {
          return square.side;
      }
  };
}

int figureArea(const structural::Rectangle &rectangle) {
    return rectangle.area();
}

void structural_example1() {
    structural::Square square{10};
    structural::SquareToRectangleAdapter adapter{square};

    cout << figureArea(adapter) << endl;
}
