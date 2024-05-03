#include <iostream>
#include <vector>
#include <functional>
#include <cmath>

// Function to generate the pseudo-random sequence
std::vector<int> generateSequence(int x0, int a, int c, int m, int N) {
    std::vector<int> sequence(N);
    sequence[0] = x0;
    for (int i = 1; i < N; ++i) {
        sequence[i] = (a * sequence[i - 1] + c) % m;
    }
    return sequence;
}

// Function to calculate the mean of the sequence
double calculateMean(const std::vector<int>& seq) {
    double sum = 0;
    for (int num : seq) {
        sum += num;
    }
    return sum / seq.size();
}

// Function to calculate the variance of the sequence
double calculateVariance(const std::vector<int>& seq, double mean) {
    double sum = 0;
    for (int num : seq) {
        sum += (num - mean) * (num - mean);
    }
    return sum / seq.size();
}

// Function to count the occurrences of each number in the sequence
std::vector<int> countOccurrences(const std::vector<int>& seq, int m) {
    std::vector<int> counts(m, 0);
    for (int num : seq) {
        counts[num]++;
    }
    return counts;
}

// Function to approximate the integral of a function over the sequence
template<typename Func>
double approximateIntegral(const std::vector<int>& seq, int m, Func f) {
    double sum = 0;
    for (int num : seq) {
        sum += f((1.0 + num) / m);
    }
    return sum / seq.size();
}

int main() {
    int x0, a, c, m, N;
    std::cout << "Enter values for x0, a, c, m, N: ";
    std::cin >> x0 >> a >> c >> m >> N;

    auto sequence = generateSequence(x0, a, c, m, N);
    double mean = calculateMean(sequence);
    double variance = calculateVariance(sequence, mean);
    auto occurrences = countOccurrences(sequence, m);

    std::cout << "Mean (EN) = " << mean << std::endl;
    std::cout << "Variance (VN) = " << variance << std::endl;
    std::cout << "Occurrences (AN,k):" << std::endl;
    for (int k = 0; k < m; ++k) {
        std::cout << "Value " << k << " appears " << occurrences[k] << " times." << std::endl;
    }

    // Testing with specific functions
    std::cout << "Integral of f(x) = 1: " << approximateIntegral(sequence, m, [](double x) { return 1; }) << std::endl;
    std::cout << "Integral of f(x) = x: " << approximateIntegral(sequence, m, [](double x) { return x; }) << std::endl;
    std::cout << "Integral of f(x) = x^2: " << approximateIntegral(sequence, m, [](double x) { return x * x; }) << std::endl;

    return 0;
}