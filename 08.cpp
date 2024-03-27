#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void monoalphabetic_cipher(char *plaintext, char *keyword, char *ciphertext) {
    int i, j;
    char key[ALPHABET_SIZE] = {0};
    int keyword_length = strlen(keyword);
    
    for (i = 0, j = 0; i < keyword_length; i++) {
        if (!isalpha(keyword[i])) continue;
        if (!key[toupper(keyword[i]) - 'A']) {
            key[toupper(keyword[i]) - 'A'] = keyword[i];
            ciphertext[j++] = toupper(keyword[i]);
        }
    }
    
    for (i = 0; i < ALPHABET_SIZE; i++) {
        if (!key[i]) {
            key[i] = 'A' + i;
            ciphertext[j++] = key[i];
        }
    }
    ciphertext[ALPHABET_SIZE] = '\0'; 
    while (*plaintext) {
        if (isalpha(*plaintext)) {
            if (islower(*plaintext)) {
                *plaintext = tolower(key[*plaintext - 'a']);
            } else {
                *plaintext = key[*plaintext - 'A'];
            }
        }
        plaintext++;
    }
}

int main() {
    char plaintext[] = "Hello World!";
    char keyword[] = "CIPHER";
    char ciphertext[ALPHABET_SIZE + 1]; 
    monoalphabetic_cipher(plaintext, keyword, ciphertext);
    
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);
    
    return 0;
}

