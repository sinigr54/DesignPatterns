//
// Created by Alexander Chekh on 19.08.2018.
//

#include "behavioral.h"

#include <iostream>
#include <vector>
#include <complex>
#include <tuple>
#include <limits>

using namespace std;

struct DiscriminantStrategy {
    virtual double calculate_discriminant(double a, double b, double c) = 0;
};

struct OrdinaryDiscriminantStrategy : DiscriminantStrategy {
    double calculate_discriminant(double a, double b, double c) override {
        double discriminant = b * b - 4 * a * c;
        return discriminant;
    }
};

struct RealDiscriminantStrategy : DiscriminantStrategy {
    double calculate_discriminant(double a, double b, double c) override {
        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0) {
            return numeric_limits<double>::quiet_NaN();
        } else {
            return discriminant;
        }
    }
};

class QuadraticEquationSolver {
    DiscriminantStrategy &strategy;
public:
    explicit QuadraticEquationSolver(DiscriminantStrategy &strategy) : strategy(strategy) {}

    tuple<complex<double>, complex<double>> solve(double a, double b, double c) {
        complex<double> positiveResult;
        complex<double> negativeResult;

        complex<double> discriminant{strategy.calculate_discriminant(a, b, c), 0};

        auto sqrtDiscriminant = sqrt(discriminant);

        positiveResult = (-b + sqrtDiscriminant) / (2 * a);
        negativeResult = (-b - sqrtDiscriminant) / (2 * a);

        return tuple{positiveResult, negativeResult};
    }
};

void strategy_exercise() {

}
