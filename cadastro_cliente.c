#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define  MAX_NUM_CLIENTES 10

struct s_cliente
    {
        /* data */
        int codigo;
        char nome[40];
        char cpf[15];
        char telefone[10];
        float credito;
        float divida;
        char obs[100];
    };

/* Declarando vetor de clientes de forma global, bem como o n_clientes (inicia com 0) */
struct s_cliente clientes[MAX_NUM_CLIENTES];
int n_clientes = 0;


void ordemAlfabetica();
void ordemPorDivida();

/* Todos os clientes na ordem de inserção */
void listarClientes();
/* Clientes devedores */
void listarClientesDevedores();
/* Funcção para usuário escolher se lista todos os clientes ou se lista os clientes devedores */
void clientesDevedores();

/* Consultar cliente pelo nome ou pelo CPF */
void consultarClienteNomeCPF();

/* Funcção registrar dívida. Pede-se o código do cliente para poder alterar*/
void registrarDivida();

/* Excluir cliente pelo número do código */
void excluirCliente();

/* Consultar cliente pelo código */
void consultarCliente();
/* Consultar cliente cod e alterar campos escolhidos */
void alterarCliente();
/* Ler dados antes de cadastrar */
struct s_cliente lerDados();
/* Função cadastrar cliente */
void cadastrarCliente(struct s_cliente cliente); 
/* Função Menu */
int menu();

/* ====== MAIN ======== */
int main() {
    //Aceitando acentos
    setlocale(LC_ALL, "Portuguese");

    int opcao;
    struct s_cliente novo_cliente;
    do
    {
       opcao = menu();
        switch (opcao)
        {
            /* cadastrar */
            case 1: 
                if (n_clientes == MAX_NUM_CLIENTES){
                    printf("\nNumero maximo de clientes atingido!");
                    break;
                }
                novo_cliente = lerDados();
                cadastrarCliente(novo_cliente); 
                break;
            
            /* consultar cliente pelo cod */
            case 2: 
                consultarCliente(); 
                break;
            
            /* Alterar cliente - alterar  digitar novos dados para a ficha do cliente, com a opção de manter os dados anteriores 
               que não forem alterados */
            case 3: alterarCliente(); break;
            
            /* Excluir cliente pelo cód */
            case 4: excluirCliente(); break;
            /* Registrar Divida/Pagamento */
            case 5: registrarDivida(); break;
            /* Consultar cliente por nome ou CPF */
            case 6: consultarClienteNomeCPF(); break;
            /* Listagem de clientes com divida maior que 0 */
            case 7: clientesDevedores(); break;
            /* code */
            case 8: ordemAlfabetica(); break;
            /* code */
            case 9: ordemPorDivida(); break;
            /* code */
            default: printf("Saindo...\n"); break;
        }
    
    } while (opcao != 0);
    
    
    return 0;
}
/* ====== FIM MAIN ======== */

int menu(){
    int opt;

    fflush(stdin); // Retira o lixo do teclado
    printf("\n\n==== Menu ===");
    printf("\n(0) Sair");
    printf("\n(1) Cadastrar cliente");
    printf("\n(2) Consultar cliente");
    printf("\n(3) Alterar cliente");
    printf("\n(4) Excluir cliente");
    printf("\n(5) Registrar Divida/Pagamento");
    printf("\n(6) Pesquisar Cliente (Nome/CPF)");
    printf("\n(7) Listar Clientes/Devedores");
    printf("\n(8) Ordenar Clientes - Alfabetica");
    printf("\n(9) Ordenar Clientes - Divida");

    /* code */
    printf("\n> ");
    fflush(stdout);
    scanf("%d", &opt);

    return opt;
}
struct s_cliente lerDados() {
    struct s_cliente auxiliar;

    printf("\n\n");
    
    // Código do cliente
    printf("\nDigite o CODIGO do cliente: ");
    fflush(stdin);
    scanf("%d", &auxiliar.codigo);
    
    // Nome do cliente 
    printf("\nDigite o NOME do cliente: ");
    fflush(stdin);
    // fgets(auxiliar.nome, 40, stdin);
    scanf("%39s", auxiliar.nome);

    // CPF do cliente 
    printf("\nDigite o CPF do cliente: ");
    fflush(stdin);
    //fgets(auxiliar.cpf, 15, stdin);
    scanf("%14s", auxiliar.cpf);
    
    // Telefone do cliente
    printf("\nDigite o TELEFONE do cliente: ");
    fflush(stdin);
    //fgets(auxiliar.telefone, 10, stdin);
    scanf("%10s", auxiliar.telefone);
    
