#ifndef PRODUTO_H
#define PRODUTO_H

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include "animal.h"

#define TAMANHO_NOME_PRODUTO 50

struct produto {
    int id;
    char nome[TAMANHO_NOME_PRODUTO];
    float valor;
    int quantidade;
    struct produto* prox;
};

struct venda {
    int id;
    int idProduto;
    int idCliente;
    char nomeProduto[TAMANHO_NOME_PRODUTO];
    char nomeCliente[TAMANHO_NOME_CLIENTE];
    float valorProduto;
    int quantidade;
    float valorTotal;
    struct venda* prox;
};

typedef struct produto Produto;
typedef Produto *Produtos;
typedef struct venda Venda;
typedef Venda *Vendas;
int idProdutos = 1;
int idVendas = 1;


Produtos* criarListaProdutos() {
    Produtos* produtos = (Produtos*) malloc(sizeof(Produtos));
    if(produtos != NULL) {
        *produtos = NULL;
        return produtos;
    }else {
        printf("Erro alocacao lista pets...\n");
        exit(0);
    }
}

Vendas* criarListaVendas() {
    Vendas* vendas = (Vendas*) malloc(sizeof(Vendas));
    if(vendas != NULL) {
        *vendas = NULL;
        return vendas;
    }else {
        printf("Erro alocacao lista pets...\n");
        exit(0);
    }
}

Produto* criarProduto() {
    Produto* novoProduto = (Produto*) malloc(sizeof(Produto));
    if(novoProduto == NULL) {
        printf("Erro alocacao novo Pet...\n");
        return NULL;
    }
    novoProduto->id = idProdutos;
    idProdutos++;
    novoProduto->prox = NULL;
    fflush(stdin);
    printf("Informe o nome do produto: ");
    fgets(novoProduto->nome, TAMANHO_NOME_PRODUTO, stdin);
    fflush(stdin);
    printf("Informe o valor do produto: ");
    scanf("%f", &novoProduto->valor);
    fflush(stdin);
    printf("Informe a quantidade do produto: ");
    scanf("%d", &novoProduto->quantidade);
    fflush(stdin);
    return novoProduto;
}

Venda* criarVenda() {
    Venda *novaVenda = (Venda*) malloc(sizeof(Venda));
    if(novaVenda == NULL) {
        printf("Erro alocacao nova Venda!");
        exit(1);
    }
    novaVenda->id = idVendas;
    idVendas++;
    novaVenda->prox = NULL;
    return novaVenda;
}

//Inserindo no final
void inserirProduto(Produtos* produtos) {
    printf("\tCadastrando novo Pet: \n");
    Produto* novoProduto = criarProduto();
    if(*produtos == NULL) {
        *produtos = novoProduto;
    }else {
        Produto* tmp = *produtos;
        while (tmp->prox != NULL){
            tmp = tmp->prox;
        }
        tmp->prox = novoProduto;
    }
    printf("Produto criado com sucesso!\n");
}

void imprimiProdutos(Produto* produto) {
    printf("\nProduto: \n[ID#%d]\n", produto->id);
    printf("Nome: %s", produto->nome);
    printf("Valor: %.2f\n", produto->valor);
    printf("Valor: %d\n", produto->quantidade);
}

void listarProdutos(Produtos* produtos) {
    if(*produtos == NULL) {
        printf("Nqo existe produtos\n");
    }else {
        Produto* produto = *produtos;
        while (produto != NULL){
            imprimiProdutos(produto);
            produto = produto->prox;
        }
    }
}

void limparProdutos(Produtos* produtos) {
    if(*produtos == NULL) {
        printf("Nao existe produtos, ja esta limpo!");
    }else {
        while ((*produtos) != NULL){
            Produto* produto = *produtos;
            *produtos = (*produtos)->prox;
            free(produto);
        }
        *produtos = NULL;
    }
}

