#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

// Class that contains an array pointer
// The point of this class is to represent
// a polynomial using the array, where the
// index is the exponent of 'x' and the number
// in the index is the coefficient of that index

class Poly
{
public:

	//Constructors / Destructors
	Poly();
	Poly(int, int);
	Poly(int);
	Poly(const Poly &);
	~Poly();

	//Member Functions / GETS&SETS
	bool setCoeff(int, int);
	int getCoeff(int) const;
	int getLargestExponent() const;

	//Operator Overloads for Polynomials
	friend ostream& operator<<(ostream&, Poly &);
	friend istream& operator>>(istream&, Poly &);
	Poly& operator=(const Poly &);
	Poly operator+(const Poly &) const;
	Poly& operator+=(const Poly &);
	Poly operator-(const Poly &) const;
	Poly& operator-=(const Poly &);
	Poly& operator-();
	bool operator==(const Poly &) const;
	bool operator!=(const Poly &) const;
	Poly operator*(const Poly &) const;
	Poly& operator*=(const Poly &);

	//Operator Overloads for Ints
	Poly operator+(int) const;
	Poly& operator+=(int);
	Poly operator-(int) const;
	Poly& operator-=(int);
	Poly operator*(int) const;
	Poly& operator*=(int);

private:
	int *arr;
	int size;
};

