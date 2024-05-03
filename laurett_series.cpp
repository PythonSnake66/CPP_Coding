#include <cmath> 
#include <complex> 
#include <cstddef> 
#include <iostream > 
#include <vector > 

template 
<typename 
T> 
class 
laurent _polynomial 
{ 
private 
: 

int 
N; 
std:: vector<T> as; 

public 
: 
laurent _polynomial() : N{ 0 }, as{ 0 } {} 
laurent _polynomial ( int 
N, Tan) :N{ N}, as(2 ∗ 
N+1, an) {} 

int 
getN() const 
{ return 
N; } 

const 
T& operator 
[]( int 
n) const 
{ return 
as[n +N]; } 
T& operator 
[]( int 
n) { return 
as[n +N]; } 

T value (T at ) const 


{ 
T res{ 0 }; 
for 
( int 
n= −N; n<= N; ++n) 

res +=(∗ 
this 
)[n] ∗ 
pow(at , n); 
return 
res ; 
} 

laurent _polynomial <T>& operator+=(laurent_polynomial<T>& other) 

{ 
int 
new_N = std::max(N, other .N); 
std :: vector<T> new_as(2 ∗ 
new_N + 1, 0); 
for 
( int 
n= −new_N; n <= new_N; ++n) 
{ 

if 
(n >= −N&& n<= N) 
new_as[n + new_N] += as[n + N]; 
if 
(n >= −other .N && n <= other .N) 

new_as[n + new_N] += other .as[n + other .N]; 
} 
N = new_N ; 
as = new_as ; 
return 
∗ 
this 
; 


} 

}; 

template 
<typename 
T> 
inline 
laurent_polynomial <T> operator+(laurent _polynomial<T>& p, 
laurent_polynomial<T>& q) 

{ 
laurent _polynomial<T> res{ p }; 
p += q; 
return 
p; 

} 

int 
main() 
{ 

// 
laurent_polynomial<double> 
p{ 
2, 
1. 
}; 


laurent _polynomial<double> p{ 3, 2.0 }; 
laurent _polynomial<double> q{ 5, −1.5 }, s; 
double 
x{ 2.1 }, y{ −1.25 }; 
std:: cout << "p(y) = " << p.value(y) << std:: endl; 
s =p+q; 
for 
( int 
i= −s.getN(); i <= s.getN(); i++) 

std:: cout << "s[ " << i << "] = " << s[i] << std:: endl; 
std:: cout << "s(x) = " << s.value(x) << std:: endl; 

// 
std:: 
complex<double> 
f{ 
1, 
1 
}, 
g{ 
0, 
−1 
}; 
std :: complex<double> f{ 2, −2}, g{ 0, 5 }; 
laurent _polynomial<std :: complex<double>> u{ 2, f }; 
laurent _polynomial<std :: complex<double>> v{ 5, g}, t; 
std :: complex<double>z{ 1, 2 }, w{ 0, −1 }; 
std:: cout << "u(w) = " << u.value(w) << std:: endl; 
t =u+v; 
for 
( int 
i= −t.getN(); i <= t.getN(); i++) 

std:: cout << "t[ " << i << "] = " << t[i] << std:: endl; 
std:: cout << "t(z) = " << t.value(z) << std:: endl; 
} 