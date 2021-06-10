//
// Gcd.h
// DS hw2 array gcd
//

#ifndef _GCD_
#define _GCD_
#define ARRAY_MAX 1000

#include <cstring>

class GCD
{
private:
public:
	GCD() {}
	~GCD() {}
	long *FindGCD(long *in1, long *in2, const int &deg1, const int &deg2);
};

class Poly
{
public:
	__int128_t coe[ARRAY_MAX];
	int degree;

	Poly(long *p, int d)
	{
		degree = d;
		for (int i = 0; i <= d; i++)
			coe[i] = __int128_t(p[i]);
		// memset(coe + d + 1, 0, (ARRAY_MAX - d - 1) * sizeof(__int128_t));
	}

	int computeDeg()
	{
		for (int i = this->degree; i >= 0; i--)
			if (this->coe[i] != 0)
			{
				this->degree = i;
				return i;
			}
		this->degree = -1;
		return -1;
	}
};
#endif
