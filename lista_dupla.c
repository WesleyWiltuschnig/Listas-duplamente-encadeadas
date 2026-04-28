#include "lista_dupla.h"

//1
Nodo* criar_nodo(int valor) {
    Nodo *novo = (Nodo*)malloc(sizeof(Nodo));
    if (novo) {
        novo->valor = valor;
        novo->anterior = NULL;
        novo->proximo = NULL;
    }
    return novo;
}

int obter_valor(Nodo *nodo) { return nodo->valor; }
void definir_valor(Nodo *nodo, int valor) { nodo->valor = valor; }
Nodo* obter_anterior(Nodo *nodo) { return nodo->anterior; }
Nodo* obter_proximo(Nodo *nodo) { return nodo->proximo; }
void definir_anterior(Nodo *nodo, Nodo *ant) { nodo->anterior = ant; }
void definir_proximo(Nodo *nodo, Nodo *prox) { nodo->proximo = prox; }
void destruir_nodo(Nodo *nodo) { free(nodo); }

//2
Lista* criar_lista() {
    Lista *l = (Lista*)malloc(sizeof(Lista));
    l->inicio = NULL;
    l->fim = NULL;
    l->tamanho = 0;
    return l;
}

int esta_vazia(Lista *lista) { return lista->tamanho == 0; }
int obter_tamanho(Lista *lista) { return lista->tamanho; }

void destruir_lista(Lista *lista) {
    Nodo *atual = lista->inicio;
    while (atual) {
        Nodo *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
    free(lista);
}

//3
int inserir_inicio(Lista *lista, int valor) {
    Nodo *novo = criar_nodo(valor);
    if (!novo) return 0;
    if (esta_vazia(lista)) {
        lista->inicio = lista->fim = novo;
    } else {
        novo->proximo = lista->inicio;
        lista->inicio->anterior = novo;
        lista->inicio = novo;
    }
    lista->tamanho++;
    return 1;
}

//4
int inserir_fim(Lista *lista, int valor) {
    Nodo *novo = criar_nodo(valor);
    if (!novo) return 0;
    if (esta_vazia(lista)) {
        lista->inicio = lista->fim = novo;
    } else {
        novo->anterior = lista->fim;
        lista->fim->proximo = novo;
        lista->fim = novo;
    }
    lista->tamanho++;
    return 1;
}

//5
void imprimir_inicio_fim(Lista *lista) {
    Nodo *atual = lista->inicio;
    while (atual) {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

void imprimir_fim_inicio(Lista *lista) {
    Nodo *atual = lista->fim;
    while (atual) {
        printf("%d ", atual->valor);
        atual = atual->anterior;
    }
    printf("\n");
}

//6
int remover_inicio(Lista *lista, int *valor_removido) {
    if (esta_vazia(lista)) return 0;
    Nodo *aux = lista->inicio;
    *valor_removido = aux->valor;
    lista->inicio = aux->proximo;
    if (lista->inicio) lista->inicio->anterior = NULL;
    else lista->fim = NULL;
    free(aux);
    lista->tamanho--;
    return 1;
}

//7
int remover_fim(Lista *lista, int *valor_removido) {
    if (esta_vazia(lista)) return 0;
    Nodo *aux = lista->fim;
    *valor_removido = aux->valor;
    lista->fim = aux->anterior;
    if (lista->fim) lista->fim->proximo = NULL;
    else lista->inicio = NULL;
    free(aux);
    lista->tamanho--;
    return 1;
}

//8
Nodo* buscar(Lista *lista, int valor) {
    Nodo *atual = lista->inicio;
    while (atual) {
        if (atual->valor == valor) return atual;
        atual = atual->proximo;
    }
    return NULL;
}

//9
int inserir_posicao(Lista *lista, int valor, int pos) {
    if (pos < 0 || pos > lista->tamanho) return 0;
    if (pos == 0) return inserir_inicio(lista, valor);
    if (pos == lista->tamanho) return inserir_fim(lista, valor);

    Nodo *novo = criar_nodo(valor);
    Nodo *atual = lista->inicio;
    for (int i = 0; i < pos; i++) atual = atual->proximo;

    novo->anterior = atual->anterior;
    novo->proximo = atual;
    atual->anterior->proximo = novo;
    atual->anterior = novo;
    lista->tamanho++;
    return 1;
}
//10
int remover_valor(Lista *lista, int valor) {
    Nodo *alvo = buscar(lista, valor);
    if (!alvo) return 0;
    if (alvo == lista->inicio) {
        int v; return remover_inicio(lista, &v);
    }
    if (alvo == lista->fim) {
        int v; return remover_fim(lista, &v);
    }
    alvo->anterior->proximo = alvo->proximo;
    alvo->proximo->anterior = alvo->anterior;
    free(alvo);
    lista->tamanho--;
    return 1;
}