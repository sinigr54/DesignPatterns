//
// Created by Alexander Chekh on 05.05.2018.
//
#include "structural.h"

#include <functional>
#include <string>
#include <utility>
#include <iostream>
#include <vector>

using namespace std;

template <typename Fun>
class Logger {
    Fun fun;
    string name;

public:
    Logger(const Fun &fun, string name) : fun(fun), name(std::move(name)) {}

    void operator()() {
        cout << "Entering " << name << endl;
        fun();
        cout << "Exiting " << name << endl;
    }
};

template <typename Fun>
auto makeLogger(Fun fun, string name) {
    return Logger<Fun>(fun, name);
}

void structural_example6() {
//    Logger{[]() { cout << "Hello, World" << endl; }, "HelloFun"}();
    makeLogger([]() { cout << "Hello, World" << endl; }, "HelloFun")();
}
