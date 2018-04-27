//
// Created by sinigr on 4/21/18.
//

#ifndef DESIGNPATTERNS_HTMLELEMENT_H
#define DESIGNPATTERNS_HTMLELEMENT_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

using std::string;
using std::vector;

// Builder example

class HtmlElement {

    string name;
    string text;
    vector<HtmlElement> elements;
    const size_t indentSize = 2;

    HtmlElement() = default;

    HtmlElement(string name, string text);

public:

    class Builder {
        std::unique_ptr<HtmlElement> root;

    public:

        explicit Builder(const string &rootName);

        Builder& addChild(const string &name, const string &text);

        HtmlElement build();
    };

    string toString(int indent = 0) const;
};


#endif //DESIGNPATTERNS_HTMLELEMENT_H
