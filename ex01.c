#include <stdio.h>

int main() {
    int n, h[5] = {0};
    char conceitos[] = {'A', 'B', 'C', 'D', 'E'};
    float nota;

    printf("Insira n. de alunos: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Insira nota %d: ", i + 1);
        scanf("%f", &nota);

        if (nota >= 9) h[0]++;
        else if (nota >= 7) h[1]++;
        else if (nota >= 5) h[2]++;
        else if (nota >= 3) h[3]++;
        else if (nota >= 0) h[4]++;
    }

    printf("\nHistograma:\n");

    for (int i = 0; i < 5; i++) {
        printf("%c: ", conceitos[i]);

        for (int j = 0; j < h[i]; j++)
            printf("*");

        printf("\n");
    }

    return 0;
}