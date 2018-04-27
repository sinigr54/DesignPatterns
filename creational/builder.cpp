//
// Created by sinigr on 4/21/18.
//
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <memory>

#include "creational.h"

using namespace std;

struct HtmlBuilder;

struct HtmlElement {

    string name;
    string text;
    vector<HtmlElement> elements;
    const size_t indentSize = 2;

    HtmlElement() = default;

    HtmlElement(string name, string text)
            : name(std::move(name)),
              text(std::move(text)) {
    }

    string str(int indent = 0) const {
        ostringstream oss;
        string i(indentSize * indent, ' ');
        oss << i << "<" << name << ">" << endl;
        if (!text.empty())
            oss << string(indentSize * (indent + 1), ' ') << text << endl;

        for (const auto &e : elements)
            oss << e.str(indent + 1);

        oss << i << "</" << name << ">" << endl;
        return oss.str();
    }

    static unique_ptr<HtmlBuilder> create(string root_name) {
        return make_unique<HtmlBuilder>(root_name);
    }

    /*static HtmlBuilder build(string root_name) {
        return {root_name};
    }*/
};

struct HtmlBuilder {
    explicit HtmlBuilder(const string &root_name) {
        cout << "HtmlBuilder" << endl;
        root.name = root_name;
    }

    HtmlBuilder(const HtmlBuilder &other) {
        cout << "HtmlBuilder copy" << endl;
    }

    HtmlBuilder(HtmlBuilder &&other) {
        cout << "HtmlBuilder moving" << endl;
    }

    // void to start with
    HtmlBuilder &add_child(const string &child_name, const string &child_text) {
        root.elements.emplace_back(child_name, child_text);
        return *this;
    }

    // pointer based
    HtmlBuilder *add_child_2(const string &child_name, const string &child_text) {
        root.elements.emplace_back(child_name, child_text);
        return this;
    }

    HtmlElement build() {
        return root;
    }

    string str() { return root.str(); }

    explicit operator HtmlElement() const {
        return root;
    }

    HtmlElement root;
};

void creation_example1() {
    // <p>hello</p>
    auto text = "hello";
    string output;
    output += "<p>";
    output += text;
    output += "</p>";
    printf("<p>%s</p>", text);

    // <ul><li>hello</li><li>world</li></ul>
    string words[] = {"hello", "world"};
    ostringstream oss;
    oss << "<ul>";
    for (const auto &w : words)
        oss << "  <li>" << w << "</li>";
    oss << "</ul>";
    printf(oss.str().c_str());

    cout << endl;

    std::to_string(1);

    // why it is work?
    // easier
   /* auto builder = HtmlBuilder("ul")
            .add_child("li", "hello")
            .add_child("li", "world");

    cout << builder.str() << endl;*/

    auto builder2 = HtmlElement::create("ul");
    builder2->add_child_2("li", "hello")
            ->add_child_2("li", "world");

    cout << builder2->str() << endl;

}
