#ifndef SERVICO_H
#define SERVICO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "animal.h"
#include "funcionario.h"

#define TAMANHO_DESCRICAO_SERVICO 200

struct servico {
    int id;
    char descricao[TAMANHO_DESCRICAO_SERVICO];
    float preco;
    struct servico *prox;
    struct servico *ant;
};
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
    fgets(novo->descricao, TAMANHO_DESCRICAO_SERVICO, stdin);

    printf("Informe o preco do servico: ");
    scanf("%f", &novo->preco);
    getchar();
    return novo;
}

void inserirServico(Servicos *servicos) {
    printf("\nCadastro de Servico:\n");

    Servico *novo = criarServico();
    if (novo == NULL) {
        printf("Falha ao criar o servico!\n");
        return;
    }

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

    printf("Servico cadastrado com sucesso!\n");
    printf("Pressione enter para continuar...\n");
    getchar();
}

void visualizarServicos(Servicos servicos) {
    if (servicos == NULL) {
        printf("Nenhum servico cadastrado.\n");
    } else {
        Servico *serv = servicos;
        while (serv != NULL) {
            printf("\nID do Servico: %i\n", serv->id);
            printf("Descricao: %s", serv->descricao);
            printf("Preco: R$ %.2f\n", serv->preco);
            serv = serv->prox;
        }
    }
    printf("\nPressione enter para continuar...\n");
    getchar();
}

void editarServico(Servicos servicos) {
    printf("\nEdicao de Servico:\n");

    if (servicos == NULL) {
        printf("Nenhum servico cadastrado para editar.\n");
        return;
    }

    visualizarServicos(servicos);

    int id;
    printf("Informe o ID do servico que deseja editar: ");
    scanf("%d", &id);
    getchar();
    Servico *serv = servicos;
    while (serv != NULL && serv->id != id) {
        serv = serv->prox;
    }

    if (serv == NULL) {
        printf("Serviço com ID %d nao encontrado.\n", id);
    } else {
        printf("Editando servico com ID %d:\n", id);

        printf("Descricao atual: %s", serv->descricao);
        printf("Informe a nova descricao: ");
        fgets(serv->descricao, TAMANHO_DESCRICAO_SERVICO, stdin);

        printf("Preco atual: R$ %.2f\n", serv->preco);
        printf("Informe o novo preco: ");
        scanf("%f", &serv->preco);
        getchar();

        printf("Servico atualizado com sucesso!\n");
    }

    printf("Pressione enter para continuar...\n");
    getchar();
}

void deletarServico(Servicos *servicos) {
    printf("\nExclusao de Servico:\n");

    if (*servicos == NULL) {
        printf("Nenhum servico cadastrado para excluir.\n");
        return;
    }

    visualizarServicos(*servicos);

    int id;
    printf("Informe o ID do servico que deseja excluir: ");
    scanf("%d", &id);
    getchar();

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
        printf("Servico com ID %d excluido com sucesso.\n", id);
    }

    printf("Pressione enter para continuar...\n");
    getchar();
}

#define TAMANHO_STATUS 20

struct agendamento {
    int idAgendamento;
    int idServico;
    int idPet;
    int idFuncionario;
    char data[20];
    char status[TAMANHO_STATUS]; 
    struct agendamento *prox;
};
typedef struct agendamento Agendamento;
typedef Agendamento* Agendamentos;

int idAgendamentos = 1;

Agendamentos criarListaAgendamentos() {
    return NULL;
}

Agendamento* criarAgendamento() {
    Agendamento* novo = (Agendamento*)malloc(sizeof(Agendamento));
    if (novo == NULL) {
        printf("Erro ao alocar memoria...\n");
        return NULL;
    }
    novo->idAgendamento = idAgendamentos++;
    novo->prox = NULL;

    printf("Informe o ID do servico: ");
    scanf("%d", &novo->idServico);

    printf("Informe o ID do pet: ");
    scanf("%d", &novo->idPet);

    printf("Informe o ID do funcionario: ");
    scanf("%d", &novo->idFuncionario);

    printf("Informe a data do agendamento (DD/MM/AAAA): ");
    scanf("%s", novo->data);

    strcpy(novo->status, "agendado");

    return novo;
}

void inserirAgendamento(Agendamentos *agendamentos, Servicos servicos, Funcionarios *funcionarios, Pets *pets) {
    Agendamento* novo = criarAgendamento();
    if (novo == NULL) {
        printf("Falha ao criar o agendamento!\n");
        return;
    }

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

    if (*agendamentos == NULL) {
        *agendamentos = novo;
    } else {
        Agendamento* atual = *agendamentos;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }

    printf("Agendamento cadastrado com sucesso!\n");
}

void listarAgendamentos(Agendamentos agendamentos) {
    if (agendamentos == NULL) {
        printf("Nenhum agendamento encontrado.\n");
    } else {
        Agendamento* ag = agendamentos;
        while (ag != NULL) {
            printf("\nID Agendamento: %d\n", ag->idAgendamento);
            printf("Data: %s\n", ag->data);
            printf("Servico ID: %d\n", ag->idServico);
            printf("Pet ID: %d\n", ag->idPet);
            printf("Funcionario ID: %d\n", ag->idFuncionario);
            printf("Status: %s\n", ag->status);
            ag = ag->prox;
        }
    }
    printf("\nPressione enter para continuar...\n");
    getchar();
}

