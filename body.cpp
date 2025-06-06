#include <math.h>
#include <stdio.h>

class Body {
    double density;
public:
    Body(double d) : density(d) {}
    virtual ~Body() {}
    virtual double Volume() const = 0;
    double Mass() const { return density * Volume(); }
};

class Cube : public Body {
    double length;
public:
    Cube(double a, double d) : Body(d), length(a) {}
    virtual ~Cube() {}
    virtual double Volume() const { return length * length * length; }
};

class Tetrahedron : public Body {
    double length;
public:
    Tetrahedron(double a, double d) : Body(d), length(a) {}
    virtual ~Tetrahedron() {}
    virtual double Volume() const
        { return M_SQRT2 / 12 * length * length * length; }
};

int main()
{
    const Body *p, *q, *r;
    Cube a(2, 10), b(5, 0.1);
    Tetrahedron t(6, 2.5);
    p = &a; q = &b; r = &t;
    printf("Volumes: %3.3f %3.3f %3.3f\n",
            p->Volume(), q->Volume(), r->Volume());
    printf("Weights: %3.3f %3.3f %3.3f\n",
            p->Mass(), q->Mass(), r->Mass());
    return 0;
}
