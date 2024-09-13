#include <iostream>
#include <random>
#include <memory>


class ProcessGenerator { 
public :
virtual	double	operator () ( double x ) = 0;
};
class  RandomWalkGenerator : public ProcessGenerator{
private:
const double F;
const double Q;
const int seed;
std::mt19937 mt;
std::normal_distribution<double> normal;
public:
double operator() (double x){
    return F * x + normal(mt);
    }
RandomWalkGenerator(double F, double Q, unsigned int seed) : F(F), Q(Q), seed(seed), mt(seed), normal(0.0, sqrt(Q)){}

};


class StochasticFilter{ 
public :
virtual	void	predict () = 0; 
virtual	void	update ( double	obs ) = 0;
virtual	double	get_state () = 0;
};

class KalmanFilter : public StochasticFilter{
private:
double x00;
double P00;
const double F;
const double Q;
const double H;
const double R;
std::normal_distribution<double> normal2;


public:
KalmanFilter(double x00, double P00, double F, double Q, double H, double R) : x00(x00), P00(P00), F(F), Q(Q), H(H), R(R), normal2(0.0, sqrt(R)){}
void predict(){
    x00 = F * x00;
    P00 = F*F*P00 + Q;
}
void update(double	obs){
double y = obs - x00;
double S = P00 + R;
double K = P00/S;
x00 = x00 + K * y;
P00= (1 - K)*P00;
}
virtual double get_state (){
    return x00;
}

};


int main() {
    unsigned int seed = 42;
    double true_F{ 1.01 };
    double true_Q{ 25. };
    double initial_x{ 100. };

    std::unique_ptr<ProcessGenerator> pg_ptr = std::make_unique<RandomWalkGenerator>(true_F, true_Q, seed);



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
