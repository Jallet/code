#include <stdio.h> 

int max(int a, int b) {
    int result = 0;
    if (a > b) {
        result = a;
    }
    else {
        result = b;
    }

    return result;
}

int min(int a , int b) {
    int result = 0;
    if (a < b) {
        result = a;
    }
    else {
        result = b;
    }

    return result;
}

int sum(int a, int b) {
    int result = a + b;
    return result;
}

int substract(int a, int b) {
    int result = a - b; 
    return result;
}

int main() {
    int i = 0; 
    printf("hello, world!\n");
    int a = 2;
    int b = 3;
    for (i = 0; i < 5; ++i) {
        printf("max is %d\n", max(a, b));
        printf("min is %d\n", min(a, b));
        printf("sum is %d\n", sum(a, b));
        printf("substract is %d\n", substract(a, b));
    }
    return 0;
}
