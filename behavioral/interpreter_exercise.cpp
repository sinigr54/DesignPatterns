//
// Created by Alexander Chekh on 27.07.2018.
//

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <utility>
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;

namespace interpreter {
  namespace exercise {

    struct Token {
        enum Type {
            integer,
            plus,
            minus,
            variable,
            bad_variable
        };

        Type type;
        string text;

        friend ostream &operator<<(ostream &os, const Token &token) {
            os << "`" << token.text << "`";
            return os;
        }
    };

    struct Element {
        virtual int eval() = 0;
    };

    struct Integer : Element {
        int value{0};

        explicit Integer(int value) : value(value) {}

        int eval() override {
            return value;
        }

        void setValue(int value) {
            Integer::value = value;
        }
    };

    struct Variable : Element {
        char name{0};
        int value{0};

        explicit Variable(char name, int value) : name(name), value(value) {}

        int eval() override {
            return value;
        }
    };

    struct BadVariable : Element {
        int eval() override {
            return -1;
        }
    };

    struct BinaryOperation : Element {
        enum Type {
            addition,
            subtraction
        };

        Type type{addition};
        shared_ptr<Element> lhs;
        shared_ptr<Element> rhs;

        bool is_bad_expression{false};

        BinaryOperation() = default;

        BinaryOperation(Type type,
                        shared_ptr<Element> lhs,
                        shared_ptr<Element> rhs)
                : type(type),
                  lhs(std::move(lhs)),
                  rhs(std::move(rhs)) {

        }

        int eval() override {
            if (is_bad_expression) {
                return 0;
            }

            if (type == addition) {
                return lhs->eval() + rhs->eval();
            } else {
                return lhs->eval() - rhs->eval();
            }
        }
    };

    struct Lexer {
        static vector<Token> eval(const string &input) {
            vector<Token> result;

            for (auto i = 0; i < input.size(); ++i) {
                auto c = input[i];
                switch (c) {
                    case '+':
                        result.emplace_back(Token{Token::plus, "+"});
                        break;
                    case '-':
                        result.emplace_back(Token{Token::minus, "-"});
                        break;
                    case ' ':
                        continue;
                    default:
                        if (isdigit(c)) {
                            ostringstream buffer;
                            buffer << c;

                            for (auto j = i + 1; j < input.size(); ++j) {
                                if (isdigit(input[j])) {
                                    buffer << input[j];
                                    ++i;
                                } else {
                                    break;
                                }
                            }

                            result.emplace_back(Token{Token::integer, buffer.str()});
                        } else {
                            ostringstream buffer;
                            buffer << c;

                            for (auto j = i + 1; j < input.size(); ++j) {
                                if (isalpha(input[j])) {
                                    buffer << input[j];
                                    ++i;
                                } else {
                                    break;
                                }
                            }

                            string text = buffer.str();
                            auto token_type =
                                    text.size() == 1 ? Token::variable : Token::bad_variable;

                            result.emplace_back(Token{token_type, text});
                        }
                        break;
                }
            }

            return result;
        }
    };

    struct Parser {
        static shared_ptr<Element> parse(const vector<Token> &tokens,
                                         const map<char, int> &variables) {

            auto result = make_shared<BinaryOperation>();

            bool is_have_lhs = false;
            bool is_full_expr = false;

            pair<int, int> operand_indexes{0, 0};

            for (auto i = 0; i < tokens.size(); ++i) {
                auto token = tokens[i];

                switch (token.type) {
                    case Token::integer:
                    case Token::variable:
                    case Token::bad_variable: {
                        shared_ptr<Element> element;

                        if (token.type == Token::integer) {
                            int value = stoi(token.text);
                            element = make_shared<Integer>(value);
                        } else if (token.type == Token::variable) {
                            auto character = token.text[0];
                            int value = 0;

                            auto variable = variables.find(character);
                            if (variable != variables.end()) {
                                value = variable->second;
                            } else {
                                result->is_bad_expression = true;

                                return result;
                            }

                            element = make_shared<Variable>(character,
                                                            value);
                        } else {
                            result->is_bad_expression = true;

                            return result;
                        }

                        if (!is_full_expr) {
                            if (!is_have_lhs) {
                                result->lhs = element;
                                is_have_lhs = true;

                                operand_indexes.first = i;
                            } else {
                                result->rhs = element;
                                is_full_expr = true;

                                operand_indexes.second = i;
                            }
                        } else {
                            result->lhs = parse(vector<Token>(&tokens[operand_indexes.first],
                                                              &tokens[operand_indexes.second + 1]),
                                                variables);

                            result->rhs = element;

                            operand_indexes = {0, i};
                        }
                    }
                        break;
                    case Token::plus:
                        result->type = BinaryOperation::addition;
                        break;
                    case Token::minus:
                        result->type = BinaryOperation::subtraction;
                        break;
                }
            }

            return result;
        }
    };
  }
}

void interpreter_exercise() {
    map<char, int> variables = {{'x', 3},
                                {'d', -6}};

    auto input = "10 - 2 - x";

    auto tokens = interpreter::exercise::Lexer::eval(input);

    try {
        auto expression = interpreter::exercise::Parser::parse(tokens, variables);

        auto result = expression->eval();

        cout << input << " = " << result << endl;
    } catch (const exception &e) {

    }
}
