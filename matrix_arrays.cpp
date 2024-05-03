#include <iostream>
#include <complex>

template<typename T>
class fullmatrix {
private:
    T** data;
    int n; // size of the matrix

public:
    // Constructor
    fullmatrix(int size) : n(size) {
        data = new T*[n];
        for (int i = 0; i < n; ++i) {
            data[i] = new T[n];
            for (int j = 0; j < n; ++j) {
                data[i][j] = T(); // Initialize elements to zero
            }
        }
    }

    // Copy constructor (deep copy)
    fullmatrix(const fullmatrix& other) : n(other.n) {
        data = new T*[n];
        for (int i = 0; i < n; ++i) {
            data[i] = new T[n];
            for (int j = 0; j < n; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    // Destructor
    ~fullmatrix() {
        for (int i = 0; i < n; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    // Assignment operator (deep copy)
    fullmatrix& operator=(const fullmatrix& other) {
        if (this != &other) {
            for (int i = 0; i < n; ++i) {
                delete[] data[i];
            }
            delete[] data;

            n = other.n;
            data = new T*[n];
            for (int i = 0; i < n; ++i) {
                data[i] = new T[n];
                for (int j = 0; j < n; ++j) {
                    data[i][j] = other.data[i][j];
                }
            }
        }
        return *this;
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
                result.data[i][j] = T(); // Reset to zero
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

    // Stream insertion operator
    friend std::ostream& operator<<(std::ostream& out, const fullmatrix& matrix) {
        for (int i = 0; i < matrix.n; i++) {
            for (int j = 0; j < matrix.n; j++) {
                out << matrix.data[i][j] << " ";
            }
            out << "\n";
        }
        return out;
    }

    // Stream extraction operator
    friend std::istream& operator>>(std::istream& in, fullmatrix& matrix) {
        for (int i = 0; i < matrix.n; i++) {
            for (int j = 0; j < matrix.n; j++) {
                in >> matrix.data[i][j];
            }
        }
        return in;
    }
};

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
