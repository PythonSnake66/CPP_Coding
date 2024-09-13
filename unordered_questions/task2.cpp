#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

class RandomNumberGenerator {
public:
    RandomNumberGenerator(uint64_t seed_) : seed(seed_) {}

    uint64_t get_seed() const { return seed; }
    void set_seed(uint64_t seed_) { seed = seed_; }
    virtual uint64_t get_random_integer() = 0;
    virtual void get_uniform_draws(std::vector<double>& draws) = 0;

private:
    uint64_t seed;
};

class LinearCongruentialGenerator : public RandomNumberGenerator {
public:
    LinearCongruentialGenerator(
        uint64_t seed_,
        uint64_t modulus = static_cast<uint64_t>(pow(2, 32)),
        uint64_t multiplier = 1664525,
        uint64_t increment = 1013904223) :
        RandomNumberGenerator(seed_),
        modulus(modulus), multiplier(multiplier), increment(increment),
        max_multiplier(1. / (1. + (modulus - 1))) {}

    virtual uint64_t get_random_integer() {
        set_seed((multiplier * get_seed() + increment) % modulus);
        return get_seed();
    }


void get_uniform_draws(std::vector<double>& draws) {
    std::generate(draws.begin(), draws.end(), [&]() {
        return static_cast<double>(get_random_integer()) * max_multiplier;
    });
}

private:
    const uint64_t modulus;
    const uint64_t multiplier;
    const uint64_t increment;
    const double max_multiplier;

};

int main() {
    std::unique_ptr<RandomNumberGenerator> rng_ptr = std::make_unique<LinearCongruentialGenerator>(42L); // 42L is the seed

    std::cout << "1st:" << rng_ptr->get_random_integer() << std::endl;
    std::cout << "2nd:" << rng_ptr->get_random_integer() << std::endl;
    std::cout << "3rd:" << rng_ptr->get_random_integer() << std::endl;

    rng_ptr->set_seed(42L);

    std::cout << "4th:" << rng_ptr->get_random_integer() << std::endl;
    std::cout << "5th:" << rng_ptr->get_random_integer() << std::endl;
    std::cout << "6th:" << rng_ptr->get_random_integer() << std::endl;

    std::vector<double> draws(9);
    rng_ptr->get_uniform_draws(draws);
    for (const auto& draw : draws) {
        std::cout << draw << std::endl;
    }
};
