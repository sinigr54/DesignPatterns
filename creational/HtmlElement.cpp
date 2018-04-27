//
// Created by sinigr on 4/21/18.
//

#include "HtmlElement.h"

#include <sstream>
#include <iostream>

using std::cout;
using std::endl;
using std::ostringstream;

HtmlElement::HtmlElement(string name, string text) :
        name(std::move(name)),
        text(std::move(text)) {

}

string HtmlElement::toString(int indent) const {
    ostringstream oss;
    string i(indentSize * indent, ' ');
    oss << i << "<" << name << ">" << endl;
    if (!text.empty()) {
        oss << string(indentSize * (indent + 1), ' ') << text << endl;
    }

    for (const auto &e : elements) {
        oss << e.toString(indent + 1);
    }

    oss << i << "</" << name << ">" << endl;
    return oss.str();
}

HtmlElement::Builder::Builder(const string &rootName) : root(new HtmlElement()) {
    root->name = rootName;
}

HtmlElement::Builder &HtmlElement::Builder::addChild(const string &name, const string &text) {
    root->elements.emplace_back(HtmlElement(name, text));
    return *this;
}

HtmlElement HtmlElement::Builder::build() {
    if (root != nullptr) {
        return *(root.release());
    } else {
        return HtmlElement();
    }
}
