#include "animal.h"
#include "funcionario.h"
#include "cliente.h"
#include "servico.h"

int main(void)
{
    int option;
    Pets *pets = criarListaPets();
    Funcionarios *funcionarios = criarListaFunc();
    Clientes* clientes = criarListaClientes();
    Servicos *servicos = criarListaServicos();

    for (;;)
    {
        system("cls");
        printf("\t---PET SHOP---\n");
        printf("[1] - Gerenciamento Pets\n");
        printf("[2] - Gerenciamento Produtos\n");
        printf("[3] - Gerenciamento Servicos\n");
        printf("[4] - Gerenciamento Clientes\n");
        printf("[5] - Gerenciamento Funcionarios\n");
        printf("[6] - Relatorios Financeiros\n");
        printf("[0] - Encerrar Programa\n\n");
        printf("Informe oque deseja: ");
        scanf("%d", &option);
        fflush(stdin);
        if (option == 1)
        {
            menuPet(pets, clientes);
        }
        else if (option == 2)
        {
            printf("Em producao...\n");
        }
        else if (option == 3)
        {
            menuServicos(servicos, funcionarios, pets);

        }
        else if (option == 4)
        {
            menuClientes(clientes);
        }
        else if (option == 5)
        {
            menuFunc(funcionarios);
        }
        else if (option == 6)
        {
            printf("Em producao...\n");
        }
        else if (option == 0)
        {
            break;
        }
        else
        {
            printf("Opcao invalida!\n");
        }
        esperarEnter();
    }
    limparPets(pets);
    deletarListaFunc(funcionarios);
    limparClientes(clientes);
    return 0;
}