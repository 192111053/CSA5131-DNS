#include <stdio.h>
#include <stdlib.h>

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return 1;
}

void encrypt(int plaintext[2], int key[2][2], int ciphertext[2]) {
    ciphertext[0] = (plaintext[0] * key[0][0] + plaintext[1] * key[0][1]) % 26;
    ciphertext[1] = (plaintext[0] * key[1][0] + plaintext[1] * key[1][1]) % 26;
}

void decrypt(int ciphertext[2], int key[2][2], int plaintext[2]) {
    int determinant = (key[0][0] * key[1][1] - key[0][1] * key[1][0] + 26) % 26;
    int inverse = modInverse(determinant, 26);

    int adjoint[2][2];
    adjoint[0][0] = key[1][1];
    adjoint[0][1] = -key[0][1];
    adjoint[1][0] = -key[1][0];
    adjoint[1][1] = key[0][0];

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            adjoint[i][j] = (adjoint[i][j] + 26) % 26;
        }
    }

    plaintext[0] = (inverse * (adjoint[0][0] * ciphertext[0] + adjoint[0][1] * ciphertext[1])) % 26;
    plaintext[1] = (inverse * (adjoint[1][0] * ciphertext[0] + adjoint[1][1] * ciphertext[1])) % 26;
}

int main() {
    int key[2][2] = {{3, 2}, {5, 7}}; 
    int plaintext[2] = {1, 0}; 
    int ciphertext[2], decryptedtext[2];

    encrypt(plaintext, key, ciphertext);

    printf("Ciphertext: %c%c\n", ciphertext[0] + 'A', ciphertext[1] + 'A');

    decrypt(ciphertext, key, decryptedtext);

    printf("Decrypted text: %c%c\n", decryptedtext[0] + 'A', decryptedtext[1] + 'A');

    return 0;
}

