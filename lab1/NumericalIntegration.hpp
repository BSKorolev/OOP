#pragma once
#include <cmath>
#include <functional>

class NumericalIntegration {
protected:
    int numPoints;
    double step;
    double precision;

public:
    NumericalIntegration(int numPoints, double step, double precision)
        : numPoints(numPoints), step(step), precision(precision) {}

    virtual double Calc(std::function<double(double)> f, double lowerBound, double upperBound) = 0;
};