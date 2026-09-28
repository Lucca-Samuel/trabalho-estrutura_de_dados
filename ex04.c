#include <stdio.h>

int multiplicar(int a, int b) {
    printf("a = %d, b = %d\n", a, b);

    if (b == 0) {
        return 0;
    }

    return a + multiplicar(a, b - 1);
}

int main() {
    int a, b;

    scanf("%d", &a);
    scanf("%d", &b);

    printf("Resultado: %d\n", multiplicar(a, b));

    return 0;
}