#include <stdio.h>

long long factorial(int n) {
    long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int main() {
    long long permutations = factorial(25);
    printf("Number of possible keys without considering identical encryption results: %lld\n", permutations);

    long long effectively_unique_keys = permutations / (factorial(10) * factorial(5));
    printf("Number of effectively unique keys considering identical encryption results: %lld\n", effectively_unique_keys);

    return 0;
}

