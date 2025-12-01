#include <stdio.h>
#include <stdlib.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// ==== Estrutura da peça ====
typedef struct {
    char nome;
    int id;
} Peca;

// ===== FILA CIRCULAR ===== //
Peca fila[TAM_FILA];
int inicio = 0;
int fim = 0;

// ===== PILHA DE RESERVA ===== //
Peca pilha[TAM_PILHA];
int topo = -1;

int proximoID = 1;

// ==== Gerar peça automática ====
Peca gerarPeca() {
    Peca p;
    char tipos[4] = {'I', 'O', 'T', 'L'};
    p.nome = tipos[rand() % 4];
    p.id = proximoID++;
    return p;
}

// === Operações da Fila ===
void enqueue(Peca p) {
    fila[fim] = p;
    fim = (fim + 1) % TAM_FILA;
}

Peca dequeue() {
    Peca p = fila[inicio];
    inicio = (inicio + 1) % TAM_FILA;
    return p;
}

// === Operações da Pilha ===
void push(Peca p) {
    topo++;
    pilha[topo] = p;
}

Peca pop() {
    Peca p = pilha[topo];
    topo--;
    return p;
}

// ===== Exibir Estado =====
void exibirEstado() {
    printf("\n=========== ESTADO ATUAL ===========\n");

    printf("\nFila (5 peças):\n");
    int i = inicio;
    for (int c = 0; c < TAM_FILA; c++) {
        printf(" %c (id %d)\n", fila[i].nome, fila[i].id);
        i = (i + 1) % TAM_FILA;
    }

    printf("\nPilha de reserva:\n");
    if (topo == -1) {
        printf(" <vazia>\n");
    } else {
        for (int i = topo; i >= 0; i--) {
            printf(" %c (id %d)\n", pilha[i].nome, pilha[i].id);
        }
    }

    printf("\n=====================================\n");
}

// ===== Trocar peça atual (fila <-> topo da pilha) =====
void trocarPeçaAtual() {
    if (topo == -1) {
        printf("\nERRO: Não há peça na pilha para trocar.\n");
        return;
    }

    int idx = inicio;
    Peca temp = fila[idx];
    fila[idx] = pilha[topo];
    pilha[topo] = temp;

    printf("\nPeça da frente da fila e topo da pilha foram trocadas.\n");
}

// ===== Troca múltipla (3 peças da fila <-> 3 da pilha) =====
void trocaMultipla() {
    if (topo < 2) {
        printf("\nERRO: A pilha não tem 3 peças para realizar a troca múltipla.\n");
        return;
    }

    int idx = inicio;
    for (int i = 0; i < 3; i++) {
        Peca temp = fila[idx];
        fila[idx] = pilha[topo - i];
        pilha[topo - i] = temp;

        idx = (idx + 1) % TAM_FILA;
    }

    printf("\nAs 3 primeiras peças da fila foram trocadas com as 3 peças da pilha.\n");
}

// ================= MAIN ==================
int main() {
    int opcao;

    // Inicializa fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(gerarPeca());
    }

    do {
        exibirEstado();

        printf("\nMENU:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça (fila → pilha)\n");
        printf("3 - Usar peça reservada (pop)\n");
        printf("4 - Trocar peça atual (fila ↔ pilha)\n");
        printf("5 - Troca múltipla (3 fila ↔ 3 pilha)\n");
        printf("6 - Exibir estado novamente\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            // Jogar
            Peca p = dequeue();
            printf("\nPeça jogada: %c (id %d)\n", p.nome, p.id);

            enqueue(gerarPeca());
        }
        else if (opcao == 2) {
            // Reservar
            if (topo == TAM_PILHA - 1) {
                printf("\nERRO: Pilha cheia!\n");
            } else {
                Peca p = dequeue();
                push(p);
                printf("\nPeça reservada: %c (id %d)\n", p.nome, p.id);

                enqueue(gerarPeca());
            }
        }
        else if (opcao == 3) {
            // Usar peça reservada
            if (topo == -1) {
                printf("\nERRO: Pilha vazia! Nada a usar.\n");
            } else {
                Peca p = pop();
                printf("\nPeça usada: %c (id %d)\n", p.nome, p.id);

                enqueue(gerarPeca());
            }
        }
        else if (opcao == 4) {
            trocarPeçaAtual();
        }
        else if (opcao == 5) {
            trocaMultipla();
        }

    } while (opcao != 0);

    printf("\nPrograma encerrado.\n");

    return 0;
}