void executarAgendamento(Agendamentos* agendamentos) {
    int idAgendamento;
    printf("\nInforme o ID do agendamento a ser executado: ");
    scanf("%d", &idAgendamento);

    Agendamento* ag = *agendamentos;
    while (ag != NULL && ag->idAgendamento != idAgendamento) {
        ag = ag->prox;
    }

    if (ag == NULL) {
        printf("Agendamento com ID %d nao encontrado.\n", idAgendamento);
        return;
    }

    if (strcmp(ag->status, "executado") == 0) {
        printf("O agendamento ja foi executado.\n");
        return;
    }

    if (strcmp(ag->status, "cancelado") == 0) {
        printf("O agendamento foi cancelado e nao pode ser executado.\n");
        return;
    }

    strcpy(ag->status, "executado");
    printf("Agendamento ID %d foi marcado como executado.\n", idAgendamento);
}

void cancelarAgendamento(Agendamentos* agendamentos) {
    int idAgendamento;
    printf("\nInforme o ID do agendamento a ser cancelado: ");
    scanf("%d", &idAgendamento);

    Agendamento* ag = *agendamentos;
    while (ag != NULL && ag->idAgendamento != idAgendamento) {
        ag = ag->prox;
    }

    if (ag == NULL) {
        printf("Agendamento com ID %d nao encontrado.\n", idAgendamento);
        return;
    }

    if (strcmp(ag->status, "executado") == 0) {
        printf("O agendamento já foi executado e nao pode ser cancelado.\n");
        return;
    }

    if (strcmp(ag->status, "cancelado") == 0) {
        printf("O agendamento ja foi cancelado.\n");
        return;
    }

    strcpy(ag->status, "cancelado");
    printf("Agendamento ID %d foi cancelado.\n", idAgendamento);
}

void gerarRecibo(Agendamentos *agendamentos, Servicos *servicos, Funcionarios *funcionarios, Pets *pets) {
    int idAgendamento;
    printf("\nInforme o ID do agendamento para gerar o recibo: ");
    scanf("%d", &idAgendamento);

    Agendamento* ag = *agendamentos;
    while (ag != NULL && ag->idAgendamento != idAgendamento) {
        ag = ag->prox;
    }

    if (ag == NULL) {
        printf("Agendamento com ID %d nao encontrado.\n", idAgendamento);
        return;
    }

    if (strcmp(ag->status, "executado") != 0) {
        printf("O serviço ainda nao foi executado.\n");
        return;
    }

    Servico* serv = *servicos;
    while (serv != NULL && serv->id != ag->idServico) {
        serv = serv->prox;
    }

    if (serv == NULL) {
        printf("Serviço com ID %d nao encontrado.\n", ag->idServico);
        return;
    }

    Funcionario* func = *funcionarios;
    while (func != NULL && func->id != ag->idFuncionario) {
        func = func->prox;
    }

    if (func == NULL) {
        printf("Funcionário com ID %d nao encontrado.\n", ag->idFuncionario);
        return;
    }

    Pet* pet = *pets;
    while (pet != NULL && pet->id != ag->idPet) {
        pet = pet->prox;
    }

    if (pet == NULL) {
        printf("Pet com ID %d nao encontrado.\n", ag->idPet);
        return;
    }

    printf("\n--- RECIBO ---\n");
    printf("Agendamento ID: %d\n", ag->idAgendamento);
    printf("Serviço: %s", serv->descricao);
    printf("Preco: R$ %.2f\n", serv->preco);
    printf("Pet: %s\n", pet->nome);
    printf("Funcionario: %s\n", func->nome);
    printf("Data do Agendamento: %s\n", ag->data);
    printf("----------------\n");
}

void menuAgendamentos(Agendamentos *agendamentos, Servicos *servicos, Funcionarios *funcionarios, Pets *pets) {
    int opcao;
    do {
        printf("\nMenu de Agendamentos:\n");
        printf("[1] - Adicionar Agendamento\n");
        printf("[2] - Listar Agendamentos\n");
        printf("[3] - Executar Agendamento\n");
        printf("[4] - Cancelar Agendamento\n");
        printf("[5] - Gerar Recibo\n");
        printf("[0] - Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirAgendamento(agendamentos, servicos, funcionarios, pets);
                break;
            case 2:
                listarAgendamentos(*agendamentos);
                break;
            case 3:
                executarAgendamento(agendamentos);
                break;
            case 4:
                cancelarAgendamento(agendamentos);
                break;
            case 5:
                gerarRecibo(agendamentos, servicos, funcionarios, pets);
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opção invalida, tente novamente.\n");
                break;
        }
    } while (opcao != 0);
}

void menuServicos(Servicos *servicos, Agendamentos *agendamentos, Funcionarios *funcionarios, Pets *pets) {
    int opcao;
    do {
        printf("\nMenu de Servicos:\n");
        printf("[1] - Cadastrar Servico\n");
        printf("[2] - Listar Servicos\n");
        printf("[3] - Editar Servico\n");
        printf("[4] - Excluir Servico\n");
        printf("[5] - Agendamentos\n");
        printf("[0] - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                inserirServico(servicos);
                break;
            case 2:
                visualizarServicos(*servicos);
                break;
            case 3:
                editarServico(*servicos);
                break;
            case 4:
                deletarServico(servicos);
                break;
            case 5:
                menuAgendamentos(agendamentos, servicos, funcionarios, pets);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida, tente novamente.\n");
                break;
        }
    } while (opcao != 8);
}

#endif