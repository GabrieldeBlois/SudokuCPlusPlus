#include <stdio.h>


int binarize(int a) {
    return ((1 << (a - 1)));
}

int doesExist(int n, int a, int b, int c) {
    printf("%d & %d = %d\n", n, a, n & a);
    printf("%d & %d = %d\n", n, b, n & b);
    printf("%d & %d = %d\n", n, c, n & c);
    return (n & a || n & b || n & c);
}

void eraseANumber() {
    int a = binarize(4) | binarize(2);
    printf("in %d, i want to erase: %d. So: %d\n", a, 2, a ^ 2);
}

int main() {
    int a, b, c = 0;
    a = 1;
    b = 2;
    c = 3;

    a = binarize(a);
    b = binarize(b);
    c = binarize(c);

    printf("%d\n", doesExist(binarize(1), a, b, c));
    printf("%d\n", doesExist(binarize(2), a, b, c));
    printf("%d\n", doesExist(binarize(3), a, b, c));
    printf("%d\n", doesExist(binarize(4), a, b, c));
    eraseANumber();
    return 0;
}