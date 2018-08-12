//
// Created by Alexander Chekh on 12.08.2018.
//

#include "behavioral.h"
#include "Observer.h"
#include "Observable.h"

#include <iostream>

using std::cout;
using std::endl;

namespace Observer {

  class Person : public Observable<Person> { // observable
  public:

      explicit Person(int age) : age(age) {

      }

      int getAge() const {
          return age;
      }

      void setAge(int age) {
          if (Person::age == age) {
              return;
          }

          Person::age = age;
          notify(*this, "age");
      }

  private:

      int age;
  };

  // observer & observable

  class ConsolePersonObserver : public Observer<Person> {
      void fieldChanged(Person &source, const string &fieldName) override {
          cout << "Person's " << fieldName << " has changed to ";
          if (fieldName == "age") {
              cout << source.getAge();
          }

          cout << ".\n";
      }
  };

}

namespace BoostObserver {

  class Person : public Observable<Person> {
  public:

      explicit Person(int age) : age(age) {

      }

      int getAge() const {
          return age;
      }

      void setAge(int age) {
          if (Person::age == age) {
              return;
          }

          Person::age = age;
          fieldChanged(*this, "age");
      }

  private:

      int age;
  };

}

void behavioral_example8() {
    /*Observer::Person person{10};
    Observer::ConsolePersonObserver observer;

    person.subscribe(observer);

    person.setAge(23);
    person.setAge(44);

    person.unSubscribe(observer);

    person.setAge(22);*/

    BoostObserver::Person person{10};
    auto conn = person.fieldChanged.connect([](auto &source, const string &fieldName) {
        cout << "Person's " << fieldName << " has changed to ";
        if (fieldName == "age") {
            cout << source.getAge();
        }

        cout << ".\n";
    });

    person.setAge(33);

    conn.disconnect();

    person.setAge(32);
}
