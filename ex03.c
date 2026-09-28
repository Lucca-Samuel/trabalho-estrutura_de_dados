#include <stdio.h>

void popular(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("Digite o valor %d: ", i + 1);
        scanf("%d", &vetor[i]);
    }
}

void dobrar(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        vetor[i] *= 2;
    }
}

void listar(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
}

int main() {
    int tamanho;

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tamanho);

    int vetor[tamanho];

    popular(vetor, tamanho);
    dobrar(vetor, tamanho);

    printf("Valores dobrados: ");
    listar(vetor, tamanho);

    return 0;
}