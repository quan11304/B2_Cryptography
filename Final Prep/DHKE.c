#include <stdio.h>
#include <math.h>

int modulus(int m, int e, int n) {
    // m is base, e is exponent, n is modulus

    int rm; // Return value

    if (e == 0) {
        rm = 1;
    } else if (e == 1) {
        rm = m % n;
    } else {
        rm = m;
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
    }
    return rm;
}

int main() {
    int a, b, g, p;
    printf("Shared values: \n");
    printf("Base: g = ");
    scanf("%d", &g);
    printf("Modulus: p = ");
    scanf("%d",&p);

    printf("\n");
    printf("Private keys: \n");
    printf("Alice: a = ");
    scanf("%d",&a);
    printf("Bob: b = ");
    scanf("%d",&b);

    printf("\n");
    printf("Public keys: \n");
    int A = modulus(g,a,p);
    printf("Alice: A = %d\n",A);
    int B = modulus(g,b,p);
    printf("Bob: B = %d\n",B);

    printf("\n");
    printf("Shared key: \n");
    int Ab = modulus(A,b,p);
    printf("From Alice: Ab = %d\n",Ab);
    int Ba = modulus(B,a,p);
    printf("From Bob: Ba = %d\n",Ba);

    if (Ab == Ba)
        printf("Valid Shared Keys");
    else
        printf("INVALID Shared Keys");
}
