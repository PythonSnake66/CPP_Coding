# define _USE_MATH_DEFINES
# include <cmath>
# include <iostream>
# include <memory>
using namespace std ;
class DefInt {
public :
typedef double (* PtrF ) ( double ) ;
private :
const double a ;
const double b ;
const PtrF ptrF ;
public :
DefInt ( double a_ , double b_ , PtrF ptrF_ ) : a { a_ } , b { b_ } , ptrF { ptrF_
} {}
double getA () const
{
return a ;
}
double getB () const
{
return b ;
}
PtrF getPtrF () const
{
return ptrF ;
}
};
class Integrator {
public :
virtual double operator () ( const DefInt & defInt ) const = 0;
};
class TrapezoidalIntegrator : public Integrator {
private :
size_t N ;
public :
TrapezoidalIntegrator ( size_t N_ ) : N { N_ } {}
virtual double operator () ( const DefInt & defInt ) const override {
double x = defInt . getA () ;
double h = ( defInt . getB () - x ) / N ;
DefInt :: PtrF ptrF = defInt . getPtrF () ;
double res = 0.;
for ( size_t n = 0; n <= N ; ++ n )
{
double factor = ( n == 0 || n == N ) ? 1. : 2.;
res += factor * (* ptrF ) ( x ) ;
x += h ;
}
return .5 * h * res ;
}
};
class SimpsonIntegrator : public Integrator {
private :
size_t N ;
public :
SimpsonIntegrator ( size_t N_ ) : N { N_ } {}
virtual double operator () ( const DefInt & defInt ) const override {
double x = defInt . getA () ;
double h = ( defInt . getB () - x ) / N ;
DefInt :: PtrF ptrF = defInt . getPtrF () ;
double res = 0.;
for ( size_t n = 0; n <= N ; ++ n )
{
double factor = ( n == 0 || n == N ) ? 1. : ( n % 2 ? 4. :
2.) ;
res += factor * (* ptrF ) ( x ) ;
x += h ;
}
return h * res / 3.;
}
};
int main ()
{
cout << " *** ␣ Function ␣ 1: ␣ square ␣ *** ␣ " << endl ;
DefInt defInt1 (0. , 1. , []( double x ) { return x * x ; }) ;
cout << " Trapezoidal ␣ approximation " << endl ;
unique_ptr < Integrator > integrator = make_unique < TrapezoidalIntegrator
>(1) ;
cout << " N =1: ␣ " << (* integrator ) ( defInt1 ) << endl ;
integrator = make_unique < TrapezoidalIntegrator >(10) ;
cout << " N =10: ␣ " << (* integrator ) ( defInt1 ) << endl ;
integrator = make_unique < TrapezoidalIntegrator >(100) ;
cout << " N =100: ␣ " << (* integrator ) ( defInt1 ) << endl ;
cout << " Simpson ␣ approximation " << endl ;
integrator = make_unique < SimpsonIntegrator >(1) ;
cout << " N =1: ␣ " << (* integrator ) ( defInt1 ) << endl ;
integrator = make_unique < SimpsonIntegrator >(10) ;
cout << " N =10: ␣ " << (* integrator ) ( defInt1 ) << endl ;
integrator = make_unique < SimpsonIntegrator >(100) ;
cout << " N =100: ␣ " << (* integrator ) ( defInt1 ) << endl ;
cout << " *** ␣ Function ␣ 2: ␣ cos ␣ *** ␣ " << endl ;
DefInt defInt2 (0. , .5 * M_PI , []( double x ) { return cos ( x ) ; }) ;
cout << " Trapezoidal ␣ approximation " << endl ;
integrator = make_unique < TrapezoidalIntegrator >(1) ;
cout << " N =1: ␣ " << (* integrator ) ( defInt2 ) << endl ;
integrator = make_unique < TrapezoidalIntegrator >(10) ;
cout << " N =10: ␣ " << (* integrator ) ( defInt2 ) << endl ;
integrator = make_unique < TrapezoidalIntegrator >(100) ;
cout << " N =100: ␣ " << (* integrator ) ( defInt2 ) << endl ;
cout << " Simpson ␣ approximation " << endl ;
integrator = make_unique < SimpsonIntegrator >(1) ;
cout << " N =1: ␣ " << (* integrator ) ( defInt2 ) << endl ;
integrator = make_unique < SimpsonIntegrator >(10) ;
cout << " N =10: ␣ " << (* integrator ) ( defInt2 ) << endl ;
integrator = make_unique < SimpsonIntegrator >(100) ;
cout << " N =100: ␣ " << (* integrator ) ( defInt2 ) << endl ;
}
