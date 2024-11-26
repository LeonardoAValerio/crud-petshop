#ifndef FINANCEIRO_H
#define FINANCEIRO_H


#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>

#include "servico.h"

void esperaEnter() {
    fflush(stdin);
    printf("Pressione Enter para continuar...\n");
    getchar();
    fflush(stdin);
}

void relatorioServ(Agendamentos *agendamentos, Servicos *servicos) {
    int contServicos = 0;
    int contExecutados = 0;

    printf("\n--- Relatorio de Servicos ---\n");

    if (*servicos == NULL) {
        printf("Nenhum servico cadastrado no sistema.\n");
        esperaEnter();
        return;
    }

    if (*agendamentos == NULL) {
        printf("\n--- Lista de Servicos Disponiveis ---\n");
        Servico *servAtual = *servicos;
        while (servAtual != NULL) {
            printf("ID: %i\n", servAtual->id);
            printf("Servico: %s", servAtual->descricao);
            printf("Preco: R$ %.2f\n", servAtual->preco);
            printf("---------------------------\n");
            servAtual = servAtual->prox;
        }
        esperaEnter();
        return;
    }

    float total = 0.0;
    int encontrouAgendamento = 0;

    printf("\n--- Lista de Servicos Disponiveis ---\n");
        Servico *servAtual = *servicos;
        while (servAtual != NULL) {
            printf("ID: %i\n", servAtual->id);
            printf("Servico: %s", servAtual->descricao);
            printf("Preco: R$ %.2f\n", servAtual->preco);
            printf("---------------------------\n");
            servAtual = servAtual->prox;
            contServicos++;
        }

    printf("\n--- Lista de Servicos Com Agendamento ---\n");
    Agendamento *agAtual = *agendamentos;

    while (agAtual != NULL) {
        Servico *servAtual = *servicos;
        while (servAtual != NULL) {
            if (servAtual->id == agAtual->idServico) {
                printf("\nAgendamento ID: %d\n", agAtual->idAgendamento);
                printf("Servico: %s", servAtual->descricao);
                printf("Preco: R$ %.2f\n", servAtual->preco);
                printf("Status: %s\n", agAtual->status);
                printf("Data: %s\n", agAtual->data);

                if (strcmp(agAtual->status, "executado") == 0) {
                    total += servAtual->preco;
                    contExecutados++;
                }

                printf("---------------------------\n");
                encontrouAgendamento = 1;
                break;
            }
            servAtual = servAtual->prox;
        }

        if (servAtual == NULL) {
            printf("Agendamento ID: %d - Servico nao encontrado!\n", agAtual->idAgendamento);
        }

        agAtual = agAtual->prox;
    }

    if (!encontrouAgendamento) {
        printf("Nenhum agendamento associado a servicos encontrados.\n");
    }

    printf("\nTotal de Servicos Cadastrados: %d\n",contServicos);
    printf("Total de Servicos Executados: %d",contExecutados);
    printf("\nTotal arrecadado com servicos executados: R$ %.2f\n", total);
    esperaEnter();
}


void relatorioVen(){
    printf("\n--- Relatorio de Produtos ---\n");

}

void relatorioMes() {
    printf("\n--- Relatorio Mensal ---\n");
}

void menuFinanceiro(Agendamentos *agendamento, Servicos *servicos){
    int option;
    for(;;) {
        system("cls");
        printf("\t---FINANCEIRO---\n");
        printf("[1] - Relatorio de Servicos \n");
        printf("[2] - Relatorio de Vendas \n");
        printf("[3] - Relatorio Mensal \n");
        printf("[0] - Voltar \n\n");
        printf("Informe a opcao que deseja: ");
        fflush(stdin);
        scanf("%d", &option);


        if(option == 1){
            relatorioServ(agendamento, servicos);
            esperaEnter();
        }else if(option == 2){
            relatorioVen();
            esperaEnter();
        }else if(option == 3){
            relatorioMes();
            esperaEnter();
        }else if (option == 0) {
            printf("Voltando...\n");
            break;
        }else{
            printf("Escolha uma opcao valida...");
        }
    }
}

#endif