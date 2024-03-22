#include <stdio.h>
#include <math.h>

int main() {
    int x, e, m;
    printf("Input x (Base): ");
    scanf("%d", &x);
    printf("Input e (Exponent): ");
    scanf("%d", &e);
    printf("Input m (Modulus): ");
    scanf("%d", &m);

    int rx;  // Return value

    if (e == 0) {
        rx = 1;
    } else if (e == 1) {
        rx = x % m;
    } else {
        rx = x;
        for (int i = 1 << ((int) log2(e) - 1); i > 0; i >>= 1) {
            // Set i to 2^(length-1) and divide it by 2 every loop
            // (int) log2(e) returns the length (base 0) of e in binary
            // Length (Base 0, i.e. start counting from 0) = Length + 1 (Base 1)
            rx *= rx;
            rx %= m;
            if (e & i) { // Checking if the current bit in the exponent is a 1 or not
                rx *= x;
                rx %= m;
            }
        }
    }
    printf("%d", rx);
}
