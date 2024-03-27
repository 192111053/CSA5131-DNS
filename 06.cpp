#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

int main() {
    char ciphertext[] = "BUnGvRmBqRnEnYzRnVmzRxQvBtUnYwRmBqRnAqRvGtRmBqRnAqRvGtRm";
    int freq[ALPHABET_SIZE] = {0};

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            freq[ciphertext[i] - 'A']++;
        }
    }

    int maxFreqIndex = 0;
    for (int i = 1; i < ALPHABET_SIZE; i++) {
        if (freq[i] > freq[maxFreqIndex]) {
            maxFreqIndex = i;
        }
    }

    int distance = (maxFreqIndex + ALPHABET_SIZE - ('E' - 'A')) % ALPHABET_SIZE;

    int a, b;
    for (a = 1; a < ALPHABET_SIZE; a++) {
        if ((a * distance) % ALPHABET_SIZE == 1) {
            b = (maxFreqIndex - (a * ('E' - 'A'))) % ALPHABET_SIZE;
            if (b < 0) {
                b += ALPHABET_SIZE;
            }
            break;
        }
    }

    printf("Possible values: a = %d, b = %d\n", a, b);
    printf("Plaintext: ");
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            char decrypted = ((modInverse(a, ALPHABET_SIZE) * (ciphertext[i] - 'A' - b)) % ALPHABET_SIZE) + 'A';
            if (decrypted < 'A') {
                decrypted += ALPHABET_SIZE;
            }
            printf("%c", decrypted);
        } else {
            printf("%c", ciphertext[i]);
        }
    }
    printf("\n");

    return 0;
}