void limparVendas(Vendas* vendas) {
    if(*vendas == NULL) {
        printf("Nao existe vendas, ja esta limpo!");
    }else {
        while ((*vendas) != NULL){
            Venda* venda = *vendas;
            *vendas = (*vendas)->prox;
            free(venda);
        }
        *vendas = NULL;
    }
}


Produto* buscarProdutoPorID(Produtos* produtos, int id) {
    Produto* produto = NULL;
    Produto* tmp = *produtos;
    while(tmp != NULL) {
        if(tmp->id == id) {
            produto = tmp;
            break;
        }
        tmp = tmp->prox;
    }
    return produto;
}

void editarProduto(Produto* produto) {
    int option;
    for(;;) {
        system("cls");
        imprimiProdutos(produto);
        printf("\n[1] - Nome\n");
        printf("[2] - Valor\n");
        printf("[3] - Quantidade\n");
        printf("[0] - Voltar\n");
        printf("Deseja alterar que campo: ");
        scanf("%d", &option);
        if(option == 1) {
            printf("Informe o novo nome: ");
            fflush(stdin);
            fgets(produto->nome, TAMANHO_NOME_PRODUTO, stdin);
            fflush(stdin);
        }else if(option == 2) {
            printf("Informe o novo valor: ");
            fflush(stdin);
            scanf("%f", &produto->valor);
            fflush(stdin);
        }else if(option == 3) {
            printf("Informe a nova quantidade: ");
            fflush(stdin);
            scanf("%d", &produto->quantidade);
            fflush(stdin);
        }else if(option == 0) {
            break;
        }else {
            printf("Opcao invalida!\n");
            esperarEnter();
        }
    }
    return;
}

void editarProdutos(Produtos* produtos) {
    int idBuscar, option = 2;
    for(;;) {
        if(option == 1) {
            printf("Informe o ID do Produto que deseja alterar: ");
            scanf("%d", &idBuscar);
            Produto* produto = buscarProdutoPorID(produtos, idBuscar);
            if(produto != NULL) {
                editarProduto(produto);
            }else {
                printf("produto nao encontrado!\n");
            }
        }else if(option == 2) {
            system("cls");
            listarProdutos(produtos);
        }else if(option == 0) {
            return;
        }else {
            printf("Opcao invalida!\n");
            esperarEnter();
            system("cls");
        }
        printf("[1] - Informar ID para Edicao de produto\n");
        printf("[2] - Listar produtos\n");
        printf("[0] - Voltar\n");
        printf("Informe a opcao que deseja: ");
        scanf("%d", &option);
    }
    return;
}


void removerProdutoPorID(Produtos* produtos, int id) {
    Produto* remover = NULL;
    if((*produtos)->id == id) {
        if(confirmarRemocao()) {
            remover = *produtos;
            *produtos = remover->prox;
            free(remover);
            printf("Removido com sucesso!\n");
            esperarEnter();
        }
    }else {
        Produto* ant = *produtos;
        while(ant->prox != NULL) {
            if(ant->prox->id == id) {
                remover = ant->prox;
                break;
            } 
            ant = ant->prox;
        }
        if(remover == NULL) {
            printf("Produto nao encontrado!\n");
            esperarEnter();
        }else {
            if(confirmarRemocao()) {
                ant->prox = remover->prox;
                free(remover);
                printf("Removido com sucesso!\n");
                esperarEnter();
            }
        }
    }
    return;
}

void removerProdutos(Produtos* produtos) {
    int idBuscar, option = 2;
    for(;;) {
        if(option == 1) {
            printf("Informe o ID do Produto que deseja alterar: ");
            scanf("%d", &idBuscar);
            removerProdutoPorID(produtos, idBuscar);
        }else if(option == 2) {
            system("cls");
            listarProdutos(produtos);
        }else {
            printf("Opcao invalida!\n");
            esperarEnter();
            system("cls");
        }
        printf("[1] - Informar ID para Remocao de Produto\n");
        printf("[2] - Listar produtos\n");
        printf("[0] - Voltar\n");
        printf("Informe a opcao que deseja: ");
        scanf("%d", &option);
    }
    return;
}

