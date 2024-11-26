/*#ifndef SERVICO_H
#define SERVICO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "animal.h"
#include "funcionario.h"

#define TAMANHO_DESCRICAO_SERVICO 200
enum Status {
    AGENDADO, CONCLUIDO, CANCELADO
}

struct servico {
    int id;
    char descricao[TAMANHO_DESCRICAO_SERVICO];
    float preco;
    struct servico *prox;
    struct servico *ant;
};

struct servicoExecutado {
    servico
}

typedef struct servico Servico;
typedef Servico *Servicos;

int idServicos = 1;

Servicos criarListaServicos() {
    Servicos servicos = NULL; 
    return servicos;
}

Servico *criarServico() {
    Servico *novo = (Servico *)malloc(sizeof(Servico));
    if (novo == NULL) {
        printf("Erro ao alocar memoria...\n");
        return NULL;
    }
    novo->id = idServicos++;
    novo->prox = NULL;
    novo->ant = NULL;

    printf("Informe a descricao do servico: ");
    fflush(stdin);
    fgets(novo->descricao, TAMANHO_DESCRICAO_SERVICO, stdin);

    printf("Informe o preco do servico: ");
    scanf("%f", &novo->preco);
    fflush(stdin);

    return novo;
}

void inserirServico(Servicos *servicos) {
    printf("\nCriacao:\n");

    Servico *novo = criarServico();
    if (*servicos == NULL) {
        *servicos = novo;
    } else {
        Servico *atual = *servicos;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
        novo->ant = atual;
    }
    printf("Servico cadastrado!\n");
    printf("Pressione enter para continuar...\n");
    getchar();
    system("cls");
}

void visualizarServicos(Servicos servicos) {
    if (servicos == NULL) {
        printf("Nenhum servico encontrado\n");
    } else {
        Servico *serv = servicos;
        while (serv != NULL) {
            printf("\nID do servico: %i\n", serv->id);
            printf("Descricao: %s", serv->descricao);
            printf("Preco: R$ %.2f\n", serv->preco);
            serv = serv->prox;
        }
    }
    printf("\nPressione enter para continuar...\n");
    getchar();
    system("cls");
}

void editarServico(Servicos servicos) {
    printf("\nEdicao:\n");

    if (servicos == NULL) {
        printf("Nenhum servico cadastrado para editar.\n");
        return;
    }

    visualizarServicos(servicos);
    int id;
    printf("Insira o ID do servico que deseja editar: ");
    scanf("%d", &id);
    fflush(stdin);

    Servico *serv = servicos;
    while (serv != NULL && serv->id != id) {
        serv = serv->prox;
    }

    if (serv == NULL) {
        printf("Servico com ID %d nao encontrado.\n", id);
    } else {
        printf("Editando servico com ID %d:\n", id);

        printf("Descricao atual: %s", serv->descricao);
        printf("Informe a nova descricao: ");
        fflush(stdin);
        fgets(serv->descricao, TAMANHO_DESCRICAO_SERVICO, stdin);

        printf("Preco atual: R$ %.2f\n", serv->preco);
        printf("Informe o novo preco: ");
        scanf("%f", &serv->preco);
        fflush(stdin);

        printf("Servico atualizado!\n");
    }

    printf("Pressione enter para continuar...\n");
    getchar();
    system("cls");
}

void deletarServico(Servicos *servicos) {
    printf("\nExclusao:\n");

    if (*servicos == NULL) {
        printf("Nenhum servico cadastrado para excluir.\n");
        return;
    }

    visualizarServicos(*servicos);

    int id;
    printf("Insira o ID do servico que deseja excluir: ");
    scanf("%d", &id);
    fflush(stdin);

    Servico *atual = *servicos, *anterior = NULL;
    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Servico com ID %d nao encontrado.\n", id);
    } else {
        if (anterior == NULL) {
            *servicos = atual->prox;
            if (*servicos != NULL)
                (*servicos)->ant = NULL;
        } else {
            anterior->prox = atual->prox;
            if (atual->prox != NULL)
                atual->prox->ant = anterior;
        }
        free(atual);
        printf("Servico com ID %d foi excluido.\n", id);
    }

    printf("Pressione enter para continuar...\n");
    getchar();
}
/*
void executarServico(Servicos servicos, Funcionarios *funcionarios, Pets *pets) {
    printf("\nExecutando:\n");

    if (servicos == NULL) {
        printf("Nenhum servico cadastrado.\n");
        return;
    }

    if (*funcionarios == NULL) {
        printf("Nenhum funcionario cadastrado.\n");
        return;
    }

    if (*pets == NULL) {
        printf("Nenhum pet cadastrado.\n");
        return;
    }

    int idServico, idFuncionario, idPets;
    printf("Informe o ID do servico a ser executado: ");
    scanf("%d", &idServico);
    fflush(stdin);

    Servico *serv = servicos;
    while (serv != NULL && serv->id != idServico) {
        serv = serv->prox;
    }

    if (serv == NULL) {
        printf("Servico com ID %d nao encontrado.\n", idServico);
        return;
    }

    printf("Informe o ID do funcionario que vai executar o servico: ");
    scanf("%d", &idFuncionario);
    fflush(stdin);

    Funcionario *func = *funcionarios;
    while (func != NULL && func->id != idFuncionario) {
        func = func->prox;
    }

    if (func == NULL) {
        printf("Funcionario com ID %d nao encontrado.\n", idFuncionario);
        return;
    }

    printf("Informe o ID do pet para o qual o servico sera executado: ");
    scanf("%d", &idPets);
    fflush(stdin);

    Pet *pet = *pets;
    while (pet != NULL && pet->id != idPets) {
        pet = pet->prox;
    }

    if (pet == NULL) {
        printf("Pet com ID %d nao encontrado.\n", idPets);
        return;
    }

    printf("Servico com ID %d executado por %s no pet %s.\n", serv->id, func->nome, pet->nome);
    printf("Descricao do servico: %s", serv->descricao);
    printf("Preco do servico: R$ %.2f\n", serv->preco);

    printf("Servico executado com sucesso!\n");
    printf("Pressione enter para continuar...\n");
    getchar();
}
*/

