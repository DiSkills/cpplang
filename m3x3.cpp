#include <stdio.h>

class I {
    friend class M;
    int i, j;
public:
    I(int i, int j) : i(i), j(j) {}
};

class M {
    enum { rows = 3, cols = 3 };
    int matrix[rows][cols];
public:
    M();
    int &operator[](const I &idx);
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

int &M::operator[](const I &idx)
{
    return matrix[idx.i - 1][idx.j - 1];
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
    printf("%d %d %d\n", m1[I(1, 1)], m1[I(2, 2)], m1[I(2, 3)]);
    M m2;
    m1[I(2, 3)] = 7;
    m2[I(2, 3)] = 350;
    M m3(m1 + m2);
    printf("%d %d %d\n", m3[I(1, 1)], m3[I(2, 2)], m3[I(2, 3)]);
    return 0;
}
