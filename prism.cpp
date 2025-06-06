#include <stdio.h>

class Prism {
    double height;
public:
    Prism(double h) : height(h) {}
    virtual ~Prism() {}
    virtual double Square() const = 0;
    double Volume() const { return Square() * height; }
};

class Box : public Prism {
    double width;
public:
    Box(double h, double w) : Prism(h), width(w) {}
    virtual ~Box() {}
    virtual double Square() const { return width * width; }
};

class Cube : public Box {
public:
    Cube(double a) : Box(a, a) {}
    virtual ~Cube() {}
};

int main()
{
    const Prism *p, *q, *r;
    Box a(0.5, 2), b(5, 0.2);
    Cube c(0.5);
    p = &a; q = &b; r = &c;
    printf("Squares: %3.3f %3.3f %3.3f\n",
            p->Square(), q->Square(), r->Square());
    printf("Volumes: %3.3f %3.3f %3.3f\n",
            p->Volume(), q->Volume(), r->Volume());
    return 0;
}
