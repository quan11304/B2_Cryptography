#include <stdio.h>

char x[19] = "1111101010101010101";
char y[22] = "1100110011001100110011";
char z[23] = "11100001111000011110000";
int n = 10; // Number of key bits to display

void shiftX() {
    int temp = (((int) x[13] - 48) ^ ((int) x[16] - 48)
                ^ ((int) x[17] - 48) ^ ((int) x[18] - 48)) + 48;
    // Starting from the last element, excluding the first element
    for (int j = 18; j > 0; j--)
        x[j] = x[j - 1];
    x[0] = (char) temp;
}

void shiftY() {
    int temp = (((int) y[20] - 48) ^ ((int) y[21] - 48)) + 48;
    for (int j = 21; j > 0; j--)
        y[j] = y[j - 1];
    y[0] = (char) temp;
}

void shiftZ() {
    int temp = (((int) z[7] - 48) ^ ((int) z[20] - 48)
                ^ ((int) z[21] - 48) ^ ((int) z[22] - 48)) + 48;
    for (int j = 22; j > 0; j--)
        z[j] = z[j - 1];
    z[0] = (char) temp;
}

int main() {
//    printf("Enter X (19 bits): ");
//    scanf("%s", x);
//    printf("Enter Y: ");
//    scanf("%s", y);
//    printf("Enter Z: ");
//    scanf("%s", z);
//    printf("Enter n: ");
//    scanf("%d", &n);

    int output[n];
    int x_check, y_check, z_check; // To see which segment has been shifted

    for (int i = 0; i < n; i++) {
        x_check = y_check = z_check = 0;

        // Convert from ASCII to binary
        int x18 = (int) x[18] - 48;
        int y21 = (int) y[21] - 48;
        int z22 = (int) z[22] - 48;

        // Calculate keystream bit
        output[i] = x18 ^ y21 ^ z22;

        // Shift
        if (x[8] == y[10]) {
            if (x[8] == z[10]) {
                shiftZ();
                z_check = 1;
            }
            shiftX();
            shiftY();
            x_check = y_check = 1;
        } else if (x[8] == z[10]) {
            shiftX();
            shiftZ();
            x_check = z_check = 1;
        } else if (y[10] == z[10]) {
            shiftY();
            shiftZ();
            y_check = z_check = 1;
        }

        printf("\nStep %d:\n", i + 1);
        printf("Key stream bit calculated: %d\n", output[i]);
        printf("X: %s %s\n", x, x_check == 1 ? "(Shifted)" : "");
        printf("Y: %s %s\n", y, y_check == 1 ? "(Shifted)" : "");
        printf("Z: %s %s\n", z, z_check == 1 ? "(Shifted)" : "");
    }
    printf("Keystream: ");
    for (int i = 0; i < n; i++)
        printf("%d", output[i]);
}