#include <stdio.h>
#include <string.h>
#include "livros.h"

Livro livros[100];
int totalLivros = 0;

void cadastrarLivro() {

    livros[totalLivros].codigo = totalLivros + 1;
    //Isso guarda o titulo do livro
    printf("Digite o titulo: ");
    fgets(livros[totalLivros].titulo, 100, stdin);
    //Isso tira o enter invisivel
    livros[totalLivros].titulo[strcspn(livros[totalLivros].titulo, "\n")] = '\0';
    //isso guarda o nome do autor
    printf("Digite o autor: ");
    fgets(livros[totalLivros].autor, 100, stdin);

    livros[totalLivros].autor[strcspn(livros[totalLivros].autor, "\n")] = '\0';
    //Isso guarda o genero do livro
    printf("Digite o genero: ");
    fgets(livros[totalLivros].genero, 50, stdin);

    livros[totalLivros].genero[strcspn(livros[totalLivros].genero, "\n")] = '\0';
    //Isso simplismente vai guardar o ano em que o livro foi feito
    printf("Digite o ano: ");
    scanf("%d", &livros[totalLivros].ano);

    //Isso vai guarda o quantidade desse livro ao todo
    printf("Digite a quantidade total: ");
    scanf("%d", &livros[totalLivros].qtd_total);
    //Isso define o numero de livros disponiveis
    livros[totalLivros].qtd_disponivel = livros[totalLivros].qtd_total;
    //O livro acabou de ser criado mas não foi feito nenhum emprestimo por hora
    livros[totalLivros].total_emprestimos = 0;
    //limpa o buffer
    //se não tiver isso proximos gets podem dar B.O
    getchar();
    printf("----- Livro foi cadastrado -----");
    totalLivros++;

}

void listarLivros() {

    //verifica se existe algum livro cadastrado
    if(totalLivros == 0) {
        printf("Nenhum livro cadastrado!\n");
        return;
    }
    //esse for vai percorrer o vetor livros e vai mostras os livros cadastrados e mostras o codigo o titulo e etc...
    for(int i = 0; i < totalLivros; i++) {
        printf("\nLivro %d\n", i + 1);
        printf("Codigo: %d\n", livros[i].codigo);
        printf("Titulo: %s\n", livros[i].titulo);
        printf("Autor: %s\n", livros[i].autor);
        printf("Genero: %s\n", livros[i].genero);
        printf("Ano: %d\n", livros[i].ano);
        printf("Quantidade Total: %d\n", livros[i].qtd_total);
        printf("Disponiveis: %d\n", livros[i].qtd_disponivel);
        printf("Total de Emprestimos: %d\n", livros[i].total_emprestimos);
    }

}