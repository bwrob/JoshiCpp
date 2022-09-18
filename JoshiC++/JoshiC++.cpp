#include <iostream>
#include <cstring>
#include <memory>
#include <windows.h>

#include"Random.h"
#include"Payoff.h"
#include"MonteCarlo.h"

using std::cout; using std::cin;

int main()
{
    double expiry(0.25), strike(110), spot(100), vol(0.2), rate(0.02);
    int type(-1);
    unsigned long paths(100000000);

    // Reading in parameters
    cout << "Enter Call (1) Putt (2) Default (-1) \n";
    cin >> type;
    if (type != -1)
    {
        cout << "\nEnter expiry\n"; cin >> expiry;
        cout << "\nEnter Strike\n"; cin >> strike;
        cout << "\nEnter spot\n"; cin >> spot;
        cout << "\nEnter vol\n"; cin >> vol;
        cout << "\nEnter rate\n"; cin >> rate;
        cout << "\nEnter # paths\n"; cin >> paths;
    }

    // Create ptr to payoff
    std::shared_ptr<PayOff> ptr_payoff;
    if (type < 1)
        ptr_payoff = std::make_shared<PayOffCall>(strike);
    if (type == 1)
        ptr_payoff = std::make_shared<PayOffPut>(strike);

    // Run MC pricing
    auto start = GetTickCount64();
    auto mcGenerator = MonteCarlo(RandomGenerator::BoxMuller);
    double result = mcGenerator.VanillaEuropeanOption(ptr_payoff, expiry, spot, vol, rate, paths);
    cout << "The price is " << result << "\n";
    cout << std::endl << GetTickCount64() - start << std::endl;
}