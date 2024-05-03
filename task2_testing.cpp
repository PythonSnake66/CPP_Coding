#include <cstdint>
#include <vector>
#include <iostream>
#include <memory>
#include <math.h>


class RandomNumberGenerator { 
public :
RandomNumberGenerator ( uint64_t	seed_ )	:	seed (	seed_	) {}

uint64_t get_seed () const { return seed ; } 
virtual void set_seed ( uint64_t seed_ ) { seed = seed_ ; }
virtual	uint64_t	get_random_integer () = 0;
virtual	void	get_uniform_draws ( std::vector <double>& draws ) = 0;
private : uint64_t	seed ;
};

class LinearCongruentialGenerator : public RandomNumberGenerator{

public: 
LinearCongruentialGenerator(uint64_t seed_): RandomNumberGenerator(seed_), m(static_cast<uint64_t>(pow(2,32))), a(1664525), c(1013904223), previousX(seed_){}


void set_seed(uint64_t seed_) override {
    RandomNumberGenerator::set_seed(seed_); 
    previousX = seed_;  
}


uint64_t get_random_integer (){
previousX=(a*previousX +c)%m;
return previousX;
}
void get_uniform_draws (std::vector <double>& draws ){
    for (int i=0; i< draws.size(); ++i){
        draws[i] = static_cast<double>(get_random_integer()) / m;
    }
}

private:
    uint64_t previousX;
    const uint64_t m;
    const uint64_t a;
    const uint64_t c;
};


int main(){
std::unique_ptr<RandomNumberGenerator> rng_ptr = std::make_unique<LinearCongruentialGenerator >(42L) ;
//	42L	i s	the	seed
std::cout << "1st: " << rng_ptr->get_random_integer() << std::endl;
std::cout << "2nd: " << rng_ptr->get_random_integer() << std::endl;
std::cout << "3rd: " << rng_ptr->get_random_integer() << std::endl;
rng_ptr->set_seed (42L);
std::cout << "1st: " << rng_ptr->get_random_integer() << std::endl;
std::cout << "2nd: " << rng_ptr->get_random_integer() << std::endl;
std::cout << "3rd: " << rng_ptr->get_random_integer() << std::endl;
std::vector <double> draws (9) ;
rng_ptr->get_uniform_draws ( draws ) ; 
 for( const	auto& draw	:	draws )	{ 
     std::cout << draw << std::endl ;
}
// }
}