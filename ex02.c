#include <stdio.h>

float delta(float a, float b, float c) {
    return b * b - 4 * a * c;
}

int main() {
    float a, b, c;

    printf("Digite a, b e c: ");
    scanf("%f %f %f", &a, &b, &c);

    printf("Delta = %.2f\n", delta(a, b, c));

    return 0;
}