/*
void agendarServico(Servicos servicos) {
    printf("\nAgendamento:\n");

    if (servicos == NULL) {
        printf("Nenhum servico cadastrado.\n");
        return;
    }

    int idServico;
    char data[11];

    printf("Informe o ID do servico a ser agendado: ");
    scanf("%d", &idServico);
    fflush(stdin);

    Servico *serv = servicos;
    while (serv != NULL && serv->id != idServico) {
        serv = serv->prox;
    }

    if (serv == NULL) {
        printf("Servico com ID %d nao encontrado.\n", idServico);
        return;
    }

    printf("Informe a data do agendamento (dd/mm/aaaa): ");
    scanf("%s", data);

    printf("\nServico agendado com sucesso!\n"); 
    printf("Servico: %s", serv->descricao);
    printf("Preco: R$ %.2f\n", serv->preco);
    printf("Data de agendamento: %s\n", data);
}
*/

/*void emitirRecibo(Servicos servicos) {
    printf("\nRecibo:\n");

    if (servicos == NULL) {
        printf("Nenhum servico cadastrado.\n");
        return;
    }

    int idServico;

    printf("Informe o ID do servico para emitir recibo: ");
    scanf("%d", &idServico);
    fflush(stdin);

    Servico *serv = servicos;
    while (serv != NULL && serv->id != idServico) {
        serv = serv->prox;
    }

    if (serv == NULL) {
        printf("Servico com ID %d nao encontrado.\n", idServico);
        return;
    }

    printf("\n--- RECIBO ---\n");
    printf("Servico: %s", serv->descricao);
    printf("Preco: R$ %.2f\n", serv->preco);
    printf("Obrigado pela preferencia!\n");
    printf("----------------\n");

    printf("Pressione enter para continuar...\n");
    getchar();
}

void menuServicos(Servicos servicos, Funcionarios *funcionarios, Pets *pets) {
    int opcao;

    do {
        printf("\tSERVICOS\n");
        printf("[1] - Cadastrar Servico\n");
        printf("[2] - Listar Servicos\n");
        printf("[3] - Editar Servico\n");
        printf("[4] - Excluir Servico\n");
        printf("[5] - Executar Servico\n");
        printf("[6] - Agendar Servico\n");
        printf("[7] - Emitir Recibo\n");
        printf("[0] - Voltar\n");
        printf("Informe a opcao que deseja: ");
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 1:
                inserirServico(&servicos);
                break;
            case 2:
                visualizarServicos(servicos);
                break;
            case 3:
                editarServico(servicos);
                break;
            case 4:
                deletarServico(&servicos);
                break;
            case 5:
                executarServico(servicos, funcionarios, pets);
                break;
            case 6:
                agendarServico(servicos);
                break;
            case 7:
                emitirRecibo(servicos);
                break;
            case 0:
                return;
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (opcao != 8);
}

#endif
/*