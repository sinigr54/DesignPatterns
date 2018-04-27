//
// Created by sinigr on 4/22/18.
//

#ifndef DESIGNPATTERNS_HOTDRINKFACTORY_H
#define DESIGNPATTERNS_HOTDRINKFACTORY_H

#include "HotDrink.h"
#include <memory>

using namespace std;

struct HotDrinkFactory {
    virtual unique_ptr<HotDrink> make() const = 0;
};

struct TeaFactory : public HotDrinkFactory {
    unique_ptr<HotDrink> make() const override {
        return make_unique<Tea>();
    }
};

struct CoffeeFactory : public HotDrinkFactory {
    unique_ptr<HotDrink> make() const override {
        return make_unique<Coffee>();
    }
};

#endif //DESIGNPATTERNS_HOTDRINKFACTORY_H
