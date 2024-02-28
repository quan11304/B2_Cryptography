#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int modulus(int m, int e, int n) {
    // m is base, e is exponent, n is modulus

    int rm = m; // Return value

    for (int i = 1 << ((int) log2(e) - 1); i > 0; i >>= 1) {
        // Set i to 2^(length-1) and divide it by 2 every loop
        // (int) log2(e) returns the length (base 0) of the binary representation of e
        // Length (base 0, i.e. start counting from 0) = Length + 1 (in base 1)
        rm *= rm;
        rm %= n;
        if (e & i) { // Checking if the current bit in the exponent is a 1 or not
            rm *= m;
            rm %= n;
        }
    }
    return rm;
}

int modMulInv(int e, int m) {
    // Output d so that (e*d) % m = 1
    for (int d = 0; d < m; d++) {
        if ((e * d) % m == 1)
            return d;
    }
    return 0;
}

int main() {
    int p, q, e, d, m, c;
    // p and q is prime
    // e is relatively prime to (p-1)(q-1)
    char choice1, choice2;

    int verify = 0;
    while (1) {
        printf("p = ");
        scanf("%d", &p);
        printf("q = ");
        scanf("%d", &q);
        fflush(stdin);

        do {
            printf("Choose encryption (e) or decryption (d) exponent: ");
            scanf("%c", &choice1);
            switch (choice1) {
                case 'e':
                case 'E':
                    printf("e = ");
                    scanf("%d", &e);
                    d = modMulInv(e, (p - 1) * (q - 1));
                    break;
                case 'd':
                case 'D':
                    printf("d = ");
                    scanf("%d", &d);
                    e = modMulInv(d, (p - 1) * (q - 1));
                    break;
                default:
                    printf("Please choose between 'e' and 'd'.");
                    verify = 1;
            }
        } while (verify);

        if (e == 0 || d == 0)
            break;
    }

    do {
        printf("Choose encryption or decryption process: ");
        scanf("%c", &choice2);
        switch (choice1) {
            case 'e':
            case 'E':
            case 'm':
            case 'M':
                printf("M = ");
                scanf("%d", &m);
                break;
            case 'd':
            case 'D':
            case 'c':
            case 'C':
                printf("d = ");
                scanf("%d", &c);
                break;
            default:
                printf("Please choose between 'e' (or 'M') and 'd' (or 'C').");
                verify = 1;
        }
    } while (verify);
}
