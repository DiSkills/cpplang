#include <stdlib.h>
#include <stdio.h>

struct bin_coefficient {
    int n, k, value;
};

class Machine {
    int k, n;
    int *next /* n + 2 */, *cur /* n + 1 */;
public:
    Machine();
    ~Machine() { delete[] cur; delete[] next; }
    bin_coefficient Step();
};

Machine::Machine() : k(0), n(0)
{
    cur = new int[1];
    cur[0] = 1;

    next = new int[2];
    next[0] = 1;
    next[1] = 1;
}

bin_coefficient Machine::Step()
{
    bin_coefficient res;
    res.k = k;
    res.n = n;
    res.value = cur[k];

    if (k == n) {
        delete[] cur;
        cur = next;
        k = 0;
        n++;

        next = new int[n + 2];
        next[0] = 1;

        int i;
        for (i = 1; i <= n; i++) {
            next[i] = cur[i - 1] + cur[i];
        }
        next[i] = 1;
    } else {
        k++;
    }
    return res;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Expected: %s <number-of-rows>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);

    Machine machine;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            bin_coefficient res = machine.Step();
            printf("(%d, %d, %d)\n", res.n, res.k, res.value);
        }
    }
    return 0;
}
