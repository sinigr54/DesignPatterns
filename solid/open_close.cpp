//
// Created by sinigr on 4/21/18.
//
// open closed principle

// open for extension, closed for modification

#include <string>
#include <vector>
#include <iostream>

#include "solid.h"

using namespace std;

enum class Color {
    red, green, blue
};
enum class Size {
    small, medium, large
};

struct Product {
    string name;
    Color color;
    Size size;
};

struct ProductFilter {
    typedef vector<Product *> Items;

    Items by_color(Items items, Color color) {
        Items result;
        for (auto &i : items)
            if (i->color == color)
                result.push_back(i);
        return result;
    }

    Items by_size(Items items, Size size) {
        Items result;
        for (auto &i : items)
            if (i->size == size)
                result.push_back(i);
        return result;
    }

    Items by_size_and_color(Items items, Size size, Color color) {
        Items result;
        for (auto &i : items)
            if (i->size == size && i->color == color)
                result.push_back(i);
        return result;
    }
};

template<typename T>
struct AndSpecification;

template<typename T>
struct Specification {
    virtual bool is_satisfied(T *item) = 0;

    AndSpecification<T> operator&&(Specification<T> &&other) {
        return AndSpecification<T>(*this, other);
    }
};

template<typename T>
struct Filter {
    virtual vector<T *> filter(vector<T *> items,
                               Specification<T> &spec) = 0;
};

struct BetterFilter : Filter<Product> {
    vector<Product *> filter(vector<Product *> items,
                             Specification<Product> &spec) override {
        vector<Product *> result;
        for (auto &p : items)
            if (spec.is_satisfied(p))
                result.push_back(p);
        return result;
    }
};

struct ColorSpecification : Specification<Product> {
    Color color;

    explicit ColorSpecification(Color color) : color(color) {}

    bool is_satisfied(Product *item) override {
        return item->color == color;
    }
};

struct SizeSpecification : Specification<Product> {
    Size size;

    explicit SizeSpecification(const Size size) : size(size) {
    }

    bool is_satisfied(Product *item) override {
        return item->size == size;
    }
};

template<typename T>
struct AndSpecification : Specification<T> {
    Specification<T> &first;
    Specification<T> &second;

    AndSpecification(Specification<T> &first, Specification<T> &second) : first(first), second(second) {}

    bool is_satisfied(T *item) override {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

void solid_example2() {
    Product apple{"Apple", Color::green, Size::small};
    Product tree{"Tree", Color::green, Size::large};
    Product house{"House", Color::blue, Size::large};

    vector<Product *> all{&apple, &tree, &house};

    BetterFilter bf;
    ColorSpecification green(Color::green);

    auto green_things = bf.filter(all, green);
    for (auto &x : green_things)
        cout << x->name << " is green\n";

    SizeSpecification large(Size::large);
    AndSpecification<Product> green_and_large(green, large);

    //auto big_green_things = bf.filter(all, green_and_large);

    auto colorSpec = ColorSpecification{Color::green};
    auto sizeSpec = SizeSpecification{Size::large};
    auto spec = colorSpec && move(sizeSpec);

    for (auto &x : bf.filter(all, spec)) {
        cout << x->name << " is green and large\n";
    }
}
