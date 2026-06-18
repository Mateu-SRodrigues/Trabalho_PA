#include "livros.h"
#include "emprestimos.h"
#include "usuarios.h"
#include <stdio.h>
#include <string.h>

extern Livro livros[100];
extern int totalLivros;

extern Emprestimo emprestimos[1000];
extern int totalEmprestimos;

void menuRelatorios() {

    int opcao;

    do {

        printf("\n===== MENU RELATORIOS =====\n");
        printf("1 - Acervo Disponivel\n");
        printf("2 - Livros Mais Emprestados\n");
        printf("3 - Usuarios em Atraso\n");
        printf("4 - Historico de Usuario\n");
        printf("0 - Voltar\n");

        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:
                relatorio_AcervoDisponivel(
                    livros,
                    totalLivros
                );
                break;

            case 2:
                relatorio_Livros_Mais_Emprestados(
                    livros,
                    totalLivros
                );
                break;

            case 3:
                relatorio_Atrasados();
                break;

            case 4:
                int matricula;

                printf("Digite a matricula: ");
                scanf("%d", &matricula);

                historico_Usuario(
                    matricula,
                    emprestimos,
                    totalEmprestimos
                );
                break;

            case 0:
                printf("Voltando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);
}

static void selectionSortLivros(Livro livros[], int n)
{
    int i, j, maior;
    Livro aux;

    for(i = 0; i < n - 1; i++)
    {
        maior = i;

        for(j = i + 1; j < n; j++)
        {
            if(livros[j].total_emprestimos >
               livros[maior].total_emprestimos)
            {
                maior = j;
            }
        }

        aux = livros[i];
        livros[i] = livros[maior];
        livros[maior] = aux;
    }
}

// Livros mais emprestados
void relatorio_Livros_Mais_Emprestados(
    Livro livros[],
    int qtdLivros)
{
    FILE *arq;

    arq = fopen("livros_mais_emprestados.txt", "w");

    if(arq == NULL)
    {
        printf("Erro ao criar arquivo!\n");
        return;
    }

    selectionSortLivros(
        livros,
        qtdLivros
    );

    printf("\n===== LIVROS MAIS EMPRESTADOS =====\n");

    fprintf(
        arq,
        "===== LIVROS MAIS EMPRESTADOS =====\n"
    );

    for(int i = 0; i < qtdLivros; i++)
    {
        printf(
            "%d - %s (%d emprestimos)\n",
            livros[i].codigo,
            livros[i].titulo,
            livros[i].total_emprestimos
        );

        fprintf(
            arq,
            "%d - %s (%d emprestimos)\n",
            livros[i].codigo,
            livros[i].titulo,
            livros[i].total_emprestimos
        );
    }

    fclose(arq);

    printf(
        "\nRelatorio salvo em livros_mais_emprestados.txt\n"
    );
}

// Livros disponíveis
void relatorio_AcervoDisponivel(
    Livro livros[],
    int qtdLivros)
{
    FILE *arq = fopen("acervo_disponivel.txt","w");

    printf("\n=== ACERVO DISPONIVEL ===\n");

    for(int i=0;i<qtdLivros;i++)
    {
        if(livros[i].qtd_disponivel > 0)
        {
            printf("%s (%d disponiveis)\n",
                   livros[i].titulo,
                   livros[i].qtd_disponivel);

            fprintf(arq,
                    "%s (%d disponiveis)\n",
                    livros[i].titulo,
                    livros[i].qtd_disponivel);
        }
    }

    fclose(arq);
}
// Usuários atrasados
void relatorio_Atrasados()
{
    FILE *arq =
        fopen(
            "usuarios_atrasados.txt",
            "w"
        );

    printf(
        "\n===== USUARIOS COM ATRASO =====\n"
    );

    int encontrou = 0;

    for(
        int i = 0;
        i < totalEmprestimos;
        i++
    )
    {
        if(
            emprestimos[i].devolvido == 0
            &&
            verificarAtraso(
                emprestimos[i]
                .data_prevista
            )
        )
        {
            encontrou = 1;

            printf(
                "Matricula: %d\n",
                emprestimos[i]
                .matricula_usuario
            );

            fprintf(
                arq,
                "Matricula: %d\n",
                emprestimos[i]
                .matricula_usuario
            );
        }
    }

    if(!encontrou)
    {
        printf(
            "Nenhum usuario em atraso.\n"
        );

        fprintf(
            arq,
            "Nenhum usuario em atraso.\n"
        );
    }

    fclose(arq);
}

// Histórico do Usuário

void historico_Usuario(
    int matricula,
    Emprestimo emprestimos[],
    int qtdEmprestimos)
{
    FILE *arq = fopen("historico_usuario.txt","w");

    printf("\n=== HISTORICO ===\n");

    for(int i=0;i<qtdEmprestimos;i++)
    {
        if(emprestimos[i].matricula_usuario
           == matricula)
        {
            printf("Livro: %d\n",
                   emprestimos[i].codigo_livro);

            fprintf(arq,
                    "Livro: %d\n",
                    emprestimos[i].codigo_livro);
        }
    }

    fclose(arq);
}
