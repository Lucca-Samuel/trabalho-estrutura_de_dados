#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

int bbr(int v[], int baixo, int alto, int chave) {
    int meio;

    while (baixo <= alto) {
        meio = (baixo + alto) / 2;

        if (v[meio] == chave)
            return meio;

        if (v[meio] < chave)
            return bbr(v, meio + 1, alto, chave);
        else
            return bbr(v, baixo, meio - 1, chave);
    }

    return -1;
}

int main() {
    int v[50];
    int chave;

    srand(time(NULL));

    // Preenche o vetor com valores de 0 a 100
    for (int i = 0; i < 50; i++) {
        v[i] = rand() % 101;
    }

    // Ordena o vetor
    sort(v, v + 50);

    // Mostra o vetor ordenado
    cout << "Vetor ordenado:\n";

    for (int i = 0; i < 50; i++) {
        cout << v[i] << " ";
    }

    cout << "\n\nDigite um valor para buscar: ";
    cin >> chave;

    int resultado = bbr(v, 0, 49, chave);

    if (resultado != -1)
        cout << "Valor encontrado na posicao: " << resultado << endl;
    else
        cout << "Valor nao encontrado." << endl;

    return 0;
}