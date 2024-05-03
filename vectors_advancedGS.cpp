#include <iostream>
#include <vector>
#include <cmath>

// Function to calculate the dot product of two vectors
double dot(const std::vector<double>& a, const std::vector<double>& b) {
    double sum = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        sum += a[i] * b[i];
    }
    return sum;
}

// Function to calculate the norm of a vector
double norm(const std::vector<double>& v) {
    return std::sqrt(dot(v, v));
}

// Function to multiply a vector by a scalar
std::vector<double> scalarMultiply(const std::vector<double>& v, double scalar) {
    std::vector<double> result(v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        result[i] = v[i] * scalar;
    }
    return result;
}

// Function to subtract vector b from vector a
std::vector<double> subtract(const std::vector<double>& a, const std::vector<double>& b) {
    std::vector<double> result(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] - b[i];
    }
    return result;
}

// Classical Gram-Schmidt process
std::vector<std::vector<double>> classicalGramSchmidt(const std::vector<std::vector<double>>& vectors) {
    size_t n = vectors.size();
    std::vector<std::vector<double>> q(n);

    // Start the process
    q[0] = scalarMultiply(vectors[0], 1 / norm(vectors[0]));

    for (size_t i = 1; i < n; ++i) {
        std::vector<double> vi = vectors[i];
        for (size_t j = 0; j < i; ++j) {
            vi = subtract(vi, scalarMultiply(q[j], dot(vectors[i], q[j])));
        }
        q[i] = scalarMultiply(vi, 1 / norm(vi));
    }

    return q;
}

int main() {
    // Example usage with 3-dimensional vectors
    std::vector<std::vector<double>> vectors = {
        {1, 1, 0},
        {1, 0, 1},
        {0, 1, 1}
    };

    auto orthogonalVectors = classicalGramSchmidt(vectors);

    // Print the orthogonalized vectors
    for (const auto& vec : orthogonalVectors) {
        for (double v : vec) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}