#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ESTRUTURAS 

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// VARIÁVEIS GLOBAIS 

#define TAM_MAX 100
Item mochilaVetor[TAM_MAX];
int qtdItensVetor = 0;

No* mochilaLista = NULL;

int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// FUNÇÕES AUXILIARES 

Item criarItem() {
    Item novo;
    printf("\nNome do item: ");
    scanf(" %[^\n]", novo.nome);
    printf("Tipo do item: ");
    scanf(" %[^\n]", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    return novo;
}

// FUNÇÕES VETOR 

void inserirItemVetor() {
    if (qtdItensVetor >= TAM_MAX) {
        printf("\nMochila cheia!\n");
        return;
    }

    mochilaVetor[qtdItensVetor++] = criarItem();
    printf("\nItem adicionado com sucesso ao vetor!\n");
}

void listarItensVetor() {
    if (qtdItensVetor == 0) {
        printf("\nMochila vazia.\n");
        return;
    }

    printf("\n--- Itens na mochila (vetor) ---\n");
    for (int i = 0; i < qtdItensVetor; i++) {
        printf("%d. %s (%s) - Quantidade: %d\n", i + 1,
               mochilaVetor[i].nome, mochilaVetor[i].tipo,
               mochilaVetor[i].quantidade);
    }
}

void removerItemVetor() {
    if (qtdItensVetor == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item a remover: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < qtdItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < qtdItensVetor - 1; j++)
                mochilaVetor[j] = mochilaVetor[j + 1];
            qtdItensVetor--;
            printf("\nItem removido com sucesso!\n");
            return;
        }
    }

    printf("\nItem não encontrado!\n");
}

void buscarSequencialVetor() {
    if (qtdItensVetor == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item a buscar: ");
    scanf(" %[^\n]", nome);

    comparacoesSequencial = 0;

    for (int i = 0; i < qtdItensVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("\nItem encontrado: %s (%s) - Quantidade: %d\n",
                   mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            printf("Comparações: %d\n", comparacoesSequencial);
            return;
        }
    }

    printf("\nItem não encontrado!\nComparações: %d\n", comparacoesSequencial);
}

void ordenarVetor() {
    for (int i = 0; i < qtdItensVetor - 1; i++) {
        for (int j = 0; j < qtdItensVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("\nItens ordenados por nome!\n");
}

void buscarBinariaVetor() {
    if (qtdItensVetor == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item a buscar (binária): ");
    scanf(" %[^\n]", nome);

    int esquerda = 0, direita = qtdItensVetor - 1;
    comparacoesBinaria = 0;

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        comparacoesBinaria++;

        int cmp = strcmp(mochilaVetor[meio].nome, nome);
        if (cmp == 0) {
            printf("\nItem encontrado: %s (%s) - Quantidade: %d\n",
                   mochilaVetor[meio].nome, mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            printf("Comparações (busca binária): %d\n", comparacoesBinaria);
            return;
        } else if (cmp < 0)
            esquerda = meio + 1;
        else
            direita = meio - 1;
    }

    printf("\nItem não encontrado!\nComparações (busca binária): %d\n", comparacoesBinaria);
}

// FUNÇÕES LISTA ENCADEADA 
void inserirItemLista() {
    No* novo = (No*)malloc(sizeof(No));
    novo->dados = criarItem();
    novo->proximo = NULL;

    if (mochilaLista == NULL)
        mochilaLista = novo;
    else {
        No* temp = mochilaLista;
        while (temp->proximo != NULL)
            temp = temp->proximo;
        temp->proximo = novo;
    }

    printf("\nItem adicionado com sucesso à lista!\n");
}

void listarItensLista() {
    if (mochilaLista == NULL) {
        printf("\nMochila vazia!\n");
        return;
    }

    printf("\n--- Itens na mochila (lista encadeada) ---\n");
    No* temp = mochilaLista;
    int i = 1;
    while (temp != NULL) {
        printf("%d. %s (%s) - Quantidade: %d\n", i++,
               temp->dados.nome, temp->dados.tipo, temp->dados.quantidade);
        temp = temp->proximo;
    }
}

void removerItemLista() {
    if (mochilaLista == NULL) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item a remover: ");
    scanf(" %[^\n]", nome);

    No* temp = mochilaLista;
    No* anterior = NULL;

    while (temp != NULL && strcmp(temp->dados.nome, nome) != 0) {
        anterior = temp;
        temp = temp->proximo;
    }

    if (temp == NULL) {
        printf("\nItem não encontrado!\n");
        return;
    }

    if (anterior == NULL)
        mochilaLista = temp->proximo;
    else
        anterior->proximo = temp->proximo;

    free(temp);
    printf("\nItem removido com sucesso!\n");
}

void buscarSequencialLista() {
    if (mochilaLista == NULL) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item a buscar: ");
    scanf(" %[^\n]", nome);

    comparacoesSequencial = 0;
    No* temp = mochilaLista;

    while (temp != NULL) {
        comparacoesSequencial++;
        if (strcmp(temp->dados.nome, nome) == 0) {
            printf("\nItem encontrado: %s (%s) - Quantidade: %d\n",
                   temp->dados.nome, temp->dados.tipo, temp->dados.quantidade);
            printf("Comparações: %d\n", comparacoesSequencial);
            return;
        }
        temp = temp->proximo;
    }

    printf("\nItem não encontrado!\nComparações: %d\n", comparacoesSequencial);
}

// MENUS 
void menuVetor() {
    int opc;
    do {
        printf("\n===== MENU MOCHILA (VETOR) =====\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar sequencial\n");
        printf("5 - Ordenar por nome\n");
        printf("6 - Buscar binária\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opc);

        clock_t inicio = clock();

        switch (opc) {
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: listarItensVetor(); break;
            case 4: buscarSequencialVetor(); break;
            case 5: ordenarVetor(); break;
            case 6: buscarBinariaVetor(); break;
        }

        clock_t fim = clock();
        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Tempo de execução: %.6f s\n", tempo);

    } while (opc != 0);
}

void menuLista() {
    int opc;
    do {
        printf("\n===== MENU MOCHILA (LISTA ENCADEADA) =====\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar sequencial\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opc);

        clock_t inicio = clock();

        switch (opc) {
            case 1: inserirItemLista(); break;
            case 2: removerItemLista(); break;
            case 3: listarItensLista(); break;
            case 4: buscarSequencialLista(); break;
        }

        clock_t fim = clock();
        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Tempo de execução: %.6f s\n", tempo);

    } while (opc != 0);
}

// PROGRAMA PRINCIPAL 

int main() {
    int opcao;

    do {
        printf("\n===== SISTEMA DE MOCHILA =====\n");
        printf("1 - Usar mochila com vetor\n");
        printf("2 - Usar mochila com lista encadeada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: menuVetor(); break;
            case 2: menuLista(); break;
            case 0: printf("\nSaindo...\n"); break;
            default: printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
