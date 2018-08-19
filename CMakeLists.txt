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
        creational/DrinkFactory.h
        creational/prototype.cpp
        creational/singleton.cpp
        structural/structural.h
        structural/adapter.cpp
        structural/bridge.cpp
        structural/Person.cpp
        structural/Person.h
        structural/composite.cpp
        structural/crtp.cpp
        structural/decorator.cpp
        structural/functional_decorator.cpp
        structural/excercise.cpp
        structural/flyweight_boost.cpp
        structural/flyweight_text.cpp
        behavioral/behavioral.h
        behavioral/chain_of_responsibility.cpp
        behavioral/command.cpp
        behavioral/interpreter.cpp
        behavioral/interpreter_exercise.cpp
        behavioral/iterator.cpp
        behavioral/mediator.cpp
        behavioral/User.cpp
        behavioral/User.h
        behavioral/ChatRoom.cpp
        behavioral/ChatRoom.h
        behavioral/memento.cpp
        behavioral/simple_observer.cpp
        behavioral/complicated_observer.cpp
        behavioral/Observer.h
        behavioral/Observable.h
        behavioral/state.cpp behavioral/dynamic_strategy.cpp)

target_link_libraries(DesignPatterns ${Boost_LIBRARIES})