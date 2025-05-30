#include <math.h>
#include <stdio.h>

class Rational {
    friend Rational operator+(const Rational &a, const Rational &b);
    friend Rational operator-(const Rational &a, const Rational &b);
    friend Rational operator*(const Rational &a, const Rational &b);
    friend Rational operator/(const Rational &a, const Rational &b);

    long long int n, m;
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
    void print(char c = '\n') const
        { printf("%lld/%lld%c", n, m, c); }
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
    const Rational a(2, 3), b(3, 15);
    a.print();

    Rational c = a + b;
    c.print();
    (a - b).print();

    Rational d = -a * b;
    d.print();

    d = 3 * d / b + 1;
    d.print();

    Rational f = 2;
    f.print();
    (f += Rational(1, 2)).print(' ');
    printf("%f %lld %lld\n", f.Double(), f.Int(), f.Round());
    f -= 2; f.print();
    f *= Rational(4, 3); f.print();
    (f /= f).print();

    f--; f.print();
    f++; f.print();
    --f; f.print();
    ++f; f.print();

#if 0
    Rational g(1, 21870289), h(1, 421730688463);
    f = g + h;
    printf("%lld/%lld\n", f.GetN(), f.GetM());
#endif
    return 0;
}
