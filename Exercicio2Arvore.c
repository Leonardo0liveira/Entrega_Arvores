#include <stdio.h>
#include <stdlib.h>

#define MAX_FILHOS 3
#define TAMANHO_PILHA_FILA 100 

struct no {
    char letra;
    struct no* filhos[MAX_FILHOS]; 
    struct no* prox; 
};

struct no* inicio = NULL;

struct no* nos[100];
int indice_no = 0;

struct no* criar_no(char letra) {
    struct no* novo_no = (struct no*)malloc(sizeof(struct no));
    novo_no->letra = letra;
    for (int i = 0; i < MAX_FILHOS; i++) {
        novo_no->filhos[i] = NULL;
    }
    novo_no->prox = NULL;
    return novo_no;
}

void inserir_no(char letra) {
    struct no* novo_no = criar_no(letra);
    nos[indice_no++] = novo_no; 

    if (inicio == NULL) {
        inicio = novo_no;
    } else {
        struct no* temp = inicio;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = novo_no;
    }
}

void adicionar_filho(struct no* pai, struct no* filho, int posicao) {
    if (pai != NULL && posicao >= 0 && posicao < MAX_FILHOS) {
        pai->filhos[posicao] = filho;
    }
}

void remover_no(struct no* pai, struct no* no_a_remover) {
    if (no_a_remover == NULL) return;

    for (int i = 0; i < MAX_FILHOS; i++) {
        if (no_a_remover->filhos[i] != NULL) {
            remover_no(no_a_remover, no_a_remover->filhos[i]);
            no_a_remover->filhos[i] = NULL;
        }
    }

    if (pai != NULL) {
        for (int i = 0; i < MAX_FILHOS; i++) {
            if (pai->filhos[i] == no_a_remover) {
                pai->filhos[i] = NULL;
            }
        }
    }

    if (inicio == no_a_remover) {
        inicio = no_a_remover->prox;
    } else {
        struct no* temp = inicio;
        while (temp->prox != NULL && temp->prox != no_a_remover) {
            temp = temp->prox;
        }
        if (temp->prox == no_a_remover) {
            temp->prox = no_a_remover->prox;
        }
    }

    free(no_a_remover);
}

void imprimir_arvore(struct no* no_atual) {
    if (no_atual == NULL) return;

    printf("Pai: %c\n", no_atual->letra);
    for (int i = 0; i < MAX_FILHOS; i++) {
        if (no_atual->filhos[i] != NULL) {
            printf("  Filho %d: %c\n", i, no_atual->filhos[i]->letra);
        } else {
            printf("  Filho %d: -\n", i);
        }
    }

    if (no_atual->prox != NULL) {
        imprimir_arvore(no_atual->prox);
    }
}

int busca_em_profundidade(struct no* raiz, char letra) {
    if (raiz == NULL) return -1;

    struct no* pilha[TAMANHO_PILHA_FILA];
    int topo = -1;

    pilha[++topo] = raiz;

    while (topo != -1) {
        struct no* atual = pilha[topo--];
        if (atual != NULL) {
            if (atual->letra == letra) {
                for (int i = 0; i < indice_no; i++) {
                    if (nos[i] == atual) {
                        return i;
                    }
                }
            }
            for (int i = MAX_FILHOS - 1; i >= 0; i--) {
                if (atual->filhos[i] != NULL) {
                    pilha[++topo] = atual->filhos[i];
                }
            }
        }
    }
    return -1; 
}

int busca_em_largura(struct no* raiz, char letra) {
    if (raiz == NULL) return -1;

    struct no* fila[TAMANHO_PILHA_FILA];
    int inicio = 0, fim = 0;

    fila[fim++] = raiz;

    while (inicio < fim) {
        struct no* atual = fila[inicio++];
        if (atual != NULL) {
            if (atual->letra == letra) {
                for (int i = 0; i < indice_no; i++) {
                    if (nos[i] == atual) {
                        return i;
                    }
                }
            }
            for (int i = 0; i < MAX_FILHOS; i++) {
                if (atual->filhos[i] != NULL) {
                    fila[fim++] = atual->filhos[i];
                }
            }
        }
    }
    return -1; 
}

int main() {
    int opcao, posicao;
    char letra, pai_letra;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Inserir nó\n");
        printf("2. Imprimir árvore\n");
        printf("3. Remover nó\n");
        printf("4. Busca em profundidade (DFS)\n");
        printf("5. Busca em largura (BFS)\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o novo nó (letra): ");
                scanf(" %c", &letra);
                inserir_no(letra);
                if (indice_no > 1) {
                    printf("Este nó é filho de qual nó (letra)? ");
                    scanf(" %c", &pai_letra);
                    printf("Qual a posição deste filho (0, 1 ou 2)? ");
                    scanf("%d", &posicao);
                    struct no* pai = inicio;
                    while (pai != NULL && pai->letra != pai_letra) {
                        pai = pai->prox;
                    }
                    if (pai != NULL) {
                        adicionar_filho(pai, nos[indice_no - 1], posicao);
                    }
                }
                break;

            case 2:
                imprimir_arvore(inicio);
                break;

            case 3:
                printf("Digite o nó a ser removido (letra): ");
                scanf(" %c", &letra);
                struct no* pai = NULL;
                struct no* no_a_remover = inicio;
                while (no_a_remover != NULL && no_a_remover->letra != letra) {
                    pai = no_a_remover;
                    no_a_remover = no_a_remover->prox;
                }
                if (no_a_remover != NULL) {
                    remover_no(pai, no_a_remover);
                }
                break;

            case 4:
                printf("Digite a letra do nó a ser encontrado: ");
                scanf(" %c", &letra);
                int indice = busca_em_profundidade(inicio, letra);
                if (indice != -1) {
                    printf("Nó encontrado no índice: %d\n", indice);
                } else {
                    printf("Nó não encontrado.\n");
                }
                break;

            case 5:
                printf("Digite a letra do nó a ser encontrado: ");
                scanf(" %c", &letra);
                indice = busca_em_largura(inicio, letra);
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
