//
// Created by sinigr on 4/23/18.
//

#include "creational.h"

#include <string>
#include <iostream>
#include <utility>
#include <memory>

using namespace std;

struct Address {
    string street, city;
    int suit;

    Address(string street, string city, int suit) :
            street(std::move(street)), city(std::move(city)), suit(suit) {

    }

    Address(const Address &other) = default;

    friend ostream &operator<<(ostream &os, const Address &address) {
        os << "street: " << address.street << " city: " << address.city << " suit: " << address.suit;
        return os;
    }
};

struct Contact {
    string name;
    Address *address;

    Contact(string name, Address *address) : name(std::move(name)), address(address) {
        // Call once at this example
    }

    Contact(const Contact &other) :
            name(other.name), address(new Address(*other.address)) {
        // Call twice at this example
    }

    ~Contact() {
        delete address;
    }

    friend ostream &operator<<(ostream &os, const Contact &contact) {
        os << "name: " << contact.name << " address: " << *contact.address;
        return os;
    }
};

class EmployeeFactory {
    static unique_ptr<Contact> employee(string name, int suit, const Contact &employee) {
        auto result = make_unique<Contact>(employee);
        result->name = std::move(name);
        result->address->suit = suit;
        return result;
    }

public:
    /* Создаем прототип, с заданными по умолчанию полями главного офиса */
    static unique_ptr<Contact> mainOfficeEmployee(string name, int suit) {
        /* Т.к. объект статический, то он создастся только 1 раз */
        static Contact prototype{"", new Address{"123 East Dr", "London", 0}};
        return employee(std::move(name), suit, prototype);
    }
};

void creation_example3() {
//    auto john = Contact{"John Doe", new Address{"123 East Dr", "London", 123}};

    auto john = EmployeeFactory::mainOfficeEmployee("John Doe", 123);
    auto jane = EmployeeFactory::mainOfficeEmployee("Jane Smith", 103);
    cout << *john << endl << *jane << endl;
}
