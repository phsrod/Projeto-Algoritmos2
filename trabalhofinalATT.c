//Seção de Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Seção de definições de constantes
#define MAX_STR_LEN 50
#define FILENAME "produtos.txt"
#define FILENAMEs "clientes.txt"
#define FILENAMEv "vendas.txt"

//Seção de Estruturas de dados

//Estrutura de armazenamento de dados de produtos
typedef struct {
    char nome[MAX_STR_LEN];
    char categoria[MAX_STR_LEN];
    int quantidade;
    float valor;
} Produtos;

//Estrutura de armazenamento de dados de clientes
typedef struct {
    char nome[MAX_STR_LEN];
    char RG[MAX_STR_LEN];
    char CPF[MAX_STR_LEN];
    char data[MAX_STR_LEN];
} Clientes;

//Estrutura de armazenamento de dados de vendas
typedef struct {
    char CPF[MAX_STR_LEN];
    char produto[MAX_STR_LEN];
    int quantidade;
    float valor;
} Vendas;

//Seção de Menus

//Função para exibir menu principal
void menu(){
    system("CLS");
    printf("---------------------------------------\n");
    printf("|                                     | \n");
    printf("|             GESTAO MP               | \n");
    printf("|                                     | \n");
    printf("---------------------------------------\n");
    printf("| 1 - Produtos                        | \n");
    printf("| 2 - Clientes                        | \n");
    printf("| 3 - Vendas                          | \n");
    printf("| 4 - Sair                            | \n");
    printf("---------------------------------------\n");
    printf("Escolha uma opcao: ");
}

//Função para exibir o menu de produtos
void menuProdutos() {
    system("CLS");
    printf("---------------------------------------\n");
    printf("|                                     | \n");
    printf("|             Produtos                | \n");
    printf("|                                     | \n");
    printf("---------------------------------------\n");
    printf("| 1 - Cadastrar Produtos              | \n");
    printf("| 2 - Consultar Produtos              | \n");
    printf("| 3 - Listar Produtos                 | \n");
    printf("| 4 - Alterar                         | \n");
    printf("| 5 - Remover                         | \n");
    printf("| 6 - Sair                            | \n");
    printf("---------------------------------------\n");
    printf("Escolha uma opcao: ");
}

//Função para exibir o menu de clientes
void menuClientes() {
    system("CLS");
    printf("---------------------------------------\n");
    printf("|                                     | \n");
    printf("|             Clientes                | \n");
    printf("|                                     | \n");
    printf("---------------------------------------\n");
    printf("| 1 - Cadastrar Clientes              | \n");
    printf("| 2 - Consultar Clientes              | \n");
    printf("| 3 - Listar Clientes                 | \n");
    printf("| 4 - Alterar                         | \n");
    printf("| 5 - Remover                         | \n");
    printf("| 6 - Sair                            | \n");
    printf("---------------------------------------\n");
    printf("Escolha uma opcao: ");
}

//Função para exibir o menu de vendas
void menuVendas() {
    system("CLS");
    printf("---------------------------------------\n");
    printf("|                                     | \n");
    printf("|             Vendas                  | \n");
    printf("|                                     | \n");
    printf("---------------------------------------\n");
    printf("| 1 - Realizar Venda                  | \n");
    printf("| 2 - Consultar Saldo do Caixa        | \n");
    printf("| 3 - Listar Vendas                   | \n");
    printf("| 4 - Total de Produtos Vendidos      | \n");
    printf("| 5 - Sair                            | \n");
    printf("---------------------------------------\n");
    printf("Escolha uma opcao: ");
}

//Seção de funções auxiliares

//Função para capturar a escolha de opção do usuário
int lerOpcao() {
    char entrada[100];
    int opcao;

    if (scanf(" %99[^\n]", entrada) == 1) {
        getchar();  
        if (sscanf(entrada, "%d", &opcao) == 1) {
            return opcao;  
        }
    } else {
        getchar();
    }

    return -1;  
}

//Função para verificar a existência de dados em um arquivo
int verificarVazio(const char *caminho){
    int v, r=0;
    FILE *arquivo = fopen(caminho, "r");
    v = fgetc(arquivo);
    if(v == EOF){
        r = 1;
    }
    fclose(arquivo);
    setbuf(stdin, NULL);
    return r;
}

