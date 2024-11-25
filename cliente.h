#ifndef CLIENTES_H
#define CLIENTES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_NOME_CLIENTE 50
#define TAMANHO_ENDERECO_CLIENTE 100
#define TAMANHO_TELEFONE_CLIENTE 20

struct cliente {
    int id;
    char nome[TAMANHO_NOME_CLIENTE];
    char endereco[TAMANHO_ENDERECO_CLIENTE];
    char telefone[TAMANHO_TELEFONE_CLIENTE];
    struct cliente* prox;
};

typedef struct cliente Cliente;
typedef Cliente *Clientes;
int idClientes = 1;

void esperarEnterCliente() {
    fflush(stdin);
    printf("Pressione Enter para continuar...\n");
    getchar();
    fflush(stdin);
}

Clientes* criarListaClientes() {
    Clientes* clientes = (Clientes*) malloc(sizeof(Clientes));
    if(clientes != NULL) {
        *clientes = NULL;
        return clientes;
    } else {
        printf("Erro de alocacao na criacao da lista de clientes...\n");
        exit(0);
    }
}

Cliente* criarCliente() {
    Cliente* novoCliente = (Cliente*) malloc(sizeof(Cliente));
    if(novoCliente == NULL) {
        printf("Erro de alocacao na criacao de um novo cliente...\n");
        return NULL;
    }
    novoCliente->id = idClientes;
    idClientes++;
    novoCliente->prox = NULL;
    fflush(stdin);
    printf("Informe o nome do cliente: ");
    fgets(novoCliente->nome, TAMANHO_NOME_CLIENTE, stdin);
    fflush(stdin);
    printf("Informe o endereco do cliente: ");
    fgets(novoCliente->endereco, TAMANHO_ENDERECO_CLIENTE, stdin);
    fflush(stdin);
    printf("Informe o telefone do cliente: ");
    fgets(novoCliente->telefone, TAMANHO_TELEFONE_CLIENTE, stdin);
    fflush(stdin);
    return novoCliente;
}

void inserirCliente(Clientes* clientes) {
    printf("\tCadastrando novo Cliente: \n");
    Cliente* novoCliente = criarCliente();
    if(*clientes == NULL) {
        *clientes = novoCliente;
    } else {
        Cliente* tmp = *clientes;
        while (tmp->prox != NULL) {
            tmp = tmp->prox;
        }
        tmp->prox = novoCliente;
    }
    printf("Cliente criado com sucesso!\n");
}

void imprimirCliente(Cliente* cliente) {
    printf("\nCliente: \n[ID#%d]\n", cliente->id);
    printf("Nome: %s", cliente->nome);
    printf("Endereco: %s", cliente->endereco);
    printf("Telefone: %s", cliente->telefone);
}

void listarClientes(Clientes* clientes) {
    if(*clientes == NULL) {
        printf("Não existem clientes cadastrados\n");
    } else {
        Cliente* cliente = *clientes;
        while (cliente != NULL) {
            imprimirCliente(cliente);
            cliente = cliente->prox;
        }
    }
}

void listarClientesFiltradosPorNome(Clientes* clientes, char filtro[TAMANHO_NOME_CLIENTE]) {
    if(*clientes == NULL) {
        printf("Não existem clientes cadastrados\n");
    } else {
        Cliente* cliente = *clientes;
        while (cliente != NULL) {
            if(strstr(cliente->nome, filtro) != NULL) {
                imprimirCliente(cliente);
            }
            cliente = cliente->prox;
        }
    }
}

void limparClientes(Clientes* clientes) {
    if(*clientes == NULL) {
        printf("Nao existem clientes, a lista ja esta limpa!\n");
    } else {
        while ((*clientes) != NULL) {
            Cliente* cliente = *clientes;
            *clientes = (*clientes)->prox;
            free(cliente);
        }
        *clientes = NULL;
    }
}

Cliente* buscarClientePorID(Clientes* clientes, int id) {
    Cliente* cliente = NULL;
    Cliente* tmp = *clientes;
    while (tmp != NULL) {
        if (tmp->id == id) {
            cliente = tmp;
            break;
        }
        tmp = tmp->prox;
    }
    return cliente;
}

void editarCliente(Cliente* cliente) {
    int option;
    for(;;) {
        system("cls");
        imprimirCliente(cliente);
        printf("\n[1] - Nome\n");
        printf("[2] - Endereco\n");
        printf("[3] - Telefone\n");
        printf("[0] - Voltar\n");
        printf("Deseja alterar qual campo: ");
        scanf("%d", &option);
        if (option == 1) {
            printf("Informe o novo nome: ");
            fflush(stdin);
            fgets(cliente->nome, TAMANHO_NOME_CLIENTE, stdin);
            fflush(stdin);
        } else if (option == 2) {
            printf("Informe o novo endereco: ");
            fflush(stdin);
            fgets(cliente->endereco, TAMANHO_ENDERECO_CLIENTE, stdin);
            fflush(stdin);
        } else if (option == 3) {
            printf("Informe o novo telefone: ");
            fflush(stdin);
            fgets(cliente->telefone, TAMANHO_TELEFONE_CLIENTE, stdin);
            fflush(stdin);
        } else if (option == 0) {
            break;
        } else {
            printf("Opcao invalida!\n");
            esperarEnterCliente();
        }
    }
}

