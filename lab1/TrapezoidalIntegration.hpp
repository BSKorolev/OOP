#pragma once
#include "NumericalIntegration.hpp"

class TrapezoidalIntegration : public NumericalIntegration {
public:
    TrapezoidalIntegration(int numPoints, double step, double precision);

    double Calc(std::function<double(double)> f, double lowerBound, double upperBound) override;
};