#include <stdio.h>
#include "livros.h"
#include "emprestimos.h"

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
void ordenarLivrosMaisEmprestados(Livro livros[], int n)
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

// Livros disponíveis
void relatorioAcervoDisponivel(
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
void relatorioUsuariosAtrasados()
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

void relatorioHistoricoUsuario(
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
