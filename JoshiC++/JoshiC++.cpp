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
        double thisGaussian = rand.getRandom();
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
    double Expiry;
    double Strike;
    double Spot;
    double Vol;
    double r;
    unsigned long NumberOfPath;
    string type_string;
    PayOff::OptionType type;

    //read in parameters
    cout << "\nEnter Call/Putt\n";
    cin >> type_string;

    cout << "\nEnter expiry\n";
    cin >> Expiry;

    cout << "\nEnter Strike\n";
    cin >> Strike;

    cout << "\nEnter spot\n";
    cin >> Spot;

    cout << "\nEnter vol\n";
    cin >> Vol;

    cout << "\nEnter r\n";
    cin >> r;

    cout << "\n Number of paths\n";
    cin >> NumberOfPath;
    
    //processing inputs
    if (type_string == "c")
        type = PayOff::Call;
    else if (type_string == "p")
        type = PayOff::Put;
    else
        throw "Invalid option type control string.";
    auto payoff = PayOff(Strike, type);
    
    auto randGen = RandomGenerator(BoxMuller);
    
    double result = SimpleMonteCarlo1(payoff,
        Expiry,
        Spot,
        Vol,
        r,
        NumberOfPath,
        randGen);
        
    cout << "the price is " << result << "\n";

    double tmp;
    cin >> tmp;

    return 0;

}