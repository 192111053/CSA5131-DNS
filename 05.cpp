#include <stdio.h>

#define ALPHABET_SIZE 26

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

int isValidKey(int a) {
    return (a % ALPHABET_SIZE != 0 && modInverse(a, ALPHABET_SIZE) != -1);
}

char encryptChar(int a, int b, char plain) {
    if (plain >= 'a' && plain <= 'z') {
        return ((a * (plain - 'a') + b) % ALPHABET_SIZE) + 'a';
    } else if (plain >= 'A' && plain <= 'Z') {
        return ((a * (plain - 'A') + b) % ALPHABET_SIZE) + 'A';
    }
    return plain;
}

void affineCaesarCipher(int a, int b, char *plaintext, char *ciphertext) {
    while (*plaintext) {
        *ciphertext++ = encryptChar(a, b, *plaintext++);
    }
    *ciphertext = '\0';
}

int main() {
    int a, b;
    char plaintext[100], ciphertext[100];

    printf("Enter the value of a: ");
    scanf("%d", &a);

    if (!isValidKey(a)) {
        printf("Invalid value of 'a'.\n");
        return 1;
    }

    printf("Enter the value of b: ");
    scanf("%d", &b);

    printf("Enter plaintext: ");
    scanf(" %[^\n]s", plaintext);

    affineCaesarCipher(a, b, plaintext, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

