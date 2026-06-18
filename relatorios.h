#ifndef RELATORIOS_H
#define RELATORIOS_H
#include "livros.h"
#include "emprestimos.h"
#include "usuarios.h"

void menuRelatorios();

void relatorio_AcervoDisponivel(
    Livro livros[],
    int totalLivros);

void relatorio_Livros_Mais_Emprestados(
    Livro livros[],
    int totalLivros);

void relatorio_Atrasados();

void historico_Usuario(
    int matricula,
    Emprestimo emprestimos[],
    int qtdEmprestimos);

#endif
