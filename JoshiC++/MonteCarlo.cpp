#include "MonteCarlo.h"
#include "Payoff.h"
#include "Random.h"

MonteCarlo::MonteCarlo(RandomGenerator::Method method)
{
    _generator = RandomGenerator(method);
};


double MonteCarlo::VanillaEuropeanOption(
    std::shared_ptr<PayOff> payoff,
    double Expiry,
    double Spot,
    double Vol,
    double r,
    unsigned long NumberOfPath)
{
    double variance = Vol * Vol * Expiry;
    double rootVariance = sqrt(variance);
    double itoVorrelation = -0.5 * variance;

    double movedSpot = Spot * exp(r * Expiry + itoVorrelation);//compute first to recude call exp()
    double thisSpot;
    double runningSum = 0;

    for (unsigned long i = 0; i < NumberOfPath; i++)
    {
        double thisGaussian = _generator();
        thisSpot = movedSpot * exp(rootVariance * thisGaussian);
        double thisPayoff = (*payoff)(thisSpot);
        runningSum += thisPayoff;
    }

    double mean = runningSum / NumberOfPath;
    mean *= exp(-r * Expiry);
    return mean;
}