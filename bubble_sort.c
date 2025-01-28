#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 51
#define MAX_PRATOS 300000

typedef struct {
    int prioridade;
    int tempo;
    char nome[MAX_NOME];
} Prato;

int compararPratos(const Prato *a, const Prato *b) {
    if (a->prioridade != b->prioridade) {
        return b->prioridade - a->prioridade;
    }
    return a->tempo - b->tempo;
}

void bubbleSort(Prato pratos[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compararPratos(&pratos[j], &pratos[j + 1]) > 0) {
                Prato temp = pratos[j];
                pratos[j] = pratos[j + 1];
                pratos[j + 1] = temp;
            }
        }
    }
}

int carregarPratos(const char *nomeArquivo, Prato pratos[]) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    char linha[128];
    int count = 0;

    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo) && count < MAX_PRATOS) {
        sscanf(linha, "%d,%d,%50[^\n]", 
               &pratos[count].prioridade, 
               &pratos[count].tempo, 
               pratos[count].nome);
        count++;
    }

    fclose(arquivo);
    return count;
}

int main() {
    Prato pratos[MAX_PRATOS];
    int totalPratos;

    totalPratos = carregarPratos("restaurante_pratos.csv", pratos);
    if (totalPratos < 0) {
        return 1;
    }

    bubbleSort(pratos, totalPratos);

    printf("\nPratos ordenados:\n");
    for (int i = 0; i < totalPratos; i++) {
        printf("%s\n", pratos[i].nome);
    }

    return 0;
}
