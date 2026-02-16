#ifndef D4DBCA08_83C0_4DB5_B22C_E5D301B63AC7
#define D4DBCA08_83C0_4DB5_B22C_E5D301B63AC7

#include <array>

/*
    Black Scholes model:
    theta:  1 for call, -1 for put
    q:      Continuos annual dividend
    r:      Continuous annual risk-free interest rate
    sigma:  Annual volatility
    N(x):   Standard normal cummulative distribution function (CDF)
*/

enum class PayoffType
{
    Call = 1,
    Put  = -1
};

class BlackScholes
{
 public:
    BlackScholes(double strike, double spot, double timeToExp, PayoffType payoffType, double rate,
                 double div = 0.0);

    double operator()(double vol) const;

 private:
    // Returns d1 & d2 to compute CDF
    std::array<double, 2> computeNormArgs(double vol) const;

    double     m_strike, m_spot, m_timeToExp;
    PayoffType m_payoffType;
    double     m_rate, m_div;
};

double implied_volatility(const BlackScholes& bsc, double opt_mkt_price, double x0, double x1,
                          double tol = 1e-6, unsigned max_iter = 1000);
#endif /* D4DBCA08_83C0_4DB5_B22C_E5D301B63AC7 */
