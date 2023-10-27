# Banco QuemPoupaTem

O projeto Banco QuemPoupaTem foi desenvolvido por alunos do curso de Ciencia da Computacao do Centro Universitario FEI, na disciplina de Desenvolvimento de Algoritimos. Guiado pelo professor Leonardo Anjoletto Ferreira, tem como intuito a criacao de um sistema bancario para controle de clientes.

## Sistema do banco

O sistema do banco possui dois tipos de contas:
* comum
Permite um saldo negativo de ate R$1000, e cobra uma taxa de 5% a cada debito realizado.
* plus,
Permite um saldo negativo de ate R$5000 e cobra uma taxa de 3% a cada debito realizado.
No sistema e possível armazenar ate 1000 clientes e as informacoes das ultimas 100 operacoes realizadas pelo cliente.

## Funcionalidades
* Adicionar novos clientes
* Remover clientes do sistema
* Listar todos os clientes cadastrados
* Debitos
* Depositos
* Transferencias
* Verificar extrato de cada cliente cadastrado, mostrado as ultimas operacoes realizadas e as tarifas impostas

## Informacoes
Todo o projeto foi desenvolvido utilizando a linguagem C.
Os dados dos clientes sao armazenados em arquivo binario, e as informacoes do extrato sao salvas em um arquivo .txt.
