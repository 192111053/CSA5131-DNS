#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

char* encrypt(char *plaintext, char *key);
char* decrypt(char *ciphertext, char *key);

int main() {
    char plaintext[100], key[ALPHABET_SIZE + 1];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter the key (permutation of the alphabet): ");
    fgets(key, sizeof(key), stdin);

    plaintext[strcspn(plaintext, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';

    char *ciphertext = encrypt(plaintext, key);
    printf("Encrypted text: %s\n", ciphertext);

    char *decryptedText = decrypt(ciphertext, key);
    printf("Decrypted text: %s\n", decryptedText);

    free(ciphertext);
    free(decryptedText);

    return 0;
}

char* encrypt(char *plaintext, char *key) {
    char *ciphertext = (char *)malloc((strlen(plaintext) + 1) * sizeof(char));
    if (ciphertext == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = key[plaintext[i] - base];
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[i] = '\0';

    return ciphertext;
}

char* decrypt(char *ciphertext, char *key) {
    char *plaintext = (char *)malloc((strlen(ciphertext) + 1) * sizeof(char));
    if (plaintext == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    int i, j;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        for (j = 0; j < ALPHABET_SIZE; j++) {
            if (ciphertext[i] == key[j]) {
                plaintext[i] = 'a' + j; 
                break;
            }
        }
        if (j == ALPHABET_SIZE) {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[i] = '\0';

    return plaintext;
}

