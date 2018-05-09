//
// Created by Alexander Chekh on 05.05.2018.
//
#include <string>
#include <sstream>
#include <iostream>
#include <typeinfo>

using namespace std;

struct Flower
{
  virtual string str() = 0;
};

struct Rose : Flower
{
  string str() override {
    // todo
    return "A rose";
  }
};

struct RedFlower : Flower
{
    Flower &flower;

    RedFlower(Flower &flower) : flower(flower) {

    }

    string str() override {
        ostringstream oss;

        if (typeid(flower) == typeid(Rose)) {
            oss << flower.str() << " thar is red";
        } else if (typeid(flower) != typeid(RedFlower)) {
            oss << " and red";
        }

        return oss.str();
    }
};

struct BlueFlower : Flower
{
    Flower &flower;

    BlueFlower(Flower &flower) : flower(flower) {

    }

    string str() override {
        ostringstream oss;
        oss << flower.str();

        if (typeid(flower) == typeid(Rose)) {
            oss << " thar is blue";
        } else if (typeid(flower) != typeid(BlueFlower)) {
            oss << " and blue";
        }

        return oss.str();
    }
};

void structural_exercise() {
    Rose rose;
    RedFlower redRose{rose};
    RedFlower redRedRose{redRose};
    BlueFlower blueRedRose{redRose};

    cout << rose.str() << endl;
    cout << redRose.str() << endl;
    cout << redRedRose.str() << endl;
    cout << blueRedRose.str() << endl;
}
