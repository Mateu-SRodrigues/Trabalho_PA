#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"

Usuario usuarios[100];
int totalUsuarios = 0;

void menuUsuarios(){
    int opcao;

    do{
        printf("\n==================== GERENCIAMENTO DE USUARIOS ====================\n");
        printf(" 1 - Cadastrar usuario\n");
        printf(" 2 - Listar usuarios cadastrados\n");                
        printf(" 3 - Buscar usuario\n");                
        printf(" 4 - Informar os esprestimos ativos do usuario\n");                
        printf(" 5 - Atualizar dados do usuario\n");                
        printf(" 6 - Remover usuario\n");                
        printf(" 0 - Voltar\n");                
        printf("Digite uma opcao: ");
        scanf("%d", &opcao);
        getchar();
    
        switch (opcao){
            case 1:
                cadUsuario();
                break;
            case 2:
                listarUsuarios();
                break;
            case 3:
                buscarUsuario();
                break;
            case 4:
                livrosEmprestados();
                break;
            case 5:
                atualizarDados();
                break;
            case 6:
                removerUsuario();
                break;
            case 0:
                printf("Voltando...");
                break;
            default:
                printf("Opcao invalida! Digite novamente: ");
                break;
        }
    } while (opcao != 0);
}

void cadUsuario(){
    printf("\n==================== CADASTRAR NOVO USUARIO ====================\n");
    
    //Verifica se o arquivo já existe 
    FILE *arq = fopen("usuario.txt","r");
    int novo;
    if(arq == NULL)
        novo = 1; //(Verdadeiro) arquivo não existe
    else
        novo = 0; //(Falso) arquivo existe
    fclose(arq);
    
    //Reabre o arquivo em modo append: cria se não existir, ou modifica ao final
    arq = fopen("usuario.txt", "a");
    if(arq == NULL){
        printf("Erro na ABERTURA do arquivo.\n");
        return;
    }
    //Armazena cada linha lida do arquivo
    char linha[256];
    //Se arquivo não existir ou estiver vazio, cria/adiciona com um cabeçalho
    if(novo != 0){
        fprintf(arq, "%-10s | %-30s | %-20s | %-10s\n", "MATRICULA", "NOME", "CURSO", "EMPRESTIMOS ATIVOS" );
        fprintf(arq, "%-10s | %-30s | %-20s | %-10s\n", "----------", 
            "------------------------------", 
            "--------------------", "----------");
    }
    
    //Gera a matrícula automaticamente para o novo usuário
    usuarios[totalUsuarios].matricula = totalUsuarios + 1;
    
    //Lê o nome do usuário e limpa o \n, delimitando o final da string em \0
    printf("Informe o nome completo do usuario: ");
    fgets(usuarios[totalUsuarios].nome, sizeof(usuarios[totalUsuarios].nome), stdin);
    usuarios[totalUsuarios].nome[strcspn(usuarios[totalUsuarios].nome, "\n")] = '\0';
    
    //Lê o curso do usuário e limpa o \n, delimitando o final da string em \0
    printf("Informe o nome do curso: ");
    fgets(usuarios[totalUsuarios].curso, sizeof(usuarios[totalUsuarios].curso), stdin);
    usuarios[totalUsuarios].curso[strcspn(usuarios[totalUsuarios].curso, "\n")] = '\0';

    //Novo usuário inicia com 0 empréstimos ativos
    usuarios[totalUsuarios].qtd_emprestimos_ativos = 0;

    //Escreve os dados formatados no arquivo 'usuario.txt'
    fprintf(arq, "%-10d | %-30s | %-20s | %-10d\n", //Os valores aparecerão alinhados a esquerda
        usuarios[totalUsuarios].matricula, 
        usuarios[totalUsuarios].nome, 
        usuarios[totalUsuarios].curso, 
        usuarios[totalUsuarios].qtd_emprestimos_ativos);

    //Quantidade de usuários cresce a cada novo cadastro
    totalUsuarios++;

    printf("\n==================== USUARIO CADASTRADO ====================\n");
    fclose(arq);
}

