#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

const float english_letter_frequency[ALPHABET_SIZE] = {
    0.0817, 0.0149, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202,
    0.0609, 0.0697, 0.0015, 0.0077, 0.0402, 0.0241, 0.0675,
    0.0751, 0.0193, 0.0009, 0.0599, 0.0633, 0.0906, 0.0276,
    0.0098, 0.0236, 0.0015, 0.0197, 0.0007
};

void decrypt(char ciphertext[], char key[]) {
    int i;
    for (i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            char decrypted_char;
            if (isupper(ciphertext[i])) {
                decrypted_char = key[ciphertext[i] - 'A'];
            } else {
                decrypted_char = tolower(key[ciphertext[i] - 'a']);
            }
            printf("%c", decrypted_char);
        } else {
            printf("%c", ciphertext[i]);
        }
    }
    printf("\n");
}

float calculate_likelihood(char plaintext[]) {
    float likelihood = 1.0;
    int i, count[ALPHABET_SIZE] = {0}, length = 0;

    for (i = 0; i < strlen(plaintext); i++) {
        if (isalpha(plaintext[i])) {
            count[toupper(plaintext[i]) - 'A']++;
            length++;
        }
    }

    for (i = 0; i < ALPHABET_SIZE; i++) {
        likelihood *= (float)count[i] / length * english_letter_frequency[i];
    }

    return likelihood;
}

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void generate_permutations(char key[], int start, int end, char ciphertext[], float *max_likelihood, char *best_key) {
    int i;
    if (start == end) {
      
        char plaintext[strlen(ciphertext) + 1];
        for (i = 0; i < strlen(ciphertext); i++) {
            if (isalpha(ciphertext[i])) {
                char decrypted_char;
                if (isupper(ciphertext[i])) {
                    decrypted_char = key[ciphertext[i] - 'A'];
                } else {
                    decrypted_char = tolower(key[ciphertext[i] - 'a']);
                }
                plaintext[i] = decrypted_char;
            } else {
                plaintext[i] = ciphertext[i];
            }
        }
        plaintext[i] = '\0';

        float likelihood = calculate_likelihood(plaintext);

        if (likelihood > *max_likelihood) {
            *max_likelihood = likelihood;
            strcpy(best_key, key);
        }
    } else {
        for (i = start; i <= end; i++) {
            swap(&key[start], &key[i]);
            generate_permutations(key, start + 1, end, ciphertext, max_likelihood, best_key);
            swap(&key[start], &key[i]); 
        }
    }
}

int main() {
    char ciphertext[] = "Zpv!tff!qjdlvujft!sfqmbdfwbmvf!obnf!jt!qvsqptfe!";
    char key[ALPHABET_SIZE];
    char plaintext[strlen(ciphertext) + 1];
    char best_key[ALPHABET_SIZE];
    float likelihood, max_likelihood = 0;
    int i, top_plaintexts;

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &top_plaintexts);

    for (i = 0; i < ALPHABET_SIZE; i++) {
        key[i] = 'A' + i;
    }

    generate_permutations(key, 0, ALPHABET_SIZE - 1, ciphertext, &max_likelihood, best_key);

    printf("\nTop %d possible plaintexts in rough order of likelihood:\n", top_plaintexts);
   
    printf("1. ");
    decrypt(ciphertext, best_key);

    return 0;
}

