#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 100

// Armazena as informações de um produto
typedef struct {
    int id;
    char nome[50];
    float valor;
    int quantidade;
} Produto;

// Lista de produtos
Produto produtos[MAX_PRODUTOS];
int totalProdutos = 0;

// Cadastrar novos produtos
void cadastrarProduto() {
    int continuar = 1;
    while (continuar) {
        if (totalProdutos >= MAX_PRODUTOS) {
            printf("Limite de produtos atingido.\n");
            return;
        }
        
        Produto p;
        p.id = totalProdutos + 1;  // ID para os produtos
        printf("Informe o nome do produto: ");
        getchar();  // Para limpar o buffer do teclado
        fgets(p.nome, 50, stdin);
        p.nome[strcspn(p.nome, "\n")] = '\0';  // Remove o espaço gerado pelo fgets
        
        printf("Informe o valor do produto: ");
        scanf("%f", &p.valor);
        
        printf("Informe a quantidade do produto: ");
        scanf("%d", &p.quantidade);
        
        produtos[totalProdutos] = p;
        totalProdutos++;
        printf("Produto cadastrado com sucesso!\n");

        // Limpa o buffer após scanf
        while(getchar() != '\n');

        printf("Deseja cadastrar outro produto? (s - Sim, n - Nao): ");
        char resposta;
        scanf(" %c", &resposta);

        while(getchar() != '\n');
        
        if (resposta == 'n' || resposta == 'N') {
            continuar = 0;
        }
    }
}

// Editar produto
void editarProduto() {
    char resposta;
    int id;
    printf("Informe o ID do produto que deseja editar: ");
    scanf("%d", &id);

    if (id < 1 || id > totalProdutos) {
        printf("Produto nao encontrado.\n");
        return;
    }

    Produto *p = &produtos[id - 1];  // Acessa o produto pelo ID (ajustado para índice 0-based)
    
    printf("Produto encontrado: %s\n", p->nome);
    printf("Quantidade atual: %d\n", p->quantidade);
    printf("Valor atual: R$ %.2f\n", p->valor);
    
      // Opção de alterar o nome
    printf("Deseja alterar o nome do produto? (s - Sim, n - Nao): ");
    scanf(" %c", &resposta);
    if (resposta == 's' || resposta == 'S') {
        printf("Informe o novo nome: ");
        getchar();  // Limpar o buffer do teclado
        fgets(p->nome, 50, stdin);
        p->nome[strcspn(p->nome, "\n")] = '\0';  // Remover o \n
    }

    // Opção de alterar a quantidade
    printf("Deseja alterar a quantidade? (s - Sim, n - Nao): ");
    scanf(" %c", &resposta);
    if (resposta == 's' || resposta == 'S') {
        int novaQuantidade;
        printf("Informe a nova quantidade (positiva para aumentar, negativa para diminuir): ");
        scanf("%d", &novaQuantidade);
        p->quantidade += novaQuantidade;
        if (p->quantidade < 0) {
            p->quantidade = 0;  // Não permite quantidade negativa
        }
        printf("Quantidade atualizada para: %d\n", p->quantidade);
    }

    // Opção de deseja alterar o valor
    printf("Deseja alterar o valor? (s - Sim, n - Nao): ");
    scanf(" %c", &resposta);
    if (resposta == 's' || resposta == 'S') {
        printf("Informe o novo valor: R$ ");
        scanf("%f", &p->valor);
        printf("Valor atualizado para: R$ %.2f\n", p->valor);
    }
}

// Venda de produto
void venderProduto() {
    int continuar = 1;
    while (continuar) {
        int id;
        printf("Informe o ID do produto que deseja vender: ");
        scanf("%d", &id);

        if (id < 1 || id > totalProdutos) {
            printf("Produto nao encontrado.\n");
            return;
        }

        Produto *p = &produtos[id - 1];  // Acessa o produto pelo ID (ajustado para índice 0-based)
        
        int quantidadeVendida;
        printf("Produto encontrado: %s\n", p->nome);
        printf("Quantidade disponivel: %d\n", p->quantidade);
        
        printf("Informe a quantidade a ser vendida: ");
        scanf("%d", &quantidadeVendida);
        
        if (quantidadeVendida <= p->quantidade) {
            float valorTotal = quantidadeVendida * p->valor;
            p->quantidade -= quantidadeVendida;
            printf("Venda realizada com sucesso! Valor total: R$ %.2f\n", valorTotal);
        } else {
            printf("Quantidade insuficiente no estoque.\n");
        }

        printf("Deseja continuar vendendo? (s - Sim, n - Nao): ");
        char resposta;
        scanf(" %c", &resposta);

        // Limpa o buffer após scanf
        while(getchar() != '\n');

        if (resposta == 'n' || resposta == 'N') {
            continuar = 0;
        }
    }
}

// Visualizar a lista de produtos
void visualizarProdutos() {
    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    
    printf("Lista de produtos cadastrados:\n");
    for (int i = 0; i < totalProdutos; i++) {
        printf("ID: %d | Produto: %s | Valor: R$ %.2f | Quantidade: %d\n", produtos[i].id, produtos[i].nome, produtos[i].valor, produtos[i].quantidade);
    }
}

// Excluir produto
void excluirProduto() {
    int id;
    printf("Informe o ID do produto que deseja excluir: ");
    scanf("%d", &id);

    if (id < 1 || id > totalProdutos) {
        printf("Produto nao encontrado.\n");
        return;
    }

    Produto *p = &produtos[id - 1];  // Acessar o produto pelo ID

    printf("Produto a ser excluido: ID: %d | Nome: %s\n", p->id, p->nome);
    char resposta;
    printf("Deseja realmente excluir este produto? (s - Sim, n - Nao): ");
    scanf(" %c", &resposta);

    if (resposta == 's' || resposta == 'S') {
        // Move todos os produtos após o excluído uma posição atrás
        for (int i = id - 1; i < totalProdutos - 1; i++) {
            produtos[i] = produtos[i + 1];
        }

        totalProdutos--;  // Reduz o contador de produtos
        printf("Produto excluido com sucesso!\n");
    } else {
        printf("Exclusao cancelada. Retornando ao menu de produtos.\n");
    }
}

void menuProdutos() {
    int opcao;
    
    do {
        printf("\n Menu de Produtos:\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Editar Produto\n");
        printf("3. Vender Produto\n");
        printf("4. Visualizar Produtos\n");
        printf("5. Excluir Produto\n");
        printf("6. Retornar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                cadastrarProduto();
                break;
            case 2:
                editarProduto();
                break;
            case 3:
                venderProduto();
                break;
            case 4:
                visualizarProdutos();
                break;
            case 5:
                excluirProduto();
                break;
            case 6:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 6);
    
    return 0;
}
