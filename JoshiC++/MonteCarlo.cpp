#include "MonteCarlo.h"
#include "Payoff.h"
#include "Random.h"

#include <omp.h>

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


    int batches(omp_get_max_threads());
    int size = (NumberOfPath / batches) + 1;
#pragma warning (disable : 6993)
#pragma omp parallel for
    for (int i = 0; i < batches; i++)
    {
        double subSum(0);
        for (long i = 0; i < size; i++)
        {
            double thisGaussian = _generator();
            thisSpot = movedSpot * exp(rootVariance * thisGaussian);
            double thisPayoff = (*payoff)(thisSpot);
            subSum += thisPayoff;
        }
#pragma omp critical
        runningSum += subSum;
    }
    double mean = runningSum / (size * batches);
    mean *= exp(-r * Expiry);
    return mean;
}