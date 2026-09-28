#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// --- ALGORITMOS DE ORDENAÇÃO ---

// 1. Bubble Sort
void bubbleSort(int v[], int n) {
    int i, j, aux;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
}

// 2. Ordenação por Seleção (Selection Sort / orsel)
void selectionSort(int v[], int n) {
    int i, j, min, aux;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (v[j] < v[min]) {
                min = j;
            }
        }
        if (min != i) {
            aux = v[i];
            v[i] = v[min];
            v[min] = aux;
        }
    }
}

// 3. Ordenação por Inserção (Insertion Sort / ordins)
void insertionSort(int v[], int n) {
    int i, j, chave;
    for (i = 1; i < n; i++) {
        chave = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > chave) {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = chave;
    }
}

// 4. Quick Sort (ordquick)
void quickSort(int v[], int inicio, int fim) {
    if (inicio < fim) {
        int pivo = v[fim];
        int i = (inicio - 1);
        int j, aux;

        for (j = inicio; j < fim; j++) {
            if (v[j] <= pivo) {
                i++;
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
        aux = v[i + 1];
        v[i + 1] = v[fim];
        v[fim] = aux;

        int p = i + 1;

        quickSort(v, inicio, p - 1);
        quickSort(v, p + 1, fim);
    }
}

// 5. Merge Sort (ordmerg)
void intercala(int v[], int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = v[inicio + i];
    for (int j = 0; j < n2; j++) R[j] = v[meio + 1 + j];

    int i = 0, j = 0, k = inicio;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            v[k] = L[i];
            i++;
        } else {
            v[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        v[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        v[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int v[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        mergeSort(v, inicio, meio);
        mergeSort(v, meio + 1, fim);
        intercala(v, inicio, meio, fim);
    }
}

// --- FUNÇÃO AUXILIAR DE MEDIÇÃO DE TEMPO ---

double medirTempo(int v[], int v_origem[], int n, int algoritmo) {
    // Restaura o vetor original para garantir que a comparação seja justa
    memcpy(v, v_origem, n * sizeof(int));

    clock_t inicio, fim;

    inicio = clock();
    switch (algoritmo) {
        case 1: bubbleSort(v, n); break;
        case 2: selectionSort(v, n); break;
        case 3: insertionSort(v, n); break;
        case 4: quickSort(v, 0, n - 1); break;
        case 5: mergeSort(v, 0, n - 1); break;
    }
    fim = clock();

    // Retorna o tempo em milissegundos
    return ((double)(fim - inicio) / (double)CLOCKS_PER_SEC) * 1000.0;
}

int main() {
    srand(time(NULL));

    int tamanhos[] = {100, 1000, 10000, 100000};
    int total_tamanhos = 4;

    for (int t = 0; t < total_tamanhos; t++) {
        int n = tamanhos[t];

        // Alocação dinâmica para suportar vetores grandes (ex: 100.000 elementos)
        int *v_original = (int *)malloc(n * sizeof(int));
        int *v_trabalho = (int *)malloc(n * sizeof(int));

        // Preenche o vetor com números aleatórios
        for (int i = 0; i < n; i++) {
            v_original[i] = rand() % 100000;
        }

        printf("=========================================\n");
        printf("  TEMPO DE EXECUÇÃO PARA N = %d\n", n);
        printf("=========================================\n");

        double t_bubble = medirTempo(v_trabalho, v_original, n, 1);
        printf("Tempo Gasto (bubble):   %lf milisegundos\n", t_bubble);

        double t_orsel = medirTempo(v_trabalho, v_original, n, 2);
        printf("Tempo Gasto (orsel):    %lf milisegundos\n", t_orsel);

        double t_ordins = medirTempo(v_trabalho, v_original, n, 3);
        printf("Tempo Gasto (ordins):   %lf milisegundos\n", t_ordins);

        double t_ordquick = medirTempo(v_trabalho, v_original, n, 4);
        printf("Tempo Gasto (ordquick): %lf milisegundos\n", t_ordquick);

        double t_ordmerg = medirTempo(v_trabalho, v_original, n, 5);
        printf("Tempo Gasto (ordmerg):  %lf milisegundos\n\n", t_ordmerg);

        free(v_original);
        free(v_trabalho);
    }

    return 0;
}