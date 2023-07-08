#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*  Instituto Federal do Maranhao - IFMA
 *  Sistemas de Informacao - 2 Periodo
 *  Linguagem de Programacao I
 *  Equipe 10 - Sistema p/ registros de empresa de construcao civil
 */


/*FUNCOES==============================================================================*/
void limparBuffer();                 /*LIMPAR O BUFFER DO TECLADO*/
void removerNovaLinha(char *string); /*REMOVE O \n DO FINAL DE UMA STRING*/
/*FUNCOES DE CADASTRO*/
void cadastraCliente(char *nome, char *endereco, char *data_nascimento, long int cep, char *email, char *telefone, long int celular);
void cadastraFuncionario(int matricula, char *nome, char *data_admissao, char *cargo);
void cadastraObra(int id_obra, char *nome_obra, char *engenheiro_responsavel, long int data_inicio, long int data_termino, int estagio_obra);
int qtdCadastros(const char *arquivo); /*ABRE O ARQUIVO CONTENDO OS CADASTROS DESEJADOS E CONTA A QTD DE LINHAS*/
/*FUNCOES DE RELATORIO*/
void relatorioCliente(const char *arquivo);
void relatorioFuncionario(const char *arquivo);
void relatorioObra(const char *arquivo);
int calculaPrazoObra(long int data_atual, long int data_inicio, long int data_termino); 
/*FUNCOES DE MENU*/
void menuPrincipal();
void menuCliente();
void menuFuncionario();
void menuObra();
/*FUNCÃO DE ALTERACAO*/
void removerRegistroPorIdentificador(const char *arquivo, long int identificador); /*REMOVE UM REGISTRO DO ARQUIVO POR IDENTIFICADOR (CELULAR, MATRICULA, ID)*/
void alterarRegistroPorCelular(const char *arquivo, long int valor);
void alterarRegistroPorMatricula(const char *arquivo, int valor);
void alterarRegistroPorID(const char *arquivo, int valor);
/* Definição das structs ===========================================================*/
struct Cliente{
    char nome[50];
    char endereco[50];
    char data_nascimento[11];
    long int cep;
    char email[50];
    char telefone[15];
    long int celular;
}clientes[] = {0}; /*Inicializa o vetor com 0 para evitar alocacao de lixos de memoria*/
struct Funcionario{
    char nome[50];
    int matricula;
    char data_admissao[11];
    char cargo[20];
}funcionarios[] = {0};
struct Obra{
    int id_obra;
    char nome_obra[50];
    char engenheiro_responsavel[50];
    long int data_inicio;
    long int data_termino;
}obras[] = {0};
/*===================================================================================*/

