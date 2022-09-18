#pragma once

#include <memory>
#include "Random.h"

class PayOff;

class MonteCarlo
{
public:
    MonteCarlo(RandomGenerator::Method method);
    double VanillaEuropeanOption(std::shared_ptr<PayOff> payoff, double Expiry, double Spot, double Vol, double r, unsigned long NumberOfPath);

private:
    RandomGenerator _generator;
};
