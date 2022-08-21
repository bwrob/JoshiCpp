#include"Random.h"
#include"Payoff.h"
#include <iostream>
#include <cmath>
#include <cstring>


using namespace std;

//function doing the MC simulation
double SimpleMonteCarlo1(
    PayOff payoff,
    double Expiry,
    double Spot,
    double Vol,
    double r,
    unsigned long NumberOfPath,
    RandomGenerator rand)
{
    double variance = Vol * Vol * Expiry;
    double rootVariance = sqrt(variance);
    double itoVorrelation = -0.5 * variance;

    double movedSpot = Spot * exp(r * Expiry + itoVorrelation);//compute first to recude call exp()
    double thisSpot;
    double runningSum = 0;

    for (unsigned long i = 0; i < NumberOfPath; i++)
    {
        double thisGaussian = rand();
        thisSpot = movedSpot * exp(rootVariance * thisGaussian);
        double thisPayoff = payoff(thisSpot);
        runningSum += thisPayoff;
    }

    double mean = runningSum / NumberOfPath;
    mean *= exp(-r * Expiry);
    return mean;
}

int main()
{
    double expiry, strike, spot, vol, rate;
    unsigned long paths;
    string type_string;
    PayOff::OptionType type;

    //read in parameters
    cout << "\nEnter Call/Putt\n";
    cin >> type_string;

    cout << "\nEnter expiry\n";
    cin >> expiry;

    cout << "\nEnter Strike\n";
    cin >> strike;

    cout << "\nEnter spot\n";
    cin >> spot;

    cout << "\nEnter vol\n";
    cin >> vol;

    cout << "\nEnter rate\n";
    cin >> rate;

    cout << "\n Number of paths\n";
    cin >> paths;
    
    //processing inputs
    if (type_string == "c")
        type = PayOff::Call;
    else if (type_string == "p")
        type = PayOff::Put;
    else
        throw "Invalid option type control string.";
    auto payoff = PayOff(strike, type);
    
    auto randGen = RandomGenerator(RandomGenerator::BoxMuller);
    
    double result = SimpleMonteCarlo1(payoff, expiry, spot, vol, rate, paths, randGen);

    cout << "the price is " << result << "\n";
}