void limparBuffer() {                 /*Função para limpar o buffer do teclado*/
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /*Lê e descarta os caracteres do buffer até encontrar uma nova linha ou o final do arquivo*/
    }
}
void removerNovaLinha(char *string) {

    /*Remove o \n do final da string
    Últil p/ que todos os dados de um cadastro fiquem na mesma linha*/

    string[strcspn(string, "\n")] = '\0';
}
void menuPrincipal(){
    int opcao;
    printf("\n##################################");
    printf("\n#                                 #");
    printf("\n#        LP CONSTRUCOES           #");
    printf("\n#                                 #");
    printf("\n##################################\n");

    printf("1 - Clientes\n");
    printf("2 - Funcionarios\n");
    printf("3 - Obras\n");
    printf("0 - Sair\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &opcao);
    system("cls");
    switch(opcao){
        case 1:
            menuCliente();
            break;
        case 2:
            menuFuncionario();
            break;
        case 3:
            menuObra();
            break;
        case 4:
            break;
    }

}
void menuCliente(){
    int opcao,i, resp = 1;
    long int celular;
    system("cls"); /*Limpa a tela*/
    printf("\n##################################");
    printf("\n#                                 #");
    printf("\n#        CLIENTES                 #");
    printf("\n#                                 #");
    printf("\n##################################\n");

    printf("1 - Cadastrar\n");
    printf("2 - Alterar\n");
    printf("3 - Excluir\n");
    printf("4 - Relatorio\n");
    printf("0 - Voltar\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &opcao);
    system("cls"); /*Limpa a tela*/

    switch(opcao){
        case 1:
            printf("Cadastro de clientes\n\n");
            while(resp == 1){
                for(i=0;i<1;i++){
                    limparBuffer();
                    printf("Nome: ");
                    fgets(clientes[i].nome, 50, stdin);
                    removerNovaLinha(clientes[i].nome); /*FUNCAO PARA REMOVER \n PORQUE NO MOMENTO DO CADASTRO, O PROGRAMA COLOCAVA UMA LINHA ENTRE UM CLIENTE E OUTRO*/
                    
                    printf("Endereco: ");
                    fgets(clientes[i].endereco, 100, stdin);
                    removerNovaLinha(clientes[i].endereco);

                    printf("Data de nascimento (DD/MM/AAAA): ");
                    fgets(clientes[i].data_nascimento, 11, stdin);
                    removerNovaLinha(clientes[i].data_nascimento);

                    printf("CEP: ");
                    scanf("%ld", &clientes[i].cep);
                    limparBuffer();

                    printf("Email: ");
                    fgets(clientes[i].email, 50, stdin);
                    removerNovaLinha(clientes[i].email);

                    printf("Telefone: ");
                    fgets(clientes[i].telefone, 15, stdin);

                    printf("Celular: ");
                    scanf("%ld", &clientes[i].celular);

                    cadastraCliente(clientes[i].nome, clientes[i].endereco, clientes[i].data_nascimento, clientes[i].cep, clientes[i].email, clientes[i].telefone, clientes[i].celular);
                    
                    printf("\nDeseja cadastrar outro cliente?\n1 - Sim\n2 - Nao\nDigite a opcao desejada");
                    scanf("%d", &resp);
                }
            }
            menuCliente();
            break;
        case 2:
            printf("Alterar cliente\n\n");
            printf("Digite o celular do cliente que deseja alterar: ");
            scanf("%ld", &celular);
            alterarRegistroPorCelular("clientes.txt", celular);
            menuCliente();
            break;
        case 3:
            printf("Excluir cliente\n\n");
            printf("Digite o celular do cliente que deseja excluir: ");
            scanf("%ld", &celular);
            removerRegistroPorIdentificador("clientes.txt", celular);
            menuCliente(); 
            break;
        case 4:
            relatorioCliente("clientes.txt");
            system("pause");
            menuCliente();
            break;
        case 0:
            menuPrincipal();
            break;
    }
}
void menuFuncionario(){
    int opcao, opcao_cargo, i, resp = 1;
    int matricula;
    char vet_cargos[][15] = {"Vendedor\n", "Engenheiro\n", "Gerente\n"};

    system("cls"); /*Limpa a tela*/
    printf("\n##################################");
    printf("\n#                                 #");
    printf("\n#        FUNCIONARIOS             #");
    printf("\n#                                 #");
    printf("\n##################################\n");

    printf("1 - Cadastrar\n");
    printf("2 - Alterar\n");
    printf("3 - Excluir\n");
    printf("4 - Relatorio\n");
    printf("0 - Voltar\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &opcao);
    system("cls"); /*Limpa a tela*/

    switch(opcao){
        case 1:
        printf("Cadastro de funcionarios: %d\n\n", qtdCadastros("funcionarios.txt"));
        while(resp == 1){
            for(i=0;i<1;i++){
                limparBuffer();

                printf("Nome: ");
                fgets(funcionarios[i].nome, 50, stdin);
                removerNovaLinha(funcionarios[i].nome);

                funcionarios[i].matricula = qtdCadastros("funcionarios.txt") + 100; /*Matricula sempre irá possuir 3 digitos*/

                printf("Data de admissao (DD/MM/AAAA): ");
                fgets(funcionarios[i].data_admissao, 11, stdin);
                removerNovaLinha(funcionarios[i].data_admissao);

                printf("Cargo:\n1 - Vendedor\n2 - Engenheiro\n3 - Gerente");
                printf("\nDigite a opcao desejada: ");
                scanf("%d", &opcao_cargo);
                if(opcao_cargo == 1){
                    strcpy(funcionarios[i].cargo, vet_cargos[0]);
                }else if(opcao_cargo == 2){
                    strcpy(funcionarios[i].cargo, vet_cargos[1]);
                }else{
                    strcpy(funcionarios[i].cargo, vet_cargos[2]);
                }

                cadastraFuncionario(funcionarios[i].matricula, funcionarios[i].nome, funcionarios[i].data_admissao, funcionarios[i].cargo);
                
                printf("\nDeseja cadastrar outro funcionario?\n1 - Sim\n2 - Nao\nDigite a opcao desejada: ");
                scanf("%d", &resp);
            }
        }
            menuFuncionario();
            break;
        case 2:
            printf("Alterar funcionario\n\n");
            printf("Digite a matricula do funcionario que deseja alterar: ");
            scanf("%d", &matricula);
            alterarRegistroPorMatricula("funcionarios.txt", matricula);
            menuFuncionario();
            break;
        case 3:
            printf("Excluir funcionario\n\n");
            printf("Digite a matricula do funcionario que deseja excluir: ");
            scanf("%d", &matricula);
            removerRegistroPorIdentificador("funcionarios.txt", matricula);
            menuFuncionario();
            break;
        case 4:
            printf("Relatorio de funcionarios\n\n");
            relatorioFuncionario("funcionarios.txt");
            system("pause");
            menuFuncionario();
            break;
        case 0:
            menuPrincipal();
            break;
    }
}
void menuObra(){
    int i, id_obra,opcao, resp = 1;
    long int data_atual;

    system("cls"); /*Limpa a tela*/
    printf("\n##################################");
    printf("\n#                                 #");
    printf("\n#        OBRAS                    #");
    printf("\n#                                 #");
    printf("\n##################################\n");

    printf("1 - Cadastrar\n");
    printf("2 - Alterar\n");
    printf("3 - Excluir\n");
    printf("4 - Relatorio\n");
    printf("0 - Voltar\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &opcao);
    system("cls"); /*Limpa a tela*/

    switch(opcao){
        case 1:
            printf("Cadastrar obra\n");
            printf("Qtd obras cadastradas: %d\n\n", qtdCadastros("obras_concluidas.txt") + qtdCadastros("obras_em_andamento.txt") + qtdCadastros("obras_previstas.txt"));
            
            printf("Data atual(ddmmaaaa): ");
            scanf("%ld", &data_atual);

            while(resp == 1){
                for(i=0;i<1;i++){
                    limparBuffer();

                    obras[i].id_obra = qtdCadastros("obras_concluidas.txt") + qtdCadastros("obras_em_andamento.txt") + qtdCadastros("obras_previstas.txt") + 1; 

                    printf("Nome: ");
                    fgets(obras[i].nome_obra, 50, stdin);
                    removerNovaLinha(obras[i].nome_obra);

                    printf("Engenheiro responsavel: ");
                    fgets(obras[i].engenheiro_responsavel, 50, stdin);
                    removerNovaLinha(obras[i].engenheiro_responsavel);

                    printf("Data de inicio (DD/MM/AAAA): ");
                    scanf("%ld", &obras[i].data_inicio);
                    printf("Data de termino (DD/MM/AAAA): ");
                    scanf("%ld", &obras[i].data_termino);

                    int estagio_obra = calculaPrazoObra(data_atual, obras[i].data_inicio, obras[i].data_termino);

                    cadastraObra(obras[i].id_obra, obras[i].nome_obra, obras[i].engenheiro_responsavel, obras[i].data_inicio, obras[i].data_termino, estagio_obra);
                    
                    printf("\nDeseja cadastrar outra obra?\n1 - Sim\n2 - Nao\nDigite a opcao desejada");
                    scanf("%d", &resp);
                }
            }
            menuObra();
            break;
        case 2:
            printf("Alterar obra\n\n");
            printf("Digite o ID da obra que deseja alterar: ");
            scanf("%d", &id_obra);

            alterarRegistroPorID("obras_concluidas.txt", id_obra); /*Procura no três arquivos de obra, o id desejado*/
            alterarRegistroPorID("obras_em_andamento.txt", id_obra);
            alterarRegistroPorID("obras_previstas.txt", id_obra);

            menuObra();
            break;
        case 3:
            printf("Excluir obra\n\n");
            printf("Digite o ID da obra que deseja excluir: ");
            scanf("%d", &id_obra);
            
            removerRegistroPorIdentificador("obras_concluidas.txt", id_obra);
            removerRegistroPorIdentificador("obras_em_andamento.txt", id_obra);
            removerRegistroPorIdentificador("obras_previstas.txt", id_obra);
            
            menuObra();
            break;
        case 4:
            printf("Relatorio de obras\n\n");
            system("cls");
            printf("====== Obras concluidas ======\n\n");
            relatorioObra("obras_concluidas.txt");
            printf("====== Obras em andamento ======\n\n");
            relatorioObra("obras_em_andamento.txt");
            printf("====== Obras previstas ======\n\n");
            relatorioObra("obras_previstas.txt");
            system("pause");
            menuObra();
            break;
        case 0:
            menuPrincipal();
            break;
    }
}

void cadastraCliente(char *nome, char *endereco, char *data_nascimento, long int cep, char *email, char *telefone, long int celular){
    int i;
    
    for(i=0;i<1;i++){
        FILE *arquivo;
        arquivo = fopen("clientes.txt", "a");
        if(arquivo == NULL){
            printf("Erro ao abrir o arquivo!");
        }
        if(strcmp(clientes[i].nome, "") == 0){ /*Evitar de imprimir o lixo de memoria alocado nos espacos vazios do vetor*/
            break;
        }
        fprintf(arquivo, "%ld - %s - %s - %s - %ld - %s - %s", clientes[i].celular, clientes[i].nome, clientes[i].endereco, clientes[i].data_nascimento, clientes[i].cep, clientes[i].email, clientes[i].telefone);

        fclose(arquivo);
    }
}
void relatorioCliente(const char *arquivo){
    typedef struct {
    	long int celular;
    	char nome[50];
        char endereco[50];
        long int datanascimento;
        long int cep;
        char email[50];
        char telefone[9];
    }dadosCliente;
    
    FILE* arquivoAtual;
    char linha[200];

    arquivoAtual = fopen(arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    system("cls");
    while (fgets(linha, sizeof(linha), arquivoAtual) != NULL) {
        dadosCliente registro;

        /*Extrai cada campo separado por '-'*/
        char* token = strtok(linha, "-");
        if (token != NULL) {
            registro.celular = atol(token);
        }

        token = strtok(NULL, "-");
        if (token != NULL) {
            strncpy(registro.nome, token, sizeof(registro.nome) - 1);
            registro.nome[sizeof(registro.nome) - 1] = '\0';
        }

        token = strtok(NULL, "-");
        if (token != NULL) {
            strncpy(registro.endereco, token, sizeof(registro.endereco) - 1);
            registro.endereco[sizeof(registro.endereco) - 1] = '\0';
        }

        token = strtok(NULL, "-");
        if (token != NULL) {
            registro.datanascimento = atol(token);
        }

        token = strtok(NULL, "-");
        if (token != NULL) {
            registro.cep = atol(token);
        }

        token = strtok(NULL, "-");
        if (token != NULL) {
            strncpy(registro.email, token, sizeof(registro.email) - 1);
            registro.email[sizeof(registro.email) - 1] = '\0';
        }

        token = strtok(NULL, "-");
        if (token != NULL) {
            strncpy(registro.telefone, token, sizeof(registro.telefone) - 1);
            registro.telefone[sizeof(registro.telefone) - 1] = '\0';
        }

        printf("Nome: %s\n", registro.nome);
        printf("Endereco: %s\n", registro.endereco);
        printf("Data de Nascimento: %ld\n", registro.datanascimento);
        printf("CEP: %ld\n", registro.cep);
        printf("Email: %s\n", registro.email);
        printf("Celular: %ld\n", registro.celular);
        printf("Telefone: %s\n", registro.telefone);
        printf("\n");
    }

    fclose(arquivoAtual);
}

void cadastraFuncionario(int matricula,char *nome, char *data_admissao, char *cargo){
    int i;
    for(i=0;i<1;i++){
        FILE *arquivo;
        arquivo = fopen("funcionarios.txt", "a");
        if(arquivo == NULL){
            printf("Erro ao abrir o arquivo!");
        }
        if(strcmp(funcionarios[i].nome, "") == 0){ /*Evitar de imprimir o lixo de memoria alocado nos espacos vazios do vetor*/
            break;
        }
        fprintf(arquivo, "%d - %s - %s - %s", funcionarios[i].matricula, funcionarios[i].nome, funcionarios[i].data_admissao, funcionarios[i].cargo);

        fclose(arquivo);
    }
};
void relatorioFuncionario(const char *arquivo) {
    typedef struct {
        char nome[50];
        int matricula;
        char dataadmissao[11];
        char cargo[20];
    } dadosFuncionarios;
    FILE *arquivoAtual;
    char linha[200];

    arquivoAtual = fopen(arquivo, "r");
    if (arquivoAtual == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivoAtual) != NULL) {
        dadosFuncionarios funcionario;

        /* Extrai cada campo separado por hífen '-'*/
        char *token = strtok(linha, "-");

        if (token != NULL) {
            funcionario.matricula = atoi(token);
        }

        token = strtok(NULL, "-");
        if (token != NULL) {
            strncpy(funcionario.nome, token, sizeof(funcionario.nome) - 1);
            funcionario.nome[sizeof(funcionario.nome) - 1] = '\0';
        }

        token = strtok(NULL, "-");
        if (token != NULL) {
            strncpy(funcionario.dataadmissao, token, sizeof(funcionario.dataadmissao) - 1);
            funcionario.dataadmissao[sizeof(funcionario.dataadmissao) - 1] = '\0';
        }

        token = strtok(NULL, "-");
        if (token != NULL) {
            strncpy(funcionario.cargo, token, sizeof(funcionario.cargo) - 1);
            funcionario.cargo[sizeof(funcionario.cargo) - 1] = '\0';
        }

        printf("Nome: %s\n", funcionario.nome);
        printf("Matricula: %d\n", funcionario.matricula);
        printf("Data de Admissao: %s\n", funcionario.dataadmissao);
        printf("Cargo: %s\n", funcionario.cargo);
        printf("\n");
    }

    fclose(arquivoAtual);
}

void cadastraObra(int id_obra, char *nome_obra, char *engenheiro_responsavel, long int data_inicio, long int data_termino, int estagio_obra){
    
    FILE *obras_concluidas, *obras_em_andamento, *obras_previstas;
    
    obras_concluidas = fopen("obras_concluidas.txt", "a");
    obras_em_andamento = fopen("obras_em_andamento.txt", "a");
    obras_previstas = fopen("obras_previstas.txt", "a");
    if(obras_concluidas == NULL || obras_em_andamento == NULL || obras_previstas == NULL){
        printf("Erro ao abrir o arquivo!");
    }

    /*Verifica o valor da variavel estagio_obra*/
    /*estagio_obra recebeu o valor retornado pela funcao calculaPrazoObra*/

    if(estagio_obra == 0){
        fprintf(obras_concluidas, "%d - %s - %s - %ld - %ld\n", id_obra, nome_obra, engenheiro_responsavel, data_inicio, data_termino);
    }
    else if(estagio_obra == 1){
        fprintf(obras_em_andamento, "%d - %s - %s - %ld - %ld\n", id_obra, nome_obra, engenheiro_responsavel, data_inicio, data_termino);
    }
    else if(estagio_obra == 2){
        fprintf(obras_previstas, "%d - %s - %s - %ld - %ld\n", id_obra, nome_obra, engenheiro_responsavel, data_inicio, data_termino);
    }
    fclose(obras_concluidas);
    fclose(obras_em_andamento);
    fclose(obras_previstas);
}
int calculaPrazoObra(long int data_atual, long int data_inicio, long int data_termino){
    
    int dia_atual, mes_atual, ano_atual;
    int dia_inicio, mes_inicio, ano_inicio;
    int dia_termino, mes_termino, ano_termino;

    dia_atual = data_atual / 1000000;       /*Mantem apenas os 2 primeiros algarismos da data no formato ddmmaaaa*/
    mes_atual = (data_atual / 10000) % 100; /*Primeiro pega os 4 primeiros algarismos e depois os 2 ultimos*/
    ano_atual = data_atual % 10000;         /*Mantem apenas os ultimos 4 algarismos*/

    dia_inicio = data_inicio / 1000000;
    mes_inicio = (data_inicio / 10000) % 100;
    ano_inicio = data_inicio % 10000;

    dia_termino = data_termino / 1000000;
    mes_termino = (data_termino / 10000) % 100;
    ano_termino = data_termino % 10000;

    /*Verifica se a data atual esta dentro do prazo de inicio e termino da obra*/
    if((ano_atual > ano_termino) || (ano_atual == ano_termino && mes_atual > mes_termino) || (ano_atual == ano_termino && mes_atual == mes_termino && dia_atual > dia_termino)){
        return 0; /*Obra concluida*/
    }else if((ano_atual < ano_inicio) || (ano_atual == ano_inicio && mes_atual < mes_inicio) || (ano_atual == ano_inicio && mes_atual == mes_inicio && dia_atual < dia_inicio)){
        return 2; /*Obra prevista*/
    }else{
        return 1; /*Obra em andamento*/
    }
}
void relatorioObra(const char *arquivo) {
    typedef struct {
        int id_obra;
        char nome_obra[50];
        char engenheiro_responsavel[50];
        long int data_inicio;
        long int data_termino;
    } dadosObras;
    FILE *arquivoAtual;

    /* Cria um array de char para armazenar cada linha do arquivo */
    char linha[200];

    arquivoAtual = fopen(arquivo, "r");
    if (arquivoAtual == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    /* Lê cada linha do arquivo */
    while (fgets(linha, sizeof(linha), arquivoAtual) != NULL) {
        dadosObras obra;

        /* Extrai cada campo separado por '-'*/
        /*Atribui as variaves da struct cada valor que encontrar entre um hífen e outro*/
        char *token = strtok(linha, "-");
        if (token != NULL) {
            obra.id_obra = atoi(token);
        }

        token = strtok(NULL, "-");
        if (token != NULL) {
            strncpy(obra.nome_obra, token, sizeof(obra.nome_obra) - 1);
            obra.nome_obra[sizeof(obra.nome_obra) - 1] = '\0';
        }

        token = strtok(NULL, "-");
        if (token != NULL) {
            strncpy(obra.engenheiro_responsavel, token, sizeof(obra.engenheiro_responsavel) - 1);
            obra.engenheiro_responsavel[sizeof(obra.engenheiro_responsavel) - 1] = '\0';
        }

        token = strtok(NULL, "-");
        if (token != NULL) {
            obra.data_inicio = atol(token);
        }

        token = strtok(NULL, "-");
        if (token != NULL) {
            obra.data_termino = atol(token);
        }

        printf("ID da Obra: %d\n", obra.id_obra);
        printf("Nome da Obra: %s\n", obra.nome_obra);
        printf("Engenheiro Responsavel: %s\n", obra.engenheiro_responsavel);
        printf("Data de Inicio: %ld\n", obra.data_inicio);
        printf("Data de Termino: %ld\n", obra.data_termino);
        printf("\n");
    }

    fclose(arquivoAtual);
}

int qtdCadastros(const char *arquivo) {
    FILE *arquivoAtual = fopen(arquivo, "r");
    if (arquivoAtual == NULL) {
        printf("Erro ao abrir o arquivo %s\n", arquivo);
    }

    int contagem = 0;
    char caracter;

    while ((caracter = fgetc(arquivoAtual)) != EOF) {
        if (caracter == '\n') {
            contagem++;
        }
    }

    fclose(arquivoAtual);
    return contagem;
}

/*FUNÇÃO PARA EXCLUIR OBRAS, FUNCIONARIOS OU CLIENTE, PELO ID, MATRICULA E CELULAR RESPECTIVAMENTE*/
void removerRegistroPorIdentificador(const char *arquivo, long int identificador) {
    FILE *arquivoAtual, *arquivoTemporario;
    
    /* Cria um array de char para armazenar cada linha do arquivo */
    char linha[100];
    int encontrou = 0;

    arquivoAtual = fopen(arquivo, "r");
    arquivoTemporario = fopen("temp.txt", "w");

    if (arquivoAtual == NULL || arquivoTemporario == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    /* Lê cada linha do arquivo */
    while (fgets(linha, sizeof(linha), arquivoAtual) != NULL) {
        long int valorLido;
        sscanf(linha, "%ld", &valorLido);
        /* Se o valor lido for igual ao identificador, não copia para o arquivo temporário */
        if (valorLido == identificador) {
            encontrou = 1;
            continue;
        }
        fputs(linha, arquivoTemporario);
    }

    fclose(arquivoAtual);
    fclose(arquivoTemporario);

    if (encontrou) {
        remove(arquivo);
        rename("temp.txt", arquivo);
        printf("O registro com o valor %ld foi removido.\n", identificador);
    } else {
        remove("temp.txt");
        printf("Nenhum registro com o valor %ld encontrado.\n", identificador);
    }
}
void alterarRegistroPorCelular(const char *arquivo, long int valor) {
    typedef struct {
        long int celular;
        char nome[50];
        char endereco[50];
        long int datanascimento;
        long int cep;
        char email[50];
        char telefone[9];
    } dadosCliente;

    dadosCliente registro;

    FILE *arquivoAtual, *arquivoTemporario;
    char linha[200];
    int encontrou = 0;

    arquivoAtual = fopen(arquivo, "r");
    arquivoTemporario = fopen("temp.txt", "w");
    if (arquivoAtual == NULL || arquivoTemporario == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivoAtual) != NULL) {
        sscanf(linha, "%ld - %[^-] - %[^-] - %ld - %ld - %[^-] - %[^\n]", &registro.celular, registro.nome, registro.endereco, &registro.datanascimento, &registro.cep, registro.email, registro.telefone);

        /* Verifica se o valor extraido do arquivo corresponde ao valor de ID, celular ou matricula fornecidos*/
        if (registro.celular == valor) {
            encontrou = 1;

            printf("Linha encontrada:\n%s\n", linha);
            printf("Selecione o campo a ser alterado:\n");
            printf("1 - Nome\n");
            printf("2 - Endereco\n");
            printf("3 - CEP\n");
            printf("4 - Email\n");
            printf("5 - Telefone\n");
            printf("Digite a opcao desejada: ");

            int opcao;
            scanf("%d", &opcao);

            int c;
            while ((c = getchar()) != '\n' && c != EOF); /* Limpa o buffer do teclado*/

            char novoCampo[50];
            printf("Digite o novo valor para o campo desejado: ");
            fgets(novoCampo, sizeof(novoCampo), stdin);
            removerNovaLinha(novoCampo);

            switch (opcao) {
                case 1:
                    strncpy(registro.nome, novoCampo, sizeof(registro.nome) - 1);
                    registro.nome[sizeof(registro.nome) - 1] = '\0';
                    break;
                case 2:
                    strncpy(registro.endereco, novoCampo, sizeof(registro.endereco) - 1);
                    registro.endereco[sizeof(registro.endereco) - 1] = '\0';
                    break;
                case 4:
                    strncpy(registro.email, novoCampo, sizeof(registro.email) - 1);
                    registro.email[sizeof(registro.email) - 1] = '\0';
                    break;
                case 5:
                    strncpy(registro.telefone, novoCampo, sizeof(registro.telefone) - 1);
                    registro.telefone[sizeof(registro.telefone) - 1] = '\0';
                    break;
                default:
                    printf("Opcao invalida!\n");
                    fclose(arquivoAtual);
                    fclose(arquivoTemporario);
                    remove("temp.txt");
                    return;
            }

            /*Escreve a linha modificada no arquivo temporario*/
            fprintf(arquivoTemporario, "%ld - %s - %s - %ld - %ld - %s - %s\n",
                    registro.celular, registro.nome, registro.endereco,
                    registro.datanascimento, registro.cep, registro.email, registro.telefone);
        } else {
            /*Copia a linha original para o arquivo temporario*/
            fputs(linha, arquivoTemporario);
        }
    }

    fclose(arquivoAtual);
    fclose(arquivoTemporario);

    if (encontrou) {
        remove(arquivo);
        rename("temp.txt", arquivo);
        printf("O registro com o valor %ld foi modificado.\n", valor);
    } else {
        remove("temp.txt");
        printf("Nenhum registro com o valor %ld encontrado.\n", valor);
    }
}
void alterarRegistroPorMatricula(const char *arquivo, int valor){
    typedef struct {
        char nome[50];
        int matricula;
        char dataadmissao[11];
        char cargo[20];
    } dadosFuncionarios;

    dadosFuncionarios registro;

    FILE *arquivoAtual, *arquivoTemporario;
    char linha[200];
    int encontrou = 0;

    arquivoAtual = fopen(arquivo, "r");
    arquivoTemporario = fopen("temp.txt", "w");
    if (arquivoAtual == NULL || arquivoTemporario == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivoAtual) != NULL) {
        sscanf(linha, "%d - %[^-] - %[^-] - %[^\n]", &registro.matricula, registro.nome, registro.dataadmissao, registro.cargo);

        /* Verifica se o valor lido corresponde ao valor fornecido de matricula*/
        if (registro.matricula == valor) {
            encontrou = 1;

            printf("Linha encontrada:\n%s\n", linha);
            printf("Selecione o campo a ser alterado:\n");
            printf("1 - Nome\n");
            printf("2 - Cargo\n");
            printf("Digite a opcao desejada: ");

            int opcao;
            scanf("%d", &opcao);

            int c;
            while ((c = getchar()) != '\n' && c != EOF); /*Limpa o buffer do teclado*/

            char novoCampo[50];
            printf("Digite o novo valor para o campo desejado: ");
            fgets(novoCampo, sizeof(novoCampo), stdin);

            /* Remove o caractere de nova linha do final da string*/
            removerNovaLinha(novoCampo);

            switch (opcao) {
                case 1:
                    strncpy(registro.nome, novoCampo, sizeof(registro.nome) - 1);
                    registro.nome[sizeof(registro.nome) - 1] = '\0';
                    break;
                case 2:
                    strncpy(registro.cargo, novoCampo, sizeof(registro.cargo) - 1);
                    registro.cargo[sizeof(registro.cargo) - 1] = '\0';
                    break;
                default:
                    printf("Opcao invalida!\n");
                    fclose(arquivoAtual);
                    fclose(arquivoTemporario);
                    remove("temp.txt");
                    return;
            }

            /* Escreve a linha modificada no arquivo temporario*/
            fprintf(arquivoTemporario, "%d - %s - %s - %s\n",
                    registro.matricula, registro.nome, registro.dataadmissao, registro.cargo);
        } else {
            /*Copia a linha original para o arquivo temporario*/
            fputs(linha, arquivoTemporario);
        }
    }

    fclose(arquivoAtual);
    fclose(arquivoTemporario);

    if(encontrou) {
        remove(arquivo);
        rename("temp.txt", arquivo);
        printf("O registro com a matricula %d foi modificado.\n", valor);
    } else {
        remove("temp.txt");
        printf("Nenhum registro com a matricula %d encontrado.\n", valor);
    }
}
void alterarRegistroPorID(const char *arquivo, int valor){
    
    typedef struct{
        int id;
        char nome[50];
        char engenheiro_responsavel[50];
        long int data_inicio;
        long int data_termino;
    }dadosObra;

    dadosObra registro;

    FILE *arquivoAtual, *arquivoTemporario;
    /*Abre o arquivo original para leitura e o arquivo temporario para escrita*/
    char linha[200];
    int encontrou = 0;
    arquivoAtual = fopen(arquivo, "r");
    arquivoTemporario = fopen("temp.txt", "w");
    if (arquivoAtual == NULL || arquivoTemporario == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    while(fgets(linha, sizeof(linha), arquivoAtual) != NULL){
        sscanf(linha, "%d - %[^-] - %[^-] - %ld - %ld", &registro.id, registro.nome, registro.engenheiro_responsavel, &registro.data_inicio, &registro.data_termino);
    
        if(registro.id == valor){
            encontrou = 1;
            printf("Linha encontrada:\n%s\n", linha);
            printf("Selecione o campo a ser alterado:\n");
            printf("1 - Nome\n");
            printf("2 - Engenheiro Responsavel\n");

            int opcao;
            scanf("%d", &opcao);

            int c;
            while ((c = getchar()) != '\n' && c != EOF); /* Limpa o buffer do teclado*/

            char novoCampo[50];
            printf("Digite o novo valor para o campo desejado: ");
            fgets(novoCampo, sizeof(novoCampo), stdin);
            novoCampo[strcspn(novoCampo, "\n")] = '\0';

            switch(opcao){
                case 1:
                    strncpy(registro.nome, novoCampo, sizeof(registro.nome) - 1);
                    registro.nome[sizeof(registro.nome) - 1] = '\0';
                    break;
                case 2:
                    strncpy(registro.engenheiro_responsavel, novoCampo, sizeof(registro.engenheiro_responsavel) - 1);
                    registro.engenheiro_responsavel[sizeof(registro.engenheiro_responsavel) - 1] = '\0';
                    break;
                default:
                    printf("Opcao invalida!\n");
                    fclose(arquivoAtual);
                    fclose(arquivoTemporario);
                    remove("temp.txt");
                    return;
            }
            fprintf(arquivoTemporario, "%d - %s - %s - %ld - %ld\n", registro.id, registro.nome, registro.engenheiro_responsavel, registro.data_inicio, registro.data_termino);
        }else{
            fputs(linha, arquivoTemporario);
        }
    }
    fclose(arquivoAtual);
    fclose(arquivoTemporario);
    if(encontrou){
        remove(arquivo);
        rename("temp.txt", arquivo);
        printf("O registro com o id %d foi modificado.\n", valor);
    }
}

int main(){
    menuPrincipal();
}
