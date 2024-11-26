#ifndef PRODUTO_H
#define PRODUTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar um produto
typedef struct Produto {
    int id;
    char nome[50];
    float valor;
    int quantidade;
    struct Produto* proximo;
} Produto;

// Ponteiro para a lista de produtos
typedef struct {
    Produto* inicio;
    int totalProdutos;
} Produtos;

// Função para criar uma lista de produtos
Produtos* criarListaProdutos() {
    Produtos* lista = (Produtos*)malloc(sizeof(Produtos));
    lista->inicio = NULL;
    lista->totalProdutos = 0;
    return lista;
}

// Função para cadastrar um novo produto
void cadastrarProduto(Produtos* produtos) {
    Produto* novo = (Produto*)malloc(sizeof(Produto));
    novo->id = ++produtos->totalProdutos;
    printf("Informe o nome do produto: ");
    getchar();
    fgets(novo->nome, 50, stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0';

    printf("Informe o valor do produto: ");
    scanf("%f", &novo->valor);

    printf("Informe a quantidade do produto: ");
    scanf("%d", &novo->quantidade);

    novo->proximo = produtos->inicio;
    produtos->inicio = novo;

    printf("Produto cadastrado com sucesso!\n");
    
    char opcao;
    printf("Deseja cadastrar outro produto? (s - Sim, n - Nao): ");
    scanf(" %c", &opcao);
    
    if (opcao == 's' || opcao == 'S') {
        cadastrarProduto(produtos); 
    } else {
        printf("Retornando ao menu de produtos...\n");
    }
}

// Função para editar um produto
void editarProduto(Produtos* produtos) {
    if (produtos->totalProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    int id;
    printf("Informe o ID do produto que deseja editar: ");
    scanf("%d", &id);

    Produto* atual = produtos->inicio;
    while (atual != NULL && atual->id != id) {
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Produto nao encontrado.\n");
        return;
    }

    printf("Produto encontrado: %s\n", atual->nome);
    printf("Quantidade atual: %d\n", atual->quantidade);
    printf("Valor atual: R$ %.2f\n", atual->valor);

    char resposta;
 
    printf("Deseja alterar o nome do produto? (s - Sim, n - Nao): ");
    scanf(" %c", &resposta);
    if (resposta == 's' || resposta == 'S') {
        printf("Informe o novo nome: ");
        getchar();
        fgets(atual->nome, 50, stdin);
        atual->nome[strcspn(atual->nome, "\n")] = '\0';
    }

    printf("Deseja alterar a quantidade? (s - Sim, n - Nao): ");
    scanf(" %c", &resposta);
    if (resposta == 's' || resposta == 'S') {
        printf("Informe a nova quantidade: ");
        scanf("%d", &atual->quantidade);
    }

    printf("Deseja alterar o valor? (s - Sim, n - Nao): ");
    scanf(" %c", &resposta);
    if (resposta == 's' || resposta == 'S') {
        printf("Informe o novo valor: R$ ");
        scanf("%f", &atual->valor);
    }

    printf("Edicao concluida com sucesso!\n");

    printf("Deseja editar outro produto? (s - Sim, n - Nao): ");
    scanf(" %c", &resposta);

    if (resposta == 's' || resposta == 'S') {
        editarProduto(produtos);  // Chama a função novamente para editar outro produto
    } else {
        printf("Retornando ao menu de produtos...\n");
        return;
    }
}

// Função para exibir os produtos
void listarProdutos(Produtos* produtos) {
    if (produtos->totalProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    Produto* atual = produtos->inicio;
    printf("\nProdutos cadastrados:\n");
    while (atual != NULL) {
        printf("ID: %d | Nome: %s | Valor: R$ %.2f | Quantidade: %d\n",
               atual->id, atual->nome, atual->valor, atual->quantidade);
        atual = atual->proximo;
    }
}

// Função para excluir um produto
void excluirProduto(Produtos* produtos) {
    if (produtos->totalProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    int id;
    printf("Informe o ID do produto que deseja excluir: ");
    scanf("%d", &id);

    Produto* atual = produtos->inicio;
    Produto* anterior = NULL;

    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Produto nao encontrado.\n");
        return;
    }

    printf("Produto a ser excluido: ID: %d | Nome: %s\n", atual->id, atual->nome);
    char resposta;
    printf("Deseja realmente excluir este produto? (s - Sim, n - Nao): ");
    scanf(" %c", &resposta);

    if (resposta == 's' || resposta == 'S') {
        if (anterior == NULL) {
            produtos->inicio = atual->proximo;
        } else {
            anterior->proximo = atual->proximo;
        }

        free(atual);
        produtos->totalProdutos--;
        printf("Produto excluido com sucesso!\n");
    } else {
        printf("Exclusao cancelada. Retornando ao menu de produtos.\n");
    }
}

// Função para o menu de gerenciamento de produtos
void menuProdutos(Produtos* produtos) {
    int opcao;
    do {
        printf("\n--- Menu de Produtos ---\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Editar Produto\n");
        printf("3. Visualizar Produtos\n");
        printf("4. Excluir Produto\n");
        printf("5. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProduto(produtos);
                break;
            case 2:
                editarProduto(produtos);
                break;
            case 3:
                listarProdutos(produtos);
                break;
            case 4:
                excluirProduto(produtos);
                break;
            case 5:
                printf("Retornando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 5);
}

#endif
