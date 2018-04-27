//
// Created by sinigr on 4/22/18.
//

#ifndef DESIGNPATTERNS_HOTDRINK_H
#define DESIGNPATTERNS_HOTDRINK_H

#include <iostream>

using namespace std;

struct HotDrink {
    virtual ~HotDrink() = default;

    virtual void prepare(int volume) const = 0;
};

struct Tea : public HotDrink {
    void prepare(int volume) const override {
        cout << "Tea is done. You can get " << volume << " ml" << endl;
    }
};

struct Coffee : public HotDrink {
    void prepare(int volume) const override {
        cout << "Coffee is done. You can get " << volume << " ml" << endl;
    }
};

#endif //DESIGNPATTERNS_HOTDRINK_H
