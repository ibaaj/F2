# Computation of polynomial on F2 of degree < 64



## Introduction


It is possible to represent a polynomial over F2 in C with an integer (int). Indeed, by writing a number N in base 2, we are able to represent any polynomial over F2 with for highest degree the size of the chosen variable type.
Example: the polynomial of AES: X^8 + X^4 + X^3 + X + 1 is represented by the integer 283 which has the binary value: b = 100011011. We read b from right to left: until the degree of the considered polynomial : 
1: 1*1, 1: 1*X^1, 0: 0*X^2, 1: 1*X^3, 1: 1*X^4, .... 1: 1*X^8 
The polynomial of the AES can be stored in a variable of type unsigned short int. The largest polynomial that can be stored in this type is represented by 65535 = 215 -1 which is X^14 +X^13 +X^12 +X^11 +X^10 +X^9 +X^8 + X^7 +X^6 +X^5 +X^4 +X^3 +X^2 +X^1 +X +1.
For our library we use the type f2 poly t = unsigned int64.

## Installation

```
make all
```

8 programmes seront générés :
- ./arithm_test : tests of the implemented arithmetic functions
- ./enumerate_irreductible N : display in the terminal (stdout) all irreducible polynomials of degree N on F2.
- ./enumerate_primitive N : displays in the terminal (stdout) all primitive polynomials of degree N on F2.
-  ./count_irreductible : Count the number of irreducible polynomials by enumeration from degree 1 to 63.
- ./count_primitive : Count the number of primitive polynomials by enumeration from degree 1 to 63.
- ./f2 poly test : Carry out tests of the implemented functions and give the number of irreducible polynomials of degree from 1 to 63 and the number of primitive polynomials from 1 to 63.
- ./f2 poly interface (P) : fast processing of a polynomial in argument (P) or via the interface
- ./f2 poly random (N): analyze random polynomials of degree N in argument or via the interface
