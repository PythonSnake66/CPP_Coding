#include <iostream > 
#include <numeric> 

int 
gcd( int 
a, int 
b) 

{ 
for 
(;;) 
{ 

if 
(a == 0) return 
b; 
b %= a; 
if 
(b == 0) return 
a; 
a %= b; 

} 
} 

int 
lcm( int 
a, int 
b) 

{ 
int 
temp = gcd(a, b); 
return 
temp ? (a / temp ∗ 
b) : 0; 

} 

class 
fraction 
{ 
private 
: 

int 
num ; 
int 
den ; 

public 
: 
fraction () : num{ 0 }, den{ 0 } {} 
fraction( int 
num, int 
den) : num{ num }, den{ den } {} 
fraction( const 
fraction& other) : num{ other .num }, den{ other .den } {} 

fraction& operator=(const 
fraction& other) 

{ 
num = other .num; 
den = other .den; 
return 
∗ 
this 
; 

} 

int 
numerator () const 
{ return 
num; } 
int 
denominator () const 
{ return 
den; } 

void 
simplify () 
{ 
if 
(den <0) {den = −den; num = −num; } 


int 
s i g n = 1 ; 
i 
f 
(num < 0) { num = −num ; s i g n = −1; } 
int 
d = gcd (num , den ) ; 
num /= d ; 
den /= d ; 
num = s i g n ; 
} 
f r a c t i o n& operator 
−() 
{ 
num = −num ; 
return 
∗ 
this 
; 
} 
f r a c t i o n& operator+=(const 
f r a c t i o n& o t her ) 
{ 
int 
new_den = lcm ( den , o th e r . den ) ; 
num = num ∗ 
( new_den / den ) + o t h e r . num ∗ 
( new_den / o t her . den ) ; 
den = new_den ; 
s i m p l i f y ( ) ; 
return 
∗ 
this 
; 
} 
f r a c t i o n& operator−=(const 
f r a c t i o n& o t her ) 
{ 
int 
new_den = lcm ( den , o th e r . den ) ; 
num = num ∗ 
( new_den / den ) − ot he r . num ∗ 
( new_den / o t her . den ) ; 
den = new_den ; 
s i m p l i f y ( ) ; 
return 
∗ 
this 
; 
} 
f r a c t i o n& operator=( int 
ot h e r ) 
{ 
num = o th e r ; 
s i m p l i f y ( ) ; 
return 
∗ 
this 
; 
} 
f r a c t i o n& operator=(const 
f r a c t i o n& o t her ) 
{ 
num = o th e r . num ; 
den = o th e r . den ; 
s i m p l i f y ( ) ; 
return 
∗ 
this 
; 
} 


fraction& operator/=( int 
other ) 

{ 
den = other ; 
simplify () ; 
return 
∗ 
this 
; 

} 

fraction& operator/=(const 
fraction& other) 

{ 
num = other . den ; 
den = other .num; 
simplify () ; 
return 
∗ 
this 
; 

} 
}; 

inline 
fraction operator+(const 
fraction& a, const 
fraction& b) 

{ 
fraction res{ a }; 
res += b; 
return 
res ; 

} 

inline 
fraction operator 
−(const 
fraction& a, const 
fraction& b) 

{ 
fraction res{ a }; 
res −= b; 
return 
res ; 

} 

inline 
fraction operator 
( const 
fraction& a, int 
b) 

{ 
fraction res{ a }; 
res = b; 
return 
res ; 

} 

inline 
fraction operator 
( int 
a, const 
fraction& b) 
{ 
return 
b ∗ 
a; 
} 

inline 
fraction operator 
( const 
fraction& a, const 
fraction& b) 
{ 
fraction res{ a }; 


res = b; 
return 
res ; 
} 

inline 
fraction operator 
/( const 
fraction& a, int 
b) 

{ 
fraction res{ a }; 
res /= b; 
return 
res ; 

} 

inline 
fraction operator 
/( int 
a, const 
fraction& b) 

{ 
fraction res{ a, 1 }; 
res /= b; 
return 
res ; 

} 

inline 
fraction operator 
/( const 
fraction& a, const 
fraction& b) 

{ 
fraction res{ a }; 
res /= b; 
return 
res ; 

} 

std :: ostream& operator<<(std :: ostream& os , const 
fraction& f) 
{ 
return 
os << f . numerator () << "/" << f . denominator () ; 
} 

int 
main() 
{ 
int 
a=4, b=3; 

// 
fraction 
f{ 
1, 
123 
}, 
g{ 
1, 
321 
}, 
h{ 
1, 
3 
}, 
res 
; 


fraction f{ 1, 45 }, g{ 1, 54 }, h{ 1, 5 }, res ; 
std :: cout << f − h << std :: endl ; 
res =a ∗ 
f − g ∗ 
b; 
res = −res +f ∗ 
h; 
std :: cout << res << std :: endl ; 
f+=g / h; 
std:: cout << f << std:: endl; 

} 