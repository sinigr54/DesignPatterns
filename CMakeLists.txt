cmake_minimum_required(VERSION 3.10)
project(DesignPatterns)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -lboost_serialization) # for clang

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost COMPONENTS filesystem system)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(DesignPatterns
        main.cpp
        di.hpp
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
        creational/factory.cpp
        creational/HotDrink.h
        creational/HotDrinkFactory.h
        creational/DrinkDirector.h
        creational/prototype.cpp
        creational/singleton.cpp)

target_link_libraries(DesignPatterns ${Boost_LIBRARIES})