# Projeto 01

- Escada Rolante

# Código

![Texto Alternativo](https://github.com/Neto-Sciamarelli/SO/blob/main/Projeto1/Testes.PNG)

# Perguntas

# Questão 01
01) Qual a estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?

R: Utilizando threads, temos um variável global que armazena a direção que a escada está, seja -1 para quando está parada, e 1 e 0 nas direções que a escada anda. Com essa variável fazemos a verificação toda fez que a pessoa chega na escada para ver se está na mesma direção ou parada, assim evitando que duas pessoas com direções diferente entrem na escada.

Utilizando processos criamos um pipe para a comunicação entre eles, e nessa comunicação é feita a verificação e a alteração da variável que guarda a direção da escada, assim como em trheads evitando que duas pessoas entrem na escada em direções opostas.

# Questão 02
02) Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?

R: Em threads por se tratar de uma variável global, ela sempre assumirá apenas um valor, ou seja, apenas uma direção por vez. Já em processoas é semelhantes, como a direção é apenas uma variável, no espaço de comunicação entre os processos ela também só assumirá apenas uma direção.

# Questão 03
03) Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta.

R: Como threads utilizam o mesmo espaço de memória, é possível utilizar variáveis globais entre elas para fazer o controle da escada rolante, enquanto que em processos, eles não utilizam o mesmo espaço, então temos que "criar um", no caso um pipe, para a comunicação entre eles, e assim fazer o controle da escada.

Como dito anteriormente, por compartilharem o mesmo espaço de memória acredito que threads seja o mais eficiente, pois só temos a variável global para fazer o controle, assim facilitando o sincronismo, enquanto que em processos precisamos criar um pipe, ou seja criar um espaço compartilhado para a comunicação entre os processos, o que acredito que de certa forma não é tão eficiente do que o espaço de memória compartilhado das threads.
