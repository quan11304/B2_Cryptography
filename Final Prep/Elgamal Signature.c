#include <stdio.h>
#include <math.h>

int modulus(int b, int e, int m) {
    // b is base, e is exponent, m is modulus

    int result = b; // Return value

    for (int i = 1 << ((int) log2(e) - 1); i > 0; i >>= 1) {
        // Set i to 2^(length-1) and divide it by 2 every loop
        // (int) log2(e) returns the length (base 0) of the binary representation of e
        // Length (base 0, i.e. start counting from 0) = Length + 1 (in base 1)
        result *= result;
        result %= m;
        if (e & i) { // Checking if the current bit in the exponent is a 1 or not
            result *= b;
            result %= m;
        }
    }
    return result;
}

int modMulInv(int e, int m) {
    // Modular Multiplicative Inverse
    // Output d so that (e*d) % m = 1
    for (int d = 1; d < m; d++) {
        if ((e * d) % m == 1)
            return d;
    }
    return 0;
    // If e and m not being relatively prime, the inverse won't be found and set to 0
}

int main() {
    // Message
    int x = 12938;

    // Private key
    int d = 4; // Chosen between 2 and p-2
    int kE = 6; // Ephemeral key, chosen from 0 to p-2, relatively prime to p

    // Public key
    int p = 13; // A large prime number
    int a = 5; // Primitive element of Galois field (?)
    int b = modulus(a, d, p);
    printf("b = %d\n",b);

    // Modular multiplicative inverse of the ephemeral key
    int kE_1 = modMulInv(kE, p - 1);
    printf("kE_1 = %d\n",kE_1);
    if (kE_1 == 0) {
        printf("kE and (p-1) are not relatively prime. Exiting...");
        return 1;
    }

    // Signature parameters
    int r = modulus(a, kE, p);
    printf("r = %d\n",r);
    int s = ((x - d * r) * kE_1) % (p - 1);
    printf("s = %d\n",s);
}