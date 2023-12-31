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

//Essa funçao cria um cliente
int novoCliente(ListaDeClientes *lc ) {
    //Se a quantidades de clientes for maior que 1000 , o programa impossibilita de criar mais usuarios
    if (lc->qtd >= 1000) {
        printf("Nao e possivel cadastrar mais clientes. Limite atingido.\n");
        return -1;
    }
    //Pede informaçoes cruciais para criar um cliente
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
//Essa funçao deleta um cliente
int deletarCliente(ListaDeClientes *lc){
    int opcao;
    printf("Qual cliente deseja deletar? ");
    scanf("%d", &opcao);
    //Se a opçao for um numero que nao existe nao dara para deletar o cliente
    if (opcao > lc->qtd) {
        printf("Numero invalido.\n");
        return 1;
    }
    //Cria um "for" para deletar o cliente ja criado na funçao "NovoCliente"
    for(int i = opcao - 1 ; i < lc->qtd -1 ; i++ ){
        lc->clientes[i] = lc->clientes[i+1];
    }

    lc->qtd--;

    printf("Cliente %d excluida com sucesso!\n", opcao);
    return 0;
};

//Lista todos os clientes existentes no programa
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

//Realiza o debito , fazendo com que tambem respeite as leis de conta comum e plus
int debito(ListaDeClientes *lc) {
    char cpf[12];
    int senha;
    float valor;
    char descricao[100];
    
    //Pede informaçoes para o cliente , para que essas sejam verificadas e que possa ocorrer o debito
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

    //Se existir esse cliente , ira ocorrer o debito
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

//Essa funçao realiza o deposito
int deposito(ListaDeClientes *lc) {
    char cpf[12];
    int senha;
    float valor;
    char descricao[100];

    //Pedindo as informaçoes necessarias para que ocorra o deposito
    printf("Digite o seu CPF: ");
    scanf("%s", cpf);

    printf("Digite a sua senha: ");
    scanf("%d", &senha);


    int clientee = 0;
    int clientenum = -1;

    //"For" para que ocorra o deposito corretamente
    for (int i = 0; i < lc->qtd; i++) {
        if (strcmp(lc->clientes[i].cpf, cpf) == 0 && lc->clientes[i].senha == senha) {
            clientee = 1;
            clientenum = i;
            break;
        }
    }

    //Verifica se existe esse cliente para que ocorra esse deposito
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

//Essa funçao realiza a transferencia entre contas ja existentes no programa
int transferencia(ListaDeClientes *lc) {
    char cpfreme[12];
    int senhareme;
    char cpfdesti[12];
    float valor;
    char descricao[100];

    //Aqui pedimos as informaçoes necesssarias para que possa ocorrer a transferencia
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

    //Verifica qual conta o cliente deseja transferir 
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
        //Verifica se o cliente foi encontrado , possibilitando , assim , a transferencia entre as contas
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

//Gera um extrato com as operaçoes realizadas pelo cliente
int extrato(ListaDeClientes lc) {
    char cpf[12];
    int senha;

    printf("Digite o seu CPF: ");
    scanf("%s", cpf);

    printf("Digite a sua senha: ");
    scanf("%d", &senha);

    int clientee = 0;
    int clientenum = -1;

    // Procurar o cliente com o CPF e senha correspondentes
    for (int i = 0; i < lc.qtd; i++) {
        if (strcmp(lc.clientes[i].cpf, cpf) == 0 && lc.clientes[i].senha == senha) {
            clientee = 1;
            clientenum = i;
            break;
        }
    }
    //Se existir cliente , cria um arquivo txt para escrever o extrato , com todas as operaçoes realizadas pelo usuario ja cadastrado
    if (clientee) {
        FILE *extrato = fopen("extrato.txt", "w");
        if (extrato == NULL) {
            printf("Erro ao gerar o extrato.\n");
            return 1;
        }

        fprintf(extrato, "Extrato do cliente: %s\n", lc.clientes[clientenum].nome);
        fprintf(extrato, "CPF: %s\n", lc.clientes[clientenum].cpf);
        fprintf(extrato, "Tipo de conta: %s\n", lc.clientes[clientenum].conta);
        fprintf(extrato, "Saldo atual: %.2f\n", lc.clientes[clientenum].valorinicial);

        for(int i = 0; i < lc.clientes[clientenum].qtde; i++){
            fprintf(extrato, "Descricao: %s\n", lc.clientes[clientenum].extratos[i].descricao);
            fprintf(extrato, "Valor: %d\n", lc.clientes[clientenum].extratos[i].valor);
            fprintf(extrato, "Operacao: %s\n", lc.clientes[clientenum].extratos[i].operacao);
        }

        // Fecha o arquivo de extrato
        fclose(extrato);

        printf("Extrato gerado com sucesso\n");
    } else {
        printf("Nao foi possivel gerar o extrato!\n");
    }

    return 0;
}

//Essa funçao salva os clientes
int salvarLista(ListaDeClientes lc, char nome[]){
    FILE *arquivo = fopen(nome, "wb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fwrite(&lc, sizeof(ListaDeClientes), 1, arquivo);
    fclose(arquivo);
    return 0;

}

//A funcao carrega os itens do arquivo e passa para a struct do programa
int carregarLista(ListaDeClientes *lc, char nome[]){
    FILE *arquivo = fopen(nome, "rb");
    //Se o arquivo nao existir , nao vai dar para abrir o arquivo
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fread(lc, sizeof(ListaDeClientes), 1, arquivo);
    fclose(arquivo);
    return 0;
};