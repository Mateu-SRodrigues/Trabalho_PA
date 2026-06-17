#ifndef USUARIOS_H
#define USUARIOS_H

typedef struct {
    int matricula;
    int qtd_emprestimos_ativos;
    char curso[100];
    char nome[100];
} Usuario;

void menuUsuarios();
void cadUsuario();
void listarUsuarios();
void buscarUsuario();
void livrosEmprestados();
void atualizarDados();
void removerUsuario();

#endif