void editarClientes(Clientes* clientes) {
    int idBuscar, option = 2;
    char filtro[TAMANHO_NOME_CLIENTE];
    for(;;) {
        if (option == 1) {
            printf("Informe o ID do Cliente que deseja alterar: ");
            scanf("%d", &idBuscar);
            Cliente* cliente = buscarClientePorID(clientes, idBuscar);
            if (cliente != NULL) {
                editarCliente(cliente);
            } else {
                printf("Cliente não encontrado!\n");
            }
        } else if (option == 2) {
            system("cls");
            listarClientes(clientes);
        } else if (option == 3) {
            system("cls");
            printf("Informe o filtro do nome que deseja: ");
            scanf("%s", filtro);
            listarClientesFiltradosPorNome(clientes, filtro);
        } else if (option == 0) {
            return;
        } else {
            printf("Opcao invalida!\n");
            esperarEnterCliente();
            system("cls");
        }
        printf("[1] - Informar ID para edicao de cliente\n");
        printf("[2] - Listar todos os clientes\n");
        printf("[3] - Filtrar cliente por nome\n");
        printf("[0] - Voltar\n");
        printf("Informe a opcao que deseja: ");
        scanf("%d", &option);
    }
}

int confirmarRemocaoCliente() {
    int option;
    for(;;) {
        system("cls");
        printf("Tem certeza que deseja apagar o registro?\n");
        printf("[1] - Sim\n");
        printf("[0] - Nao\n");
        printf("Informe a opcao que deseja: ");
        scanf("%d", &option);
        if (option == 1 || option == 0) {
            return option;
        } else {
            printf("Opcao invalida!\n");
        }
    }
}

void removerClientePorID(Clientes* clientes, int id) {
    Cliente* remover = NULL;
    if ((*clientes)->id == id) {
        if (confirmarRemocaoCliente()) {
            remover = *clientes;
            *clientes = remover->prox;
            free(remover);
            printf("Removido com sucesso!\n");
            esperarEnterCliente();
        }
    } else {
        Cliente* ant = *clientes;
        while (ant->prox != NULL) {
            if (ant->prox->id == id) {
                remover = ant->prox;
                break;
            }
            ant = ant->prox;
        }
        if (remover == NULL) {
            printf("Cliente nao encontrado!\n");
            esperarEnterCliente();
        } else {
            if (confirmarRemocaoCliente()) {
                ant->prox = remover->prox;
                free(remover);
                printf("Removido com sucesso!\n");
                esperarEnterCliente();
            }
        }
    }
}

void removerClientes(Clientes* clientes) {
    int idBuscar, option = 2;
    char filtro[TAMANHO_NOME_CLIENTE];
    for(;;) {
        if (option == 1) {
            printf("Informe o ID do Cliente que deseja remover: ");
            scanf("%d", &idBuscar);
            removerClientePorID(clientes, idBuscar);
        } else if (option == 2) {
            system("cls");
            listarClientes(clientes);
        } else if (option == 3) {
            system("cls");
            printf("Informe o filtro do nome que deseja: ");
            scanf("%s", filtro);
            listarClientesFiltradosPorNome(clientes, filtro);
        } else if (option == 0) {
            return;
        } else {
            printf("Opcao invalida!\n");
            esperarEnterCliente();
            system("cls");
        }
        printf("[1] - Informar ID para remocao de cliente\n");
        printf("[2] - Listar Todos os clientes\n");
        printf("[3] - Filtrar cliente por nome\n");
        printf("[0] - Voltar\n");
        printf("Informe a opcao que deseja");
        scanf("%d", &option);
    }
}

void menuClientes(Clientes* clientes) {
    int option;
    for(;;) {
        system("cls");
        printf("\tCLIENTES\n");
        printf("[1] - Inserir Cliente\n");
        printf("[2] - Listar Clientes\n");
        printf("[3] - Editar Cliente\n");
        printf("[4] - Remover Cliente\n");
        printf("[0] - Voltar\n");
        printf("Informe a opcao que deseja: ");
        scanf("%d", &option);
        if (option == 1) {
            inserirCliente(clientes);
            esperarEnterCliente();
        } else if (option == 2) {
            listarClientes(clientes);
            esperarEnterCliente();
        } else if (option == 3) {
            editarClientes(clientes);
        } else if (option == 4) {
            removerClientes(clientes);
        } else if (option == 0) {
            return;
        } else {
            printf("Opcao invalida!");
            esperarEnterCliente();
        }
    }
}

#endif