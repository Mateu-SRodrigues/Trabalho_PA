#include <stdio.h>
#include "recuperar_e_salvar.h"
#include "livros.h"

extern Livro livros[100];
extern int totalLivros;

void menuRecuperar(Livro livros[], int totalLivros){
    int opcao;

    do{
        printf("\n==================== GERENCIAMENTO DE USUARIOS ====================\n");
        printf(" 1 - Salvar livros\n");
        printf(" 2 - Carregar livros\n");      
        printf(" 0 - Voltar\n");                
        printf("Digite uma opcao: ");
        scanf("%d", &opcao);
        getchar();
    
        switch (opcao){
            case 1:
                salvarLivros(
                    livros, 
                    totalLivros
                );
                break;
            case 2:
                carregarLivros(livros, totalLivros);
                break;
            case 0:
                printf("Voltando...");
                break;
            default:
                printf("Opcao invalida! Digite novamente: ");
                break;
        }
    } while (opcao != 0);
}

void salvarLivros(Livro livros[], int totalLivros)
{
    FILE *arq = fopen("livros.txt", "w");

    if(arq == NULL)
        return;

    for(int i = 0; i < totalLivros; i++)
    {
        fprintf(arq,
        "%d;%s;%s;%d;%s;%d;%d;%d\n",

        livros[i].codigo,
        livros[i].titulo,
        livros[i].autor,
        livros[i].ano,
        livros[i].genero,
        livros[i].qtd_total,
        livros[i].qtd_disponivel,
        livros[i].total_emprestimos);
    }

    fclose(arq);
}

//carregar livros

int carregarLivros(Livro livros[], int totalLivros)
{
    FILE *arq = fopen("livros.txt", "r");

    if(arq == NULL)
        return 0;

    while(
        fscanf(arq,
        "%d;%99[^;];%99[^;];%d;%49[^;];%d;%d;%d\n",

        &livros[totalLivros].codigo,
        livros[totalLivros].titulo,
        livros[totalLivros].autor,
        &livros[totalLivros].ano,
        livros[totalLivros].genero,
        &livros[totalLivros].qtd_total,
        &livros[totalLivros].qtd_disponivel,
        &livros[totalLivros].total_emprestimos) == 8
    )
    {
        totalLivros++;
    }

    fclose(arq);

    return totalLivros;
}

