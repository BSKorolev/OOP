#include <iostream>
#include "NumericalIntegration.hpp"
#include "TrapezoidalIntegration.hpp"
#include "SimpsonIntegration.hpp"

double f(double x) {
    return x * x;
}

int main() {
    int numPoints = 1000;
    double step = 1.0 / numPoints;
    double precision = 0.0001;

    NumericalIntegration* trapezoidal = new TrapezoidalIntegration(numPoints, step, precision);
    NumericalIntegration* simpson = new SimpsonIntegration(numPoints, step, precision);
        
    double lowerBound = 0;
    double upperBound = 1;

    double integralTrap = trapezoidal->Calc(f, lowerBound, upperBound);
    double integralSimp = simpson->Calc(f, lowerBound, upperBound);

    std::cout << "Trapezoidal integration result: " << integralTrap << std::endl;
    std::cout << "Simpson integration result: " << integralSimp << std::endl;

    delete trapezoidal;
    delete simpson;

    return 0;
}