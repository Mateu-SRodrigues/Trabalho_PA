#ifndef LIVROS_H
#define LIVROS_H

typedef struct {
    int codigo;
    char titulo[100];
    char autor[100];
    int ano;
    char genero[50];
    int qtd_total;
    int qtd_disponivel;
    int total_emprestimos;
} Livro;

void cadastrarLivro();
void listarLivros();

#endif