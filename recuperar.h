#ifndef RECUPERAR_H
#define RECUPERAR_H

#include "estruturas.h"

void salvarLivros(Livro livros[], int qtd);
int carregarLivros(Livro livros[]);

void salvarUsuarios(Usuario usuarios[], int qtd);
int carregarUsuarios(Usuario usuarios[]);

void salvarEmprestimos(Emprestimo emprestimos[], int qtd);
int carregarEmprestimos(Emprestimo emprestimos[]);

#endif
