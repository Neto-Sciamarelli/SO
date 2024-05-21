# Projeto 02

- Transferência Bancária

# Código

- Primeiro entramos na AWS academy, e realizamos o passo a passo proposto pelo professor que consta no moodle. Após realizar todo esse processo, instalamos o git, o vim e o gcc na máquina criada, e depois criamos a chave ssh e a colocamos no github. Diante disso clonamos o repositório do github, abrimos o repositório no terminal e por fim compilamos e executamos o arquivo.c utilizando os seguintes comandos: gcc nome_do_arquivo.c -o nome_do_executavel (para compilar) ./nome_do_executavel (para executar). Após esse processo, é mostrado na tela as 100 transferências realizadas, mostrando o saldo das duas contas a cada transferência.
- O código apresetado na documentação do projeto usa clone para criar threads sem sincronização, o que pode causar problemas de concorrência, enquanto o código realizado utiliza pthread_create para criar threads e emprega mutexes para proteger seções críticas, garantindo sincronização adequada. O segundo código também possui duas funções de transferência distintas, trata saldos insuficientes com mensagens de erro, e usa pthread_join para esperar a conclusão de todas as threads antes de liberar recursos, tornando-o mais seguro e robusto.

# 1. A conta to pode receber mais de uma transferência simultânea;

-Aqui vemos a conta to recebendo 5 transferências ao mesmo tempo.

![Texto Alternativo](https://github.com/Neto-Sciamarelli/SO/blob/main/Projeto2/teste1.png)

# 2. A conta from pode enviar mais de uma transferência simultânea;

-Da mesma forma que antes, a conta from enviando 5 transferências ao mesmo tempo.

![Texto Alternativo](https://github.com/Neto-Sciamarelli/SO/blob/main/Projeto2/teste2.png)

# 3. A conta from não pode enviar dinheiro se não tiver mais saldo;

-Aqui vemos que não ocorre nada quando o saldo da conta from é insuficiente, apenas uma mensagem é mostrada na tela.

![Texto Alternativo](https://github.com/Neto-Sciamarelli/SO/blob/main/Projeto2/teste3.png)

# 4. A conta to pode trocar de ordem com a conta from, ou seja, a conta que enviava pode receber e a conta que recebia pode enviar;

-Aqui podemos ver as duas contas realizando transferências.

![Texto Alternativo](https://github.com/Neto-Sciamarelli/SO/blob/main/Projeto2/teste4.png)

# 5. Poderão ser realizadas até 100 transações simultâneas de transferência.
   
-Aqui vemos 100 transações sendo realizadas.

![Texto Alternativo](https://github.com/Neto-Sciamarelli/SO/blob/main/Projeto2/Print1.png)
![Texto Alternativo](https://github.com/Neto-Sciamarelli/SO/blob/main/Projeto2/Print2.png)
![Texto Alternativo](https://github.com/Neto-Sciamarelli/SO/blob/main/Projeto2/Print3.png)
![Texto Alternativo](https://github.com/Neto-Sciamarelli/SO/blob/main/Projeto2/Print4.png)
![Texto Alternativo](https://github.com/Neto-Sciamarelli/SO/blob/main/Projeto2/Print5.png)
![Texto Alternativo](https://github.com/Neto-Sciamarelli/SO/blob/main/Projeto2/Print6.png)
