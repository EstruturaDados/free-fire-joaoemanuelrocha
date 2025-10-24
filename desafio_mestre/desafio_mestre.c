#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// Estrutura do componente
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// FUNÇÕES DE APOIO

// Exibe a lista de componentes
void mostrarComponentes(Componente v[], int n) {
    printf("\n--- LISTA DE COMPONENTES ---\n");
    for (int i = 0; i < n; i++) {
        printf("Nome: %-20s | Tipo: %-15s | Prioridade: %d\n",
               v[i].nome, v[i].tipo, v[i].prioridade);
    }
    printf("-----------------------------\n");
}

// ALGORITMOS DE ORDENAÇÃO
// Bubble Sort (por nome)
int bubbleSortNome(Componente v[], int n) {
    int comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                Componente temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
    return comparacoes;
}

// Insertion Sort (por tipo)
int insertionSortTipo(Componente v[], int n) {
    int comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;
        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
        comparacoes++;
    }
    return comparacoes;
}

// Selection Sort (por prioridade)
int selectionSortPrioridade(Componente v[], int n) {
    int comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade < v[min].prioridade)
                min = j;
        }
        if (min != i) {
            Componente temp = v[i];
            v[i] = v[min];
            v[min] = temp;
        }
    }
    return comparacoes;
}

// BUSCA BINÁRIA 

int buscaBinariaPorNome(Componente v[], int n, char chave[]) {
    int esquerda = 0, direita = n - 1;
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        int cmp = strcmp(v[meio].nome, chave);
        if (cmp == 0) return meio;
        else if (cmp < 0) esquerda = meio + 1;
        else direita = meio - 1;
    }
    return -1;
}

// MEDIÇÃO DE TEMPO
double medirTempo(int (*algoritmo)(Componente[], int), Componente v[], int n, int *comparacoes) {
    clock_t inicio = clock();
    *comparacoes = algoritmo(v, n);
    clock_t fim = clock();
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

// FUNÇÃO PRINCIPAL

int main() {
    Componente componentes[MAX_COMPONENTES];
    int n, opcao;
    char nomeBusca[30];
    int comparacoes;
    double tempo;

    printf("=== DESAFIO FINAL: Torre de Resgate ===\n");
    printf("Quantos componentes deseja cadastrar");
    scanf("%d", &n);
    getchar(); // limpar buffer

    for (int i = 0; i < n; i++) {
        printf("\nComponente %d:\n", i + 1);
        printf("Nome: ");
        fgets(componentes[i].nome, sizeof(componentes[i].nome), stdin);
        componentes[i].nome[strcspn(componentes[i].nome, "\n")] = '\0';
        printf("Tipo: ");
        fgets(componentes[i].tipo, sizeof(componentes[i].tipo), stdin);
        componentes[i].tipo[strcspn(componentes[i].tipo, "\n")] = '\0';
        printf("Prioridade (1 a 10): ");
        scanf("%d", &componentes[i].prioridade);
        getchar();
    }

    do {
        printf("\n=== MENU DE ESTRATÉGIAS ===\n");
        printf("1 - Ordenar por nome (Bubble Sort)\n");
        printf("2 - Ordenar por tipo (Insertion Sort)\n");
        printf("3 - Ordenar por prioridade (Selection Sort)\n");
        printf("4 - Buscar componente-chave (após ordenação por nome)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                tempo = medirTempo(bubbleSortNome, componentes, n, &comparacoes);
                printf("\nOrdenado por nome (Bubble Sort).\n");
                mostrarComponentes(componentes, n);
                printf("Comparações: %d | Tempo: %.6f s\n", comparacoes, tempo);
                break;

            case 2:
                tempo = medirTempo(insertionSortTipo, componentes, n, &comparacoes);
                printf("\nOrdenado por tipo (Insertion Sort).\n");
                mostrarComponentes(componentes, n);
                printf("Comparações: %d | Tempo: %.6f s\n", comparacoes, tempo);
                break;

            case 3:
                tempo = medirTempo(selectionSortPrioridade, componentes, n, &comparacoes);
                printf("\nOrdenado por prioridade (Selection Sort).\n");
                mostrarComponentes(componentes, n);
                printf("Comparações: %d | Tempo: %.6f s\n", comparacoes, tempo);
                break;

            case 4:
                printf("\nDigite o nome do componente-chave: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                {
                    int pos = buscaBinariaPorNome(componentes, n, nomeBusca);
                    if (pos != -1) {
                        printf("\n✅ Componente encontrado!\n");
                        printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
                               componentes[pos].nome,
                               componentes[pos].tipo,
                               componentes[pos].prioridade);
                    } else {
                        printf("\n❌ Componente não encontrado.\n");
                    }
                }
                break;

            case 0:
                printf("\nSaindo do sistema... Missão concluída!\n");
                break;

            default:
                printf("\nOpção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
