#include <cmath>
#include <stdio.h>

class Complex {
    friend Complex operator+(const Complex &a, const Complex &b);

    double re, im;
public:
    Complex(double a = 0, double b = 0) : re(a), im(b) {}
    double Modulo() const
        { return sqrt(re * re + im * im); }
    double Argument() const
        { return atan2(im, re); }
    double GetRe() const { return re; }
    double GetIm() const { return im; }
#if 0
    Complex operator+(const Complex &op2) const
        { return Complex(re + op2.re, im + op2.im); }
#endif
    Complex operator-(const Complex &op2) const
        { return Complex(re - op2.re, im - op2.im); }
    Complex operator*(const Complex &op2) const {
        return Complex(re * op2.re - im * op2.im,
                re * op2.im + im * op2.re);
    }
    Complex operator/(const Complex &op2) const {
        double dvs = op2.re * op2.re + op2.im * op2.im;
        return Complex((re * op2.re + im * op2.im) / dvs,
                       (im * op2.re - re * op2.im) / dvs);
    }
};

Complex operator+(const Complex &a, const Complex &b)
{
    return Complex(a.re + b.re, a.im + b.im);
}

int main()
{
    Complex z(2.8, 3.8);
    double mod = z.Modulo();
    printf("%f\n", mod);
    return 0;
}
