/*#ifndef SERVICO_H
#define SERVICO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "animal.h"
#include "funcionario.h"

#define TAMANHO_DESCRICAO_SERVICO 200

void esperarEnterServ() {
    fflush(stdin);
    printf("Pressione Enter para continuar...\n");
    getchar();
    fflush(stdin);
}

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

Servicos *criarListaServicos() {
    Servicos *servicos = (Servicos*) malloc(sizeof(Servico*));
    if(servicos != NULL) {
        *servicos = NULL;
    }else {
        printf("Erro na alocacao da lista de servicos!");
        exit(0);
    }
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
    fflush(stdin);

    printf("Informe o preco do servico: ");
    fflush(stdin);
    scanf("%f", &novo->preco);
    fflush(stdin);
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

    esperarEnterServ();
}

void visualizarServicos(Servicos *servicos) {
    if (*servicos == NULL) {
        printf("Nenhum servico cadastrado.\n");
        esperarEnterServ();
    } else {
        Servico *serv = *servicos;
        while (serv != NULL) {
            printf("\nID do Servico: %i\n", serv->id);
            printf("Descricao: %s", serv->descricao);
            printf("Preco: R$ %.2f\n", serv->preco);
            serv = serv->prox;
        }
    }
    esperarEnterServ();
}

void editarServico(Servicos *servicos) {
    printf("\nEdicao de Servico:\n");

    if (servicos == NULL) {
        printf("Nenhum servico cadastrado para editar.\n");
        esperarEnterServ();
        return;
    }

    visualizarServicos(servicos);

    int id;
    printf("Informe o ID do servico que deseja editar: \n");
    fflush(stdin);
    scanf("%d", &id);
    fflush(stdin);
    Servico* serv = *servicos;
    while (serv != NULL && serv->id != id) {
        serv = serv->prox;
    }

    if (serv == NULL) {
        printf("Serviço com ID %d nao encontrado.\n", id);
    } else {
        printf("Editando servico com ID %d:\n", id);

        printf("Descricao atual: %s", serv->descricao);
        printf("Informe a nova descricao: ");
        fflush(stdin);
        fgets(serv->descricao, TAMANHO_DESCRICAO_SERVICO, stdin);
        fflush(stdin);

        printf("Preco atual: R$ %.2f", serv->preco);
        printf("Informe o novo preco: ");
        fflush(stdin);
        scanf("%f", &serv->preco);
        fflush(stdin);

        printf("Servico atualizado com sucesso!\n");
    }

    esperarEnterServ();
}

void deletarServico(Servicos *servicos) {
    printf("\nExclusao de Servico:\n");

    if (*servicos == NULL) {
        printf("Nenhum servico cadastrado para excluir.\n");
        return;
    }

    visualizarServicos(servicos);

    int id;
    printf("Informe o ID do servico que deseja excluir: \n");
    fflush(stdin);
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
        printf("Servico com ID %d excluido com sucesso.\n", id);
    }

    esperarEnterServ();
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

Agendamentos* criarListaAgendamentos() {
    Agendamentos *agendamentos = (Agendamentos*) malloc(sizeof(agendamentos));
    if(agendamentos != NULL) {
        *agendamentos = NULL;
    }else {
        printf("Erro na alocacao da lista de agendamentos!");
        exit(0);
    }
    return agendamentos;
}

Agendamento* criarAgendamento() {
    Agendamento* novo = (Agendamento*) malloc(sizeof(Agendamento));
    if (novo == NULL) {
        printf("Erro ao alocar memoria...\n");
        return NULL;
    }
    novo->idAgendamento = idAgendamentos++;
    novo->prox = NULL;

    printf("Informe o ID do servico: ");
    fflush(stdin);
    scanf("%d", &novo->idServico);
    fflush(stdin);

    printf("Informe o ID do pet: ");
    fflush(stdin);
    scanf("%d", &novo->idPet);
    fflush(stdin);

    printf("Informe o ID do funcionario: ");
    fflush(stdin);
    scanf("%d", &novo->idFuncionario);
    fflush(stdin);

    printf("Informe a data do agendamento (DD/MM/AAAA): ");
    fflush(stdin);
    scanf("%s", novo->data);
    fflush(stdin);

    strcpy(novo->status, "agendado");
    return novo;
}

void inserirAgendamento(Agendamentos *agendamentos, Servicos *servicos, Funcionarios *funcionarios, Pets *pets) {
    Agendamento* novo = criarAgendamento();
    if (novo == NULL) {
        printf("Falha ao criar o agendamento!\n");
        esperarEnterServ();
        return;
    }

    if (*servicos == NULL) {
        printf("Servico com ID %d nao encontrado.\n", novo->idServico);
        esperarEnterServ();
        return;
    }

    if (*funcionarios == NULL) {
        printf("Funcionario com ID %d nao encontrado.\n", novo->idFuncionario);
        esperarEnterServ();
        return;
    }

    if (*pets == NULL) {
        printf("Pet com ID %d nao encontrado.\n", novo->idPet);
        esperarEnterServ();
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
    esperarEnterServ();
}

void listarAgendamentos(Agendamentos *agendamentos) {
    if (*agendamentos == NULL) {
        printf("Nenhum agendamento encontrado.\n");
        esperarEnterServ();
    } else {
        Agendamento* ag = *agendamentos;
        while (ag != NULL) {
            printf("\nID: %d\n", ag->idAgendamento);
            printf("Data: %s\n", ag->data);
            printf("Servico ID: %d\n", ag->idServico);
            printf("Pet ID: %d\n", ag->idPet);
            printf("Funcionario ID: %d\n", ag->idFuncionario);
            printf("Status: %s\n", ag->status);
            ag = ag->prox;
        }
    }
    esperarEnterServ();
}

void executarAgendamento(Agendamentos* agendamentos) {
    int idAgendamento;

    listarAgendamentos(agendamentos);

    printf("\nInforme o ID do agendamento a ser executado: ");
    fflush(stdin);
    scanf("%d", &idAgendamento);
    fflush(stdin);

    Agendamento* ag = *agendamentos;
    while (ag != NULL && ag->idAgendamento != idAgendamento) {
        ag = ag->prox;
    }

    if (ag == NULL) {
        printf("Agendamento com ID %d nao encontrado.\n", idAgendamento);
        esperarEnterServ();
        return;
    }

    if (strcmp(ag->status, "executado") == 0) {
        printf("\nO agendamento ja foi executado.\n");
        esperarEnterServ();
        return;
    }

    if (strcmp(ag->status, "cancelado") == 0) {
        printf("\nO agendamento foi cancelado e nao pode ser executado.\n");
        esperarEnterServ();
        return;
    }

    strcpy(ag->status, "executado");
    printf("Agendamento ID %d foi marcado como executado.\n", idAgendamento);
    esperarEnterServ();
}

void cancelarAgendamento(Agendamentos* agendamentos) {
    int idAgendamento;

    listarAgendamentos(agendamentos);

    printf("\nInforme o ID do agendamento a ser cancelado: ");
    fflush(stdin);
    scanf("%d", &idAgendamento);
    fflush(stdin);

    Agendamento* ag = *agendamentos;
    while (ag != NULL && ag->idAgendamento != idAgendamento) {
        ag = ag->prox;
    }

    if (ag == NULL) {
        printf("\nAgendamento com ID %d nao encontrado.\n", idAgendamento);
        esperarEnterServ();
        return;
    }

    if (strcmp(ag->status, "executado") == 0) {
        printf("O agendamento ja foi executado e nao pode ser cancelado.\n");
        esperarEnterServ();
        return;
    }

    if (strcmp(ag->status, "cancelado") == 0) {
        printf("O agendamento ja foi cancelado.\n");
        esperarEnterServ();
        return;
    }

    strcpy(ag->status, "cancelado");
    printf("Agendamento ID %d foi cancelado.\n", idAgendamento);
    esperarEnterServ();
}

void gerarRecibo(Agendamentos *agendamentos, Servicos *servicos, Funcionarios *funcionarios, Pets *pets) {
    int idAgendamento;

    listarAgendamentos(agendamentos);

    printf("\nInforme o ID do agendamento para gerar o recibo: ");
    fflush(stdin);
    scanf("%d", &idAgendamento);
    fflush(stdin);

    Agendamento* ag = *agendamentos;
    while (ag != NULL && ag->idAgendamento != idAgendamento) {
        ag = ag->prox;
    }

    if (ag == NULL) {
        printf("Agendamento com ID %d nao encontrado.\n", idAgendamento);
        esperarEnterServ();
        return;
    }

    if (strcmp(ag->status, "executado") != 0) {
        printf("O servico ainda nao foi executado.\n");
        esperarEnterServ();
        return;
    }

    Servico* serv = *servicos;
    while (serv != NULL && serv->id != ag->idServico) {
        serv = serv->prox;
    }

    if (serv == NULL) {
        printf("Servico com ID %d nao encontrado.\n", ag->idServico);
        esperarEnterServ();
        return;
    }

    Funcionario* func = *funcionarios;
    while (func != NULL && func->id != ag->idFuncionario) {
        func = func->prox;
    }

    if (func == NULL) {
        printf("Funcionario com ID %d nao encontrado.\n", ag->idFuncionario);
        esperarEnterServ();
        return;
    }

    Pet* pet = *pets;
    while (pet != NULL && pet->id != ag->idPet) {
        pet = pet->prox;
    }

    if (pet == NULL) {
<<<<<<< HEAD
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
=======
        printf("Pet com ID %d nao encontrado.\n", ag->idPet);
        esperarEnterServ();
>>>>>>> main
        return;
    }

    printf("\n--- RECIBO ---\n");
    printf("ID: %d\n", ag->idAgendamento);
    printf("Servico: %s", serv->descricao);
    printf("Preco: R$ %.2f\n", serv->preco);
    printf("Pet: %s\n", pet->nome);
    printf("Funcionario: %s\n", func->nome);
    printf("Data do Agendamento: %s\n", ag->data);
    printf("----------------\n");
    esperarEnterServ();
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
        fflush(stdin);
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 1:
                inserirAgendamento(agendamentos, servicos, funcionarios, pets);
                break;
            case 2:
                listarAgendamentos(agendamentos);
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
                return;
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
        printf("[5] - Agendar Servico\n");
        printf("[0] - Sair\n");
        printf("Escolha uma opcao: ");
        fflush(stdin);
        scanf("%d", &opcao);
        fflush(stdin);
        switch (opcao) {
            case 1:
                inserirServico(servicos);
                break;
            case 2:
                visualizarServicos(servicos);
                break;
            case 3:
                editarServico(servicos);
                break;
            case 4:
                deletarServico(servicos);
                break;
            case 5:
                menuAgendamentos(agendamentos, servicos, funcionarios, pets);
                break;
            case 0:
                printf("Saindo...\n");
                return;
            default:
                printf("Opção inválida, tente novamente.\n");
                break;
        }
    } while (opcao != 8);
}

<<<<<<< HEAD
#endif
/*
=======
#endif
>>>>>>> main
