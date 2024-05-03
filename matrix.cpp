#include <iostream>
#include <vector>
#include <complex>

template<typename T>
class fullmatrix {
private:
    std::vector<std::vector<T>> data;
    int n; // size of the matrix

public:
    fullmatrix(int size) : n(size), data(size, std::vector<T>(size)) {}

    // Accessor for matrix dimension
    int size() const {
        return n;
    }

    // Access and modify elements
    T& at(int i, int j) {
        return data.at(i).at(j);
    }

    const T& at(int i, int j) const {
        return data.at(i).at(j);
    }

    // Scalar multiplication
    fullmatrix& operator*=(const T& scalar) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                data[i][j] *= scalar;
            }
        }
        return *this;
    }

    // Matrix addition
    fullmatrix& operator+=(const fullmatrix& other) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                data[i][j] += other.data[i][j];
            }
        }
        return *this;
    }

    // Matrix multiplication
    fullmatrix operator*(const fullmatrix& other) {
        fullmatrix result(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Trace of the matrix
    T trace() const {
        T tr = T(); // Initialize to zero
        for (int i = 0; i < n; i++) {
            tr += data[i][i];
        }
        return tr;
    }
};

// Overload the stream insertion operator
template<typename T>
std::ostream& operator<<(std::ostream& out, const fullmatrix<T>& matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            out << matrix.at(i, j) << " ";
        }
        out << "\n";
    }
    return out;
}

// Overload the stream extraction operator
template<typename T>
std::istream& operator>>(std::istream& in, fullmatrix<T>& matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            in >> matrix.at(i, j);
        }
    }
    return in;
}

int main() {
    fullmatrix<double> A(3), B(3);
    std::cout << "Enter matrix A:\n";
    std::cin >> A;
    std::cout << "Enter matrix B:\n";
    std::cin >> B;

    A *= 2.0; // Scalar multiplication
    std::cout << "A after scalar multiplication:\n" << A;

    A += B; // Matrix addition
    std::cout << "A after addition with B:\n" << A;

    fullmatrix<double> C = A * B; // Matrix multiplication
    std::cout << "A * B:\n" << C;

    double trA = A.trace(); // Trace of A
    std::cout << "Trace of A: " << trA << std::endl;

    return 0;
}