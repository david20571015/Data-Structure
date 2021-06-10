//
// GCD.cpp
// ds_hw2_array_gcd
//
#include "GCD.h"

inline int getDeg(long *poly, const int &deg)
{
    for (int i = deg; i >= 0; i--)
        if (poly[i] != 0)
            return i;
    return -1;
}

inline long getLeadingCoeff(long *poly, const int &deg)
{
    return poly[getDeg(poly, deg)];
}

template <typename T>
inline T getGcd(T a, T b)
{
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    while ((a %= b) && (b %= a))
    {
    }
    return a | b;
}

inline long getCoeffGcd(long *in1, const int &deg1)
{
    if (deg1 == 0)
        return in1[0] > 0 ? in1[0] : -in1[0];

    long gcd = getGcd(in1[0], in1[1]);
    for (int i = 2; i <= deg1; i++)
        gcd = getGcd(gcd, in1[i]);

    return gcd > 0 ? gcd : -gcd;
}

inline void simplify(long *p, const int &deg)
{
    long gcd = getCoeffGcd(p, deg);

    if (p[deg] < 0)
        gcd *= -1;
    for (int i = 0; i <= deg; i++)
        p[i] /= gcd;
}

inline void polynomialMod(Poly &a, const Poly &b)
{
    if (a.degree < b.degree || (a.degree == b.degree && a.coe[a.degree] < b.coe[b.degree]))
        return;

    while (a.degree >= b.degree)
    {
        __int128_t lc_a = a.coe[a.degree];
        __int128_t lc_b = b.coe[b.degree];
        __int128_t a_times = lc_b / getGcd(lc_a, lc_b);
        __int128_t b_times = a_times * lc_a / lc_b;

        for (int i = 0; i <= a.degree; i++)
            a.coe[i] *= a_times;
        for (int i = 0; i <= b.degree; i++)
            a.coe[i + a.degree - b.degree] -= b.coe[i] * b_times;

        a.computeDeg();
    }

    __int128_t gcd = 0;
    for (int i = 0; i <= a.degree; i++)
        gcd = getGcd(gcd, a.coe[i]);
    for (int i = 0; i <= a.degree; i++)
        a.coe[i] /= gcd;
}

long *GCD::FindGCD(long *in1, long *in2, const int &deg1, const int &deg2)
{
    simplify(in1, deg1);
    simplify(in2, deg2);

    Poly a(in1, deg1), b(in2, deg2);
    Poly *ap = &a, *bp = &b, *t;

    while ((*bp).degree >= 0)
    {
        polynomialMod((*ap), (*bp));
        t = ap;
        ap = bp;
        bp = t;
        (*ap).computeDeg();
        (*bp).computeDeg();
    }

    for (int i = 0; i <= (*ap).degree; i++)
        in1[i] = long((*ap).coe[i]);

    memset(in1 + (*ap).degree + 1, 0, (ARRAY_MAX - (*ap).degree) * sizeof(long));
    simplify(in1, (*ap).degree);

    return in1;
}
