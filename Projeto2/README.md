# Projeto 02

- Transferência Bancária

# Código

- Primeiro entramos na AWS academy, e realizamos o passo a passo proposto pelo professor que consta no moodle. Após realizar todo esse processo, instalamos o git, o vim e o gcc na máquina criada, e depois criamos a chave ssh e a colocamos no github. Diante disso clonamos o repositório do github, abrimos o repositório no terminal e por fim compilamos e executamos o arquivo.c utilizando os seguintes comandos: gcc nome_do_arquivo.c -o nome_do_executavel (para compilar) ./nome_do_executavel (para executar). Após esse processo, é mostrado na tela as 100 transferências realizadas, mostrando o saldo das duas contas a cada transferência.
- No teste apresentado as duas contas apresentam o mesmo saldo que começaram, isso devido ao fato de estarmos realizando o mesmo número de transferências entre elas com o mesmo valor, 50 de cada lado com o valor de 10. O único caso em que o saldo poderia estar diferente é se uma das contas ficasse com o saldo 0 e logo em seguida uma transferência tentasse acessar esse saldo, assim não realizando nenhuma mudança nas contas e alterando o saldo final de ambas.

