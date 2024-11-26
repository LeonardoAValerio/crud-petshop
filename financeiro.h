#ifndef FINANCEIRO_H
#define FINANCEIRO_H

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>

#include "servico.h"
#include "produto.h"

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
            contServicos++;
        }
        printf("\nTotal de Servicos Cadastrados: %d\n",contServicos);
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

void relatorioProdutos(Vendas *vendas, Produtos *produtos) {
    printf("\n--- Relatorio de Produtos ---\n");

    if (produtos->totalProdutos == 0) {
        printf("Sem Produtos cadastrados\n\n");
        esperaEnter();
        return;
    }

    printf("\n--- Produtos cadastrados ---\n");
    Produto *pdAtual = produtos->inicio;
    int contProdutos = 0;
    float totalEstoque = 0.0;

    while (pdAtual != NULL) {
        printf("ID: %d\n", pdAtual->id);
        printf("Nome: %s\n", pdAtual->nome);
        printf("Quantidade em estoque: %d\n", pdAtual->quantidade);
        printf("Preco: R$ %.2f\n", pdAtual->valor);
        printf("---------------------------\n");
        totalEstoque += pdAtual->quantidade * pdAtual->valor;
        contProdutos++;
        pdAtual = pdAtual->proximo;
    }

    if (*vendas == NULL) {
        printf("Sem vendas registradas.\n");
        printf("\n\n--- Resumo do Estoque ---\n");
        printf("Total de Produtos Cadastrados: %d\n", contProdutos);
        printf("Valor Total Estimado do Estoque: R$ %.2f\n", totalEstoque);
        esperaEnter();
        return;
    }

    float total = 0.0;
    int totalVdPd = 0;
    int contVendas = 0;
    int encontrouVenda = 0;

    printf("\n--- Vendas Cadastradas ---\n");
    Venda *vdAtual = *vendas;

    while (vdAtual != NULL) {
        pdAtual = produtos->inicio;
        encontrouVenda = 0;

        while (pdAtual != NULL) {
            if (vdAtual->idProduto == pdAtual->id) {
                printf("\nProduto: \n[ID#%d]\n", vdAtual->idProduto);
                printf("Nome produto: %s\n", vdAtual->nomeProduto);
                printf("Cliente: %s\n", vdAtual->nomeCliente);
                printf("Valor produto: R$ %.2f\n", vdAtual->valorProduto);
                printf("Quantidade: %d\n", vdAtual->quantidade);
                printf("Valor total: R$ %.2f\n", vdAtual->valorTotal);
                printf("---------------------------\n");
                total += vdAtual->valorTotal;
                totalVdPd += vdAtual->quantidade;
                encontrouVenda = 1;
                contVendas++;
                break;
            }
            pdAtual = pdAtual->proximo;
        }

        if (!encontrouVenda) {
            printf("Venda com ID de produto inválido: %d\n", vdAtual->idProduto);
        }

        vdAtual = vdAtual->prox;
    }

    printf("\n\n--- Resumo do Estoque ---\n");
    printf("Total de Produtos Cadastrados: %d\n", contProdutos);
    printf("Valor Total Estimado do Estoque: R$ %.2f\n", totalEstoque);

    printf("\n\n--- Resumo do Vendas ---\n");
    printf("Total de Produtos Vendidos: %d\n", totalVdPd);
    printf("Total de Vendas: %d\n", contVendas);
    printf("Total arrecadado com Produtos Vendidos: R$ %.2f\n", total);

    esperaEnter();
}

void relatorioTotal(Agendamentos *agendamentos, Servicos *servicos, Vendas *vendas) {
    printf("\n--- Relatorio Financeiro ---\n");

    float totalArrecadadoServicos = 0.0;
    float totalArrecadadoProdutos = 0.0;

    if (*servicos != NULL && *agendamentos != NULL) {
        Agendamento *agAtual = *agendamentos;
        while (agAtual != NULL) {
            Servico *servAtual = *servicos;
            while (servAtual != NULL) {
                if (servAtual->id == agAtual->idServico && strcmp(agAtual->status, "executado") == 0) {
                    totalArrecadadoServicos += servAtual->preco;
                    break;
                }
                servAtual = servAtual->prox;
            }
            agAtual = agAtual->prox;
        }
    }

    if (*vendas != NULL) {
        Venda *vdAtual = *vendas;
        while (vdAtual != NULL) {
            totalArrecadadoProdutos += vdAtual->valorTotal;
            vdAtual = vdAtual->prox;
        }
    }

    printf("Total arrecadado com Servicos Executados: R$ %.2f\n", totalArrecadadoServicos);
    printf("Total arrecadado com Produtos Vendidos: R$ %.2f\n", totalArrecadadoProdutos);
    printf("\nTotal Geral Arrecadado: R$ %.2f\n", totalArrecadadoServicos + totalArrecadadoProdutos);

    esperaEnter();
}

void menuFinanceiro(Agendamentos *agendamento, Servicos *servicos, Produtos *produtos, Vendas *vendas){
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
            relatorioProdutos(vendas, produtos);
            esperaEnter();
        }else if(option == 3){
            relatorioTotal(agendamento, servicos, vendas);
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