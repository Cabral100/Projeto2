#include <stdio.h>
#include "proj2.h"
#include "string.h"
//A funcao apenas printa as opcoes disponiveis
void printMenu(){
    printf("1 - Novo Cliente\n");
    printf("2 - Deletar Cliente\n");
    printf("3 - Listar Clientes\n");
    printf("4 - Debito\n");
    printf("5 - Deposito\n");
    printf("6 - Extrato\n");
    printf("7 - Transferencia entre contas\n");
    printf("8 - Sair\n");
    printf("Digite a opcao que voce quer executar: ");
};

int novoCliente(ListaDeClientes *lc ) {
    if (lc->qtd >= 1000) {
        printf("Nao e possivel cadastrar mais clientes. Limite atingido.\n");
        return -1;
    }

    printf("Nome: ");
    scanf(" %s", lc->clientes[lc->qtd].nome);

    printf("CPF: ");
    scanf(" %s", lc->clientes[lc->qtd].cpf);

    printf("Tipo de conta (comum ou plus): ");
    scanf(" %s", &lc->clientes[lc->qtd].conta);

    printf("Digite o valor inicial: ");
    scanf(" %f", &lc->clientes[lc->qtd].valorinicial);

    printf("Senha: ");
    scanf(" %d", &lc->clientes[lc->qtd].senha);

    printf("\n");

    lc->qtd += 1;

    return 0;
}

int deletarCliente(ListaDeClientes *lc){
    int opcao;
    printf("Qual cliente deseja deletar? ");
    scanf("%d", &opcao);
    if (opcao > lc->qtd) {
        printf("Numero invalido.\n");
        return 1;
    }

    for(int i = opcao - 1 ; i < lc->qtd -1 ; i++ ){
        lc->clientes[i] = lc->clientes[i+1];
    }

    lc->qtd--;

    printf("Cliente %d excluida com sucesso!\n", opcao);
    return 0;
};

int listarClientes(ListaDeClientes lc){
    for (int i = 0; i < lc.qtd; i++){
        printf("Cliente %d:\n", i + 1);
        printf("Nome: %s\n", lc.clientes[i].nome);
        printf("CPF: %s\n", lc.clientes[i].cpf);
        printf("Tipo de conta (comum ou plus): %s\n" , lc.clientes[i].conta);
        printf("Saldo: %f\n" , lc.clientes[i].valorinicial);
        printf("\n");
    }
    return 0;
}