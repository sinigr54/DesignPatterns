//
// Created by sinigr on 4/22/18.
//

#ifndef DESIGNPATTERNS_HOTDRINKDIRECTOR_H
#define DESIGNPATTERNS_HOTDRINKDIRECTOR_H

#include <unordered_map>
#include <string>
#include <memory>
#include <functional>

#include "HotDrink.h"
#include "HotDrinkFactory.h"

using namespace std;

class DrinkDirector {
    unordered_map<string, unique_ptr<HotDrinkFactory>> drinkFactories;

public:
    DrinkDirector() {
        drinkFactories["tea"] = make_unique<TeaFactory>();
        drinkFactories["coffee"] = make_unique<CoffeeFactory>();
    }

    unique_ptr<HotDrink> makeDrink(const string &name) {
        auto drink = drinkFactories[name]->make();
        drink->prepare(100);
        return drink;
    }
};

class DrinkFactoryWithVolume {
    unordered_map<string, function<unique_ptr<HotDrink>()>> factories;

public:
    DrinkFactoryWithVolume() {
        factories["tea"] = []() -> auto {
            auto tea = make_unique<Tea>();
            tea->prepare(200);
            return tea;
        };

        factories["coffee"] = []() -> auto {
            auto drink = TeaFactory().make();
            drink->prepare(200);
            return drink;
        };
    }

    unique_ptr<HotDrink> makeDrink(const string &name) {
        return factories[name]();
    }
};

#endif //DESIGNPATTERNS_HOTDRINKDIRECTOR_H
