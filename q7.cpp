/* 7. Implement a Black–Scholes pricer for a European call option using procedural
(rather than objectoriented) programming. Use it to price a European call option with t = 1 / 4
years (one quarter), K = 95 USD, S = 100 USD, σ = 50 percent per annum, r = 10 percent per annum
(not very realistic these days, I know).
*/

#include <iostream>
#include <cmath>
#include <cstdlib>
double norm_cdf(double value){
    return 0.5 * erfc(-value / sqrt(2));
}

double d1(double S, double r, double sigma, double K, double T){
    return (log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
}

double d2(double d1, double sigma, double T){
    return d1 - sigma * sqrt(T);
}

double black_scholes(double S, double r, double sigma, double K, double T){
    double d1var = d1(S, r, sigma, K, T);
    double d2var = d2(d1var, sigma, T);
    return S * norm_cdf(d1var) - K * exp(-r * T) * norm_cdf(d2var);
}

int main() {
    double S = 100.0;
    double K = 95.0;
    double r = 0.10;
    double sigma = 0.50;
    double T = 1.0 / 4.0;
    double call_price = black_scholes(S, r, sigma, K, T);
    std::cout << "The European call option price is: " << call_price << " USD" << std::endl;
    return 0;
}

/* Output:

The European call option price is: 13.6953 USD

*/
