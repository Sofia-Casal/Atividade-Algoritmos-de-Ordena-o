#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

void trocar(Prato *a, Prato *b) {
    Prato temp = *a;
    *a = *b;
    *b = temp;
}

int particionar(Prato pratos[], int inicio, int fim) {
    int indicePivo = inicio + rand() % (fim - inicio + 1);
    trocar(&pratos[indicePivo], &pratos[fim]);

    Prato pivo = pratos[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (compararPratos(&pratos[j], &pivo) < 0) {
            i++;
            trocar(&pratos[i], &pratos[j]);
        }
    }
    trocar(&pratos[i + 1], &pratos[fim]);
    return i + 1;
}

void quickSort(Prato pratos[], int inicio, int fim) {
    if (inicio < fim) {
        int pivo = particionar(pratos, inicio, fim);
        quickSort(pratos, inicio, pivo - 1);
        quickSort(pratos, pivo + 1, fim);
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

    srand(time(NULL));

    totalPratos = carregarPratos("restaurante_pratos.csv", pratos);
    if (totalPratos < 0) {
        return 1;
    }

    quickSort(pratos, 0, totalPratos - 1);

    printf("\nPratos ordenados:\n");
    for (int i = 0; i < totalPratos; i++) {
        printf("%s\n", pratos[i].nome);
    }

    return 0;
}
