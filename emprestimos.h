#ifndef EMPRESTIMOS_H
#define EMPRESTIMOS_H

typedef struct {

    int id;                     
    int matricula_usuario;      
    int codigo_livro;           
    char data_retirada[11];     
    char data_prevista[11];     
    char data_devolucao[11];    
    int devolvido;              
                               

} Emprestimo;

extern Emprestimo emprestimos[1000];
extern int totalEmprestimos;

void realizarEmprestimo();
void registrarDevolucao();
void listarEmprestimos();
void listarEmprestimosAtrasados();
void gerarDataAtual(char data[]);
void gerarDataPrevista(char data[]);
int verificarAtraso(char dataPrevista[]);

#endif
