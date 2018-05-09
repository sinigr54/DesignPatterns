//
// Created by Alexander Chekh on 01.05.2018.
//

#include "structural.h"

#include <iostream>
#include <string>
#include <utility>
#include <vector>

// Treats the scalar object and composite object it's same

using std::cout;
using std::endl;
using std::string;
using std::vector;

struct GraphicObject {
    virtual void draw() = 0;
};

struct Circle : GraphicObject {
    void draw() override {
        cout << "Circle" << endl;
    }
};

struct Group : GraphicObject {
    string name;
    vector<GraphicObject*> objects;

    explicit Group(string name) : name(std::move(name)) {

    }

    void draw() override {
        cout << "Group " << name << " contains:" << endl;
        for (auto &&object : objects) {
            object->draw();
        }
    }

    void add(GraphicObject *object) {
        objects.push_back(object);
    }
};

void structural_example3() {
    Circle circle1;
    Circle circle2;

    Group group1{"root"};
    Group group2{"sub"};

    group1.add(&circle1);
    group2.add(&circle2);
    group1.add(&group2);

    group1.draw();
}
