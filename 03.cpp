#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 5

void prepareKey(char *key, char *preparedKey);
void buildMatrix(char *preparedKey, char matrix[MATRIX_SIZE][MATRIX_SIZE]);
void encryptPlayfair(char matrix[MATRIX_SIZE][MATRIX_SIZE], char *plaintext, char *ciphertext);

int main() {
    char key[100], plaintext[100], ciphertext[100], preparedKey[26] = "";
    char matrix[MATRIX_SIZE][MATRIX_SIZE];

    printf("Enter the keyword: ");
    fgets(key, sizeof(key), stdin);

    prepareKey(key, preparedKey);

    buildMatrix(preparedKey, matrix);

    printf("Enter the plaintext (in uppercase): ");
    fgets(plaintext, sizeof(plaintext), stdin);

    plaintext[strcspn(plaintext, "\n")] = '\0';

    encryptPlayfair(matrix, plaintext, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);

    return 0;
}

void prepareKey(char *key, char *preparedKey) {
    int i, j;
    char temp[26] = "";

    for (i = 0, j = 0; key[i] != '\0'; i++) {
        if (!isspace(key[i])) {
            temp[j++] = toupper(key[i]);
        }
    }

    for (i = 0, j = 0; temp[i] != '\0'; i++) {
        if (strchr(preparedKey, temp[i]) == NULL) {
            preparedKey[j++] = temp[i];
        }
    }
    preparedKey[j] = '\0';
}

void buildMatrix(char *preparedKey, char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int i, j, k = 0;
    char alphabet[26] = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; 
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            if (k < strlen(preparedKey)) {
                matrix[i][j] = preparedKey[k++];
            } else {
                while (strchr(preparedKey, alphabet[k - MATRIX_SIZE]) != NULL) {
                    k++;
                }
                matrix[i][j] = alphabet[k - MATRIX_SIZE];
                k++;
            }
        }
    }
}

void encryptPlayfair(char matrix[MATRIX_SIZE][MATRIX_SIZE], char *plaintext, char *ciphertext) {
    int i, len = strlen(plaintext), index = 0;
    char a, b;
    for (i = 0; i < len; i += 2) {
        a = plaintext[i];
        b = (i + 1 < len) ? plaintext[i + 1] : 'X';
        if (a == 'J')
            a = 'I';
        if (b == 'J')
            b = 'I';
        int row1, col1, row2, col2;
        for (int j = 0; j < MATRIX_SIZE; j++) {
            for (int k = 0; k < MATRIX_SIZE; k++) {
                if (matrix[j][k] == a) {
                    row1 = j;
                    col1 = k;
                }
                if (matrix[j][k] == b) {
                    row2 = j;
                    col2 = k;
                }
            }
        }
        if (row1 == row2) {
            ciphertext[index++] = matrix[row1][(col1 + 1) % MATRIX_SIZE];
            ciphertext[index++] = matrix[row2][(col2 + 1) % MATRIX_SIZE];
        } else if (col1 == col2) {
            ciphertext[index++] = matrix[(row1 + 1) % MATRIX_SIZE][col1];
            ciphertext[index++] = matrix[(row2 + 1) % MATRIX_SIZE][col2];
        } else {
            ciphertext[index++] = matrix[row1][col2];
            ciphertext[index++] = matrix[row2][col1];
        }
    }
    ciphertext[index] = '\0';
}

