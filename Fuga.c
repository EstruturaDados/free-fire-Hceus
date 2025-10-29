#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 10

// ==========================
// Estrutura principal
// ==========================
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
    int quantidade;
} Componente;

// ==========================
// Protótipos de função
// ==========================
void exibirMenu(int total);
void adicionarComponente(Componente componentes[], int *total);
void removerComponente(Componente componentes[], int *total);
void listarComponentes(Componente componentes[], int total);
void organizarMochila(Componente componentes[], int total, int *ordenadoPorNome);
void bubbleSortNome(Componente componentes[], int total);
void insertionSortTipo(Componente componentes[], int total);
void selectionSortPrioridade(Componente componentes[], int total);
int buscaBinariaPorNome(Componente componentes[], int total, char nomeBusca[]);
void buscarComponente(Componente mochila[], int total, int ordenadoPorNome);

// ==========================
// Função principal
// ==========================
int main() {
    Componente mochila[MAX_COMPONENTES];
    int total = 0;
    int opcao;
    int ordenadoPorNome = 0; // 1 se estiver ordenado por nome

    do {
        exibirMenu(total);
        scanf("%d", &opcao);
        getchar(); // limpa buffer

        switch (opcao) {
            case 1:
                adicionarComponente(mochila, &total);
                ordenadoPorNome = 0;
                break;

            case 2:
                removerComponente(mochila, &total);
                ordenadoPorNome = 0;
                break;

            case 3:
                listarComponentes(mochila, total);
                break;

            case 4:
                organizarMochila(mochila, total, &ordenadoPorNome);
                break;

            case 5:
                buscarComponente(mochila, total, ordenadoPorNome);
                break;

            case 6:
                printf("\n ATIVANDO TORRE DE FUGA... Boa sorte, sobrevivente!\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 6);

    return 0;
}

// ==========================
// Menus e Funções principais
// ==========================

void exibirMenu(int total) {
    printf("\n===========================================\n");
    printf("   MOCHILA DE SOBREVIVÊNCIA - TORRE DE FUGA\n");
    printf("===========================================\n");
    printf("Itens armazenados: %d/%d\n", total, MAX_COMPONENTES);
    printf("\n1. Adicionar componente\n");
    printf("2. Remover componente\n");
    printf("3. Listar componentes\n");
    printf("4. Organizar mochila (ordenar componentes)\n");
    printf("5. Busca binária por componente-chave\n");
    printf("6. ATIVAR TORRE DE FUGA (SAIR)\n");
    printf("Escolha uma opção: ");
}

void adicionarComponente(Componente componentes[], int *total) {
    if (*total >= MAX_COMPONENTES) {
        printf("\n Mochila cheia! Não é possível adicionar mais componentes.\n");
        return;
    }

    printf("\n--- Adicionando novo componente (%d/%d) ---\n", *total + 1, MAX_COMPONENTES);

    printf("Nome: ");
    fgets(componentes[*total].nome, sizeof(componentes[*total].nome), stdin);
    componentes[*total].nome[strcspn(componentes[*total].nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(componentes[*total].tipo, sizeof(componentes[*total].tipo), stdin);
    componentes[*total].tipo[strcspn(componentes[*total].tipo, "\n")] = '\0';

    do {
        printf("Prioridade (1 a 5) [5 = mais alta]: ");
        scanf("%d", &componentes[*total].prioridade);
        getchar();
    } while (componentes[*total].prioridade < 1 || componentes[*total].prioridade > 5);

    printf("Quantidade: ");
    scanf("%d", &componentes[*total].quantidade);
    getchar();

    (*total)++;

    printf(" Componente adicionado à mochila!\n");
}

void removerComponente(Componente componentes[], int *total) {
    if (*total == 0) {
        printf("\n Mochila vazia! Nenhum componente para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do componente que deseja remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int encontrado = 0;

    for (int i = 0; i < *total; i++) {
        if (strcmp(componentes[i].nome, nomeRemover) == 0) {
            encontrado = 1;
            for (int j = i; j < *total - 1; j++) {
                componentes[j] = componentes[j + 1];
            }
            (*total)--;
            printf("  Componente \"%s\" removido da mochila.\n", nomeRemover);
            break;
        }
    }

    if (!encontrado) {
        printf(" Componente \"%s\" não encontrado na mochila.\n", nomeRemover);
    }
}

void listarComponentes(Componente componentes[], int total) {
    if (total == 0) {
        printf("\n Mochila vazia.\n");
        return;
    }

    printf("\n%-25s | %-15s | %-10s | %-10s\n", "NOME", "TIPO", "PRIORIDADE", "QUANTIDADE");
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < total; i++) {
        printf("%-25s | %-15s | %-10d | %-10d\n",
               componentes[i].nome,
               componentes[i].tipo,
               componentes[i].prioridade,
               componentes[i].quantidade);
    }
    printf("--------------------------------------------------------------------------\n");
}

// ==========================
// Submenu de organização
// ==========================

void organizarMochila(Componente componentes[], int total, int *ordenadoPorNome) {
    if (total == 0) {
        printf("\n Mochila vazia! Adicione componentes primeiro.\n");
        return;
    }

    int opcao;
    printf("\n=============================\n");
    printf("     ORGANIZAR MOCHILA \n");
    printf("=============================\n");
    printf("1. Ordenar por nome (Bubble Sort)\n");
    printf("2. Ordenar por tipo (Insertion Sort)\n");
    printf("3. Ordenar por prioridade (Selection Sort)\n");
    printf("4. Voltar ao menu principal\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
        case 1:
            bubbleSortNome(componentes, total);
            *ordenadoPorNome = 1;
            break;

        case 2:
            insertionSortTipo(componentes, total);
            *ordenadoPorNome = 0;
            break;

        case 3:
            selectionSortPrioridade(componentes, total);
            *ordenadoPorNome = 0;
            break;

        case 4:
            printf("\n↩  Retornando ao menu principal...\n");
            return;

        default:
            printf("\nOpção inválida! Tente novamente.\n");
            return;
    }

    listarComponentes(componentes, total);
    printf("\n Retornando ao menu principal...\n");
}

// ==========================
// Ordenações com medição de desempenho
// ==========================

void bubbleSortNome(Componente componentes[], int total) {
    long comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            comparacoes++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                Componente temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
            }
        }
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n[BUBBLE SORT - NOME]\nComparações: %ld\nTempo de execução: %.6f segundos\n", comparacoes, tempo);
}

void insertionSortTipo(Componente componentes[], int total) {
    long comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 1; i < total; i++) {
        Componente chave = componentes[i];
        int j = i - 1;

        while (j >= 0 && (++comparacoes && strcmp(chave.tipo, componentes[j].tipo) < 0)) {
            componentes[j + 1] = componentes[j];
            j--;
        }
        componentes[j + 1] = chave;
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n[INSERTION SORT - TIPO]\nComparações: %ld\nTempo de execução: %.6f segundos\n", comparacoes, tempo);
}

void selectionSortPrioridade(Componente componentes[], int total) {
    long comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 0; i < total - 1; i++) {
        int max = i;
        for (int j = i + 1; j < total; j++) {
            comparacoes++;
            if (componentes[j].prioridade > componentes[max].prioridade)
                max = j;
        }
        if (max != i) {
            Componente temp = componentes[i];
            componentes[i] = componentes[max];
            componentes[max] = temp;
        }
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n[SELECTION SORT - PRIORIDADE]\nComparações: %ld\nTempo de execução: %.6f segundos\n", comparacoes, tempo);
}


int buscaBinariaPorNome(Componente componentes[], int total, char nomeBusca[]) {
    int inicio = 0, fim = total - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(nomeBusca, componentes[meio].nome);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }
    return -1;
}


void buscarComponente(Componente mochila[], int total, int ordenadoPorNome) {
    if (total == 0) {
        printf("\n Mochila vazia! Adicione componentes primeiro.\n");
        return;
    }

    if (!ordenadoPorNome) {
        printf("\n A busca binária só pode ser feita se a mochila estiver ordenada por NOME.\n");
        printf("   Use a opção 4 e escolha 'Ordenar por nome' antes de continuar.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n🔍 Digite o nome do componente-chave para ativar a torre: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int pos = buscaBinariaPorNome(mochila, total, nomeBusca);

    if (pos != -1) {
        printf("\n Componente encontrado!\n");
        printf("Nome: %s | Tipo: %s | Prioridade: %d | Quantidade: %d\n",
               mochila[pos].nome,
               mochila[pos].tipo,
               mochila[pos].prioridade,
               mochila[pos].quantidade);
    } else {
        printf("\n Componente \"%s\" não encontrado na mochila.\n", nomeBusca);
    }
}
