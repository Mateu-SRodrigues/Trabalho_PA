#include <stdio.h>
#include <string.h>
#include <time.h>

#include "emprestimos.h"
#include "livros.h"

// Vetor de empréstimos.

Emprestimo emprestimos[1000];

// Quantidade atual de empréstimos.

int totalEmprestimos = 0;

// Gera a data atual.

void gerarDataAtual(char data[]) {

    time_t t = time(NULL);

    struct tm tm = *localtime(&t);

    sprintf(
        data,
        "%02d/%02d/%d",
        tm.tm_mday,
        tm.tm_mon + 1,
        tm.tm_year + 1900
    );
}

// Gera data prevista (+14 dias).

void gerarDataPrevista(char data[]) {

    time_t t = time(NULL);

    t += 14 * 24 * 60 * 60;

    struct tm tm = *localtime(&t);

    sprintf(
        data,
        "%02d/%02d/%d",
        tm.tm_mday,
        tm.tm_mon + 1,
        tm.tm_year + 1900
    );
}

// Realiza um empréstimo.

void realizarEmprestimo() {

    Emprestimo e;

    printf("\n===== NOVO EMPRESTIMO =====\n");

    printf("Matricula do usuario: ");
    scanf("%d", &e.matricula_usuario);

    printf("Codigo do livro: ");
    scanf("%d", &e.codigo_livro);

    // Procura o livro.
    
    int posLivro =
        buscarIndiceLivroPorCodigo(
            e.codigo_livro
        );

    if(posLivro == -1) {

        printf("Livro nao encontrado!\n");

        return;
    }

    // Verifica disponibilidade.
    
    if(livros[posLivro].qtd_disponivel <= 0) {

        printf(
            "Nao existem exemplares disponiveis!\n"
        );

        return;
    }

    /*
        Quando usuarios.c ficar pronto:

        - verificar usuario
        - verificar limite de 3 livros
    */

    e.id = totalEmprestimos + 1;

    gerarDataAtual(
        e.data_retirada
    );

    gerarDataPrevista(
        e.data_prevista
    );

    strcpy(
        e.data_devolucao,
        ""
    );

    e.devolvido = 0;

    emprestimos[totalEmprestimos] = e;

    totalEmprestimos++;

    /*
        Atualiza estoque
    */
    livros[posLivro]
        .qtd_disponivel--;

    livros[posLivro]
        .total_emprestimos++;

    printf(
        "\nEmprestimo realizado com sucesso!\n"
    );

    printf(
        "Data retirada: %s\n",
        e.data_retirada
    );

    printf(
        "Data prevista: %s\n",
        e.data_prevista
    );
}


// Registra devolução.

void registrarDevolucao() {

    int id;

    printf("\n===== DEVOLUCAO =====\n");

    printf("ID do emprestimo: ");

    scanf("%d", &id);

    for(
        int i = 0;
        i < totalEmprestimos;
        i++
    ) {

        if(
            emprestimos[i].id == id
        ) {

            if(
                emprestimos[i]
                .devolvido == 1
            ) {

                printf(
                    "Livro ja devolvido!\n"
                );

                return;
            }

            int posLivro =
                buscarIndiceLivroPorCodigo(
                    emprestimos[i]
                    .codigo_livro
                );

            if(posLivro != -1) {

                livros[posLivro]
                    .qtd_disponivel++;
            }

            gerarDataAtual(
                emprestimos[i]
                .data_devolucao
            );

            emprestimos[i]
                .devolvido = 1;

            printf(
                "Devolucao registrada com sucesso!\n"
            );

            return;
        }
    }

    printf(
        "Emprestimo nao encontrado!\n"
    );
}

// Lista todos os empréstimos.

void listarEmprestimos() {

    if(totalEmprestimos == 0) {

        printf(
            "Nenhum emprestimo cadastrado!\n"
        );

        return;
    }

    for(
        int i = 0;
        i < totalEmprestimos;
        i++
    ) {

        printf(
            "\nID: %d\n",
            emprestimos[i].id
        );

        printf(
            "Matricula: %d\n",
            emprestimos[i]
            .matricula_usuario
        );

        printf(
            "Livro: %d\n",
            emprestimos[i]
            .codigo_livro
        );

        printf(
            "Retirada: %s\n",
            emprestimos[i]
            .data_retirada
        );

        printf(
            "Prevista: %s\n",
            emprestimos[i]
            .data_prevista
        );

        if(
            emprestimos[i]
            .devolvido
        ) {

            printf(
                "Devolucao: %s\n",
                emprestimos[i]
                .data_devolucao
            );

            printf(
                "Status: DEVOLVIDO\n"
            );
        }
        else {

            printf(
                "Status: EM ABERTO\n"
            );
        }
    }
}


// Verifica atraso.

int verificarAtraso(
    char dataPrevista[]
) {

    int dia;
    int mes;
    int ano;

    sscanf(
        dataPrevista,
        "%d/%d/%d",
        &dia,
        &mes,
        &ano
    );

    struct tm data = {0};

    data.tm_mday = dia;
    data.tm_mon = mes - 1;
    data.tm_year = ano - 1900;

    time_t prazo =
        mktime(&data);

    time_t agora =
        time(NULL);

    if(
        difftime(
            agora,
            prazo
        ) > 0
    ) {

        return 1;
    }

    return 0;
}


// Lista empréstimos atrasados.

void listarEmprestimosAtrasados() {

    int encontrou = 0;

    printf(
        "\n===== EMPRESTIMOS ATRASADOS =====\n"
    );

    for(
        int i = 0;
        i < totalEmprestimos;
        i++
    ) {

        if(
            emprestimos[i]
            .devolvido == 0
            &&
            verificarAtraso(
                emprestimos[i]
                .data_prevista
            )
        ) {

            encontrou = 1;

            printf(
                "\nID: %d\n",
                emprestimos[i].id
            );

            printf(
                "Usuario: %d\n",
                emprestimos[i]
                .matricula_usuario
            );

            printf(
                "Livro: %d\n",
                emprestimos[i]
                .codigo_livro
            );

            printf(
                "Data prevista: %s\n",
                emprestimos[i]
                .data_prevista
            );
        }
    }

    if(!encontrou) {

        printf(
            "Nenhum emprestimo atrasado!\n"
        );
    }
}
