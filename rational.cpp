#include <math.h>
#include <stdio.h>

class Rational {
    friend Rational operator+(const Rational &a, const Rational &b);
    friend Rational operator-(const Rational &a, const Rational &b);
    friend Rational operator*(const Rational &a, const Rational &b);
    friend Rational operator/(const Rational &a, const Rational &b);

    long long int n;
    long long int m;
public:
    Rational(long long int n = 0, long long int m = 1) : n(n), m(m) {}
    long long int GetN() const { return n; }
    long long int GetM() const { return m; }
    double Double() const { return (double)n / m; }
    long long int Int() const { return trunc(Double()); }
    long long int Round() const { return round(Double()); }
    Rational operator-() const { return Rational(-n, m); }
    const Rational &operator+=(const Rational &r)
        { *this = *this + r; return *this; }
    const Rational &operator-=(const Rational &r)
        { *this = *this - r; return *this; }
    const Rational &operator*=(const Rational &r)
        { *this = *this * r; return *this; }
    const Rational &operator/=(const Rational &r)
        { *this = *this / r; return *this; }
    const Rational &operator++()
        { n += m; return *this; }
    const Rational operator++(int)
        { Rational r(*this); n += m; return r; }
    const Rational &operator--()
        { n -= m; return *this; }
    const Rational operator--(int)
        { Rational r(*this); n -= m; return r; }
};

inline Rational operator+(const Rational &a, const Rational &b)
{
    return Rational(a.n * b.m + a.m * b.n, a.m * b.m);
}

inline Rational operator-(const Rational &a, const Rational &b)
{
    return a + (-b);
}

inline Rational operator*(const Rational &a, const Rational &b)
{
    return Rational(a.n * b.n, a.m * b.m);
}

inline Rational operator/(const Rational &a, const Rational &b)
{
    return Rational(a.n * b.m, a.m * b.n);
}

int main()
{
    Rational a(2, 3), b(3, 15), f;
    printf("%lld/%llu\n", a.GetN(), a.GetM()); /* 2/3 */

    Rational c(a + b);
    printf("%lld/%llu\n", c.GetN(), c.GetM()); /* 39/45 */

    Rational d(c - a + 1);
    printf("%lld/%llu\n", d.GetN(), d.GetM()); /* 162/135 */

    d = -a * b;
    printf("%lld/%llu\n", d.GetN(), d.GetM()); /* -6/45 */

    Rational e = 3 * d / b + 1;
    printf("%lld/%llu\n", e.GetN(), e.GetM()); /* -135/135 */

    f = 2;
    printf("%lld/%llu\n", f.GetN(), f.GetM()); /* 2/1 */

    f += Rational(1, 2);
    printf("%lld/%llu %f %lld %lld\n", f.GetN(), f.GetM(),
            f.Double(), f.Int(), f.Round()); /* 5/2 2.5 2 3 */

    f -= 2;
    printf("%lld/%llu\n", f.GetN(), f.GetM()); /* 1/2 */

    f *= Rational(4, 3);
    printf("%lld/%llu\n", f.GetN(), f.GetM()); /* 4/6 */

    f /= f;
    printf("%lld/%llu\n", f.GetN(), f.GetM()); /* 24/24 */

    f--;
    printf("%lld/%llu\n", f.GetN(), f.GetM()); /* 0/24 */
    f++;
    printf("%lld/%llu\n", f.GetN(), f.GetM()); /* 24/24 */
    --f;
    printf("%lld/%llu\n", f.GetN(), f.GetM()); /* 0/24 */
    ++f;
    printf("%lld/%llu\n", f.GetN(), f.GetM()); /* 24/24 */
    return 0;
}
