#include <iostream>
#include<cmath>
#include <utility>
//using namespace std;

class Bond{
private:
    const double par;
    const double coupon;
    const int maturity;
public:
    Bond(double par, double coupon, int maturity): par(par), coupon(coupon), maturity(maturity){}

    double get_price(double ytm) const{
        double currCoupon = coupon;
        double currSum = 0;
        for(int i=1; i <= maturity; ++i){
            currCoupon /= 1 + ytm;
            currSum += currCoupon;
        }
        double price = currSum + par * pow(1/(1 + ytm), maturity);
        return price;
    }


};

template <typename T>
double secant_method(const T &f, double x0, double x1, const double eps){
    double x2(0.0);
while (fabs(x0 - x1)>=eps){
    x2 = x1 - f(x1)*(x1 - x0)/ (f(x1) - f(x0));
    x0 = x1;
    x1 = x2;
}
return x2;
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