void imprimiVendas(Venda* venda) {
    printf("\nProduto: \n[ID#%d]\n", venda->id);
    printf("Nome: %s", venda->nomeCliente);
    printf("Nome produto: %s", venda->nomeProduto);
    printf("Valor produto: %.2f\n", venda->valorProduto);
    printf("Quantidade: %d\n", venda->quantidade);
    printf("Valor total: %.2f\n", venda->valorTotal);
}

void inserirVenda(Vendas* vendas, Venda* venda) {
    if(*vendas == NULL) {
        *vendas = venda;
    }else {
        venda->prox = *vendas;
        *vendas = venda;
    }
    printf("Venda cadastrada com sucesso!");
}

void listarVendas(Vendas* vendas) {
    if(*vendas == NULL) {
        printf("Nao existe vendas\n");
    }else {
        Venda* venda = *vendas;
        while (venda != NULL){
            imprimiVendas(venda);
            venda = venda->prox;
        }
    }
    esperarEnter();
}

void cadastrarVenda(Produtos* produtos, Vendas* vendas, Clientes* clientes) {
    int idProduto, idCliente, quantidade;
    if(*produtos == NULL) {
        printf("Nao existem produtos!\n");
        esperarEnter();
        return;
    }

    if(*clientes == NULL) {
        printf("Nao existem clientes!\n");
        esperarEnter();
        return;
    }

    system("cls");
    listarProdutos(produtos);
    printf("Informe o id do produto para a venda:");
    scanf("%d", &idProduto);
    Produto* produtoBusca = buscarProdutoPorID(produtos, idProduto);
    if(produtoBusca == NULL) {
        printf("produto invalido!\n");
        esperarEnter();
        return;
    }

    system("cls");
    listarClientes(clientes);
    printf("Informe o id do cliente para a venda:");
    scanf("%d", &idCliente);
    Cliente* clienteBusca = buscarClientePorID(clientes, idCliente);
    if(clienteBusca == NULL) {
        printf("cliente invalido!\n");
        esperarEnter();
        return;
    }

    system("cls");
    printf("Informe a quantidade comprada: ");
    scanf("%d", &quantidade);
    if(quantidade > produtoBusca->quantidade || quantidade < 1) {
        printf("Quantidade inválida!\n");
        esperarEnter();
        return;
    }

    Venda* novaVenda = criarVenda();
    produtoBusca->quantidade -= quantidade;
    novaVenda->idCliente = idCliente;
    strcpy(novaVenda->nomeCliente, clienteBusca->nome);
    novaVenda->idProduto = idProduto;
    novaVenda->quantidade = quantidade;
    novaVenda->valorProduto = produtoBusca->valor;
    novaVenda->valorTotal = (produtoBusca->valor * ((float)quantidade));
    strcpy(novaVenda->nomeProduto, produtoBusca->nome);
    inserirVenda(vendas, novaVenda);
    esperarEnter();
}

void menuProduto(Produtos* produtos, Vendas* vendas, Clientes* clientes) {
    int option;
    for(;;) {
        system("cls");
        printf("\tProdutos\n");
        printf("[1] - Cadastrar Produtos\n");
        printf("[2] - Listar Produtos\n");
        printf("[3] - Editar Produtos\n");
        printf("[4] - Remover Produtos\n");
        printf("[5] - Cadastrar Venda\n");
        printf("[0] - Voltar\n");
        printf("Informe a opcao que deseja: ");
        scanf("%d", &option);
        if (option == 1) {
            inserirProduto(produtos);
            esperarEnter();
        }else if(option == 2) {
            listarProdutos(produtos);
            esperarEnter();
        }else if(option == 3) {
            editarProdutos(produtos);
        }else if(option == 4) {
            removerProdutos(produtos);
        }else if(option == 5) {
            cadastrarVenda(produtos, vendas, clientes);
        }else if(option == 6) {
            listarVendas(vendas);
        }else if(option == 0) {
            return;
        }else {
            printf("Opcao invalida!");
            esperarEnter();
        }
    }
}

#endif