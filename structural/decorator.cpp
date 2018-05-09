//
// Created by Alexander Chekh on 01.05.2018.
//

#include "structural.h"
#include "Person.h"

#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <typeinfo>

using std::ostringstream;
using std::cout;
using std::endl;
using std::string;
using std::byte;

namespace dd {

  struct Shape {
      virtual string str() const = 0;
  };

  struct Circle : Shape {

      float radius{0};

      Circle() = default;

      explicit Circle(float radius) : radius(radius) {}

      /* Do not apply this method from dd when use dynamic dd */
      void resize(float factor) {
          radius *= factor;
      }

      string str() const override {
          ostringstream oss;
          oss << "Circle with radius " << radius;

          return oss.str();
      }
  };

  struct Square : Shape {

      float side{0};

      Square() = default;

      explicit Square(float side) : side(side) {}

      string str() const override {
          ostringstream oss;
          oss << "Square with side " << side;

          return oss.str();
      }
  };

  struct ColoredShape : Shape {
      Shape &shape;
      string color;

      ColoredShape(Shape &shape, string color) : shape(shape), color(std::move(color)) {}

      string str() const override {
          ostringstream oss;
          oss << shape.str() << " has a " << color << " color";

          return oss.str();
      }
  };

  struct TransparentShape : Shape {
      Shape &shape;
      byte transparency;

      TransparentShape(Shape &shape, byte transparency) : shape(shape), transparency(transparency) {

      }

      string str() const override {
          ostringstream oss;

          oss << shape.str() << " has "
              << static_cast<float>(transparency) / 255.0f * 100.0f
              << "% transparency";

          return oss.str();
      }
  };
}

namespace sd {

  template<typename T>
  struct ColoredShape : T {

      static_assert(std::is_base_of<dd::Shape, T>::value,
                    "Template argument must be a shape");

      string color;

      ColoredShape() = default;

      template<typename ...Args>
      explicit ColoredShape(string color, Args ...args) :
              T(std::forward<Args>(args)...), color(std::move(color)) {

      }

      string str() const override {
          ostringstream oss;
          oss << T::str() << " has a " << color << " color";

          return oss.str();
      }
  };

  template<typename T>
  struct TransparentShape : T {
      static_assert(std::is_base_of<dd::Shape, T>::value,
                    "Template argument must be a shape");

      byte transparency{static_cast<byte>(0)};

      TransparentShape() = default;

      template<typename ...Args>
      explicit TransparentShape(byte transparency, Args ...args) :
              T(std::forward<Args>(args)...), transparency(transparency) {

      }

      string str() const override {
          ostringstream oss;
          oss << T::str()
              << " has "
              << static_cast<float>(transparency) / 255.0f * 100.0f
              << "% transparency";

          return oss.str();
      }
  };

}

void structural_example5() {
    dd::Square square{4};
    dd::ColoredShape redSquare{square, "red"};
    dd::TransparentShape transparentRedSquare(redSquare, static_cast<byte>(51));

    cout << square.str() << endl;
    cout << redSquare.str() << endl;
    cout << transparentRedSquare.str() << endl;

    sd::ColoredShape<dd::Circle> greenCircle{"green", 5};
    greenCircle.resize(1.5f);
    cout << greenCircle.str() << endl;

    sd::TransparentShape<sd::ColoredShape<dd::Circle>> transparentRedCircle{
            static_cast<byte>(51), "red", 6
    };

    transparentRedCircle.resize(2);

    cout << transparentRedCircle.str() << endl;
    cout << endl;

    dd::Square rSquare{};
    dd::Shape &rShape = rSquare;

    if (typeid(rShape) == typeid(dd::Square)) {
        auto &realSquare = dynamic_cast<dd::Square &>(rShape);
        cout << realSquare.str() << endl;
    }

}


