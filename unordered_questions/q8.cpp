/* 8. Function templates are special functions that can operate with generic types. This allows us to create
a function template whose functionality can be adapted to more than one type or class without
repeating the entire code for each type. In C++ this can be achieved using template parameters.
A template parameter is a special kind of parameter that can be used to pass a type as argument:
just like regular function parameters can be used to pass values to a function, template parameters
allow to pass types to a function. These function templates can use these parameters as if they
were any other regular type. Provide an implementation of the following function template implementing the
bisection method (https://en.wikipedia.org/wiki/Bisection_method)
*/


#include <iostream>
#include <cmath>
#include <functional>


template <typename T>

// Normally, a variable used to denote the maximum number of iterations should also be included. However, according
// to the problem description, such a variable is not used in this scenario.
double interval_bisection(double y_target, double left, double right, double epsilon, T functor) {
    double mid;
    double y_mid;
    while ((right - left) > epsilon) {
        mid = (left + right) / 2.0;
        y_mid = functor(mid);
        if ((y_mid - y_target) * (functor(left) - y_target) > 0) {
            left = mid;
        } else {
            right = mid;
        }
    }
    return (left + right) / 2.0;
}



class BlackScholesCallFunctor {
    private:
        double T, K, S, r;
    public:
        double d1(double S, double r, double sigma, double K, double T) const {
            return (log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
        }

        double d2(double d1, double sigma, double T) const {
            return d1 - sigma * sqrt(T);
        }

        double norm_cdf(double value) const {
            return 0.5 * erfc(-value / sqrt(2));
        }

        BlackScholesCallFunctor(double T, double K, double S, double r): T(T), K(K), S(S), r(r) {}

        double operator()(double sigma) const {
            double d1var = d1(S, r, sigma, K, T);
            double d2var = d2(d1var, sigma, T);
            return S * norm_cdf(d1var) - K * exp(-r * T) * norm_cdf(d2var);
        }
};



int main() {
    double price = 13.6953;
    double T = 0.25;
    double K = 95;
    double S = 100;
    double r = 0.10;
    double epsilon = 0.00001;
    double left = 0.0001;
    double right = 100.0;
    BlackScholesCallFunctor bs_functor(T, K, S, r);
    double implied_volatility = interval_bisection(price, left, right, epsilon, bs_functor);

    std::cout << "The implied volatility is: " << implied_volatility << std::endl;
    return 0;
}

/* Output:

The implied volatility is: 0.500001

*/
