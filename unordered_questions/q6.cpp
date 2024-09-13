// 6. Consider the following interface (the finished code is already included):
/* Provide an implementation. Do not use malloc and free; instead use operator new[] and
operator delete[]. Come up with appropriate unit tests and use them to verify your implementation.
*/

#include <iostream>
class Vector {
    private:
    int nn; // size of array; upper index is nn - 1
    double* v;
    public:

    Vector() : nn(0), v(nullptr) {} // empty

    explicit Vector(int n) : nn(n), v(new double[n]) { // zero -based array
        for (int i = 0; i < nn; i++){
            v[i] = 0.0;
        }
    }

    Vector(int n, double a) : nn(n), v(new double[n]) { // initialize to constant value
        for (int i = 0; i < nn; i++){
            v[i] = a;
        }
    }

    Vector(int n, const double* a) : nn(n), v(new double[n]) { // initialize to array
        for (int i = 0; i < nn; i++){
            v[i] = a[i];
        }
    }

    Vector(const Vector& rhs) : nn(rhs.nn), v(new double[rhs.nn]) { // copy constructor
        for (int i = 0; i < nn; i++){
            v[i] = rhs.v[i];
        }
    }

    Vector& operator=(const Vector& rhs) { // assignment
        if (this != &rhs) {
            delete[] v;
            nn = rhs.nn;
            v = new double[nn];
            for (int i = 0; i < nn; i++){
                v[i] = rhs.v[i];
            }
        }
        return *this;
    }

    // Destructor
    ~Vector() {
        delete[] v;
    }

    inline double& operator[](const int i) const{ // i’th element
        return v[i];
    }

    inline const double& operator[](const int i) {
        return v[i];
    }

    inline int size() const {
        return nn;
    }

    void resize(int newn) { // resize (contents not preserved )
        delete[] v;
        nn = newn;
        v = new double[nn];
        for (int i = 0; i < nn; i++){
            v[i] = 0.0;
        }
    }

    void assign(int newn , double a){ // resize and assign a constant value
        delete[] v;
        nn = newn;
        v = new double[nn];
        for (int i = 0; i < nn; i++){
            v[i] = a;
        }
    }
};



//----------------------------------------------------------------------------------------------------------
// Unit tests to verify the implementation
void unit_tests() {
    // Test default constructor
    Vector v1;
    if (v1.size() != 0) {
        std::cout << "Test 1 failed" << std::endl;
        return;
    }

    // Test constructor with size
    Vector v2(10);
    if (v2.size() != 10) {
        std::cout << "Test 2 failed" << std::endl;
        return;
    }
    for (int i = 0; i < v2.size(); i++) {
        if (v2[i] != 0.0) {
            std::cout << "Test 3 failed" << std::endl;
            return;
        }
    }

    // Test constructor with size and value
    Vector v3(10, 2.0);
    for (int i = 0; i < v3.size(); i++) {
        if (v3[i] != 2.0) {
            std::cout << "Test 4 failed" << std::endl;
            return;
        }
    }

    // Test copy constructor
    Vector v4(v3);
    for (int i = 0; i < v4.size(); i++) {
        if (v4[i] != v3[i]) {
            std::cout << "Test 5 failed" << std::endl;
            return;
        }
    }

    // Test assignment
    Vector v5 = v2;
    for (int i = 0; i < v5.size(); i++) {
        if (v5[i] != v2[i]) {
            std::cout << "Test 6 failed" << std::endl;
            return;
        }
    }

    // Test assign
    v5.assign(7, 1.0);
    if (v5.size() != 7) {
        std::cout << "Test 7 failed" << std::endl;
        return;
    }
    for (int i = 0; i < v5.size(); i++) {
        if (v5[i] != 1.0) {
            std::cout << "Test 8 failed" << std::endl;
            return;
        }
    }

    // Test resize
    v5.resize(10);
    if (v5.size() != 10) {
        std::cout << "Test 9 failed" << std::endl;
        return;
    }
    for (int i = 5; i < v5.size(); i++) {
        if (v5[i] != 0.0) {
            std::cout << "Test 10 failed" << std::endl;
            return;
        }
    }

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    unit_tests();
    return 0;
}


