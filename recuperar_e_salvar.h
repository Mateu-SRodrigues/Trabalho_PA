#ifndef RECUPERAR_E_SALVAR_H
#define RECUPERAR_E_SALVAR_H

#include "livros.h";
#include "emprestimos.h"
#include "usuarios.h"

void salvarLivros(Livro livros[], int qtd);
int carregarLivros(Livro livros[]);

void salvarUsuarios(Usuario usuarios[], int qtd);
int carregarUsuarios(Usuario usuarios[]);

void salvarEmprestimos(Emprestimo emprestimos[], int qtd);
int carregarEmprestimos(Emprestimo emprestimos[]);

#endif
