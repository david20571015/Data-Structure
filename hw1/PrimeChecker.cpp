//
// PrimeChecker.cpp
// ds_hw1_warm_up
//
#include "PrimeChecker.h"

#include <bits/stdc++.h>
using namespace std;

unsigned long power(unsigned long &x, unsigned long y, unsigned long &p)
{
	unsigned long res = 1;
	x = x % p;
	while (y > 0)
	{
		// if (y & 1)
		// 	res = (res * x) % p;
		res = (y & 1) ? ((res * x) % p) : res;

		x = (x * x) % p;
		y >>= 1;
	}
	return res;
}

bool isPrime(unsigned long &n)
{
	if (n == 2)
		return true;

	// if (n < 2 || !(n & 1))
	// 	return false;
	if (n == 0 || n == 1 || !(n & 1))
		return false;

	unsigned long u = n - 1, t = 0;
	while (!(u & 1))
	{
		u >>= 1;
		t++;
	}

	unsigned long sprp[3] = {2, 7, 61};
	for (int k = 0; k < 3; ++k)
	{
		unsigned long a = sprp[k] % n;
		if (a == 0 || a == 1 || a == n - 1)
			continue;

		unsigned long x = power(a, u, n);
		if (x == 1 || x == n - 1)
			continue;

		for (unsigned long i = 0; i < t - 1; i++)
		{
			x = (x * x) % n;
			if (x == 1)
				return false;
			if (x == n - 1)
				break;
		}
		if (x == n - 1)
			continue;

		return false;
	}
	return true;
}

unsigned long PRIMECHECKER::PrimeChecker(unsigned long a, unsigned long b)
{
	unsigned int found = 0;

	// a += !(a & 1);
	// b -= !(b & 1);

	for (unsigned long i = a; i <= b; i++)
	{
		found += isPrime(i);
	}

	return found;
}
