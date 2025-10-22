#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo o tamanho máximo de itens
#define MAX_ITENS 10

// Estrutura que representa um item do inventário
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor de itens e contador atual
Item mochila[MAX_ITENS];
int totalItens = 0;

// Função para inserir um novo item no inventário
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novoItem;

    printf("Digite o nome do item: ");
    scanf(" %[^\n]", novoItem.nome);

    printf("Digite o tipo do item (arma, municao, cura, etc): ");
    scanf(" %[^\n]", novoItem.tipo);

    printf("Digite a quantidade do item: ");
    scanf("%d", &novoItem.quantidade);

    mochila[totalItens] = novoItem;
    totalItens++;

    printf("Item adicionado com sucesso!\n");
}

// Função para remover um item do inventário pelo nome
void removerItem() {
    if (totalItens == 0) {
        printf("Mochila vazia! Nenhum item para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("Digite o nome do item a ser removido: ");
    scanf(" %[^\n]", nomeRemover);

    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = 1;
            // Desloca os itens para preencher o espaço
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            printf("Item removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Item não encontrado.\n");
    }
}

// Função para listar todos os itens da mochila
void listarItens() {
    if (totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    printf("\nItens na mochila:\n");
    printf("========================\n");
    for (int i = 0; i < totalItens; i++) {
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
        printf("------------------------\n");
    }
}

// Função de busca sequencial por nome do item
void buscarItem() {
    if (totalItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    char nomeBuscar[30];
    printf("Digite o nome do item a ser buscado: ");
    scanf(" %[^\n]", nomeBuscar);

    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBuscar) == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item não encontrado.\n");
    }
}

// Função principal com menu interativo
int main() {
    int opcao;

    do {
        printf("\n==== Menu da Mochila ====\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
