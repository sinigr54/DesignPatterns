//
// Created by Alexander Chekh on 01.05.2018.
//

#ifndef DESIGNPATTERNS_PERSON_H
#define DESIGNPATTERNS_PERSON_H

#include <string>

class Person {
    std::string name;

    class PersonImpl;
    PersonImpl *impl;

public:

    explicit Person(const std::string &name);

    ~Person();

    void greet();
};


#endif //DESIGNPATTERNS_PERSON_H
