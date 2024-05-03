# include <algorithm>
# include <cmath>
# include <cstddef>
# include <iostream>
# include <vector>
using namespace std ;
class EuropeanOption
{
public :
virtual double Payoff ( double S ) const = 0;
};
class EuropeanCall : public EuropeanOption
{
private :
const double K ;
public :
EuropeanCall ( double K_ ) : K { K_ } {}
double Payoff ( double S ) const
{
return max ( S - K , 0.) ;
}
};
class EuropeanPut : public EuropeanOption
{
private :
const double K ;
public :
EuropeanPut ( double K_ ) : K { K_ } {}
double Payoff ( double S ) const
{
return max ( K - S , 0.) ;
}
};
class EuropeanDigitalCall : public EuropeanOption
{
private :
const double K ;
public :
EuropeanDigitalCall ( double K_ ) : K { K_ } {}
double Payoff ( double S ) const
{
return K < S ? 1. : 0.;
}
};
class EuropeanDigitalPut : public EuropeanOption
{
private :
const double K ;
public :
EuropeanDigitalPut ( double K_ ) : K { K_ } {}
double Payoff ( double S ) const
{
return K > S ? 1. : 0.;
}
};
class EuropeanDoubleDigital : public EuropeanOption
{
private :
const double K1 , K2 ;
public :
EuropeanDoubleDigital ( double K1_ , double K2_ ) : K1 { K1_ } , K2 { K2_ }
{
}
double Payoff ( double S ) const
{
return K1 < S && S < K2 ? 1. : 0.;
}
};
class CoxRossRubinsteinPricer {
private :
const double tau ;
const double S0 ;
const double r ;
const double sigma ;
const size_t N ;
const double delta_t ;
const double root_delta_t ;
const double u ;
const double d ;
const double pu ;
const double pd ;
const double disc ;
public :
CoxRossRubinsteinPricer ( double tau_ , double S0_ , double r_ , double sigma_ ,
size_t N_ )
: tau { tau_ } , S0 { S0_ } , r { r_ } , sigma { sigma_ } , N { N_ } ,
delta_t { tau / N } , root_delta_t { sqrt ( delta_t ) } ,
u { exp ( sigma * root_delta_t ) } , d { exp ( - sigma * root_delta_t ) } ,
pu { (( exp ( r * delta_t ) ) - d ) / ( u - d ) } , pd { 1. - pu } ,
disc { exp ( - r * delta_t ) }
{
}
double operator () ( const EuropeanOption & option )
{
vector <double > St ( N + 1) ;
vector <double > C ( N + 1) ;
St [0] = S0 * pow (d , N ) ;
for ( size_t j = 1; j < N + 1; ++ j )
St [ j ] = St [ j - 1] * u / d ;
for ( size_t j = 1; j < N + 1; ++ j )
C [ j ] = option . Payoff ( St [ j ]) ;
for ( size_t i = N ; i > 0; --i )
for ( size_t j = 0; j < i ; ++ j )
C [ j ] = disc * ( pu * C [ j + 1] + pd * C [ j ]) ;
return C [0];
}
};
int main ()
{
const double tau { 1. };
const double S0 { 100. };
const double r { .05 };
const double sigma { .2 };
size_t N { 10 };
cout << " N ␣ = ␣ " << N << endl ;
CoxRossRubinsteinPricer pricer10 { tau , S0 , r , sigma , N };
cout << " European ␣ call : ␣ " << pricer10 ( EuropeanCall {100.}) << endl ;
cout << " European ␣ put : ␣ " << pricer10 ( EuropeanPut {100.}) << endl ;
cout << " European ␣ digital ␣ call : ␣ " << pricer10 ( EuropeanDigitalCall {100.}) <<
endl ;
cout << " European ␣ digital ␣ put : ␣ " << pricer10 ( EuropeanDigitalPut {100.}) <<
endl ;
cout << " European ␣ double ␣ digital : ␣ " << pricer10 ( EuropeanDoubleDigital {100. ,
110.}) << endl ;
N = 100;
cout << " N ␣ = ␣ " << N << endl ;
CoxRossRubinsteinPricer pricer100 { tau , S0 , r , sigma , N };
cout << " European ␣ call : ␣ " << pricer100 ( EuropeanCall { 100. }) << endl ;
cout << " European ␣ put : ␣ " << pricer100 ( EuropeanPut { 100. }) << endl ;
cout << " European ␣ digital ␣ call : ␣ " << pricer100 ( EuropeanDigitalCall { 100. })
<< endl ;
cout << " European ␣ digital ␣ put : ␣ " << pricer100 ( EuropeanDigitalPut { 100. }) <<
endl ;
cout << " European ␣ double ␣ digital : ␣ " << pricer100 ( EuropeanDoubleDigital {
100. , 110. }) << endl ;
N = 1000;
cout << " N ␣ = ␣ " << N << endl ;
CoxRossRubinsteinPricer pricer1000 { tau , S0 , r , sigma , N };
cout << " European ␣ call : ␣ " << pricer1000 ( EuropeanCall { 100. }) << endl ;
cout << " European ␣ put : ␣ " << pricer1000 ( EuropeanPut { 100. }) << endl ;
cout << " European ␣ digital ␣ call : ␣ " << pricer1000 ( EuropeanDigitalCall { 100. })
<< endl ;
cout << " European ␣ digital ␣ put : ␣ " << pricer1000 ( EuropeanDigitalPut { 100. })
<< endl ;
cout << " European ␣ double ␣ digital : ␣ " << pricer1000 ( EuropeanDoubleDigital {
100. , 110. }) << endl ;
}