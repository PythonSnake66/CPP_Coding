#include <cstddef> 
#include <iostream> 
int 
naive_sum ( int 
p , int 
q , std::size_t N) 
{ 
int 
sum = 0; 
for 
( auto 
i = 1 ; i < N; ++i ) 
{ 
i 
f 
( i % p == 0 | | i % q == 0) 
sum += i ; 
} 
return 
sum ; 
} 
int 
smart_sum ( int 
p , int 
q , std::size_ t N) 
{ 
int 
sum = 0 , p1 = p , q1 = q ; 
while 
( p1 < N || q1 < N) 
{ 
i 
f 
( p1 < q1 ) 
{ 
sum += p1 ; 
p1 += p ; 
} 
else 
i 
f 
( q1 < p1 ) 
{ 
sum += q1 ; 
q1 += q ; 
} 
else 
{ 
sum += p1 ; 
p1 += p ; 
q1 += q ; 
} 
} 
return 
sum ; 
} 
int 
main ( ) 
{ 

std:: cout << naive_sum(3, 5, 16) << std:: endl; 

std:: cout << smart_sum(3, 5, 16) << std:: endl; 

std:: cout << naive_sum(4, 7, 1000) << std:: endl; 

std:: cout << smart_sum(4, 7, 1000) << std:: endl; 

std:: cout << naive_sum(11, 13, 10000) << std:: endl; 

std:: cout << smart_sum(11, 13, 10000) << std:: endl; 
} 
