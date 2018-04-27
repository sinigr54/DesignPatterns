//
// Created by sinigr on 4/22/18.
//

#include <cmath>
#include <ostream>
#include <cmath>
#include <iosfwd>
#include <iostream>

#include "creational.h"

#include "DrinkDirector.h"

// Factory Example

class Point {
    float x, y;

    Point(float x, float y) : x(x), y(y) {

    }

    class Factory {
        Factory() = default;

    public:

        static Point cartesian(float x, float y) {
            return {x, y};
        }

        static Point polar(float r, float t) {
            return {r * std::cos(t), r * std::sin(t)};
        }
    };

public:

    static Factory factory;

    friend std::ostream &operator<<(std::ostream &os, const Point &point) {
        os << "x: " << point.x << " y: " << point.y;
        return os;
    }
};

void creation_example2() {
    DrinkDirector director;
    auto drink = director.makeDrink("tea");

    DrinkFactoryWithVolume directorWithVolume;
    auto drinkWithVolume = directorWithVolume.makeDrink("tea");
}
