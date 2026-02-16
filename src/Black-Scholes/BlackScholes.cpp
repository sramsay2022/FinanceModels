#include "BlackScholes.h"

#include <algorithm>
#include <cmath>
#include <numbers>

BlackScholes::BlackScholes(double strike, double spot, double timeToExp, PayoffType payoffType,
                           double rate, double div)
    : m_strike{strike}
    , m_spot{spot}
    , m_timeToExp{timeToExp}
    , m_payoffType{payoffType}
    , m_rate{rate}
    , m_div{div}
{
}

double BlackScholes::operator()(double vol)
{
    using std::exp;

    const int phi = static_cast<int>(m_payoffType);

    if (m_timeToExp > 0.0)
    {
        auto   normArgs = computeNormArgs(vol);
        double d1       = normArgs[0];
        double d2       = normArgs[1];

        auto normCDF = [](double x) { return (1.0 + std::erf(x / std::numbers::sqrt2)) / 2.0; };

        double nd1 = normCDF(phi * d1);
        double nd2 = normCDF(phi * d2);

        double discFactor = exp(-m_rate * m_timeToExp);

        return phi * (m_spot * exp(-m_div * m_timeToExp) * nd1 - discFactor * m_strike * nd2);
    }
    else
    {
        return std::max(phi * (m_spot - m_strike), 0.0);
    }
}

std::array<double, 2> BlackScholes::computeNormArgs(double vol)
{
    double d1 = ((std::log(m_spot / m_strike) + (m_rate - m_div + 0.5 * vol * vol)) * m_timeToExp) /
                (vol * sqrt(m_timeToExp));

    double d2 = d1 - (vol * sqrt(m_timeToExp));

    return {d1, d2};
}
