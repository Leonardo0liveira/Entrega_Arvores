#include <stdio.h>
#include <stdlib.h>

#define MAX_NO 100
#define MAX_FILHOS 3

struct no {
    char letra;
    int filhos[MAX_FILHOS]; 
};


struct no exemplo1[MAX_NO];

void inicializar_arvore() {
    int i, j;
    for (i = 0; i < MAX_NO; i++) {
        exemplo1[i].letra = '\0'; 
        for (j = 0; j < MAX_FILHOS; j++) {
            exemplo1[i].filhos[j] = -1; 
        }
    }
}

void inserir_no(int indice, char letra) {
    if (indice >= 0 && indice < MAX_NO) {
        exemplo1[indice].letra = letra;
    }
}

void adicionar_filho(int pai, int filho, int posicao) {
    if (pai >= 0 && pai < MAX_NO && filho >= 0 && filho < MAX_NO && posicao >= 0 && posicao < MAX_FILHOS) {
        exemplo1[pai].filhos[posicao] = filho;
    }
}

void remover_no(int indice) {
    if (indice >= 0 && indice < MAX_NO) {
        exemplo1[indice].letra = '\0';
        for (int i = 0; i < MAX_FILHOS; i++) {
            int filho = exemplo1[indice].filhos[i];
            if (filho != -1) {
                remover_no(filho);
                exemplo1[indice].filhos[i] = -1;
            }
        }
    }
}

void imprimir_arvore() {
    for (int i = 0; i < MAX_NO; i++) {
        if (exemplo1[i].letra != '\0') {
            printf("\nPai: %c\n", exemplo1[i].letra);
            for (int j = 0; j < MAX_FILHOS; j++) {
                if (exemplo1[i].filhos[j] != -1) {
                    printf("Filho %d: %c ", j, exemplo1[exemplo1[i].filhos[j]].letra);
                } else {
                    printf("Filho %d: - ", j);
                }
            }
            printf("\n");
        }
    }
}

int busca_em_profundidade(int raiz, char letra) {
    int pilha[MAX_NO];
    int topo = -1;

    pilha[++topo] = raiz;

    while (topo != -1) {
        int atual = pilha[topo--];

        if (atual != -1 && exemplo1[atual].letra != '\0') {
            if (exemplo1[atual].letra == letra) {
                return atual;
            }
            for (int i = MAX_FILHOS - 1; i >= 0; i--) { 
                if (exemplo1[atual].filhos[i] != -1) {
                    pilha[++topo] = exemplo1[atual].filhos[i];
                }
            }
        }
    }
    return -1; 
}

int busca_em_largura(int raiz, char letra) {
    int fila[MAX_NO];
    int inicio = 0, fim = 0;

    fila[fim++] = raiz;

    while (inicio < fim) {
        int atual = fila[inicio++];

        if (atual != -1 && exemplo1[atual].letra != '\0') {
            if (exemplo1[atual].letra == letra) {
                return atual;
            }
            for (int i = 0; i < MAX_FILHOS; i++) {
                if (exemplo1[atual].filhos[i] != -1) {
                    fila[fim++] = exemplo1[atual].filhos[i];
                }
            }
        }
    }
    return -1; 
}

int main() {
    int opcao, pai, posicao, indice, indice_atual = 0;
    char letra;

    inicializar_arvore();

    while (1) {
        printf("\nMenu:\n");
        printf("1. Inserir nó\n");
        printf("2. Imprimir árvore\n");
        printf("3. Remover nó\n");
        printf("4. Buscar em profundidade (DFS)\n");
        printf("5. Buscar em largura (BFS)\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o novo nó (letra): ");
                scanf(" %c", &letra);
                inserir_no(indice_atual, letra);

                if (indice_atual > 0) {
                    printf("Este nó é filho de qual nó (índice)? ");
                    scanf("%d", &pai);
                    printf("Qual a posição deste filho (0, 1 ou 2)? ");
                    scanf("%d", &posicao);
                    adicionar_filho(pai, indice_atual, posicao);
                }

                indice_atual++;
                break;

            case 2:
                imprimir_arvore();
                break;

            case 3:
                printf("Digite o índice do nó a ser removido: ");
                scanf("%d", &indice);
                remover_no(indice);
                break;

            case 4:
                printf("Digite a letra do nó a ser encontrado: ");
                scanf(" %c", &letra);
                indice = busca_em_profundidade(0, letra);
                if (indice != -1) {
                    printf("Nó encontrado no índice: %d\n", indice);
                } else {
                    printf("Nó não encontrado.\n");
                }
                break;

            case 5:
                printf("Digite a letra do nó a ser encontrado: ");
                scanf(" %c", &letra);
                indice = busca_em_largura(0, letra);
                if (indice != -1) {
                    printf("Nó encontrado no índice: %d\n", indice);
                } else {
                    printf("Nó não encontrado.\n");
                }
                break;

            case 6:
                exit(0);

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}
