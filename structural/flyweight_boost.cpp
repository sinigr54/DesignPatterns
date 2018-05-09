//
// Created by Alexander Chekh on 05.05.2018.
//

#include "structural.h"

#include <string>
#include <boost/flyweight.hpp>
#include <iostream>

using std::string;
using std::ostream;
using std::cout;
using std::endl;

using boost::flyweight;

class User {
    flyweight<string> firstName;
    flyweight<string> lastName;

public:
    User(const string &firstName, const string &lastName) :
            firstName(firstName), lastName(lastName) {

    }

    friend ostream &operator<<(ostream &os, const User &user) {
        os << "firstName: " << user.firstName.get() << " lastName: " << user.lastName.get();
        return os;
    }

    const string &getFirstName() const {
        return firstName.get();
    }

    const string &getLastName() const {
        return lastName.get();
    }
};

void structural_example7() {
    User user1{"John", "Doe"};
    User user2{"Jane", "Doe"};

    cout << user1 << endl << user2 << endl;

    // Verify that last names of user1 and user2 point to one object
    cout << std::boolalpha << (&user1.getFirstName() == &user2.getFirstName()) << endl;
    cout << std::boolalpha << (&user1.getLastName() == &user2.getLastName()) << endl;
}

