
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include <memory>

class ProcessGenerator {
public:
    virtual double operator()(double x) = 0;
};

class RandomWalkGenerator : public ProcessGenerator {
public:
    RandomWalkGenerator(double F, double Q, unsigned int seed) :
        F{F}, generator{seed}, normal{0.0, sqrt(Q)} {}

    double operator()(double x) {
        return F * x + normal(generator);
    }

private:
    const double F;
    std::mt19937 generator;
    std::normal_distribution<double> normal;
};

class StochasticFilter {
public:
    virtual void predict() = 0;
    virtual void update(double obs) = 0;
    virtual double get_state() = 0;
};



class KalmanFilter : public StochasticFilter {
public:
    KalmanFilter(double x, double P, double F, double Q, double H, double R) :
        x{x}, P{P}, F{F}, Q{Q}, H{H}, R{R},
        F_squared{F * F}, H_squared{H * H} {}




void predict() {
    x = F * x;
    P = F_squared * P + Q;
}

void update(double obs) {
    double innov = obs - H * x;
    double S = H_squared * P + R;
    double K = P * H / S;
    x = x + K * innov;
    P = (1. - K * H) * P;
}

double get_state() {
    return x;
}

private:
    const double F;
    const double Q;
    const double H;
    const double R;

    const double F_squared;
    const double H_squared;

    double x;
    double P;
};


int main() {
    unsigned int seed = 42;
    double true_F{ 1.01 };
    double true_Q{ 25. };
    double initial_x{ 100. };

    std::unique_ptr<ProcessGenerator> pg_ptr =
        std::make_unique<RandomWalkGenerator>(true_F, true_Q, seed);



size_t process_size{ 10 };
std::vector<double> true_process;
true_process.reserve(process_size);
true_process.push_back(initial_x);

for (size_t i = 1; i < process_size; ++i){
    true_process.push_back((*pg_ptr)(true_process.back()));
}

for (size_t i = 0; i < process_size; ++i) {
    std::cout << i << ": " << true_process[i] << std::endl;
}

double true_R{ 100. };

std::mt19937 generator(seed);
std::normal_distribution<double> normal(0.0, sqrt(true_R));
std::vector<double> noisy_process;
noisy_process.reserve(process_size);
for (size_t i = 0; i < process_size; ++i) {
    noisy_process.push_back(true_process[i] + normal(generator));
}

std::cout << "NoisyProcess_values:" << std::endl;
for (size_t i = 0; i < process_size; ++i) {
    std::cout << i << ": " << noisy_process[i] << std::endl;
}

std::unique_ptr<StochasticFilter> sf = std::make_unique<KalmanFilter>(
    initial_x, 100.0, true_F, true_Q, 1.0, true_R);

std::vector<double> filtered_process;
filtered_process.reserve(process_size);
filtered_process.push_back(initial_x);
for (size_t i = 1; i < process_size; ++i) {
    sf->predict();
    sf->update(noisy_process[i]);
    filtered_process.push_back(sf->get_state());
}

std::cout << "Filtered_process_values:" << std::endl;
for (size_t i = 0; i < process_size; ++i) {
    std::cout << i << ": " << filtered_process[i] << std::endl;
}
};
