#include <iostream>

#include <cstring>
#include <memory>

#include"Random.h"
#include"Payoff.h"
#include"MonteCarlo.h"

using namespace std;

int main()
{
    double expiry, strike, spot, vol, rate;
    unsigned long paths, type;

    //read in parameters
    cout << "\nEnter Call/Putt\n";
    cin >> type;

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
    shared_ptr<PayOff> ptr_payoff;
    if (type == 0)
        ptr_payoff = make_shared<PayOffCall>(strike);
    else
        ptr_payoff = make_shared<PayOffPut>(strike);

    auto mcGenerator = MonteCarlo(RandomGenerator::BoxMuller);
    double result = mcGenerator.VanillaEuropeanOption(ptr_payoff, expiry, spot, vol, rate, paths);

    cout << "the price is " << result << "\n";
}