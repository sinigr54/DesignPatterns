//
// Created by Alexander Chekh on 29.04.2018.
//

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <memory>

#include "../di.hpp"

using namespace std;
using namespace boost;

class Database {
    unordered_map<string, int> capitals;

    Database() {
        cout << "Database initialization" << endl;

        ifstream file("/Users/sinigr/CLionProjects/DesignPatterns/creational/capitals.txt");

        string cityName;
        string peoplesCount;

        while (getline(file, cityName)) {
            getline(file, peoplesCount);

            int count = stoi(peoplesCount);
            capitals[cityName] = count;
        }
    }

public:

    Database(const Database &) = delete;

    void operator=(Database &) = delete;

    static Database &instance() {
        static Database database;
        return database;
    }

    int peoplesCount(const string &cityName) {
        return capitals[cityName];
    }
};

struct IFoo {
    virtual ~IFoo() = default;

    virtual string name() = 0;
};

struct Foo : public IFoo {
    static int count;

    Foo() {
        ++count;
    }

    string name() override {
        return "foo " + to_string(count);
    }
};

int Foo::count = 0;

struct Bar {
    std::shared_ptr<IFoo> foo;
};

void creation_example4() {
    cout << Database::instance().peoplesCount("Tokio") << endl;
    cout << Database::instance().peoplesCount("Moscow") << endl;

    auto injector = di::make_injector(
            di::bind<IFoo>().to<Foo>().in(di::singleton) // create only one instance of foo ptr in bar
    );

    auto bar1 = injector.create<std::shared_ptr<Bar>>();
    auto bar2 = injector.create<std::shared_ptr<Bar>>();

    cout << bar1->foo->name() << endl;
    cout << bar2->foo->name() << endl;

    cout << boolalpha << (bar1.get() == bar2.get()) << endl;

    auto singletonInjector = di::make_injector(
            di::bind<Foo>().in(di::singleton)
    );

    auto f1 = injector.create<Foo>();
    auto f2 = injector.create<Foo>();

    cout << f1.name() << endl;
    cout << f2.name() << endl;
}
