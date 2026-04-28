#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int matricula;
    char nome[50];
    float media;
} Aluno;

typedef struct NodoAluno {
    Aluno dado;
    struct NodoAluno *ant, *prox;
} NodoAluno;

typedef struct {
    NodoAluno *inicio, *fim;
} ListaAlunos;

ListaAlunos* criar_lista_alunos() {
    ListaAlunos *l = malloc(sizeof(ListaAlunos));
    l->inicio = l->fim = NULL;
    return l;
}

void inserir_aluno_fim(ListaAlunos *l, Aluno a) {
    NodoAluno *novo = malloc(sizeof(NodoAluno));
    novo->dado = a;
    novo->prox = NULL;
    novo->ant = l->fim;
    if (l->fim) l->fim->prox = novo;
    else l->inicio = novo;
    l->fim = novo;
}

void imprimir_por_status(ListaAlunos *l, int aprovado) {
    NodoAluno *atual = l->inicio;
    printf(aprovado ? "--- APROVADOS ---\n" : "--- REPROVADOS ---\n");
    while (atual) {
        if ((aprovado && atual->dado.media >= 7.0) || (!aprovado && atual->dado.media < 7.0)) {
            printf("Mat: %d | Nome: %s | Nota: %.1f\n", atual->dado.matricula, atual->dado.nome, atual->dado.media);
        }
        atual = atual->prox;
    }
}

int remover_por_matricula(ListaAlunos *l, int mat) {
    NodoAluno *atual = l->inicio;
    while (atual) {
        if (atual->dado.matricula == mat) {
            if (atual->ant) atual->ant->prox = atual->prox;
            else l->inicio = atual->prox;
            if (atual->prox) atual->prox->ant = atual->ant;
            else l->fim = atual->ant;
            free(atual);
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

//exemplo de uso
int main() {
    ListaAlunos *turma = criar_lista_alunos();
    Aluno a1 = {101, "Alice", 8.5}, a2 = {102, "Bob", 5.0};
    
    inserir_aluno_fim(turma, a1);
    inserir_aluno_fim(turma, a2);
    
    imprimir_por_status(turma, 1); // Aprovados
    imprimir_por_status(turma, 0); // Reprovados
    
    return 0;
}