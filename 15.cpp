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

void decrypt(char ciphertext[], int key) {
    int i;
    for (i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            char decrypted_char = ((toupper(ciphertext[i]) - 'A' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
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

int main() {
    char ciphertext[] = "Zpv!tff!qjdlvujft!sfqmbdfwbmvf!obnf!jt!qvsqptfe!";
    int i, key, top_plaintexts;
    float likelihood, max_likelihood = 0;
    char plaintext[strlen(ciphertext) + 1];
    char best_plaintext[strlen(ciphertext) + 1];

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &top_plaintexts);

  
    for (key = 1; key < ALPHABET_SIZE; key++) {
        
        for (i = 0; i < strlen(ciphertext); i++) {
            if (isalpha(ciphertext[i])) {
                plaintext[i] = ((toupper(ciphertext[i]) - 'A' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
            } else {
                plaintext[i] = ciphertext[i];
            }
        }
        plaintext[i] = '\0';

        likelihood = calculate_likelihood(plaintext);

       
        if (likelihood > max_likelihood) {
            max_likelihood = likelihood;
            strcpy(best_plaintext, plaintext);
        }
    }

    printf("\nTop %d possible plaintexts in rough order of likelihood:\n", top_plaintexts);
    
    printf("1. %s (Likelihood: %.6f)\n", best_plaintext, max_likelihood);

    for (i = 2; i <= top_plaintexts; i++) {
   
        max_likelihood = 0;

        for (key = 1; key < ALPHABET_SIZE; key++) {
            for (int j = 0; j < strlen(ciphertext); j++) {
                if (isalpha(ciphertext[j])) {
                    plaintext[j] = ((toupper(ciphertext[j]) - 'A' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
                } else {
                    plaintext[j] = ciphertext[j];
                }
            }
            plaintext[i] = '\0';

            likelihood = calculate_likelihood(plaintext);

            if (likelihood > max_likelihood) {
                max_likelihood = likelihood;
                strcpy(best_plaintext, plaintext);
            }
        }

        printf("%d. %s (Likelihood: %.6f)\n", i, best_plaintext, max_likelihood);
    }

    return 0;
}

