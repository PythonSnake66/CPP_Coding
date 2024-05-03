#include <iostream>
#include <vector>

class Polynomial {
public:
    // Store coefficients, where index represents power of x
    std::vector<double> coefficients;

    // Constructor from a vector of coefficients
    Polynomial(const std::vector<double>& coeffs) : coefficients(coeffs) {}

    // Addition of two polynomials
    Polynomial operator+(const Polynomial& other) const {
        size_t max_size = std::max(coefficients.size(), other.coefficients.size());
        std::vector<double> result(max_size, 0);

        for (size_t i = 0; i < max_size; ++i) {
            double coeff1 = (i < coefficients.size()) ? coefficients[i] : 0;
            double coeff2 = (i < other.coefficients.size()) ? other.coefficients[i] : 0;
            result[i] = coeff1 + coeff2;
        }

        return Polynomial(result);
    }

    // Scalar multiplication
    Polynomial operator*(double scalar) const {
        std::vector<double> result(coefficients.size());

        for (size_t i = 0; i < coefficients.size(); ++i) {
            result[i] = coefficients[i] * scalar;
        }

        return Polynomial(result);
    }

    // Polynomial multiplication
    Polynomial operator*(const Polynomial& other) const {
        std::vector<double> result(coefficients.size() + other.coefficients.size() - 1, 0);

        for (size_t i = 0; i < coefficients.size(); ++i) {
            for (size_t j = 0; j < other.coefficients.size(); ++j) {
                result[i + j] += coefficients[i] * other.coefficients[j];
            }
        }

        return Polynomial(result);
    }

    // Evaluate polynomial at a certain value x
    double evaluate(double x) const {
        double result = 0;
        double x_power = 1; // Represents x^i

        for (double coeff : coefficients) {
            result += coeff * x_power;
            x_power *= x;
        }

        return result;
    }

    // Print the polynomial
    void print() const {
        for (size_t i = 0; i < coefficients.size(); ++i) {
            std::cout << coefficients[i] << "x^" << i;
            if (i != coefficients.size() - 1) std::cout << " + ";
        }
        std::cout << "\n";
    }
};

int main() {
    Polynomial p1({1, 2, 3});  // Represents 1 + 2x + 3x^2
    Polynomial p2({3, 4});     // Represents 3 + 4x

    Polynomial sum = p1 + p2;
    Polynomial product = p1 * p2;
    Polynomial scaled = p1 * 2.5;

    std::cout << "p1(x) = ";
    p1.print();
    std::cout << "p2(x) = ";
    p2.print();
    std::cout << "Sum: ";
    sum.print();
    std::cout << "Product: ";
    product.print();
    std::cout << "Scaled p1 by 2.5: ";
    scaled.print();

    std::cout << "Evaluation of p1 at x=2: " << p1.evaluate(2) << std::endl;

    return 0;
}