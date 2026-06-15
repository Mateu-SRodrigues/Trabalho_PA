#include <stdio.h>
#include "recuperar_e_salvar.h"

#salvar livros

void salvarLivros(Livro livros[], int qtd)
{
    FILE *arq = fopen("livros.txt", "w");

    if(arq == NULL)
        return;

    for(int i = 0; i < qtd; i++)
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

#carregar livros

int carregarLivros(Livro livros[])
{
    FILE *arq = fopen("livros.txt", "r");

    if(arq == NULL)
        return 0;

    int qtd = 0;

    while(
        fscanf(arq,
        "%d;%99[^;];%99[^;];%d;%49[^;];%d;%d;%d\n",

        &livros[qtd].codigo,
        livros[qtd].titulo,
        livros[qtd].autor,
        &livros[qtd].ano,
        livros[qtd].genero,
        &livros[qtd].qtd_total,
        &livros[qtd].qtd_disponivel,
        &livros[qtd].total_emprestimos) == 8
    )
    {
        qtd++;
    }

    fclose(arq);

    return qtd;
}

