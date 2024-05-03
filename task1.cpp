#include <iostream>
#include <cmath>
#include <utility>

class Bond {
public:
    Bond(double par, double coupon, unsigned int maturity) :
        par(par), coupon(coupon), maturity(maturity) {}

    double get_price(double yield) const {
        double price(0.0);
        double denominator(1.0);
        for (unsigned int i = 0; i < maturity; ++i) {
            denominator *= 1.0 + yield;
            price += coupon / denominator;
        }
        price += par / denominator;
        return price;
    }

private:
    const double par;
    const double coupon;
    const unsigned int maturity;
};

template <typename F>
double secant_method(const F &f, double x0, double x1, double eps) {
    do {
        double f0 = f(x0);
        double f1 = f(x1);
        double x =  (x0 * f1 - x1 * f0) / (f1 - f0);
        x0 = x1;
        x1 = x;
    } while (fabs(x1 - x0) >= eps);
    return x1;
}

int main(){

Bond bond1{ 1000.0, 100.0, 10 };
std::cout << bond1.get_price(0.1138) << std::endl;
Bond bond2{ 100.0, 7.0, 5 };
std::cout << bond2.get_price(0.05819) << std::endl;
std::cout << bond2.get_price(0.08261) << std::endl;
Bond bond3{ 100.0, 5.0, 10 };
std::cout << bond3.get_price(0.04372) << std::endl;
std::cout << bond3.get_price(0.05669) << std::endl;

auto f1 = [&bond1 = std::as_const(bond1)](double x) { return bond1.get_price(x) - 1050.0; };
std::cout << secant_method(f1, .1, .9, 1e-7) << std::endl;
auto f2 = [&bond2 = std::as_const(bond2)](double x) { return bond2.get_price(x) - 90.0; };
std::cout << secant_method(f2, .1, .9, 1e-7) << std::endl;
auto f3 = [&bond2 = std::as_const(bond2)](double x) { return bond2.get_price(x) - 110.0; };
std::cout << secant_method(f3, .1, .9, 1e-7) << std::endl;
auto f4 = [&bond2 = std::as_const(bond2)](double x) { return bond2.get_price(x) - 99.0; };
std::cout << secant_method(f4, .1, .9, 1e-7) << std::endl;
auto f5 = [&bond2 = std::as_const(bond2)](double x) { return bond2.get_price(x) - 101.0; };
std::cout << secant_method(f5, .1, .9, 1e-7) << std::endl;
}
