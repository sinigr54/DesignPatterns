#include <iostream>
#include "solid/solid.h"
#include "creational/HtmlElement.h"
#include "creational/creational.h"

#include <string>
#include <utility>
#include <ostream>

using namespace std;

int main() {
    auto element = HtmlElement::Builder("ul")
            .addChild("li", "hello")
            .addChild("li", "world")
            .build();

    std::cout << element.toString() << std::endl;

    creation_example3();

    return 0;
}