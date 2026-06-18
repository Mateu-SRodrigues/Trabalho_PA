#include <stdio.h>

#include "menu.h"
#include "livros.h"
#include "usuarios.h"
#include "emprestimos.h"
#include "relatorios.h"

void menuPrincipal()
{
    int opcao;

    do
    {
        printf("\n -BIBLIOTECA UECE- \n");
        printf("1 - Gerenciar Livros\n");
        printf("2 - Gerenciar Usuarios\n");
        printf("3 - Realizar Emprestimo\n");
        printf("4 - Registrar Devolucao\n");
        printf("5 - Relatorios\n");
        printf("0 - Sair\n");

        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                menuLivros();
                break;

            case 2:
                menuUsuarios();
                break;

            case 3:
                realizarEmprestimo();
                break;

            case 4:
                registrarDevolucao();
                break;

            case 5:
                menuRelatorios();
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);
}
