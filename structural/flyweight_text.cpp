//
// Created by Alexander Chekh on 06.05.2018.
//

#include "structural.h"

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <algorithm>

using namespace std;

struct Interval {
    int start;
    int end;
    bool capitalize;

    Interval(int start, int end) : start(start), end(end), capitalize(false) {

    }

    bool covers(int position) const {
        return position >= start && position <= end;
    }
};

/* Можно было для каждого символа текста держать флаг
 * нужно форматировать или нет, для того, чтобы сэкономить память
 * выделяем внешнее состояние в отдельный объект и передаем его со сторны
 * увеличиваем лишь расходы на вычисления, но сокращаем расходы на память */
class FormattedText {
    vector<Interval> intervals;
    string text;

public:

    explicit FormattedText(string text) : text(std::move(text)) {

    }

    Interval &interval(int start, int end) {
        return intervals.emplace_back(start, end);
    }

    friend ostream &operator<<(ostream &os, const FormattedText &text) {
        string output;
        for (auto position = 0; position < text.text.length(); ++position) {
            for (auto &&interval : text.intervals) {
                char symbol = text.text[position];
                if (interval.covers(position) && interval.capitalize) {
                    output += static_cast<char>(toupper(symbol));
                } else {
                    output += symbol;
                }
            }
        }

        os << output;

        return os;
    }
};

void structural_example8() {
    FormattedText text("Hello, World!");
    text.interval(2, 10).capitalize = true;

    cout << text << endl;
}

