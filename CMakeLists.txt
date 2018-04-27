cmake_minimum_required(VERSION 3.10)
project(DesignPatterns)

set(CMAKE_CXX_STANDARD 17)

add_executable(DesignPatterns
        main.cpp
        solid/single_responsibility.cpp
        solid/solid.h
        solid/open_close.cpp
        solid/liscov_substitution.cpp
        solid/interface_segregation.cpp
        solid/dependency_inversion.cpp
        creational/creational.h
        creational/builder.cpp
        creational/HtmlElement.cpp
        creational/HtmlElement.h
        creational/factory.cpp creational/HotDrink.h creational/HotDrinkFactory.h creational/DrinkDirector.h creational/prototype.cpp)