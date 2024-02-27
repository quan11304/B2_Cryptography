#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int modulus(int m, int e, int n) {
    // m is base, e is exponent, n is modulus

    int rm = m; // Return value

    for (int i = 1 << ((int) log2(e) - 1); i > 0; i >>= 1) {
        // Set i to 2^(length-1) and divide it by 2 every loop
        // (int) log2(e) returns the length (base 0) of e in binary
        // Length (Base 0, i.e. start counting from 0) = Length + 1 (Base 1)
        rm *= rm;
        rm %= n;
        if (e & i) { // Checking if the current bit in the exponent is a 1 or not
            rm *= m;
            rm %= n;
        }
    }
    return rm;
}

int main() {
    int p, q, e, d, m, c;
    // p and q is prime
    // e is relatively prime to (p-1)(q-1)
    char choice1, choice2;
    printf("p = ");
    scanf("%d", &p);
    printf("q = ");
    scanf("%d", &q);
    fflush(stdin);
    int verify = 0;
    do {
        printf("Choose encryption (e) or decryption (d) exponent: ");
        scanf("%c", choice1);
        printf("%c", choice1);
        switch (choice1) {
            case 'e':
            case 'E':
                printf("e = ");
                break;
            case 'd':
            case 'D':
                printf("d = ");
                break;
            default:
                verify = 1;
        }
    } while (verify);
    printf("p = ");
    scanf("%d", &p);
    printf("p = ");
    scanf("%d", &p);
    printf("p = ");
    scanf("%d", &p);
}
