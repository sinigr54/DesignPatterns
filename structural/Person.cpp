//
// Created by Alexander Chekh on 01.05.2018.
//

#include "Person.h"

#include <iostream>

using std::cout;
using std::endl;

class Person::PersonImpl {
public:

    void greet(const Person* person);
};

void Person::PersonImpl::greet(const Person *person) {
    cout << "My name is " << person->name << endl;
}

Person::Person(const std::string &name)
        : name(name), impl(new PersonImpl{}) {

}

Person::~Person() {
    delete impl;
}

void Person::greet() {
    impl->greet(this);
}