void listarUsuarios(){
    printf("====================== USUARIOS CADASTRADOS ======================\n");
    //Abre o arquivo para leitura e verifica se o arquivo existe
    FILE *arq = fopen("usuario.txt", "r");
    if(arq == NULL){
        printf("Erro na ABERTURA do arquivo.\n");
        return;
    }
    //Armazena cada linha lida do arquivo
    char linha[256];
    //Conta quantas linhas foram armazenadas
    int encontrado = 0;

    //Lê e armazena o arquivo linha por linha até o EOF(fgets == NULL)
    while(fgets(linha, sizeof(linha), arq) != NULL){
            printf("%s", linha);
            encontrado++;
        }
    //Se leu só duas linhas(Cabeçalho) ou menos, não existe cadastros
    if(encontrado <= 2)
        printf("Nenhum usuario cadastrado ainda.");

    fclose(arq);
}

void buscarUsuario(){
    printf("==================== BUSCAR USUARIO ====================\n");
    //Abre o arquivo para buscar informações de um usuário
    FILE *arq = fopen("usuario.txt", "r");
    if(arq == NULL){ //Verifica se o arquivo existe
        printf("Erro na ABERTURA do arquivo.\n");
        return;
    }
    //Armazena cada linha do arquivo
    char linha[256];
    //Armazena a entrada de busca
    char busca[256];
    //Conta quantas linhas foram lidas
    int encontrado = 0;
    
    //Lê o nome ou número de matricula do usuario e limpa o \n, delimitando o final da string em \0
    printf("Digite o nome ou numero de matricula do usuario: ");
    fgets(busca, sizeof(busca), stdin);//Lê do teclado
    busca[strcspn(busca, "\n")] = '\0';

    //Lê e armazena o arquivo linha por linha até o EOF(fgets == NULL)
    while(fgets(linha, sizeof(linha), arq) != NULL){
        //Verifica se a entrada está no conteúdo do arquivo
        if(strstr(linha, busca) != NULL){
            printf("Usuario encontrado: %s", linha);
            encontrado = 1;
        }
    }
    //Se nenhuma linha foi lida, usuario não existe
    if(encontrado == 0){
        printf("\nUsuario nao encontrado!\n");
        return;
    }
    fclose(arq);
}

void livrosEmprestados(){
    printf("==================== EMPRESTIMOS ATIVOS DO USUARIO ====================\n");
    //Abre o arquivo para buscar informações de um determinado usuário
    FILE *arq = fopen("usuario.txt", "r");
    if(arq == NULL){ //Verifica se o arquivo existe
        printf("Erro na ABERTURA do arquivo.\n");
        return;
    }
    //Armazena a entrada de busca
    char busca[100];
    //Armazena cada linha lida do arquivo
    char linha[256];
    //Armazena as informações de um usuário específico
    char linhaEncontrada[256];
    //Conta quantas linhas foram lidas
    int encontrado = 0;

    //Lê o nome ou número de matricula do usuario e limpa o \n, delimitando o final da string em \0
    printf("Informe o nome ou numero de matricula do usuario: ");
    fgets(busca, sizeof(busca), stdin); //Lê do teclado
    busca[strcspn(busca, "\n")] = '\0';

    //Lê e armazena o arquivo linha por linha até o EOF(fgets == NULL)
    while(fgets(linha, sizeof(linha), arq) != NULL){
        //Verifica se a entrada está no conteúdo do arquivo
        if(strstr(linha, busca) != NULL){
            strcpy(linhaEncontrada, linha); //Extrai os dados da linha que contém o mesmo termo de busca, e armazena em linhaEncontrada
            encontrado = 1;
            break; //Para na primeira ocorrência do if
        }
    }
    fclose(arq);
    //Se nenhuma linha foi lida, usuario não existe
    if (encontrado == 0){
        printf("Usuario nao encontrado!\n");
        return;
    }
    //Armazena a quantidade de empréstimos ativos
    int quantidade;
    //Armazena o número de matrícula do aluno
    int matricula;
    //Armazena o nome do usuário
    char nome[100];
    //Armazena o curso do usuário
    char curso[100];
    //Lê os dados do usuário e armazena os valores inteiros e char
    sscanf(linhaEncontrada, "%d | %[^|] | %[^|] | %d", &matricula, nome, curso, &quantidade); //'%[^|]' lê tudo até |
    //Se o usuário não tiver empréstimos ativos, imprime um texto formatado
    if (quantidade == 0){
        printf("%-10s | %-30s | %-20s | %-10s\n", 
            "MATRICULA", "NOME", "CURSO", "EMPRESTIMOS ATIVOS" );
        printf("%-10d |%-30s |%-20s | ", 
            matricula, nome, curso);
        printf("O usuario nao possui livros emprestados\n");
    }
    //Caso contrário, imprime a linha com os dados do usuário
    else
        printf("%s", linhaEncontrada);
}

