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

int debito(ListaDeClientes *lc) {
    char cpf[12];
    int senha;
    float valor;
    char descricao[100];

    printf("Digite o seu CPF: ");
    scanf("%s", cpf);

    printf("Digite a sua senha: ");
    scanf("%d", &senha);

    int clientee = 0;
    int clientenum = -1;

    // Procurar o cliente com o CPF e senha correspondentes
    for (int i = 0; i < lc->qtd; i++) {
        if (strcmp(lc->clientes[i].cpf, cpf) == 0 && lc->clientes[i].senha == senha) {
            clientee = 1;
            clientenum = i;
            break;
        }
    }

    if (clientee) {
        printf("Digite o valor a ser debitado: ");
        scanf("%f", &valor);

        printf("Qual o motivo da operacao? ");
        scanf("%s", descricao);

        // Verificar o tipo de conta e aplicar as regras de débito
        if (strcmp(lc->clientes[clientenum].conta, "comum" ) == 0) {
            // Conta comum
            float limneg = -1000.0;
            if (lc->clientes[clientenum].valorinicial - valor >= limneg) {
                lc->clientes[clientenum].valorinicial -= valor * 1.05; // Cobrança da taxa (5%)
                printf("Debito realizado com sucesso , o seu saldo atualizado eh: %.2f\n", lc->clientes[clientenum].valorinicial);
                lc->clientes[clientenum].extratos[lc->clientes[clientenum].qtde].valor = valor * 1.05;
                strcpy(lc->clientes[clientenum].extratos[lc->clientes[clientenum].qtde].operacao, "Debito");
                strcpy(lc->clientes[clientenum].extratos[lc->clientes[clientenum].qtde].descricao, descricao);
                lc->clientes[clientenum].qtde += 1;
            } else {
                printf("Saldo insuficiente para realizar o debito.\n");
            }
        } else if (strcmp(lc->clientes[clientenum].conta, "plus") == 0) {
            // Conta plus
            float limneg = -5000.0;
            if (lc->clientes[clientenum].valorinicial - valor >= limneg) {
                lc->clientes[clientenum].valorinicial -= valor * 1.03; // Cobrança da taxa (3%)
                printf("Debito realizado com sucesso , o seu saldo atualizado eh: %.2f\n", lc->clientes[clientenum].valorinicial);
                lc->clientes[clientenum].extratos[lc->clientes[clientenum].qtde].valor = valor * 1.03;
                strcpy(lc->clientes[clientenum].extratos[lc->clientes[clientenum].qtde].operacao, "Debito");
                strcpy(lc->clientes[clientenum].extratos[lc->clientes[clientenum].qtde].descricao, descricao);
                lc->clientes[clientenum].qtde += 1;
            } else {
                printf("Saldo insuficiente para efetuar o debito.\n");
            }
        } else {
            printf("Tipo de conta invalido.\n");
        }
    } else {
        printf("Algo deu errado , portanto , nao foi possivel realizar o debito!\n");
    }


    return 0;
}

int deposito(ListaDeClientes *lc) {
    char cpf[12];
    int senha;
    float valor;
    char descricao[100];

    printf("Digite o seu CPF: ");
    scanf("%s", cpf);

    printf("Digite a sua senha: ");
    scanf("%d", &senha);


    int clientee = 0;
    int clientenum = -1;

    for (int i = 0; i < lc->qtd; i++) {
        if (strcmp(lc->clientes[i].cpf, cpf) == 0 && lc->clientes[i].senha == senha) {
            clientee = 1;
            clientenum = i;
            break;
        }
    }

    if (clientee) {
        printf("Cliente encontrado , o seu saldo atual eh de %.2f\n", lc->clientes[ clientenum].valorinicial);
        printf("Digite o valor a ser depositado: ");
        scanf("%f", &valor);
        printf("Qual o motivo da operacao? ");
        scanf("%s", &descricao);

        lc->clientes[clientenum].valorinicial += valor;
        printf("Deposito realizado com sucesso , o seu saldo atualizado eh: %.2f\n", lc->clientes[ clientenum].valorinicial);
        lc->clientes[clientenum].extratos[lc->clientes[clientenum].qtde].valor = valor;
        strcpy(lc->clientes[clientenum].extratos[lc->clientes[clientenum].qtde].operacao, "Deposito");
        strcpy(lc->clientes[clientenum].extratos[lc->clientes[clientenum].qtde].descricao, descricao);
        lc->clientes[clientenum].qtde += 1;
    } else {
        printf("Algo deu errado , portanto , nao foi possivel realizar o debito!\n");
    }

    return 0;
}

int transferencia(ListaDeClientes *lc) {
    char cpfreme[12];
    int senhareme;
    char cpfdesti[12];
    float valor;
    char descricao[100];

    printf("Digite o seu CPF : ");
    scanf("%s", cpfreme);

    printf("Digite a sua senha : ");
    scanf("%d", &senhareme);

    int clienteremee = 0;
    int  clienteremenum= -1;


    for (int i = 0; i < lc->qtd; i++) {
        if (strcmp(lc->clientes[i].cpf, cpfreme) == 0 && lc->clientes[i].senha == senhareme) {
            clienteremee = 1;
            clienteremenum = i;
            break;
        }
    }

    if (clienteremee) {
        printf("Digite o CPF da conta que voce quer  transferir: ");
        scanf("%s", cpfdesti);

        int  clientedestinae= 0;
        int clientedestinanum = -1;


        for (int i = 0; i < lc->qtd; i++) {
            if (strcmp(lc->clientes[i].cpf, cpfdesti) == 0) {
                clientedestinae = 1;
                clientedestinanum = i;
                break;
            }
        }

        if (clientedestinae) {
            printf("Cliente destinatario encontrado , o seu saldo eh de %.2f\n", lc->clientes[clientedestinanum].valorinicial);
            printf("Digite o valor para a transferencia: ");
            scanf("%f", &valor);
            printf("Qual o motivo da operacao? ");
            scanf("%s", &descricao);

            if (lc->clientes[clienteremenum].valorinicial >= valor) {
                lc->clientes[clienteremenum].valorinicial -= valor;
                lc->clientes[clientedestinanum].valorinicial += valor;
                printf("Transferencia realizada com sucesso!\n");
                printf("O seu saldo atual eh %.2f\n", lc->clientes[clienteremenum].valorinicial);
                printf("O saldo atual do destinatario eh %.2f\n", lc->clientes[clientedestinanum].valorinicial);
                lc->clientes[clienteremenum].extratos[lc->clientes[clienteremenum].qtde].valor = valor;
                strcpy(lc->clientes[clienteremenum].extratos[lc->clientes[clienteremenum].qtde].operacao, "Transferencia");
                strcpy(lc->clientes[clienteremenum].extratos[lc->clientes[clienteremenum].qtde].descricao, descricao);
                lc->clientes[clienteremenum].qtde += 1;
            } else {
                printf("Saldo insuficiente.\n");
            }
        } else {
            printf("CPF do destinatario nao foi encontrado.\n");
        }
    } else {
        printf("Algo deu errado , portanto ,transferencia cancelada!\n");
    }

    return 0;
}