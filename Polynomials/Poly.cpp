#include "poly.h"


////////////////
//Constructors//
////////////////

//---------------------------------------
//Default Constructor
//The default constructor
Poly::Poly()
{
	arr = new int[1];
	arr[0] = 0;
	size = 1;
}

//---------------------------------------
//Constructor with 1 int
//Makes the array the size of x but empty
Poly::Poly(int x)
{
	size = x + 1;
	arr = new int[x + 1];
	for (int i = 0; i < x; i++)
	{
		arr[i] = 0;
	}
	arr[x] = 0;
}

//---------------------------------------
//Constructor with 2 ints
//Highest exponenet is y with coefficient x
Poly::Poly(int x, int y)
{
	size = y + 1;
	arr = new int[y + 1];
	for (int i = 0; i < y; i++)
	{
		arr[i] = 0;
	}
	arr[y] = x;
}

//---------------------------------------
//Copy Constructor
//Makes the array the same as the other's
Poly::Poly(const Poly &a)
{
	this->arr = new int[a.getLargestExponent()];
	this->size = a.getLargestExponent();
	for (int i = 0; i < a.getLargestExponent(); i++)
	{
		this->arr[i] = a.arr[i];
	}
}

//---------------------------------------
//Destructor
//Cleans up allocated memory
Poly::~Poly()
{
	delete[] arr;
	arr = NULL;
}


////////////////////
//Helper Functions//
////////////////////

//---------------------------------------
//Get Coefficient
//Returns the coefficient with the given exponent
int Poly::getCoeff(int x) const
{
	if (x > size || x < 0)
	{
		return -1;
	}
	return arr[x];
}

//---------------------------------------
//Set Coefficient
//Sets the coefficient of y to x
//Also will make the array larger if needed
bool Poly::setCoeff(int x, int y)
{                                 
	if (y > size)
	{
		Poly temp(x, y);
		for (int i = 0; i < size; i++)
		{
			temp.setCoeff(arr[i], i);
		}
		*this = temp;
		return true;
	}
	if (y < 0)
	{
		return false;
	}
	arr[y] = x;
	return true;
}

//---------------------------------------
//Get Largest Exponent
//Returns the size of the array
int Poly::getLargestExponent() const
{
	return size;
}


////////////////////////////////
//Operator Overloads With Self//
////////////////////////////////

ostream& operator<<(ostream& o, Poly &a)
{
	for (int i = a.getLargestExponent() - 1; i > 0; i--)
	{
		if (a.arr[i] > 0 && i != 1)
		{
			if (i == 1)
			{
				o << " +" << a.arr[i] << "x";
			}
			o << " +" << a.arr[i] << "x^" << i;
		}
		else if (a.arr[i] < 0 && i != 1)
		{
			o << " " << a.arr[i] << "x^" << i;
			if (i == 1)
			{
				o << " " << a.arr[i] << "x";
			}
		}
		else
		{
			continue;
		}
	}
	if (a.arr[1] != 0)
	{
		if (a.arr[1] > 0)
		{
			o << " +" << a.arr[1] << "x";
		}
		else
		{
			o << " " << a.arr[1] << "x";
		}
	}
	if (a.arr[0] != 0)
	{
		if (a.arr[0] > 0)
		{
			o << " +" << a.arr[0];
		}
		else
		{
			o << " " << a.arr[0];
		}
	}
	return o;
}

istream& operator>>(istream& i, Poly &a)
{
	int x = 0, y = 0, count = 0; 
	bool done = false;
	while (!done)
	{
		count++;
		i >> x >> y;
		if (x == -1 && y == -1)
		{
			return i;
		}
		else if (/*count > a.size ||*/ y < -1 /*|| y > a.size*/)
		{
			return i;
		}
		else if (i.fail())
		{
			return i;
		}
		else
		{
			a.setCoeff(x, y);
		}
	}
	return i;
}

Poly& Poly::operator=(const Poly &a)
{
	if (*this != a)
	{
		delete[] this->arr;
		this->arr = new int[a.getLargestExponent()];
		this->size = a.getLargestExponent();
		for (int i = 0; i < a.getLargestExponent(); i++)
		{
			this->arr[i] = a.arr[i];
		}
	}
	return *this;
} 

Poly Poly::operator+(const Poly &a) const
{
	Poly temp;
	if (a.getLargestExponent() > getLargestExponent())
	{
		temp = a;
		for (int i = 0; i < getLargestExponent(); i++)
		{
			temp.arr[i] = a.arr[i] + arr[i];
		} 
		return temp;
	}
	else
	{
		temp = *this;
		for (int i = 0; i < a.getLargestExponent(); i++)
		{
			temp.arr[i] = a.arr[i] + arr[i];
		} 
		return temp;
	}
}

Poly& Poly::operator+=(const Poly &a)
{
	*this = *this + a;
	return *this;
}

Poly Poly::operator-(const Poly &a) const
{
	Poly temp;
	if (a.getLargestExponent() > getLargestExponent())
	{
		temp = a;
		for (int i = 0; i < getLargestExponent(); i++)
		{
			temp.arr[i] = arr[i] - a.arr[i];
		}
		for (int i = getLargestExponent(); i < a.getLargestExponent(); i++)
		{
			temp.arr[i] = a.arr[i] * -1;
		}
		return temp;
	}
	else
	{
		temp = *this;
		for (int i = 0; i < a.getLargestExponent(); i++)
		{
			temp.arr[i] = arr[i] - a.arr[i];
		}
		return temp;
	}
}

Poly& Poly::operator-=(const Poly &a)
{
	*this = *this - a;
	return *this;
}

Poly& Poly::operator-()
{
	for (int i = 0; i < getLargestExponent(); i++)
	{
		this->arr[i] *= -1;
	}
	return *this;
}

bool Poly::operator==(const Poly &a) const
{
	if (this->getLargestExponent() == a.getLargestExponent())
	{
		for (int i = 0; i < getLargestExponent(); i++)
		{
			if (arr[i] == a.arr[i])
			{
				continue;
			}
			else
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool Poly::operator!=(const Poly &a) const
{
	if (this->getLargestExponent() == a.getLargestExponent())
	{
		for (int i = 0; i < getLargestExponent(); i++)
		{
			if (arr[i] == a.arr[i])
			{
				continue;
			}
			else
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		return true;
	}
}

Poly Poly::operator*(const Poly &a) const
{
	Poly temp(a.getLargestExponent() + this->getLargestExponent());
	for (int i = 0; i < this->getLargestExponent(); i++)
	{
		for (int j = 0; j < a.getLargestExponent(); j++)
		{
			temp.arr[i + j] += (this->arr[i] * a.arr[j]);
		}
	}
	return temp;
}

Poly& Poly::operator*=(const Poly &a)
{
	*this = *this * a;
	return *this;
}


////////////////////////////////
//Operator Overloads With Ints//
////////////////////////////////

Poly Poly::operator+(int n) const
{
	Poly temp = *this;
	temp.arr[0] += n;
	return temp;
}

Poly& Poly::operator+=(int n)
{
	*this = *this + n;
	return *this;
}

Poly Poly::operator-(int n) const
{
	Poly temp = *this;
	temp.arr[0] -= n;
	return temp;
}

Poly& Poly::operator-=(int n)
{
	*this = *this - n;
	return *this;
}

Poly Poly::operator*(int n) const
{
	Poly temp = *this;
	for(int i = 0; i < temp.getLargestExponent(); i++)
	{
		temp.arr[i] *= n;
	}
	return temp;
}

Poly& Poly::operator*=(int n)
{
	*this = *this * n;
	return *this;
}
