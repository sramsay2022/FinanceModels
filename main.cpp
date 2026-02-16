#include <cmath>
#include <format>
#include <iostream>

#include "BlackScholes.h"

void Volatility_Known()
{
    double strike     = 75.0;
    auto   payoffType = PayoffType::Call;
    double spot       = 100.0;
    double rate       = 0.05;
    double vol        = 0.25;
    double timeToExp  = 0.0;

    BlackScholes bscITM{strike, spot, timeToExp, payoffType, rate};

    double value = bscITM(vol);

    std::cout << " ITM Value: " << value << std::endl;

    timeToExp = 0.25;
    // double dividend = 0.075;
    payoffType = PayoffType::Call;

    BlackScholes bscOTM{strike, spot, timeToExp, payoffType, rate};

    value = bscOTM(vol);

    std::cout << "OTM Value: " << value << std::endl;
}
void Volatility_Unknown()
{
    double strike     = 95.0;
    double spot       = 100.0;
    double timeToExp  = 0.25;
    auto   payoffType = PayoffType::Call;
    double rate       = 0.05;
    double dividend   = 0.07;

    BlackScholes bscITM{strike, spot, timeToExp, payoffType, rate, dividend};

    double mktOptPrice   = 6.2;
    double initVolGuess1 = 0.1;
    double initVolGuess2 = 0.15;

    double impliedVol = implied_volatility(bscITM, mktOptPrice, initVolGuess1, initVolGuess2);

    if (!std::isnan(impliedVol))
    {
        std::cout << std::format("Call ITM, time to expire = {}, ", timeToExp);
        std::cout << std::format("Implied vol = {}\n", impliedVol);

        double optVal = bscITM(impliedVol);
        std::cout << std::format("Value of option at implied vol = {}, ", optVal);
        std::cout << std::format("Market option price = {} \n", mktOptPrice);
    }
    else
    {
        std::cout << "No convergence to implied volatility" << std::endl;
    }
}

int main()
{
    Volatility_Known();

    Volatility_Unknown();

    return 0;
}
