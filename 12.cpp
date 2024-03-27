#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

int charToIndex(char c) {
    if (isupper(c))
        return c - 'A';
    else if (islower(c))
        return c - 'a';
    else
        return -1; 
}

char indexToChar(int index) {
    return (char)(index + 'a');
}

void encrypt(char *plaintext, int key[][4], int keySize) {
    int plaintextSize = strlen(plaintext);
    int i, j, k;
    int *plaintextVector = (int *)malloc(keySize * sizeof(int));
    int *resultVector = (int *)malloc(keySize * sizeof(int));

    for (i = 0; i < plaintextSize; i += keySize) {
        for (j = 0; j < keySize; j++) {
            if (i + j < plaintextSize)
                plaintextVector[j] = charToIndex(plaintext[i + j]);
            else
                plaintextVector[j] = 0; // Pad with 'a' (0 index)
        }

        for (j = 0; j < keySize; j++) {
            resultVector[j] = 0;
            for (k = 0; k < keySize; k++) {
                resultVector[j] += key[j][k] * plaintextVector[k];
            }
            resultVector[j] %= ALPHABET_SIZE; // Take modulo to keep result within alphabet size
        }

        // Convert result vector back to characters and print
        for (j = 0; j < keySize; j++) {
            printf("%c", indexToChar(resultVector[j]));
        }
    }

    free(plaintextVector);
    free(resultVector);
}

int main() {
    char plaintext[] = "meet me at the usual place at ten rather than eight oclock";
    int key[4][4] = {
        {9, 7, 11, 13},
        {4, 7, 5, 6},
        {2, 21, 14, 9},
        {3, 23, 21, 8}
    };
    int keySize = 4;

    printf("Original Message: %s\n", plaintext);
    printf("Encrypted Message: ");
    encrypt(plaintext, key, keySize);
    printf("\n");

    return 0;
}