void atualizarDados(){
    printf("==================== ATUALIZAR DADOS DO USUARIO ====================\n");
    //Abre o arquivo para buscar informações de um determinado usuário
    FILE *arq = fopen("usuario.txt", "r");
    if(arq == NULL){ //Verifica se o arquivo existe
        printf("Erro na ABERTURA do arquivo.\n");
        return;
    }
    //Armazena a entrada de busca
    char busca[256];
    //Armazena cada linha lida do arquivo
    char linha[256];
    //Armazena as informações de um usuário específico
    char linhaEncontrada[256];
    //Armazena a quantida de linhas lidas
    int encontrado = 0;
    //Lê o nome ou número de matricula do usuario e limpa o \n, delimitando o final da string em \0
    printf("Digite o nome ou numero de matricula do usuario: ");
    fgets(busca, sizeof(busca), stdin);//Lê do teclado
    busca[strcspn(busca, "\n")] = '\0';

    //Lê e armazena o arquivo linha por linha até o EOF(fgets == NULL)
    while(fgets(linha, sizeof(linha), arq) != NULL){
        //Verifica se o termo de busca está no conteúdo do arquivo
        if(strstr(linha, busca) != NULL){
            strcpy(linhaEncontrada, linha); //Extrai os dados da linha, que contém o mesmo termo de busca, e armazena em linhaEncontrada
            encontrado = 1;
            break; //Encerra na primeira ocorrência do if
        }
    }
    fclose(arq);
    //Se nenhuma linha foi lida, usuario não encontrado
    if(encontrado == 0){
        printf("Usuario nao encontrado!\n");
        return;
    }
    //Lê e armazena a matrícula do usúario
    int matricula;
    sscanf(linhaEncontrada, "%d", &matricula); //Armazena o primeiro inteiro
    //Armazena o novo nome do usuário
    char novoNome[100];
    //Armazena o novo curso do usuário
    char novoCurso[100];

    //Lê e armazena o novo nome do usuario e limpa o \n, delimitando o final da string em \0
    printf("Digite o novo nome: ");
    fgets(novoNome, sizeof(novoNome), stdin);
    novoNome[strcspn(novoNome, "\n")] = '\0';

    //Lê e armazena o novo curso do usuario e limpa o \n, delimitando o final da string em \0
    printf("Digite o novo curso: ");
    fgets(novoCurso, sizeof(novoCurso), stdin);
    novoCurso[strcspn(novoCurso, "\n")] = '\0';

    //Reabre o arquivo para buscar informações do usuário
    arq = fopen("usuario.txt", "r");
    //Abre o arquivo temporário para registrar informções do usuário
    FILE *temp = fopen("temp.txt", "w");
    //Verifica se os arquivos existem
    if(arq == NULL || temp == NULL){
        printf("Erro na ABERTURA do arquivo.\n");
        //Quando temp == NULL, fecha arq
        if (arq != NULL)
            fclose(arq);
        //Quando arq == NULL, fecha temp
        if (temp != NULL)
            fclose(temp);
        return;
    }
    //Lê e armazena o arquivo linha por linha até o EOF(fgets == NULL)
    while(fgets(linha, sizeof(linha), arq) != NULL){
        //Se o termo de busca estiver no conteúdo do arquivo, escreve as novas informações do usuário no arquivo temporário
        if(strstr(linha, busca) != NULL){
            fprintf(temp, "%-10d | %-30s | %-20s | %-10d\n", matricula, novoNome, novoCurso, 0);
        }
        //Se não estiver, escreve os dados dos usuários que não estão sendo atualizados no arquivo temporário
        else
            fprintf(temp, "%s", linha);//Preserva os dados dos usuários que não estão sendo atualizados, escrevendo-os no arquivo temporário
    }
    //Fecha os dois arquivos
    fclose(temp);
    fclose(arq);
    //Remove usuario.txt
    remove("usuario.txt");
    //Renomea arquivo temporário
    rename("temp.txt", "usuario.txt");
}

