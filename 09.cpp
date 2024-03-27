#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char grid[SIZE][SIZE];

void prepareKey(char key[], int len) {
    int i, j, k;
    char temp[26] = {0};
    
    for (i = 0; i < len; i++) {
        if (key[i] != 'j')
            temp[key[i] - 'a'] = 2;
    }
    
    j = 0;
    k = 0;
    for (i = 0; i < 26; i++) {
        if (temp[i] != 2) {
            if (j < len)
                grid[0][j++] = 'a' + i;
            else
                grid[1][k++] = 'a' + i;
        }
    }
}

void printGrid() {
    int i, j;
    printf("Playfair Matrix:\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
}

void formatMessage(char str[]) {
    int i;
    for (i = 0; i < strlen(str); i++) {
        if (str[i] == 'j')
            str[i] = 'i';
    }
    for (i = 0; i < strlen(str); i += 2) {
        if (str[i] == str[i + 1])
            strcat(str, "x");
    }
    if (strlen(str) % 2 != 0)
        strcat(str, "x");
}

void findPosition(char ch, int *row, int *col) {
    int i, j;
    if (ch == 'j')
        ch = 'i';
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (grid[i][j] == ch) {
                *row = i;
                *col = j;
            }
        }
    }
}

void encrypt(char str[]) {
    int i, row1, row2, col1, col2;
    for (i = 0; i < strlen(str); i += 2) {
        findPosition(str[i], &row1, &col1);
        findPosition(str[i + 1], &row2, &col2);
        if (row1 == row2) {
            str[i] = grid[row1][(col1 + 1) % SIZE];
            str[i + 1] = grid[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            str[i] = grid[(row1 + 1) % SIZE][col1];
            str[i + 1] = grid[(row2 + 1) % SIZE][col2];
        } else {
            str[i] = grid[row1][col2];
            str[i + 1] = grid[row2][col1];
        }
    }
}

void decrypt(char str[]) {
    int i, row1, row2, col1, col2;
    for (i = 0; i < strlen(str); i += 2) {
        findPosition(str[i], &row1, &col1);
        findPosition(str[i + 1], &row2, &col2);
        if (row1 == row2) {
            str[i] = grid[row1][(col1 - 1 + SIZE) % SIZE];
            str[i + 1] = grid[row2][(col2 - 1 + SIZE) % SIZE];
        } else if (col1 == col2) {
            str[i] = grid[(row1 - 1 + SIZE) % SIZE][col1];
            str[i + 1] = grid[(row2 - 1 + SIZE) % SIZE][col2];
        } else {
            str[i] = grid[row1][col2];
            str[i + 1] = grid[row2][col1];
        }
    }
}

int main() {
    char key[] = "PT109";
    char message[] = "SUNKBYJAPANESEDESTROYER";
    char encrypted[strlen(message) * 2];
    char decrypted[strlen(message) * 2];
    
    prepareKey(key, strlen(key));
    formatMessage(message);
    
    printf("Original Message: %s\n", message);
    
    encrypt(message);
    printf("Encrypted Message: %s\n", message);
    
    decrypt(message);
    printf("Decrypted Message: %s\n", message);
    
    return 0;
}

