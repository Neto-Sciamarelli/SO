# Projeto 02

- Transferência Bancária

# Código

- Primeiro entramos na AWS academy, e realizamos o passo a passo proposto pelo professor que consta no moodle. Após realizar todo esse processo, instalamos o git, o vim e o gcc na máquina criada, e depois criamos a chave ssh e a colocamos no github. Diante disso clonamos o repositório do github, abrimos o repositório no terminal e por fim compilamos e executamos o arquivo.c utilizando os seguintes comandos: gcc nome_do_arquivo.c -o nome_do_executavel (para compilar) ./nome_do_executavel (para executar). Após esse processo, é mostrado na tela as 100 transferências realizadas, mostrando o saldo das duas contas a cada transferência.
- No teste apresentado as duas contas ficam com saldos diferentes, pois mesmo tendo o mesmo número de tranferencias uma com a outra, o valor é diferente, a conta from mando 20 para a conta to, e a to manda 10 para a from. Além de que sempre que não há salfo insuficiente, há uma mensagem na tela e a thread não faz nenhuma mudança no saldo de nenhuma das contas.
- Para realizar mais teste seria bem simples, poderiamos apenas mudar os valores das tranferencias, o que já resultaria em saldos diferentes dos apresentados, porém podemos também mudar o número de tranferencias realizadas, apenas mudando o for que cria as threads, resultando em saídas diferentes.
- O código apresetado na documentação do projeto usa clone para criar threads sem sincronização, o que pode causar problemas de concorrência, enquanto o código realizado utiliza pthread_create para criar threads e emprega mutexes para proteger seções críticas, garantindo sincronização adequada. O segundo código também possui duas funções de transferência distintas, trata saldos insuficientes com mensagens de erro, e usa pthread_join para esperar a conclusão de todas as threads antes de liberar recursos, tornando-o mais seguro e robusto.

# Teste

![Texto Alternativo](https://github.com/Neto-Sciamarelli/SO/blob/main/Projeto2/Print1.png)
![Texto Alternativo](https://github.com/Neto-Sciamarelli/SO/blob/main/Projeto2/Print2.png)
![Texto Alternativo](https://github.com/Neto-Sciamarelli/SO/blob/main/Projeto2/Print3.png)
![Texto Alternativo](https://github.com/Neto-Sciamarelli/SO/blob/main/Projeto2/Print4.png)
![Texto Alternativo](https://github.com/Neto-Sciamarelli/SO/blob/main/Projeto2/Print5.png)
![Texto Alternativo](https://github.com/Neto-Sciamarelli/SO/blob/main/Projeto2/Print6.png)
