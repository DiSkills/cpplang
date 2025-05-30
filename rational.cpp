#include <math.h>
#include <stdio.h>

class Rational {
    friend Rational operator+(const Rational &a, const Rational &b);
    friend Rational operator-(const Rational &a, const Rational &b);
    friend Rational operator*(const Rational &a, const Rational &b);
    friend Rational operator/(const Rational &a, const Rational &b);

    long long int n, m;
public:
    Rational(long long int a = 0, long long int b = 1)
        { long long int d = gcd(a, b); n = a / d; m = b / d; }
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
private:
    static long long int gcd(long long int a, long long int b);
};

Rational operator+(const Rational &a, const Rational &b)
{
    long long int d = Rational::gcd(a.m, b.m);
    return Rational((b.m / d) * a.n + (a.m / d) * b.n, (a.m / d) * b.m);
}

Rational operator-(const Rational &a, const Rational &b)
{
    long long int d = Rational::gcd(a.m, b.m);
    return Rational((b.m / d) * a.n - (a.m / d) * b.n, (a.m / d) * b.m);
}

Rational operator*(const Rational &a, const Rational &b)
{
    long long int d1 = Rational::gcd(a.n, b.m), d2 = Rational::gcd(a.m, b.n);
    return Rational((a.n / d1) * (b.n / d2), (a.m / d2) * (b.m / d1));
}

Rational operator/(const Rational &a, const Rational &b)
{
    long long int d1 = Rational::gcd(a.n, b.n), d2 = Rational::gcd(a.m, b.m);
    bool is_negative = (a.n < 0 && b.n > 0) || (a.n > 0 && b.n < 0);
    long long int numerator = (llabs(a.n) / d1) * (b.m / d2),
         denominator = (a.m / d2) * (llabs(b.n) / d1);
    return Rational(is_negative ? -numerator : numerator, denominator);
}

long long int Rational::gcd(long long int a, long long int b)
{
    a = llabs(a);
    b = llabs(b);
    while (a != 0 && b != 0) {
        if (a > b) {
            a %= b;
        } else {
            b %= a;
        }
    }
    return a + b;
}

int main()
{
    const Rational a(2, 3), b(3, 15);
    a.print();
    b.print();

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

    c = Rational(2, 3);
    d = Rational(-1, 3);
    (c / d).print();
    (c / -d).print();
    (-c / d).print();
    (-c / -d).print();

    Rational g(1, 4294967298), h(1, 4294967298);
    f = g + h;
    printf("%lld/%lld\n", f.GetN(), f.GetM());
    return 0;
}
