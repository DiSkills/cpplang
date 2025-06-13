#include <stdio.h>
#include <stdlib.h>
#include <string.h>

template <class T>
void swap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

static void print_numbers(int *arr, int length)
{
    for (int i = 0; i < length; i++) {
        printf("%d%c", arr[i], i == length - 1 ? '\n' : ' ');
    }
}

class PermutationMachine {
    enum node_states { start, completed };
    struct node {
        int i;
        enum node_states state;
    };
    node *nodes;
    int top, n;
public:
    PermutationMachine(int n);
    ~PermutationMachine() { delete[] nodes; }
    void Step(int *arr);
private:
    bool RealStep(int *arr);
};

PermutationMachine::PermutationMachine(int n) : top(0), n(n)
{
    nodes = new node[n];
    for (int i = 0; i < n; i++) {
        nodes[i].i = i;
        nodes[i].state = start;
    }
}

bool PermutationMachine::RealStep(int *arr)
{
    if (top == -1) {
        memset(arr, 0, n * sizeof(*arr));
        return true;
    }

    node *top_node = nodes + top;
    switch (top_node->state) {
    case start:
        swap(arr[top], arr[top_node->i]);
        top_node->state = completed;
        if (top < n - 1) {
            top++;
            nodes[top].i = top;
            nodes[top].state = start;
        } else {
            return true;
        }
        break;
    case completed:
        swap(arr[top], arr[top_node->i]);
        if (top_node->i >= n - 1) {
            top--;
        } else {
            top_node->i++;
            top_node->state = start;
        }
        break;
    }
    return false;
}

void PermutationMachine::Step(int *arr)
{
    bool res;
    do {
        res = RealStep(arr);
    } while (!res);
}

int main()
{
    int i, arr[] = { 1, 2, 3, 4 };
    int len = sizeof(arr) / sizeof(*arr);
    PermutationMachine machine(len);
    for (i = 0; i < 25; i++) {
        machine.Step(arr);
        print_numbers(arr, len);
    }
    return 0;
}
