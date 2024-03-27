#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char grid[SIZE][SIZE];

void setupMatrix(char key[]) {
    int i, j, k;
    int len = strlen(key);
    char alphabet[26] = {0};

    for (i = 0, k = 0; i < len; i++) {
        if (key[i] == 'j')
            key[i] = 'i';
        if (!alphabet[key[i] - 'a']) {
            grid[k / SIZE][k % SIZE] = key[i];
            alphabet[key[i] - 'a'] = 1;
            k++;
        }
    }

    for (i = 0; i < 26; i++) {
        if (alphabet[i] == 0) {
            if (i == ('j' - 'a')) continue;
            grid[k / SIZE][k % SIZE] = 'a' + i;
            k++;
        }
    }
}

void findPosition(char ch, int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (grid[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void formatPlaintext(char *plaintext) {
    int i, len;
    len = strlen(plaintext);
    for (i = 0; i < len; i++) {
        if (!isalpha(plaintext[i]))
            continue;
        if (plaintext[i] == 'j')
            plaintext[i] = 'i';
        else
            plaintext[i] = tolower(plaintext[i]);
    }
}

void encrypt(char *plaintext, char *ciphertext) {
    int i, row1, row2, col1, col2;
    int len = strlen(plaintext);
    for (i = 0; i < len; i += 2) {
        findPosition(plaintext[i], &row1, &col1);
        findPosition(plaintext[i + 1], &row2, &col2);
        if (row1 == row2) {
            ciphertext[i] = grid[row1][(col1 + 1) % SIZE];
            ciphertext[i + 1] = grid[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            ciphertext[i] = grid[(row1 + 1) % SIZE][col1];
            ciphertext[i + 1] = grid[(row2 + 1) % SIZE][col2];
        } else {
            ciphertext[i] = grid[row1][col2];
            ciphertext[i + 1] = grid[row2][col1];
        }
    }
    ciphertext[len] = '\0';
}

int main() {
    char key[] = "MFHIJKUNOPQZVWXYELARGDSTBC";
    char plaintext[] = "Must see you over Cadogan West. Coming at once.";
    char ciphertext[strlen(plaintext) * 2]; 
    formatPlaintext(plaintext);
    setupMatrix(key);
    encrypt(plaintext, ciphertext);

    printf("Original message: %s\n", plaintext);
    printf("Encrypted message: %s\n", ciphertext);

    return 0;
}

