#include <cassert>
#include <complex>
#include <iostream>

template<typename T>
class QObj {
public:
    QObj(std::initializer_list<std::initializer_list<std::complex<T>>> data) :
        rc{data.size()}, cc{0} {
        for (auto& x : data) {
            if (x.size() > cc) {
                cc = x.size();
            }
        }
        impl = new std::complex<T>*[rc];
        auto it = data.begin();
        for (size_t i = 0; i < rc; ++i, ++it) {
            impl[i] = new std::complex<T>[cc];
            std::copy(it->begin(), it->end(), impl[i]);
        }
    }

    QObj() : QObj({{{0, 0}}}) {}

    QObj(const QObj<T>& another) : rc{another.rc}, cc{another.cc} {
        impl = new std::complex<T>*[rc];
        for (size_t i = 0; i < rc; ++i) {
            impl[i] = new std::complex<T>[cc];
            for (size_t j = 0; j < cc; ++j) {
                impl[i][j] = another.impl[i][j];
            }
        }
    }

    ~QObj() {
        for (size_t i = 0; i < rc; ++i) {
            delete[] impl[i];
        }
        delete[] impl;
    }

    QObj<T>& operator=(const QObj<T>& another) {
        if (this != &another) {
            for (size_t i = 0; i < rc; ++i) {
                delete[] impl[i];
            }
            delete[] impl;

            rc = another.rc;
            cc = another.cc;

            impl = new std::complex<T>*[rc];
            for (size_t i = 0; i < rc; ++i) {
                impl[i] = new std::complex<T>[cc];
                for (size_t j = 0; j < cc; ++j) {
                    impl[i][j] = another.impl[i][j];
                }
            }
        }
        return *this;
    }

    QObj<T>& operator+() {
        return *this;
    }

    QObj<T>& operator-() {
        for (size_t i = 0; i < rc; ++i) {
            for (size_t j = 0; j < cc; ++j) {
                impl[i][j] = -impl[i][j];
            }
        }
        return *this;
    }

    QObj<T>& operator+=(const QObj<T>& rhs) {
        assert(rc == rhs.rc && cc == rhs.cc);
        for (size_t i = 0; i < rc; ++i) {
            for (size_t j = 0; j < cc; ++j) {
                impl[i][j] += rhs.impl[i][j];
            }
        }
        return *this;
    }

    QObj<T>& operator-=(const QObj<T>& rhs) {
        assert(rc == rhs.rc && cc == rhs.cc);
        for (size_t i = 0; i < rc; ++i) {
            for (size_t j = 0; j < cc; ++j) {
                impl[i][j] -= rhs.impl[i][j];
            }
        }
        return *this;
    }

    QObj<T>& operator*=(const std::complex<T>& scalar) {
        for (size_t i = 0; i < rc; ++i) {
            for (size_t j = 0; j < cc; ++j) {
                impl[i][j] *= scalar;
            }
        }
        return *this;
    }

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const QObj<U>& qo);

private:
    size_t rc;
    size_t cc;
    std::complex<T>** impl;
};

template<typename T>
QObj<T> operator+(const QObj<T>& lhs, const QObj<T>& rhs) {
    QObj<T> temp{lhs};
    temp += rhs;
    return temp;
}

template<typename T>
QObj<T> operator-(const QObj<T>& lhs, const QObj<T>& rhs) {
    QObj<T> temp{lhs};
    temp -= rhs;
    return temp;
}

template<typename T>
QObj<T> operator*(const std::complex<T>& scalar, const QObj<T>& qo) {
    QObj<T> temp{qo};
    temp *= scalar;
    return temp;
}

template<typename T>
QObj<T> operator*(const QObj<T>& qo, const std::complex<T>& scalar) {
    QObj<T> temp{qo};
    temp *= scalar;
    return temp;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const QObj<T>& qo) {
    os << "[";
    for (size_t i = 0; i < qo.rc; ++i) {
        if (i > 0) {
            os << ", ";
        }
        os << "[";
        for (size_t j = 0; j < qo.cc; ++j) {
            if (j > 0) {
                os << ", ";
            }
            os << qo.impl[i][j];
        }
        os << "]";
    }
    os << "]";
    return os;
}

int main() {
    QObj<double> q;
    q = QObj<double>({{{1, 0.}}, {0, 0.}});
    // The sigma-y Pauli operator
    QObj<double> sy({{{0., 0.}, {0., -1.}}, {{0., 1.}, {0., 0.}}});

    // The sigma-z Pauli operator
    QObj<double> sz({{{1., 0.}, {0., 0.}}, {{0., 0.}, {-1., 0.}}});

    QObj<double> H = std::complex<double>{1.} * sz + std::complex<double>{0.1} * sy;
    std::cout << "Qubit Hamiltonian: " << H << std::endl;
}
