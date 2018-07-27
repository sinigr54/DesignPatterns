//
// Created by Alexander Chekh on 01.05.2018.
//

#include "structural.h"

#include <iostream>
#include <string>
#include <vector>

/* Example composite pattern with CRTP */

using std::cout;
using std::endl;
using std::string;
using std::vector;

/* CRTP sample */
template<typename T>
struct SomeNeurons {
    template<typename R>
    void connectTo(R &other) {
        for (auto &from : *static_cast<T *>(this)) {
            for (auto &to : other) {
                from.out.push_back(&to);
                to.in.push_back(&from);
            }
        }
    }
};

struct Neuron : SomeNeurons<Neuron> {
    vector<Neuron *> in;
    vector<Neuron *> out;

    unsigned int id;

    Neuron() {
        static unsigned int id = {1};
        this->id = id++;
    }

    Neuron *begin() {
        return this;
    }

    Neuron *end() {
        return this + 1;
    }

    friend std::ostream &operator<<(std::ostream &os, const Neuron &obj) {
        for (auto *neuron : obj.in) {
            os << neuron->id << "\t-->\t[" << obj.id << "]" << endl;
        }

        for (auto *neuron : obj.out) {
            os << "[" << obj.id << "]" << "\t-->\t" << neuron->id << endl;
        }

        return os;
    }
};

/*
 * Do not inherit STL classes, because they do not have virtual destructor.
 * This is only example CRTP
 * */
struct NeuronLayer : public vector<Neuron>, SomeNeurons<NeuronLayer> {
    explicit NeuronLayer(int count) {
        while (count-- > 0) {
            emplace_back(Neuron{});
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const NeuronLayer &layer) {
        for (auto &neuron : layer) {
            os << neuron;
        }

        return os;
    }
};

void structural_example4() {
    Neuron n1;

    NeuronLayer layer1{3};
    layer1.connectTo(n1);

    cout << n1 << endl;

    cout << layer1 << endl;
}
