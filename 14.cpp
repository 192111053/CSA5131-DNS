#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encrypt(char plaintext[], int key[], char ciphertext[]) {
    int i, j = 0;
    for (i = 0; i < strlen(plaintext); i++) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = ((plaintext[i] - 'a' + key[j]) % 26) + 'a';
            j = (j + 1) % strlen(plaintext);
        }
        else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = ((plaintext[i] - 'A' + key[j]) % 26) + 'A';
            j = (j + 1) % strlen(plaintext);
        }
        else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';
}

void decrypt(char ciphertext[], int key[], char decryptedtext[]) {
    int i, j = 0;
    for (i = 0; i < strlen(ciphertext); i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            decryptedtext[i] = ((ciphertext[i] - 'a' - key[j] + 26) % 26) + 'a';
            j = (j + 1) % strlen(ciphertext);
        }
        else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            decryptedtext[i] = ((ciphertext[i] - 'A' - key[j] + 26) % 26) + 'A';
            j = (j + 1) % strlen(ciphertext);
        }
        else {
            decryptedtext[i] = ciphertext[i];
        }
    }
    decryptedtext[i] = '\0';
}

int main() {
    char plaintext[] = "sendmoremoney";
    int key[] = {9, 0, 1, 7, 2, 3, 1, 5, 2, 1, 1, 4, 2, 1, 1, 1, 2, 8, 9}; // Key stream
    char ciphertext[strlen(plaintext) + 1];
    char decryptedtext[strlen(plaintext) + 1];

    encrypt(plaintext, key, ciphertext);
    printf("Encrypted ciphertext: %s\n", ciphertext);

    decrypt(ciphertext, key, decryptedtext);
    printf("Decrypted plaintext: %s\n", decryptedtext);

    return 0;
}

