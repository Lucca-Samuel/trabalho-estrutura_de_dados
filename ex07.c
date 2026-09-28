#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_DEPTOS 8
#define TAM_NOME 100

// Estrutura para armazenar os dados de cada funcionário
typedef struct {
    char nome[TAM_NOME];
    int idade;
    char sexo; // 'F' ou 'M'
    int tempo_casa;
    double salario;
    int departamento; // Valores de 1 a 8
} Funcionario;

// Função auxiliar para converter caractere para maiúsculo
char paraMaiusculo(char c) {
    return (char)toupper((unsigned char)c);
}

// Função auxiliar para remover o \n do final da string lida via fgets
void limparQuebraLinha(char *str) {
    size_t tam = strlen(str);
    if (tam > 0 && str[tam - 1] == '\n') {
        str[tam - 1] = '\0';
    }
}

// --- FUNÇÕES DE CADA OPERAÇÃO ---

// a) Procurar no cadastro e informar dados do funcionário por nome
void buscarPorNome(Funcionario vet[], int n) {
    char nome_busca[TAM_NOME];
    int encontrado = 0;

    printf("\n--- a) BUSCAR FUNCIONÁRIO POR NOME ---\n");
    printf("Digite o nome do funcionário: ");
    getchar(); // Limpa o buffer do teclado
    fgets(nome_busca, TAM_NOME, stdin);
    limparQuebraLinha(nome_busca);

    for (int i = 0; i < n; i++) {
        if (strcasecmp(vet[i].nome, nome_busca) == 0) { // Comparação case-insensitive
            printf("\nFuncionario encontrado:\n");
            printf("Nome: %s\n", vet[i].nome);
            printf("Idade: %d anos\n", vet[i].idade);
            printf("Sexo: %c\n", vet[i].sexo);
            printf("Tempo de casa: %d anos\n", vet[i].tempo_casa);
            printf("Salário: R$ %.2f\n", vet[i].salario);
            printf("Departamento: %d\n", vet[i].departamento);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Funcionário com o nome '%s' não foi encontrado.\n", nome_busca);
    }
}

// b) Informar o número de funcionários de determinado departamento
void contarPorDepartamento(Funcionario vet[], int n) {
    int depto, qtd = 0;

    printf("\n--- b) QTD. DE FUNCIONÁRIOS POR DEPARTAMENTO ---\n");
    printf("Informe o número do departamento (1 a %d): ", NUM_DEPTOS);
    scanf("%d", &depto);

    if (depto < 1 || depto > NUM_DEPTOS) {
        printf("Departamento inválido!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        if (vet[i].departamento == depto) {
            qtd++;
        }
    }

    printf("O departamento %d possui %d funcionário(s).\n", depto, qtd);
}

// c) Número de funcionários do sexo feminino
void contarFeminino(Funcionario vet[], int n) {
    int qtd = 0;

    for (int i = 0; i < n; i++) {
        if (vet[i].sexo == 'F') {
            qtd++;
        }
    }

    printf("\n--- c) FUNCIONÁRIOS DO SEXO FEMININO ---\n");
    printf("Total de funcionários do sexo feminino: %d\n", qtd);
}

// d) Exibir dados dos funcionários com menor e maior tempo de casa
void maiorEMenorTempoCasa(Funcionario vet[], int n) {
    if (n == 0) return;

    int idx_menor = 0;
    int idx_maior = 0;

    for (int i = 1; i < n; i++) {
        if (vet[i].tempo_casa < vet[idx_menor].tempo_casa) {
            idx_menor = i;
        }
        if (vet[i].tempo_casa > vet[idx_maior].tempo_casa) {
            idx_maior = i;
        }
    }

    printf("\n--- d) MENOR E MAIOR TEMPO DE CASA ---\n");
    printf(">> Menor tempo de casa (%d ano(s)):\n", vet[idx_menor].tempo_casa);
    printf("   Nome: %s | Depto: %d | Idade: %d\n", vet[idx_menor].nome, vet[idx_menor].departamento, vet[idx_menor].idade);

    printf(">> Maior tempo de casa (%d ano(s)):\n", vet[idx_maior].tempo_casa);
    printf("   Nome: %s | Depto: %d | Idade: %d\n", vet[idx_maior].nome, vet[idx_maior].departamento, vet[idx_maior].idade);
}

// e) Exibir o salário médio, por departamento
void salarioMedioPorDepartamento(Funcionario vet[], int n) {
    double soma_salario[NUM_DEPTOS] = {0.0};
    int qtd[NUM_DEPTOS] = {0};

    for (int i = 0; i < n; i++) {
        int d = vet[i].departamento - 1; // Ajusta índice (1-8 para 0-7)
        soma_salario[d] += vet[i].salario;
        qtd[d]++;
    }

    printf("\n--- e) SALÁRIO MÉDIO POR DEPARTAMENTO ---\n");
    for (int i = 0; i < NUM_DEPTOS; i++) {
        if (qtd[i] > 0) {
            printf("Departamento %d: R$ %.2f\n", i + 1, soma_salario[i] / qtd[i]);
        } else {
            printf("Departamento %d: Nenhum funcionário cadastrado.\n", i + 1);
        }
    }
}

// f) Exibir a idade média, por departamento
void idadeMediaPorDepartamento(Funcionario vet[], int n) {
    int soma_idade[NUM_DEPTOS] = {0};
    int qtd[NUM_DEPTOS] = {0};

    for (int i = 0; i < n; i++) {
        int d = vet[i].departamento - 1;
        soma_idade[d] += vet[i].idade;
        qtd[d]++;
    }

    printf("\n--- f) IDADE MÉDIA POR DEPARTAMENTO ---\n");
    for (int i = 0; i < NUM_DEPTOS; i++) {
        if (qtd[i] > 0) {
            printf("Departamento %d: %.1f anos\n", i + 1, (double)soma_idade[i] / qtd[i]);
        } else {
            printf("Departamento %d: Nenhum funcionário cadastrado.\n", i + 1);
        }
    }
}

// g) Exibir número de masc. e fem. com idade entre 29 e 35 anos
void contarPorSexoEFaixaEtaria(Funcionario vet[], int n) {
    int fem = 0, masc = 0;

    for (int i = 0; i < n; i++) {
        if (vet[i].idade >= 29 && vet[i].idade <= 35) {
            if (vet[i].sexo == 'F') fem++;
            else if (vet[i].sexo == 'M') masc++;
        }
    }

    printf("\n--- g) FUNCIONÁRIOS ENTRE 29 E 35 ANOS ---\n");
    printf("Feminino:  %d funcionária(s)\n", fem);
    printf("Masculino: %d funcionário(s)\n", masc);
}

int main() {
    int n;

    printf("===================================================\n");
    printf("  CADASTRO DE FUNCIONÁRIOS DA EMPRESA (8 DEPTOS)\n");
    printf("===================================================\n");
    printf("Informe a quantidade total de funcionários: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Quantidade inválida!\n");
        return 0;
    }

    // Alocação dinâmica para o número de funcionários
    Funcionario *cadastro = (Funcionario *)malloc(n * sizeof(Funcionario));

    // Leitura dos dados
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastro do Funcionário %d ---\n", i + 1);
        
        printf("Nome: ");
        getchar(); // Limpa o buffer do teclado
        fgets(cadastro[i].nome, TAM_NOME, stdin);
        limparQuebraLinha(cadastro[i].nome);

        printf("Idade: ");
        scanf("%d", &cadastro[i].idade);

        do {
            printf("Sexo (F/M): ");
            scanf(" %c", &cadastro[i].sexo);
            cadastro[i].sexo = paraMaiusculo(cadastro[i].sexo);
        } while (cadastro[i].sexo != 'F' && cadastro[i].sexo != 'M');

        printf("Tempo de casa (em anos): ");
        scanf("%d", &cadastro[i].tempo_casa);

        printf("Salário (R$): ");
        scanf("%lf", &cadastro[i].salario);

        do {
            printf("Departamento (1 a %d): ", NUM_DEPTOS);
            scanf("%d", &cadastro[i].departamento);
        } while (cadastro[i].departamento < 1 || cadastro[i].departamento > NUM_DEPTOS);
    }

    // Execução dos itens a-g
    buscarPorNome(cadastro, n);
    contarPorDepartamento(cadastro, n);
    contarFeminino(cadastro, n);
    maiorEMenorTempoCasa(cadastro, n);
    salarioMedioPorDepartamento(cadastro, n);
    idadeMediaPorDepartamento(cadastro, n);
    contarPorSexoEFaixaEtaria(cadastro, n);

    // Liberação da memória alocada
    free(cadastro);

    return 0;
}