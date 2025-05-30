#include <stdio.h>

class M {
    enum { rows = 3, cols = 3 };
    int matrix[rows][cols];
public:
    class I {
        friend class M;
        M *m;
        int i;
        I(M *m, int i) : m(m), i(i) {}
    public:
        int &operator[](int j) { return m->matrix[i - 1][j - 1]; }
    };
    friend class I;

    M();
    I operator[](int i) { return I(this, i); }
    M operator+(const M &op2) const;
};

M::M()
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = (i == j);
        }
    }
}

M M::operator+(const M &op2) const
{
    M res;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            res.matrix[i][j] = matrix[i][j] + op2.matrix[i][j];
        }
    }
    return res;
}

int main()
{
    M m1;
    printf("%d %d %d\n", m1[1][1], m1[2][2], m1[2][3]);
    M m2;
    m1[2][3] = 7;
    m2[2][3] = 350;
    M m3(m1 + m2);
    printf("%d %d %d\n", m3[1][1], m3[2][2], m3[2][3]);
    return 0;
}
