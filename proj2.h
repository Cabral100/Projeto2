#ifndef PROJETO_PROJ_H
#define PROJETO_PROJ_H

typedef struct{
    char descricao[100];
    int valor;
    char operacao[100];
}Extrato;

typedef struct{
    char nome[100];
    char cpf[12];
    char conta[5];
    float valorinicial;
    int senha;
    Extrato extratos[10];
    int qtde;
}Clientes;

typedef struct {
    Clientes clientes[10];
    int qtd;
}ListaDeClientes;

int novoCliente(ListaDeClientes *lc );
int deletarCliente(ListaDeClientes *lc);
int listarClientes(ListaDeClientes lc);
int debito(ListaDeClientes *lc);
int deposito(ListaDeClientes *lc);
int extrato(ListaDeClientes lc);
int transferencia(ListaDeClientes *lc);

int salvarLista(ListaDeClientes lc, char nome[]);
int carregarLista(ListaDeClientes *lc, char nome[]);


void printMenu();


#endif //PROJETO_PROJ_H
