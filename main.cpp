#include <iostream>

#include "BlackScholes.h"

int main()
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

    return 0;
}
