# Lab3: Threads

Nesse código utilizamos a função clone(), que de certa forma é parecida com a função fork(), porém permite maior controle sobre o ambiente da thread. Começamos por criar uma estrutura shared_data que contém uma variável de inteiro value. Antes de chamar a função clone(), o processo principal aloca memória para essa estrutura e a inicializa. O endereço dessa estrutura é passado como argumento para a função executada pelo processo filho. Dentro da função threadFunction, o processo filho modifica o valor de value. Depois que o processo filho termina, o processo pai lê e exibe o valor modificado, mostrando a comunicação entre os processos pai e filho.

# Código

![Texto Alternativo](https://github.com/Neto-Sciamarelli/SO/blob/main/Lab3/Imagem3.PNG)
