#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

char* encryptPolySubstitution(char *plaintext, char *key);
char shiftChar(char c, int shift);

int main() {
    char plaintext[100], key[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';
    char *ciphertext = encryptPolySubstitution(plaintext, key);
    printf("Encrypted text: %s\n", ciphertext);
    free(ciphertext);

    return 0;
}

char* encryptPolySubstitution(char *plaintext, char *key) {
    char *ciphertext = (char *)malloc((strlen(plaintext) + 1) * sizeof(char));
    if (ciphertext == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    int keyLength = strlen(key);
    int i, j = 0;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            int shift = tolower(key[j % keyLength]) - 'a';
            ciphertext[i] = shiftChar(plaintext[i], shift);
            j++;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';

    return ciphertext;
}

char shiftChar(char c, int shift) {
    char base = isupper(c) ? 'A' : 'a';
    return (base + (c - base + shift) % ALPHABET_SIZE);
}

