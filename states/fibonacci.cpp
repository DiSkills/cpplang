#include <stdio.h>
#include <stdlib.h>

class FibonacciMachine {
    int f1, f2;
public:
    FibonacciMachine() : f1(1), f2(1) {}
    int Step();
};

int FibonacciMachine::Step()
{
    int res = f1;
    f1 = f2;
    f2 += res;
    return res;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Expected: %s <n>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);

    FibonacciMachine machine;
    for (; n > 0; n--) {
        printf("%d\n", machine.Step());
    }
    return 0;
}
