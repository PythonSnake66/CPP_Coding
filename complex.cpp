#include <iostream>
#include <cmath>

template<typename T>
class complex {
private:
    T real;
    T imag;

public:
   
    complex() : real(0), imag(0) {}

    
    complex(T real, T imag) : real(real), imag(imag) {}

   
    T getReal() const { return real; }

   
    T getImag() const { return imag; }

    
    complex operator+(const complex& other) const {
        return complex(this->real + other.real, this->imag + other.imag);
    }

    
    complex operator-(const complex& other) const {
        return complex(this->real - other.real, this->imag - other.imag);
    }

    
    complex operator-() const {
        return complex(-this->real, -this->imag);
    }

    
    complex operator*(const complex& other) const {
        T new_real = this->real * other.real - this->imag * other.imag;
        T new_imag = this->real * other.imag + this->imag * other.real;
        return complex(new_real, new_imag);
    }

    
    complex operator*(const T& scalar) const {
        return complex(this->real * scalar, this->imag * scalar);
    }

    
    friend complex operator*(const T& scalar, const complex& c) {
        return complex(scalar * c.real, scalar * c.imag);
    }

    
    complex operator/(const complex& other) const {
        T divisor = other.real * other.real + other.imag * other.imag;
        T new_real = (this->real * other.real + this->imag * other.imag) / divisor;
        T new_imag = (this->imag * other.real - this->real * other.imag) / divisor;
        return complex(new_real, new_imag);
    }

    
    complex& operator+=(const complex& other) {
        this->real += other.real;
        this->imag += other.imag;
        return *this;
    }
};


template <typename T>
std::ostream& operator<<(std::ostream& os, const complex<T>& c) {
    return os << '(' << c.getReal() << ", " << c.getImag() << ')';
}



template<typename T>
complex<T> my_power(const complex<T>& z, int n) {
    complex<T> result(1, 0);
    for (int i = 0; i < n; i++) {
        result = result * z;
    return result;
}
}

int main() {
    double x = 4.1, y = -3.5;
    complex<double> z(x, y), v(0., 1.), w(-2., 3.), res;

    std::cout << z << std::endl;

    res = x * z + v * y;
    std::cout << res << std::endl;

    res = -res + z * w;
    std::cout << res << std::endl;

    z += v / w;
    std::cout << z << std::endl;

    std::cout << my_power(z, 3) << std::endl;
    std::cout << my_power(v, -2) << std::endl;

    return 0;
}