#include <stdio.h>
#include <string.h>
#include <time.h>

#include "emprestimos.h"

// Vetor de empréstimos.

Emprestimo emprestimos[1000];

// Quantidade de empréstimos cadastrados.

int totalEmprestimos = 0;

// Gera a data atual.

void gerarDataAtual(char data[]) {

    time_t t = time(NULL);

    struct tm tm = *localtime(&t);

    sprintf(data,
            "%02d/%02d/%d",
            tm.tm_mday,
            tm.tm_mon + 1,
            tm.tm_year + 1900);
}

// Gera a data prevista para devolução. (14 dias após a retirada)

void gerarDataPrevista(char data[]) {

    time_t t = time(NULL);

    t += 14 * 24 * 60 * 60;

    struct tm tm = *localtime(&t);

    sprintf(data,
            "%02d/%02d/%d",
            tm.tm_mday,
            tm.tm_mon + 1,
            tm.tm_year + 1900);
}

// Cria um novo empréstimo.

void realizarEmprestimo() {

    Emprestimo e;

    printf("\n===== NOVO EMPRESTIMO =====\n");

    printf("Matricula do usuario: ");
    scanf("%d", &e.matricula_usuario);

    printf("Codigo do livro: ");
    scanf("%d", &e.codigo_livro);

    // Depois será integrado com os módulos de livros e usuários.

    e.id = totalEmprestimos + 1;

    gerarDataAtual(e.data_retirada);

    gerarDataPrevista(e.data_prevista);

    strcpy(e.data_devolucao, "");

    e.devolvido = 0;

    emprestimos[totalEmprestimos] = e;

    totalEmprestimos++;

    printf("\nEmprestimo realizado com sucesso!\n");
}

// Registra a devolução de um livro.

void registrarDevolucao() {

    int id;

    printf("\n===== DEVOLUCAO =====\n");

    printf("ID do emprestimo: ");
    scanf("%d", &id);

    for(int i = 0; i < totalEmprestimos; i++) {

        if(emprestimos[i].id == id) {

            if(emprestimos[i].devolvido == 1) {

                printf("Livro ja devolvido!\n");

                return;
            }

            gerarDataAtual(
                emprestimos[i].data_devolucao
            );

            emprestimos[i].devolvido = 1;

            printf("Devolucao registrada!\n");

            return;
        }
    }

    printf("Emprestimo nao encontrado!\n");
}

// Mostra todos os empréstimos.

void listarEmprestimos() {

    printf("\n===== EMPRESTIMOS =====\n");

    if(totalEmprestimos == 0) {

        printf("Nenhum emprestimo cadastrado.\n");

        return;
    }

    for(int i = 0; i < totalEmprestimos; i++) {

        printf("\nID: %d\n",
               emprestimos[i].id);

        printf("Matricula: %d\n",
               emprestimos[i].matricula_usuario);

        printf("Codigo Livro: %d\n",
               emprestimos[i].codigo_livro);

        printf("Retirada: %s\n",
               emprestimos[i].data_retirada);

        printf("Prevista: %s\n",
               emprestimos[i].data_prevista);

        if(emprestimos[i].devolvido) {

            printf("Devolucao: %s\n",
                   emprestimos[i].data_devolucao);

            printf("Status: DEVOLVIDO\n");
        }
        else {

            printf("Status: EM ABERTO\n");
        }
    }
}

// Verifica se uma data já passou.

int verificarAtraso(char dataPrevista[]) {

    int dia;
    int mes;
    int ano;

    sscanf(dataPrevista,
           "%d/%d/%d",
           &dia,
           &mes,
           &ano);

    struct tm data = {0};

    data.tm_mday = dia;
    data.tm_mon = mes - 1;
    data.tm_year = ano - 1900;

    time_t prazo = mktime(&data);

    time_t agora = time(NULL);

    if(difftime(agora, prazo) > 0) {

        return 1;
    }

    return 0;
}


// Lista apenas empréstimos atrasados.

void listarEmprestimosAtrasados() {

    int encontrou = 0;

    printf("\n===== ATRASADOS =====\n");

    for(int i = 0; i < totalEmprestimos; i++) {

        if(emprestimos[i].devolvido == 0 &&
           verificarAtraso(
               emprestimos[i].data_prevista
           )) {

            encontrou = 1;

            printf("\nID: %d\n",
                   emprestimos[i].id);

            printf("Usuario: %d\n",
                   emprestimos[i].matricula_usuario);

            printf("Livro: %d\n",
                   emprestimos[i].codigo_livro);

            printf("Data Prevista: %s\n",
                   emprestimos[i].data_prevista);
        }
    }

    if(!encontrou) {

        printf("Nenhum emprestimo atrasado.\n");
    }
}
