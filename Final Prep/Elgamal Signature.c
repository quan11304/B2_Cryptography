#include <stdio.h>
#include <math.h>

int modulus(int b, int e, int m) {
    // b is base, e is exponent, m is modulus

    int result; // Return value

    if (e == 0) {
        result = 1;
    } else if (e == 1) {
        result = b % m;
    } else {
        result = b;
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
    printf("Message: x = ");
    scanf("%d",&x);

    // Private key
    int d = 4; // Chosen between 2 and p-2
    int kE = 6; // Ephemeral key, chosen from 0 to p-2, relatively prime to p
    printf("Private key: d = ");
    scanf("%d",&d);
    printf("Ephemeral key: kE = ");
    scanf("%d",&kE);

    // Public key
    printf("Public key: \n");
    int p = 13; // A large prime number
    int a = 5; // Primitive element of Galois field (?)
    printf("p = ");
    scanf("%d",&p);
    printf("a = ");
    scanf("%d",&a);


    int b = modulus(a, d, p);
    printf("b = %d\n",b);


    // Signing process
    printf("\nSigning...\n");

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


    // Verifying process
    printf("\nVerifying...\n");

    int t = modulus(b,r,p) * modulus(r,s,p);
    t %= p;
    printf("t = %d\n",t);
    if (t == modulus(a,x,p))
        printf("Valid signature.\n");
    else
        printf("***INVALID signature.***\n");
}