void removerUsuario(){
    printf("==================== REMOVER USUARIO ====================\n");
    //Abre o arquivo para buscar informações de um determinado usuário
    FILE *arq = fopen("usuario.txt", "r");
    if(arq == NULL){ //Verifica se o arquivo exise
        printf("Erro na ABERTURA do arquivo.\n");
        return;
    }
    //Armazena termo de busca
    char busca[256];
    //Armazena cada linha lida do arquivo
    char linha[256];
    //Armazena as informações de um usuário específico
    char linhaEncontrada[256];
    //Conta quantas linhas foram lidas
    int encontrado = 0;

    //Lê o nome ou número de matricula do usuario e limpa o \n, delimitando o final da string em \0
    printf("Digite o nome ou numero de matricula do usuario: ");
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = '\0';
    
    //Lê e armazena o arquivo linha por linha até o EOF(fgets == NULL)
    while(fgets(linha, sizeof(linha), arq) != NULL){
        //Se o termo de busca estiver no conteúdo do arquivo 
        if(strstr(linha, busca) != NULL){
            strcpy(linhaEncontrada, linha);//Copia todos os dados da linha que contém o termo de busca para linhaEncontrada
            encontrado = 1;
            break; //Para na primeira ocorrência do if
        }
    }
    fclose(arq);
    //Se nenhuma linha foi lida, usuario não encontrado
    if(encontrado == 0){
        printf("Usuario nao encontrado!\n");
        return;
    }
    //Reabre para buscar informações do usuário
    arq = fopen("usuario.txt", "r");
    //Abre o arquivo temporário para registrar informações do usuário
    FILE *temp = fopen("temp.txt", "w");
    //Verifica se os arquivos existem
    if(arq == NULL || temp == NULL){
        printf("Nenhum usuario cadastrado ainda.\n");
        //Quando temp == NULL, fecha arq
        if (arq != NULL)
            fclose(arq);
        //Quando arq == NULL, fecha temp
        if (temp != NULL)
            fclose(temp);
        return;
    }
    //Lê e armazena o arquivo linha por linha até o EOF(fgets == NULL)
    while(fgets(linha, sizeof(linha), arq) != NULL){
        //Se as informações do usuário não estiverem naquela linha, copia ela para o arquivo temporário 
        if(strstr(linha, linhaEncontrada) == NULL)
            fprintf(temp, "%s", linha);
    }
    //Fecha ambos os arquivos
    fclose(temp);
    fclose(arq);
    //Remove usuario.txt
    remove("usuario.txt");
    //Renomea arquivo temporário
    rename("temp.txt", "usuario.txt");
}