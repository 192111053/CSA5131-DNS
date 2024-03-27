#include <stdio.h>
#include <string.h>
#include <ctype.h>

void caesarCipher(char *message, int shift);

int main() {
    char message[100];
    int shift, i;

    printf("Enter a message to encrypt: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter the shift value (0 to 25): ");
    scanf("%d", &shift);
    shift = shift % 26;

    caesarCipher(message, shift);

    printf("Encrypted message: %s\n", message);

    return 0;
}

void caesarCipher(char *message, int shift) {
    int i;
    for (i = 0; i < strlen(message); i++) {
        if (isalpha(message[i])) {
            char base = isupper(message[i]) ? 'A' : 'a';
            message[i] = base + (message[i] - base + shift) % 26;
        }
    }
}