    // Credito do cliente 
    printf("\nDigite o CREDITO do cliente: ");
    fflush(stdin);
    scanf("%f", &auxiliar.credito);
    
    // Observacao para o cliente 
    printf("\nDigite uma OBSERVACAO para o cliente: ");
    fflush(stdin);
    //fgets(auxiliar.obs, 100, stdin);
    scanf("%99s", auxiliar.obs);
    auxiliar.divida = 0;
    return auxiliar;
}
void cadastrarCliente(struct s_cliente cliente){
    
    clientes[n_clientes] = cliente;
    n_clientes++;
    
}
void consultarCliente(){
    int cod;
    int encontrado = 0;
    printf("Digite o código do cliente a ser pesquisado: ");
    scanf("%d", &cod);
    for (size_t i = 0; i < n_clientes; i++)
    {
        if (cod == clientes[i].codigo){
            printf("\n\n==== Cliente encontrado ====");
            printf("\nCódigo: %d", clientes[i].codigo);
            printf("\nNome: %s", clientes[i].nome);
            printf("\nCPF: %s", clientes[i].cpf);
            printf("\nTelefone: %s", clientes[i].telefone);
            printf("\nCrédito: %.2f", clientes[i].credito);
            printf("\nObservação: %s", clientes[i].obs);
            encontrado = 1;
        }
    }
    if (encontrado == 0) printf("Cliente não encontrado!\n");    
}
void alterarCliente(){
    int cod, op;
    int encontrado = 0;
    printf("Digite o código do cliente a ser editado: ");
    fflush(stdin);
    scanf("%d", &cod);
    for (size_t i = 0; i < n_clientes; i++)
    {
        if (cod == clientes[i].codigo){
            // Código do cliente
            printf("\n\n====Cliente encontrado====");
            printf("\nDigite (1) para alterar cod, (0), caso não queira: ");
            fflush(stdin);
            scanf("%d", &op);
            if (op == 1){
                printf("\nDigite o novo CODIGO: ");
                fflush(stdin);
                scanf("%d", &clientes[i].codigo);
            }
            printf("\nDigite (1) para alterar nome, (0), caso não queira: ");
            fflush(stdin);
            scanf("%d", &op);
            if (op == 1){
                // Nome do cliente 
                printf("\nDigite o novo NOME do cliente: ");
                fflush(stdin);
                // fgets(auxiliar.nome, 40, stdin);
                scanf("%39s", clientes[i].nome);
            }

            printf("\nDigite (1) para alterar CPF, (0), caso não queira: ");
            fflush(stdin);
            scanf("%d", &op);
            if (op == 1){
                // CPF do cliente    
                printf("\nDigite o novo CPF: ");
                fflush(stdin);
                //fgets(auxiliar.cpf, 15, stdin);
                scanf("%14s", clientes[i].cpf);
            }
            printf("\nDigite (1) para alterar TELEFONE, (0), caso não queira: ");
            fflush(stdin);
            scanf("%d", &op);
            if (op == 1){
                // Telefone do cliente
                printf("\nDigite o novo TELEFONE: ");
                fflush(stdin);
                //fgets(auxiliar.telefone, 10, stdin);
                scanf("%10s", clientes[i].telefone);
            }            

            printf("\nDigite (1) para alterar CRÉDITO, (0), caso não queira: ");
            fflush(stdin);
            scanf("%d", &op);
            if (op == 1){
                // Credito do cliente 
                printf("\nDigite o novo CREDITO: ");
                fflush(stdin);
                scanf("%f", &clientes[i].credito);
            }    
            
            printf("\nDigite (1) para nova OBS.:, (0), caso não queira: ");
            fflush(stdin);
            scanf("%d", &op);
            if (op == 1){
                // Observacao para o cliente 
                printf("\nDigite uma nova OBSERVACAO: ");
                fflush(stdin);
                //fgets(auxiliar.obs, 100, stdin);
                scanf("%99s", clientes[i].obs);
            }
            encontrado = 1;

        }
    }
    if (encontrado == 0) printf("Cliente não encontrado!\n");  
}
void excluirCliente(){
    int cod, encontrado=0;
    printf("\nDigite o código do cliente a ser removido: ");
    scanf("%d", &cod);
    for (size_t i = 0; i < n_clientes; i++)
    {
        if (clientes[i].codigo == cod){
            /* Remove caso encontre. Levar elemento para última posição e decrementar o vetor */
            struct s_cliente aux;
            for (size_t x = i; x < n_clientes; x++){
                aux = clientes[x];
                clientes[x] = clientes[x+1];
                clientes[x+1] = aux;
            }
            n_clientes--;
            printf("\nCliente excluído com sucesso!");
            encontrado = 1;
        }
    }
    if (encontrado == 0) printf("\nCliente não encontrado!");
}
void registrarDivida(){
    int cod, div, encontrado=0;
    printf("\nDigite o código do cliente que deseja inserir dívida/pagamento: ");
    scanf("%d", &cod);
    for (size_t i = 0; i < n_clientes; i++){
        if (clientes[i].codigo == cod){
            printf("\nDigite o valor da dívida/pagamento: ");
            scanf("%d", &div);
            int soma = div + clientes[i].divida;
            /* Inserir dívida/pagamento apenas se for menor ou igual ao crédito */
            if (soma <= clientes[i].credito){
                clientes[i].divida = div + clientes[i].divida;
                clientes[i].credito = clientes[i].credito - clientes[i].divida;
                printf("\nDívida cadastrada com sucesso!!");
            }
            else{
                printf("\nValor inválido!!");
                printf("\nDívida atual: %.2f", clientes[i].divida);
                printf("\nCrédito do cliente: %.2f", clientes[i].credito);
                
            }
            encontrado = 1;
        }
    }
    if (encontrado == 0) printf("\nCódigo inválido");
}
void consultarClienteNomeCPF(){
    char resposta[40];
    int encontrado = 0;
    printf("\nDigite o nome ou CPF do cliente a ser consultado: ");
    scanf("%39s", resposta);
    printf("%s", resposta);
    for (size_t i = 0; i < n_clientes; i++)
    {
        if (strcmp(clientes[i].nome, resposta) == 0 || strcmp(clientes[i].cpf, resposta)==0){
            printf("\n\n==== Cliente encontrado ====");
            printf("\nCódigo: %d", clientes[i].codigo);
            printf("\nNome: %s", clientes[i].nome);
            printf("\nCPF: %s", clientes[i].cpf);
            printf("\nTelefone: %s", clientes[i].telefone);
            printf("\nCrédito: %.2f", clientes[i].credito);
            printf("\nObservação: %s", clientes[i].obs);
            encontrado = 1;
        }
    }
    if (encontrado == 0) printf("\nCliente não encontrado! Nome ou CPF inválido!");
    
}
void clientesDevedores(){
    int op;
    printf("\nDigite (1) para listar todos o clientes ou (0) para listar todos os devedores: ");
    fflush(stdin);
    scanf("%d", &op);
    switch (op)
    {
        case 1: // Listar todos os clientes na ordem natural
            listarClientes();        
            break;
        case 0:
            listarClientesDevedores();
            break;
        default:
            printf("\nOpção inválida!!");
            break;
    }
    
}
void listarClientes(){
    
    if (n_clientes > 0){
        for (int i = 0; i < n_clientes; i++)
        {
            printf("\n\nCliente número %d", i);
            printf("\nCódigo: %d", clientes[i].codigo);
            printf("\nNome: %s", clientes[i].nome);
            printf("\nCPF: %s", clientes[i].cpf);
            printf("\nTelefone: %s", clientes[i].telefone);
            printf("\nCrédito: %.2f", clientes[i].credito);
            printf("\nDívida: %.2f", clientes[i].divida);
            printf("\nObservação: %s", clientes[i].obs);
        }
    }
    else printf("\nLista de Clientes está vazia");
}        

