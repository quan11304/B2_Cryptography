#include <stdio.h>

char x[19] = "1111101010101010101";
char y[22] = "1100110011001100110011";
char z[23] = "11100001111000011110000";
int n = 10;

int shiftX() {
    int temp = ((int) x[13] - 48) ^ ((int) x[16] - 48)
               ^ ((int) x[17] - 48) ^ ((int) x[18] - 48);
    // Starting from the last element, excluding the first element
    for (int j = 18; j > 0; j--)
        x[j] = x[j - 1];
    x[0] = (char) temp;
}
int shiftY() {
    int temp = ((int) y[20] - 48) ^ ((int) y[21] - 48);
    for (int j = 21; j > 0; j--)
        y[j] = y[j - 1];
    y[0] = (char) temp;
}
int shiftZ() {
    int temp = ((int) z[7] - 48) ^ ((int) z[20] - 48)
               ^ ((int) z[21] - 48) ^ ((int) z[22] - 48);
    for (int j = 22; j > 0; j--)
        z[j] = z[j - 1];
    z[0] = (char) temp;
}

int main() {


//	printf("Enter X (19 bits): ");
//	scanf("%s", x);
//	printf("Enter Y: ");
//	scanf("%s", y);
//	printf("Enter Z: ");
//	scanf("%s", z);
//	printf("Enter n: ");
//	scanf("%d",&n);

    printf("Keystream: ");
    for (int i = 1; i <= n; i++) {
        // Calculate keystream bit
        int x18 = (int) x[18] - 48;
        int y21 = (int) y[21] - 48;
        int z22 = (int) z[22] - 48;
        printf("%d", x18 ^ y21 ^ z22);

        // Shift
        if (x[8] == y[10]) {
            shiftX();
            shiftY();
            if (x[8] == z[10])
                shiftZ();
        }
        else if (x[8] == z[10]) {
            shiftX();
            shiftZ();
        }
        else if (y[10] == z[10]) {
            shiftY();
            shiftZ();
        }
    }
}