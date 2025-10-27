#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Struct que representa um item do inventário
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Variáveis globais
Item mochila[MAX_ITENS];
int totalItens = 0;

// ====== Protótipos das funções ======
void exibirMenu();
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
int buscaBinaria(char nomeBusca[]);

// ====== Função principal ======
int main() {
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;
            case 2:
                removerItem();
                listarItens();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("\nSaindo do sistema de inventário...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

// ====== Implementações das funções ======
void exibirMenu() {
    printf("\n========================================\n");
    printf("  MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
    printf("========================================\n");
    printf("Itens na Mochila: %d/%d\n", totalItens, MAX_ITENS);
    printf("\nMenu de Opções:\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("4. Buscar item\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

// ====== Inserção ordenada na lista vetorial ======
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\nMochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novoItem;

    printf("\nCadastro de novo item:\n");
    printf("Digite o nome do item: ");
    scanf(" %[^\n]", novoItem.nome);

    printf("Digite o tipo do item (ex: arma, municao, cura): ");
    scanf(" %[^\n]", novoItem.tipo);

    printf("Digite a quantidade do item: ");
    scanf("%d", &novoItem.quantidade);

    // Encontrar posição correta (ordem alfabética)
    int i = totalItens - 1;
    while (i >= 0 && strcmp(novoItem.nome, mochila[i].nome) < 0) {
        mochila[i + 1] = mochila[i]; // desloca para a direita
        i--;
    }

    // Inserir o novo item na posição correta
    mochila[i + 1] = novoItem;
    totalItens++;

    printf("Item \"%s\" adicionado com sucesso!\n", novoItem.nome);
}

// ====== Remoção de item ======
void removerItem() {
    char nomeRemover[30];
    printf("\nRemover item:\n");
    printf("Digite o nome do item a ser removido: ");
    scanf(" %[^\n]", nomeRemover);

    int pos = buscaBinaria(nomeRemover);

    if (pos == -1) {
        printf("Item \"%s\" não encontrado na mochila.\n", nomeRemover);
        return;
    }

    // Desloca os itens restantes
    for (int j = pos; j < totalItens - 1; j++) {
        mochila[j] = mochila[j + 1];
    }

    totalItens--;
    printf("Item \"%s\" removido com sucesso!\n", nomeRemover);
}

// ====== Listagem ======
void listarItens() {
    printf("\nItens na mochila:\n");

    if (totalItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    printf("%-20s | %-15s | %s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < totalItens; i++) {
        printf("%-20s | %-15s | %d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }

    printf("--------------------------------------------------------\n");
}

// ====== Busca binária por nome ======
int buscaBinaria(char nomeBusca[]) {
    int inicio = 0, fim = totalItens - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(nomeBusca, mochila[meio].nome);

        if (cmp == 0) {
            return meio; // encontrado
        } else if (cmp < 0) {
            fim = meio - 1; // busca na metade esquerda
        } else {
            inicio = meio + 1; // busca na metade direita
        }
    }

    return -1; // não encontrado
}

// ====== Buscar item usando busca binária ======
void buscarItem() {
    char nomeBusca[30];
    printf("\nBuscar item:\n");
    printf("Digite o nome do item que deseja buscar: ");
    scanf(" %[^\n]", nomeBusca);

    int pos = buscaBinaria(nomeBusca);

    if (pos == -1) {
        printf("Item \"%s\" não encontrado na mochila.\n", nomeBusca);
        return;
    }

    printf("\nItem encontrado:\n");
    printf("%-20s | %-15s | %s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("--------------------------------------------------------\n");
    printf("%-20s | %-15s | %d\n",
           mochila[pos].nome,
           mochila[pos].tipo,
           mochila[pos].quantidade);
    printf("--------------------------------------------------------\n");
}
