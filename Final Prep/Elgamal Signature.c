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

int main() {
    int p, a, b; // Public key
    // p is prime
    printf("p = ");
    scanf("%d", &p);
    printf("a = ");
    scanf("%d", &a);

    int d; // Private key
    // Chosen from 2 to p-2
    printf("d = ");
    scanf("%d", &d);

    b = modulus(a,d,p);
}