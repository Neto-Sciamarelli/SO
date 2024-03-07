# Lab2: Processos

# Perguntas

01) Você é capaz de identificar os trechos executados por pai e filho?
   
R: Sim, o controle sobre a execução de cada trecho é feita atrvés do valor em pid, sendo 0 para o trecho que será executado pelo filho, e 1 para o trecho que será executado pelo pai, que por sua vez espera pelo filho para realizar seu trecho. Há também o caso de erro, que ocorre quando pid tem valor menor que zero.

2) Quantos processos serão criados?
   
R: Sabemos que p número total de processos criados a partir de fork() é 2^n, onde n é o número de forks executados. Então no caso apresentado teremos 2^3 assim tendo 8 processos executados;

# Código 