void listarClientesDevedores(){
    int x = 0;
    for (size_t i = 0; i < n_clientes; i++)
    {
        if (clientes[i].divida > 0) {
            printf("\n\n");
            printf("\nCódigo: %d", clientes[i].codigo);
            printf("\nNome: %s", clientes[i].nome);
            printf("\nCPF: %s", clientes[i].cpf);
            printf("\nTelefone: %s", clientes[i].telefone);
            printf("\nCrédito: %.2f", clientes[i].credito);
            printf("\nObservação: %s", clientes[i].obs);
            x = x + 1;
        }
    }
    if (x == 0) printf("\nNão há devedores!");

}

void ordemAlfabetica(){
    struct s_cliente aux;
    for (size_t i = 0; i < n_clientes; i++)
    {
        for (size_t j = 0; j < n_clientes; j++)
        {
            if (strcmp(clientes[j].nome, clientes[i].nome) > 0) {
                aux = clientes[i];
                clientes[i] = clientes[j];
                clientes[j] = aux;
            }
        }
        
    }
    listarClientes();
}

void ordemPorDivida(){
    struct s_cliente aux;
    for (size_t i = 0; i < n_clientes; i++)
    {
        for (size_t j = 0; j < n_clientes; j++)
        {
            if (clientes[j].nome < clientes[i].nome) {
                aux = clientes[i];
                clientes[i] = clientes[j];
                clientes[j] = aux;
            }
        }
        
    }
    listarClientes();
}