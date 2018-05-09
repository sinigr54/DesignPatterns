//
// Created by Alexander Chekh on 30.04.2018.
//

#include "structural.h"
#include "Person.h"

#include <iostream>

using std::cout;
using std::endl;

// Shapes: Circle, Square
// Renderers: RasterRenderer, VectorRenderer
// 2x2 classes: CircleRasterRenderer, SquareRasterRenderer, CircleVectorRenderer, SquareVectorRenderer

// Bridge allows us to avoid this situation and give 2 + 2 classes (or 3 + 3, instead 3 * 3)

struct Renderer {
    virtual void drawCircle(float x, float y, float radius) const = 0;
};

struct RasterRenderer : Renderer {
    void drawCircle(float x, float y, float radius) const override {
        cout << "Draw raster circle with radius: " << radius << endl;
    }
};

struct VectorRenderer : Renderer {
    void drawCircle(float x, float y, float radius) const override {
        cout << "Draw vector circle with radius: " << radius << endl;
    }
};

struct Shape {
    const Renderer &renderer;

    explicit Shape(const Renderer &renderer) : renderer(renderer) {

    }

    virtual void draw() const = 0;

    virtual void resize(float factor) = 0;

    virtual ~Shape() = default;
};

struct Circle : Shape {

    float x;
    float y;
    float radius;

    Circle(const Renderer &renderer, float x, float y,
           float radius) : Shape{renderer}, x{x}, y{y}, radius{radius} {

    }

    void draw() const override {
        renderer.drawCircle(x, y, radius);
    }

    void resize(float factor) override {
        radius *= factor;
    }
};

void structural_example2() {
    Person p{"Sasha"};

    p.greet();

    RasterRenderer rasterRenderer;
    VectorRenderer vectorRenderer;

    Circle rasterCircle{rasterRenderer, 5, 5, 5};
    Circle vectorCircle{vectorRenderer, 5, 5, 5};

    rasterCircle.draw();
    vectorCircle.draw();
}
