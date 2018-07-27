//
// Created by Alexander Chekh on 27.07.2018.
//

#include "behavioral.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <utility>

#include <boost/lexical_cast.hpp>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::to_string;

using std::isdigit;
using std::ostringstream;
using std::shared_ptr;
using std::make_shared;

struct Token {
    enum Type {
        integer,
        plus,
        minus,
        lparen,
        rparen
    };

    Type type;
    string text;

    Token(Type type, string text) : type(type), text(std::move(text)) {

    }

    friend std::ostream &operator<<(std::ostream &os, const Token &token) {
        os << "`" << token.text << "`";
        return os;
    }
};

vector<Token> lex(const string &input) {
    vector<Token> result;

    for (int i = 0; i < input.size(); ++i) {
        switch (input[i]) {
            case '+':
                result.emplace_back(Token{Token::plus, "+"});
                break;
            case '-':
                result.emplace_back(Token{Token::minus, "-"});
                break;
            case '(':
                result.emplace_back(Token{Token::lparen, "("});
                break;
            case ')':
                result.emplace_back(Token{Token::rparen, ")"});
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': {
                ostringstream buffer;
                buffer << input[i];
                for (int j = i + 1; j < input.size(); ++j) {
                    if (isdigit(input[j])) {
                        buffer << input[j];
                        ++i;
                    } else {
                        result.emplace_back(Token{Token::integer, buffer.str()});
                        break;
                    }
                }
            }
                break;
            default:
                break;
        }
    }

    return result;
}

struct Element {
    virtual int eval() = 0;
};

struct Integer : Element {
    int value{0};

    explicit Integer(int value) : value(value) {}

    int eval() override {
        return value;
    }
};

struct BinaryOperation : Element {
    enum Type {
        addition, subtraction
    } type;

    shared_ptr<Element> lhs;
    shared_ptr<Element> rhs;

    int eval() override {
        switch (type) {
            case addition:
                return lhs->eval() + rhs->eval();
            case subtraction:
                return lhs->eval() - rhs->eval();
            default:
                return 0;
        }
    }
};

shared_ptr<Element> parse(const vector<Token> &tokens) {
    shared_ptr<BinaryOperation> result = make_shared<BinaryOperation>();
    bool have_lhs{false};

    for (auto i = 0; i < tokens.size(); ++i) {
        auto token = tokens[i];
        switch (token.type) {
            case Token::integer: {
                auto value = boost::lexical_cast<int>(token.text);
                auto integer = make_shared<Integer>(value);
                if (!have_lhs) {
                    result->lhs = integer;
                    have_lhs = true;
                } else {
                    result->rhs = integer;
                }
            }
                break;
            case Token::plus:
                result->type = BinaryOperation::addition;
                break;
            case Token::minus:
                result->type = BinaryOperation::subtraction;
                break;
            case Token::lparen: {
                auto j = i;

                for (; j < tokens.size(); ++j) {
                    if (tokens[j].type == Token::rparen) {
                        break;
                    }
                }

                vector<Token> subexpression(&tokens[i + 1], &tokens[j]);
                auto element = parse(subexpression);

                if (!have_lhs) {
                    result->lhs = element;
                    have_lhs = true;
                } else {
                    result->rhs = element;
                }

                i = j;
            }
                break;

            case Token::rparen:
                break;
        }
    }

    return result;
}

void behavioral_example3() {
    string input{"(13 - 4) - (12 + 1)"};

    auto result = lex(input);

    for (auto &item : result) {
        cout << item << " ";
    }
    cout << endl;

    try {
        auto element = parse(result);
        cout << input << " = " << element->eval() << endl;
    } catch (const boost::bad_lexical_cast &e) {
        cout << e.what() << endl;
    }

    cout << endl;
}
