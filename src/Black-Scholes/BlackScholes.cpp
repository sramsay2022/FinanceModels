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

double BlackScholes::operator()(double vol) const
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

std::array<double, 2> BlackScholes::computeNormArgs(double vol) const
{
    const double sqrT = std::sqrt(m_timeToExp);

    const double d1 =
        (std::log(m_spot / m_strike) + ((m_rate - m_div + 0.5 * vol * vol) * m_timeToExp)) /
        (vol * sqrT);

    const double d2 = d1 - (vol * sqrT);

    return {d1, d2};
}

double implied_volatility(const BlackScholes& bsc, double opt_mkt_price, double x0, double x1,
                          double tol, unsigned max_iter)
{
    auto diff = [&bsc, opt_mkt_price](double x) { return bsc(x) - opt_mkt_price; };

    // x -> vol, y -> BSc opt price - mkt opt price
    double y0 = diff(x0);
    double y1 = diff(x1);

    double   impl_vol   = 0.0;
    unsigned count_iter = 0;
    for (count_iter = 0; count_iter <= max_iter; ++count_iter)
    {
        if (std::abs(x1 - x0) > tol)
        {
            impl_vol = x1 - (x1 - x0) * y1 / (y1 - y0);

            // Update x1 & x0:
            x0 = x1;
            x1 = impl_vol;
            y0 = y1;
            y1 = diff(x1);
        }
        else
        {
            return x1;
        }
    }

    return std::nan("");  // std::nan(" ") in <cmath>
}
