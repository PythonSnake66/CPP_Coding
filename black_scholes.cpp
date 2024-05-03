# define _USE_MATH_DEFINES
# include <cmath>
# include <iostream>
# include <memory>
# include <optional>
using namespace std ;
constexpr double gamma { 0.2316419 };
constexpr double a1 { 0.319381530 };
constexpr double a2 { -0.356563782 };
constexpr double a3 { 1.781477937 };
constexpr double a4 { -1.821255978 };
constexpr double a5 { 1.330274429 };
double phi ( double x )
{
return exp ( -.5 * x * x ) / sqrt (2. * M_PI ) ;
}
double N ( double x )
{
const double k = 1.0 / (1.0 + gamma * x ) ;
if ( x >= 0.)
{
return 1. - (((( a5 * k + a4 ) * k + a3 ) * k + a2 ) * k + a1 ) * k *
exp ( - x * x / 2.) / sqrt (2. * M_PI ) ;
}
else return 1. - N ( - x ) ;
}
class BlackScholesPricer
{
private :
const double tau ;
const double sqrtTau ;
const double K ;
const double S0 ;
const double sigma ;
const double r ;
const double q ;
optional <double > cachedD1 ;
optional <double > cachedD2 ;
optional <double > cachedForward ;
optional <double > cachedEuropeanCallPrice ;
optional <double > cachedEuropeanPutPrice ;
optional <double > cachedVega ;
public :
BlackScholesPricer ( double tau_ , double K_ , double S0_ , double sigma_ ,
double r_ , double q_ )
: tau { tau_ } , sqrtTau { sqrt ( tau_ ) } , K { K_ } , S0 { S0_ } , sigma {
sigma_ } , r { r_ } , q { q_ } ,
cachedD1 { nullopt } , cachedD2 { nullopt } ,
cachedForward { nullopt } ,
cachedEuropeanCallPrice { nullopt } , cachedEuropeanPutPrice {
nullopt } ,
cachedVega { nullopt }
{
}
double d1 ()
{
if (! cachedD1 . has_value () )
cachedD1 = ( log ( S0 / K ) + ( r - q + .5 * sigma * sigma ) *
tau ) / ( sigma * sqrtTau ) ;
return cachedD1 . value () ;
}
double d2 ()
{
if (! cachedD2 . has_value () )
cachedD2 = d1 () - sigma * sqrtTau ;
return cachedD2 . value () ;
}
double forward ()
{
if (! cachedForward . has_value () )
cachedForward = S0 * exp (( r - q ) * tau ) ;
return cachedForward . value () ;
}
double europeanCallPrice ()
{
if (! cachedEuropeanCallPrice . has_value () )
cachedEuropeanCallPrice = exp ( - r * tau ) * ( forward () * N
( d1 () ) - K * N ( d2 () ) ) ;
return cachedEuropeanCallPrice . value () ;
}
double europeanPutPrice ()
{
if (! cachedEuropeanPutPrice . has_value () )
cachedEuropeanPutPrice = exp ( - r * tau ) * ( K * N ( - d2 () ) -
forward () * N ( - d1 () ) ) ;
return cachedEuropeanPutPrice . value () ;
}
double vega ()
{
if (! cachedVega . has_value () )
cachedVega = exp ( - q * tau ) * S0 * phi ( d1 () ) * sqrtTau ;
return cachedVega . value () ;
}
};
template < typename Function >
double NewtonRaphson ( const Function & f , double guess , double epsilon )
{
double xPrev = guess ;
double xNext = xPrev - f . Value ( xPrev ) / f . Deriv ( xPrev ) ;
while ( xNext - xPrev >= epsilon || xPrev - xNext >= epsilon )
{
xPrev = xNext ;
xNext = xPrev - f . Value ( xPrev ) / f . Deriv ( xPrev ) ;
}
return xNext ;
}
class ImpliedVolatilityWrapper
{
private :
const double tau ;
const double K ;
const double S0 ;
const double r ;
const double q ;
const double price ;
const bool put ;
mutable optional <double > cachedSigma ;
mutable optional < unique_ptr < BlackScholesPricer > > cachedPricer ;
public :
ImpliedVolatilityWrapper ( double tau_ , double K_ , double S0_ , double r_ ,
double q_ , double price_ , bool put_ )
: tau { tau_ } , K { K_ } , S0 { S0_ } , r { r_ } , q { q_ } , price { price_ } , put {
put_ } ,
cachedSigma { nullopt } , cachedPricer { nullopt }
{
}
double Value ( double sigma ) const
{
if (! cachedSigma . has_value () || cachedSigma . value () != sigma )
{
cachedSigma = sigma ;
cachedPricer = make_unique < BlackScholesPricer >( tau , K ,
S0 , sigma , r , q ) ;
}
return ( put ? cachedPricer . value () -> europeanPutPrice () :
cachedPricer . value () -> europeanCallPrice () ) - price ;
}
double Deriv ( double sigma ) const
{
if (! cachedSigma . has_value () || cachedSigma . value () != sigma )
{
cachedSigma = sigma ;
cachedPricer = make_unique < BlackScholesPricer >( tau , K ,
S0 , sigma , r , q ) ;
}
return cachedPricer . value () -> vega () ;
}
};
int main ()
{
double tau = 1.;
double K = 100.;
double S0 = 100.;
double sigma = .15;
double r = .01;
double q = .02;
unique_ptr < BlackScholesPricer > pricer = make_unique < BlackScholesPricer >(
tau , K , S0 , sigma , r , q ) ;
cout << pricer-> europeanCallPrice () << endl ;
cout << pricer-> europeanPutPrice () << endl ;
cout << pricer-> vega () << endl ;
r = .02;
q = .03;
pricer = make_unique < BlackScholesPricer >( tau , K , S0 , sigma , r , q ) ;
cout << pricer-> europeanCallPrice () << endl ;
cout << pricer-> europeanPutPrice () << endl ;
cout << pricer-> vega () << endl ;
r = .03;
q = .04;
pricer = make_unique < BlackScholesPricer >( tau , K , S0 , sigma , r , q ) ;
cout << pricer-> europeanCallPrice () << endl ;
cout << pricer-> europeanPutPrice () << endl ;
cout << pricer-> vega () << endl ;
r = .01;
q = .02;
double price = 7.36;
double put = false ;
cout << NewtonRaphson ( ImpliedVolatilityWrapper ( tau , K , S0 , r , q , price ,
put ) , .1 , .001) << endl ;
price = 10.30;
put = true ;
cout << NewtonRaphson ( ImpliedVolatilityWrapper ( tau , K , S0 , r , q , price ,
put ) , .1 , .001) << endl ;
price = 11.26;
put = false ;
cout << NewtonRaphson ( ImpliedVolatilityWrapper ( tau , K , S0 , r , q , price ,
put ) , .1 , .001) << endl ;
price = 14.18;
put = true ;
cout << NewtonRaphson ( ImpliedVolatilityWrapper ( tau , K , S0 , r , q , price ,
put ) , .1 , .001) << endl ;
price = 1.51;
put = false ;
cout << NewtonRaphson ( ImpliedVolatilityWrapper ( tau , K , S0 , r , q , price ,
put ) , .1 , .001) << endl ;
price = 4.44;
put = true ;
cout << NewtonRaphson ( ImpliedVolatilityWrapper ( tau , K , S0 , r , q , price ,
put ) , .1 , .001) << endl ;
price = 5.41;
put = false ;
cout << NewtonRaphson ( ImpliedVolatilityWrapper ( tau , K , S0 , r , q , price ,
put ) , .1 , .001) << endl ;
price = 8.35;
put = true ;
cout << NewtonRaphson ( ImpliedVolatilityWrapper ( tau , K , S0 , r , q , price ,
put ) , .1 , .001) << endl ;
}