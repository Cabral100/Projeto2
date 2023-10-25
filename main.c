#include <stdio.h>
#include "proj2.h"


int main() {
    int cod;
    ListaDeClientes lc;

    cod = carregarLista(&lc, "clientes");

    if (cod == 1){
        lc.qtd = 0;
    }

    int opcao;
    do{
        printMenu();
        scanf("%d", &opcao);

        if (opcao == 1){
            novoCliente(&lc);
        } else if (opcao == 2){
            deletarCliente(&lc);
        } else if (opcao == 3){
            listarClientes(lc);
        } else if (opcao == 4){
            debito(&lc);
        } else if (opcao == 5){
            deposito(&lc);
        } else if (opcao == 6){
            extrato(lc);
        } else if (opcao == 7){
            transferencia(&lc);
        }
    } while (opcao != 8);

    cod = salvarLista(lc, "clientes");

    if (cod != 0){
        printf("Erro ao salvar lista\n");
    }

}
