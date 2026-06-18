#include <stdio.h>
#include <string.h>
#include "livros.h"
#include "emprestimos.h"

Livro livros[100];
int totalLivros = 0;

void menuLivros() {

    int opcao;

    do {

        printf("\n===== MENU LIVROS =====\n");

        printf("1 - Cadastrar Livro\n");
        printf("2 - Listar Livros\n");
        printf("3 - Buscar Livro por Codigo\n");
        printf("4 - Buscar Livro por Titulo\n");
        printf("5 - Atualizar Livro\n");
        printf("6 - Remover Livro\n");
        printf("7 - Mostrar Usuarios com Livro\n");
        printf("0 - Voltar\n");

        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {

            case 1:
                /* chamar cadastrarLivro() */
                cadastrarLivro();
                break;

            case 2:
                /* chamar listarLivros() */
                listarLivros();
                break;

            case 3:
                /* chamar buscarLivroPorCodigo() */
                buscarLivroPorCodigo();
                break;

            case 4:
                /* chamar buscarLivroPorTitulo() */
                buscarLivroPorTitulo();
                break;

            case 5:
                /* chamar atualizarLivro() */
                atualizarLivro();
                break;

            case 6:
                /* chamar removerLivro() */
                removerLivro();
                break;

            case 7:
                /* chamar mostrarUsuariosDoLivro() */
                mostrarUsuariosDoLivro();
                break;

            case 0:
                printf("Voltando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);
}

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
        printf("-------------------------------\n");
    }

}

void mostrarUsuariosDoLivro() {

    int codigo;
    int encontrou = 0;

    printf("\n===== USUARIOS COM ESTE LIVRO =====\n");

    printf("Digite o codigo do livro: ");
    scanf("%d", &codigo);

    for(int i = 0; i < totalEmprestimos; i++) {

        if(emprestimos[i].codigo_livro == codigo &&
           emprestimos[i].devolvido == 0) {

            encontrou = 1;

            printf("Matricula do usuario: %d\n",
                   emprestimos[i].matricula_usuario);
        }
    }

    if(encontrou == 0) {

        printf("Este livro nao possui emprestimos ativos.\n");
    }
}

void buscarLivroPorCodigo() {

    int codigo;
    int encontrou = 0;

    printf("Digite o codigo do livro: ");
    scanf("%d", &codigo);

    for(int i = 0; i < totalLivros; i++) {

        if(livros[i].codigo == codigo) {

            encontrou = 1;

            // mostrar todos os dados do livro
            printf("\nCodigo: %d\n", livros[i].codigo);
            printf("Titulo: %s\n", livros[i].titulo);
            printf("Autor: %s\n", livros[i].autor);
            printf("Genero: %s\n", livros[i].genero);
            printf("Ano: %d\n", livros[i].ano);
            printf("Quantidade Total: %d\n", livros[i].qtd_total);
            printf("Disponiveis: %d\n", livros[i].qtd_disponivel);
            printf("Total Emprestimos: %d\n", livros[i].total_emprestimos);

            break;
        }
    }

    if(encontrou == 0) {
        printf("Livro nao encontrado!\n");
    }
}

void buscarLivroPorTitulo() {

    char busca[100];
    int encontrou = 0;

    getchar();

    printf("Digite parte do titulo: ");
    fgets(busca, 100, stdin);

    busca[strcspn(busca, "\n")] = '\0';

    for(int i = 0; i < totalLivros; i++) {

        if(strstr(livros[i].titulo, busca) != NULL) {

            encontrou = 1;

            // mostrar livro
            printf("\nCodigo: %d\n", livros[i].codigo);
            printf("Titulo: %s\n", livros[i].titulo);
            printf("Autor: %s\n", livros[i].autor);
            printf("Genero: %s\n", livros[i].genero);
            printf("Ano: %d\n", livros[i].ano);
            printf("Quantidade Total: %d\n", livros[i].qtd_total);
            printf("Disponiveis: %d\n", livros[i].qtd_disponivel);
            printf("Total Emprestimos: %d\n", livros[i].total_emprestimos);
        }
    }

    if(encontrou == 0) {

        printf("Nenhum livro encontrado.\n");
    }
}

int buscarIndiceLivroPorCodigo(int codigo) {

    for(int i = 0; i < totalLivros; i++) {

        if(livros[i].codigo == codigo) {

            return i;
        }
    }

    return -1;
}

void atualizarLivro() {

    int codigo;

    printf("Digite o codigo do livro: ");
    scanf("%d", &codigo);

    int pos = buscarIndiceLivroPorCodigo(codigo);

    if(pos == -1) {

        printf("Livro nao encontrado!\n");
        return;
    }

    getchar();
    printf("Novo titulo: ");
    fgets(livros[pos].titulo, 100, stdin);
    livros[pos].titulo[strcspn(livros[pos].titulo, "\n")] = '\0';

    printf("Novo autor: ");
    fgets(livros[pos].autor, 100, stdin);
    livros[pos].autor[strcspn(livros[pos].autor, "\n")] = '\0';

    printf("Novo genero: ");
    fgets(livros[pos].genero, 50, stdin);
    livros[pos].genero[strcspn(livros[pos].genero, "\n")] = '\0';

    printf("Novo ano: ");
    scanf("%d", &livros[pos].ano);

    printf("Nova quantidade total: ");
    scanf("%d", &livros[pos].qtd_total);
    livros[pos].qtd_disponivel = livros[pos].qtd_total;

    printf("Livro atualizado com sucesso!\n");

    // pedir novos dados

}

void removerLivro() {

    int codigo;

    printf("Digite o codigo do livro: ");
    scanf("%d", &codigo);

    int pos = buscarIndiceLivroPorCodigo(codigo);

    if(pos == -1) {

        printf("Livro nao encontrado!\n");
        return;
    }

    if(livros[pos].qtd_disponivel != livros[pos].qtd_total) {

    printf("Nao e possivel remover. Existem exemplares emprestados.\n");
    return;
    }

    for(int i = pos; i < totalLivros - 1; i++) {

    livros[i] = livros[i + 1];
    }

    totalLivros--;
    printf("Livro removido com sucesso!\n");

}