//Função para verificar a "duplicidade" do atributo "nome" no arquivo
int verificarNomeExistente(const char *nome) {
    FILE *arquivo = fopen(FILENAME, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 0; 
    }
    Produtos p;
    while (fscanf(arquivo, "%[^|]|%[^|]|%d|%f\n", p.nome, p.categoria, &p.quantidade, &p.valor) != EOF) {
        if (stricmp(p.nome, nome) == 0) {
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);
    return 0; 
}

//Função para verificar a "duplicidade" do atributo "CPF" no arquivo
int verificarCpfExistente(const char *cpf) {
    FILE *arquivo = fopen(FILENAMEs, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 0; 
    }
    Clientes c;
    while (fscanf(arquivo, "%[^|]|%[^|]|%[^|]|%[^|]|\n", c.nome, c.data, c.CPF, c.RG) != EOF) {
        if (strcmp(c.CPF, cpf) == 0) {
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);
    return 0; 
}

//Seção de funções primárias

//Função para cadastrar um produto no arquivo
void cadastrarProduto(Produtos *p) {
    int encontrado = 0;
    FILE *arquivo = fopen(FILENAME, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
    }
    
    Produtos aux;

    system("CLS");
    printf("---------------------------------------\n");
    printf("|          Cadastrar Produto          |\n");
    printf("---------------------------------------\n\n");
    setbuf(stdin, NULL);
    printf("Nome: ");
    scanf("%[^\n]", aux.nome);
    setbuf(stdin, NULL);
    FILE *arq = fopen(FILENAME, "r");

    while (fscanf(arq, "%[^|]|%[^|]|%d|%f\n", (*p).nome, (*p).categoria, &(*p).quantidade, &(*p).valor) != EOF) {
        if(stricmp(aux.nome, (*p).nome) == 0){
            encontrado = 1;
            break;
        }
    }

    fclose(arq);

    if (encontrado == 0){
        printf("Categoria: ");
        scanf("%[^\n]", aux.categoria);
        setbuf(stdin, NULL);
        printf("Quantidade: ");
        scanf("%d", &aux.quantidade);
        setbuf(stdin, NULL);
        while(aux.quantidade < 1){
            printf("ERRO: A quantidade nao pode ser menor/igual a zero!\nDigite um novo valor: ");
            setbuf(stdin, NULL);
            scanf("%d", &aux.quantidade);
            setbuf(stdin, NULL);
        }
        printf("Valor Unitario: ");
        scanf("%f", &aux.valor);
        setbuf(stdin, NULL);
        while(aux.valor <= 0){
            printf("ERRO: O valor nao pode ser menor/igual a zero!\nDigite um novo valor: ");
            setbuf(stdin, NULL);
            scanf("%f", &aux.valor);
            setbuf(stdin, NULL);
        }
        *p = aux;

        fprintf(arquivo, "%s|%s|%d|%.2f\n", (*p).nome, (*p).categoria, (*p).quantidade, (*p).valor);
        fclose(arquivo);
        printf("Produto cadastrado com sucesso!\n");
    }
    else if(encontrado == 1){
        printf("Voce nao pode cadastrar um mesmo produto duas vezes!\n");
    }
    
    system("PAUSE");
}

//Função para buscar um produto no arquivo
void consultarProduto(Produtos *p) {

    if(verificarVazio(FILENAME)){
        printf("Nenhum produto cadastrado!\n");
        system("PAUSE");
        return;
    }

    FILE *arquivo = fopen(FILENAME, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
    }

    char nome[MAX_STR_LEN];
    system("CLS");
    printf("---------------------------------------\n");
    printf("|          Consultar Produto          |\n");
    printf("---------------------------------------\n\n");
    printf("Digite o nome do produto: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", nome);
    setbuf(stdin, NULL);

    int encontrado = 0;
    while (fscanf(arquivo, "%[^|]|%[^|]|%d|%f\n", (*p).nome, (*p).categoria, &(*p).quantidade, &(*p).valor) != EOF) {
        if (stricmp((*p).nome, nome) == 0) {
            printf("\nProduto encontrado:\n");
            printf("Nome: %s\nCategoria: %s\nQuantidade: %d\nValor Unitario: %.2f\n", (*p).nome, (*p).categoria, (*p).quantidade, (*p).valor);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Produto nao encontrado.\n");
    }

    fclose(arquivo);
    system("PAUSE");
}

//Função para alterar um produto existente dentro do arquivo
void alterarProduto(Produtos *p) {
    if(verificarVazio(FILENAME)){
        printf("Nenhum produto cadastrado!\n");
        system("PAUSE");
        return;
    }
    FILE *arquivo = fopen(FILENAME, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario");
        fclose(arquivo);
        return;
    }

    char nome[MAX_STR_LEN];
    system("CLS");
    printf("---------------------------------------\n");
    printf("|            Editar Produto           |\n");
    printf("---------------------------------------\n\n");
    printf("Digite o nome do produto a ser editado: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", nome);
    setbuf(stdin, NULL);

    int encontrado = 0;
    while (fscanf(arquivo, "%[^|]|%[^|]|%d|%f\n", (*p).nome, (*p).categoria, &(*p).quantidade, &(*p).valor) != EOF) {
        if (stricmp((*p).nome, nome) == 0) {
            printf("\nProduto encontrado. \nDigite os novos dados:\n");
            char novoNome[MAX_STR_LEN];
            int nomeValido = 0;
            while (!nomeValido) {
                printf("Nome: ");
                setbuf(stdin, NULL);
                scanf("%[^\n]", novoNome);
                setbuf(stdin, NULL);
                if (stricmp(novoNome, (*p).nome) == 0) {
                    strcpy((*p).nome, novoNome);
                    nomeValido = 1;
                } else {
                    if (verificarNomeExistente(novoNome)) {
                        printf("ERRO: O nome do produto ja existe. Tente outro nome.\n");
                    } else {
                        strcpy((*p).nome, novoNome);
                        nomeValido = 1;
                    }
                }
            }

            printf("Categoria: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]", (*p).categoria);
            setbuf(stdin, NULL);
            printf("Quantidade: ");
            scanf("%d", &(*p).quantidade);
            setbuf(stdin, NULL);
            while((*p).quantidade < 1){
                printf("ERRO: A quantidade nao pode ser menor/igual a zero!\nDigite um novo valor: ");
                scanf("%d", &(*p).quantidade);
                setbuf(stdin, NULL);
            }
            printf("Valor Unitário: ");
            scanf("%f", &(*p).valor);
            setbuf(stdin, NULL);
            while((*p).valor <= 0){
                printf("ERRO: O valor nao pode ser menor/igual a zero!\nDigite um novo valor: ");
                scanf("%f", &(*p).valor);
                setbuf(stdin, NULL);
            }
            encontrado = 1;
        }
        fprintf(temp, "%s|%s|%d|%.2f\n", (*p).nome, (*p).categoria, (*p).quantidade, (*p).valor);
    }

    fclose(arquivo);
    fclose(temp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (encontrado) {
        printf("Produto editado com sucesso!\n");
    } else {
        printf("Produto nao encontrado.\n");
    }
    system("PAUSE");
}

//Função para listar produtos cadastrados dentro do arquivo
void listarProdutos(Produtos *p) {
    if(verificarVazio(FILENAME)){
        printf("Nenhum produto cadastrado!\n");
        system("PAUSE");
        return;
    }
    FILE *arquivo = fopen(FILENAME, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
    }

    system("CLS");
    printf("---------------------------------------\n");
    printf("|           Listar Produtos           |\n");
    printf("---------------------------------------\n\n");
    
    while (fscanf(arquivo, "%[^|]|%[^|]|%d|%f\n", (*p).nome, (*p).categoria, &(*p).quantidade, &(*p).valor) != EOF) {
        printf("Nome: %s\nCategoria: %s\nQuantidade: %d\nValor Unitario: %.2f\n\n", (*p).nome, (*p).categoria, (*p).quantidade, (*p).valor);
        
    }
    
    fclose(arquivo);
    system("PAUSE");
}

//Função para excluir um produto existente dentro do arquivo
void excluirProduto(Produtos *p) {
    if(verificarVazio(FILENAME)){
        printf("Nenhum produto cadastrado!\n");
        system("PAUSE");
        return;
    }
    FILE *arquivo = fopen(FILENAME, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario");
        fclose(arquivo);
        return;
    }

    char nome[MAX_STR_LEN];
    system("CLS");
    printf("---------------------------------------\n");
    printf("|           Excluir Produto           |\n");
    printf("---------------------------------------\n\n");
    printf("Digite o nome do produto a ser excluido: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", nome);
    setbuf(stdin, NULL);

    int encontrado = 0;
    while (fscanf(arquivo, "%[^|]|%[^|]|%d|%f\n", (*p).nome, (*p).categoria, &(*p).quantidade, &(*p).valor) != EOF) {
        if (stricmp((*p).nome, nome) != 0) {
            fprintf(temp, "%s|%s|%d|%.2f\n", (*p).nome, (*p).categoria, (*p).quantidade, (*p).valor);
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (encontrado) {
        printf("Produto excluido com sucesso!\n");
    } else {
        printf("Produto nao encontrado.\n");
    }
    system("PAUSE");
}

//Seção de Clientes

//Função para cadastrar um cliente no arquivo
void cadastrarClientes(Clientes *c) {
    FILE *arquivo = fopen(FILENAMEs, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
    }
    Clientes aux;
    
    system("CLS");
    printf("---------------------------------------\n");
    printf("|         Cadastro de Clientes        |\n");
    printf("---------------------------------------\n\n");
    setbuf(stdin, NULL);

    printf("CPF: ");
    setbuf(stdin, NULL); 
    scanf("%[^\n]", aux.CPF);
    setbuf(stdin, NULL);

    FILE *arq = fopen(FILENAMEs, "r");
    int encontrado = 0;
    
    while (fscanf(arq, "%[^|]|%[^|]|%[^|]|%[^|]|\n", (*c).nome, (*c).data, (*c).CPF, (*c).RG) != EOF) {
        if(strcmp(aux.CPF, (*c).CPF) == 0){
            encontrado = 1;
            break;
        }
    }

    fclose(arq);

    if (encontrado == 0){
        printf("Nome: ");
        setbuf(stdin, NULL);   
        scanf("%[^\n]", aux.nome);
        setbuf(stdin, NULL);
        printf("Data: "); 
        scanf("%[^\n]", aux.data);
        setbuf(stdin, NULL); 
        printf("RG: "); 
        scanf("%[^\n]", aux.RG);
        setbuf(stdin, NULL);
        *c = aux;
        fprintf(arquivo, "%s|%s|%s|%s|\n", (*c).nome, (*c).data, (*c).CPF, (*c).RG);
        fclose(arquivo);
        printf("Cliente cadastrado com sucesso!\n");
    } 
    
    else if(encontrado == 1) {
        printf("CPF ja existente!\n");
    }
    system("PAUSE");
}

//Função para buscar clientes cadastrados dentro do arquivo
void consultarCliente(Clientes *c) {
    if(verificarVazio(FILENAMEs)){
        printf("Nenhum usuario cadastrado!\n");
        system("PAUSE");
        return;
    }
    FILE *arquivo = fopen(FILENAMEs, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
    }

    char cpf[MAX_STR_LEN];
    system("CLS");
    printf("---------------------------------------\n");
    printf("|          Consultar Clientes         |\n");
    printf("---------------------------------------\n\n");
    printf("Digite o CPF do cliente: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", cpf);
    setbuf(stdin, NULL);

    int encontrado = 0;
    while (fscanf(arquivo, "%[^|]|%[^|]|%[^|]|%[^|]|\n", (*c).nome, (*c).data, (*c).CPF, (*c).RG) != EOF) {
        if (strcmp((*c).CPF, cpf) == 0) {
            printf("\nCliente encontrado:\n");
            printf("Nome: %s\nData: %s\nCPF: %s\nRG: %s\n", (*c).nome, (*c).data, (*c).CPF, (*c).RG);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente nao encontrado.\n");
    }

    fclose(arquivo);
    system("PAUSE");
}

//Função para alterar dados de cliente(s) existente(s) dentro do arquivo
void alterarCliente(Clientes *c) {
    if(verificarVazio(FILENAMEs)){
        printf("Nenhum usuario cadastrado!\n");
        system("PAUSE");
        return;
    }
    FILE *arquivo = fopen(FILENAMEs, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario");
        fclose(arquivo);
        return;
    }

    char cpf[MAX_STR_LEN];
    system("CLS");
    printf("---------------------------------------\n");
    printf("|            Editar Cliente           |\n");
    printf("---------------------------------------\n\n");
    printf("Digite o CPF do cliente a ser editado: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", cpf);
    setbuf(stdin, NULL);

    int encontrado = 0;
    while (fscanf(arquivo, "%[^|]|%[^|]|%[^|]|%[^|]|\n", (*c).nome, (*c).data, (*c).CPF, (*c).RG) != EOF) {
        if (strcmp((*c).CPF, cpf) == 0) {
            printf("\nCliente encontrado. Digite os novos dados:\n");
            char novoCpf[MAX_STR_LEN];
            int cpfValido = 0;
            while (!cpfValido) {
                printf("CPF: ");
                scanf("%[^\n]", novoCpf);
                setbuf(stdin, NULL);

                if (strcmp(novoCpf, (*c).CPF) == 0) {
                    strcpy((*c).CPF, novoCpf);
                    cpfValido = 1;
                } else {
                    if (verificarCpfExistente(novoCpf)) {
                        printf("ERRO: O CPF ja esta cadastrado. Tente outro CPF.\n");
                    } else {
                        strcpy((*c).CPF, novoCpf);
                        cpfValido = 1;
                    }
                }
            }

            printf("Nome: ");
            scanf("%[^\n]", (*c).nome);
            setbuf(stdin, NULL);
            printf("Data: ");
            scanf("%[^\n]", (*c).data);
            setbuf(stdin, NULL);
            printf("RG: ");
            scanf("%[^\n]", (*c).RG);
            setbuf(stdin, NULL);
            encontrado = 1;
        }
        fprintf(temp, "%s|%s|%s|%s|\n", (*c).nome, (*c).data, (*c).CPF, (*c).RG);
    }

    fclose(arquivo);
    fclose(temp);

    remove(FILENAMEs);
    rename("temp.txt", FILENAMEs);

    if (encontrado) {
        printf("Cliente editado com sucesso!\n");
    } else {
        printf("Cliente nao encontrado.\n");
    }
    system("PAUSE");
}

//Função para listar o(s) cliente(s) existente(s) dentro do arquivo
void listarClientes(Clientes *c) {
    if(verificarVazio(FILENAMEs)){
        printf("Nenhum usuario cadastrado!\n");
        system("PAUSE");
        return;
    }
    FILE *arquivo = fopen(FILENAMEs, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
    }

    system("CLS");
    printf("---------------------------------------\n");
    printf("|          Lista de Clientes          |\n");
    printf("---------------------------------------\n\n");

    while (fscanf(arquivo, "%[^|]|%[^|]|%[^|]|%[^|]|\n", (*c).nome, (*c).data, (*c).CPF, (*c).RG) != EOF) {
        printf("Nome: %s\nData: %s\nCPF: %s\nRG: %s\n\n", (*c).nome, (*c).data, (*c).CPF, (*c).RG);
    }

    fclose(arquivo);
    system("PAUSE");
}

//Função para excluir cliente(s) existente(s) dentro do arquivo
void excluirClientes(Clientes *c) {
    if(verificarVazio(FILENAMEs)){
        printf("Nenhum usuario cadastrado!\n");
        system("PAUSE");
        return;
    }
    FILE *arquivo = fopen(FILENAMEs, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario");
        fclose(arquivo);
        return;
    }

    char cpf[MAX_STR_LEN];
    system("CLS");
    printf("---------------------------------------\n");
    printf("|           Excluir Cliente           |\n");
    printf("---------------------------------------\n\n");
    printf("Digite o CPF do cliente a ser excluido: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", cpf);
    setbuf(stdin, NULL);

    int encontrado = 0;
    while (fscanf(arquivo, "%[^|]|%[^|]|%[^|]|%[^|]|\n", (*c).nome, (*c).data, (*c).CPF, (*c).RG) != EOF) {
        if (strcmp((*c).CPF, cpf) != 0) {
            fprintf(temp, "%s|%s|%s|%s|\n", (*c).nome, (*c).data, (*c).CPF, (*c).RG);
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove(FILENAMEs);
    rename("temp.txt", FILENAMEs);

    if (encontrado) {
        printf("Cliente excluido com sucesso!\n");
    } else {
        printf("Cliente nao encontrado.\n");
    }
    system("PAUSE");
}

//Seção de Vendas

//Função para realizar possível venda
void realizarvenda(Clientes *c, Produtos *p, Vendas *v){
    Vendas aux;
    system("CLS");
    printf("---------------------------------------\n");
    printf("|            Realizar Venda           |\n");
    printf("---------------------------------------\n\n");
    FILE *arquivo = fopen(FILENAMEv, "a");
    printf("Digite o CPF do cliente: ");
    setbuf(stdin, NULL); 
    scanf("%[^\n]", aux.CPF);
    setbuf(stdin, NULL);

    FILE *arq = fopen(FILENAMEs, "r");
    int encontrado = 0;

    while (fscanf(arq, "%[^|]|%[^|]|%[^|]|%[^|]|\n", (*c).nome, (*c).data, (*c).CPF, (*c).RG) != EOF) {
        if(strcmp(aux.CPF, (*c).CPF) == 0){
            encontrado = 1;
            break;
        }
    }
    fclose(arq);

    if(encontrado == 0){
        printf("O CPF do cliente nao esta cadastrado no sistema!\n");
        system("PAUSE");
    }
    else if(encontrado == 1){
        printf("Digite o nome do produto: ");
        setbuf(stdin, NULL);   
        scanf("%[^\n]", aux.produto);
        setbuf(stdin, NULL);
        FILE *arq = fopen(FILENAME, "r");

        while (fscanf(arq, "%[^|]|%[^|]|%d|%f\n", (*p).nome, (*p).categoria, &(*p).quantidade, &(*p).valor) != EOF) {
            if(stricmp(aux.produto, (*p).nome) == 0){
                encontrado = 0;
                break;
            }
        }

        fclose(arq);
        if(encontrado == 0){
            printf("Quantidade: "); 
            scanf("%d", &aux.quantidade);
            setbuf(stdin, NULL);
            while(aux.quantidade < 1){
                printf("ERRO: O quantidade nao pode ser menor/igual a zero!\nDigite uma nova quantidade: ");
                setbuf(stdin, NULL);
                scanf("%d", &aux.quantidade);
                setbuf(stdin, NULL);
            }
            if(aux.quantidade <= (*p).quantidade){
                
            aux.valor = aux.quantidade * (*p).valor;
            *v = aux;
            
            fprintf(arquivo, "%s|%s|%d|%.2f|\n", (*v).CPF, (*p).nome, (*v).quantidade, (*v).valor);
            fclose(arquivo);

            FILE *arq = fopen(FILENAME, "r");
            FILE *temp = fopen("temp.txt", "w");

            if (arq == NULL || temp == NULL) {
                printf("Erro ao acessar o arquivo de produtos!\n");
                return;
            }

            while (fscanf(arq, "%[^|]|%[^|]|%d|%f\n", (*p).nome, (*p).categoria, &(*p).quantidade, &(*p).valor) != EOF) {
                if (stricmp(aux.produto, (*p).nome) == 0) {
                    (*p).quantidade -= aux.quantidade;
                }
                
                fprintf(temp, "%s|%s|%d|%.2f\n", (*p).nome, (*p).categoria, (*p).quantidade, (*p).valor);
            }

            fclose(arq);
            fclose(temp);

            remove(FILENAME);
            rename("temp.txt", FILENAME);

            printf("\n\nVenda realizada com sucesso e estoque atualizado!\n");

            }
            else{
                printf("Esse produto nao possui essa quantidade!\n");
            }
            system("Pause");
        }
        else{
            printf("O produto nao existe no estoque!\n");
            system("PAUSE");
        }
    }

    
    fclose(arquivo);
}

//Função para listar a(s) venda(s) realizada(s)
void vendasRealizadas(Vendas *v) {
    
    if(verificarVazio(FILENAMEv)){
        printf("Nenhuma venda realizada!\n");
        system("PAUSE");
        return;
    }
    FILE *arquivo = fopen(FILENAMEv, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
    }
    
    system("CLS");
    
    printf("---------------------------------------\n");
    printf("|          Vendas Realizadas          |\n");
    printf("---------------------------------------\n\n");
    
    while (fscanf(arquivo, "%[^|]|%[^|]|%d|%f|\n", (*v).CPF, (*v).produto, &(*v).quantidade, &(*v).valor) != EOF) {
        printf("CPF: %s\nProduto: %s\nQuantidade: %d\nValor: %.2f\n\n", (*v).CPF, (*v).produto, (*v).quantidade, (*v).valor);
    }
    
    fclose(arquivo);
    system("PAUSE");
}

//Função para exibição do saldo do caixa
void saldoCaixa(Vendas *v){
    system("CLS");
    float saldo=0;
    if(verificarVazio(FILENAMEv)){
        printf("Nenhuma venda realizada!\n");
        printf("Saldo: R$ 0\n");
        system("PAUSE");
        return;
    }
    FILE *arquivo = fopen(FILENAMEv, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
    }
    while (fscanf(arquivo, "%[^|]|%[^|]|%d|%f|\n", (*v).CPF, (*v).produto, &(*v).quantidade, &(*v).valor) != EOF) {
        saldo += (*v).valor;
    }
    fclose(arquivo);
    printf("---------------------------------------\n");
    printf("|                CAIXA                |\n");
    printf("---------------------------------------\n");
    printf("Saldo total: R$ %.2f \n", saldo);
    system("PAUSE");
}

//Função para mostrar o total (em unidades) de produtos vendidos
void totalVendidos(Vendas *v){
    system("CLS");
    int qntdTotal=0;
    if(verificarVazio(FILENAMEv)){
        printf("Nenhum produto foi vendido!\n");
        system("PAUSE");
        return;
    }
    FILE *arquivo = fopen(FILENAMEv, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
    }
    while (fscanf(arquivo, "%[^|]|%[^|]|%d|%f|\n", (*v).CPF, (*v).produto, &(*v).quantidade, &(*v).valor) != EOF) {
        qntdTotal += (*v).quantidade;
    }
    fclose(arquivo);
    printf("---------------------------------------\n");
    printf("|                CAIXA                |\n");
    printf("---------------------------------------\n");
    printf("Total de produtos vendidos: %d\n", qntdTotal);
    system("PAUSE");
}

//Função principal - lógica do programa
int main(){
    //Variáveis auxiliares de navegação
    int respMenu, respVendas, respProdutos, respClientes;

    //Instâncias das estruturas de armazenamento de dados
    Produtos p;
    Clientes c;
    Vendas v;

    //Estrutura de navegação entre menus do sistema
    do{
        menu();
        respMenu = lerOpcao();
        switch(respMenu){
            
        case 1:
            do{
                menuProdutos();
                respProdutos = lerOpcao();
                switch (respProdutos){
                case 1:
                    cadastrarProduto(&p);
                    break;
                case 2:
                    consultarProduto(&p);
                    break;
                case 3:
                    listarProdutos(&p);
                    break;
                case 4:
                    alterarProduto(&p);
                    break;
                case 5:
                    excluirProduto(&p);
                    break;
                case 6:
                    break;
                default:
                    printf("ERRO -- Digite uma opcao valida! \n");
                    system("PAUSE");
                    break;
                }
            }while(respProdutos != 6);
            break;

        case 2:
            do{
                menuClientes();
                respClientes = lerOpcao();
                switch (respClientes){
                case 1:
                    cadastrarClientes(&c);
                    break;
                case 2:
                    consultarCliente(&c);
                    break;
                case 3:
                    listarClientes(&c);
                    break;
                case 4:
                    alterarCliente(&c);
                    break;
                case 5:
                    excluirClientes(&c);
                    break;
                case 6:
                    break;
                default:
                    printf("ERRO - Digite uma opcao valida! \n");
                    system("PAUSE");
                    break;
                }
            }while(respClientes != 6);
            break;

        case 3:
            do{
                menuVendas();
                respVendas = lerOpcao();
                switch (respVendas){
                    case 1:
                        realizarvenda(&c, &p, &v);
                        break;
                    case 2:
                        saldoCaixa(&v);
                        break;
                    case 3:
                        vendasRealizadas(&v);
                        break;
                    case 4:
                        totalVendidos(&v);
                        break;
                    case 5:
                        break;
                    default:
                        printf("ERRO - Digite uma opcao valida! \n");
                        system("PAUSE");
                        break;
                }
            }while(respVendas != 5);
            break;
        case 4:
            printf("Finalizando o programa...\n");
            system("PAUSE");
            break;
        default:
            printf("ERRO - Digite uma opcao valida! \n");
            system("PAUSE");
            break;
        }

    }while(respMenu != 4);

    return 0;
}
