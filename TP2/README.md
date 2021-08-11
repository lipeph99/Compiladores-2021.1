Compiladores 2021/01 TP2
Philippe Santos Silva
Marcos Vinicius de Carvalho Ribeiro

#O Trabalho
O objetivo do TP2 é criar um ligador para uma máquina que foi previamente projetada.
Esse ligador usa o montador criado no TP1 para gerar os arquivos iniciais e depois realizer a ligação.
O programa recebe como entrada uma série de arquivos a serem ligados e retorna como saída um arquivo ex.mv que roda no emulador.

#O TP1
A implementação usada no TP1 não ficou bem feita por falta de tempo, por isso ela foi inteiramente refeita.
A nova implementação do TP1 resolve os erros que aconteciam na versão inicial e permite que o TP2 seja muito mais bem feito.


#Implementação
O trabalho foi implementado em c++ e só foram usadas bibliotecas de input/output e de arquivos.
O desenvolvimento e os testes foram feitos em dupla.
Não houveram grandes problemas durante o processo.

#Detalhes
Os arquivos gerados pelo montador mantém a tabela de símbolos para serem ligados.
Os símbolos que foram usados e já estavam no mesmo arquivo já são substítuidos no próprio montador.
Depois da leitura completa as lacunas são preenchidas de acordo com as posições corretas.
Caso algum símbolo seja usado e não definido ele dispara um runtime_error e não gera o arquivo de saída.
Nenhum outro detalhe foge muito da ideia básica de ler os comandos, os operadores necessários e preencher os labels.

#Testes
Para testar o código foram usados 3 códigos
O programa que soma 100 na entrada dado na documentação.
A segunda parte do soma 100 que também é dada na documentação.
Um fibonacci que lê um numero da entrada e imprime o fibonacci desejado
Todos os testes estão disponíveis na pasta tst

#Execução
O TP1 havia sido entregue fora do formato, o TP2 está no formato correto e pode ser executado com um make.
O programa lê os arquivos passados por parâmetro na pasta tst e gera os arquivos na pasta tst.
Ao fim é gerado um arquivo ex.mv, também na pasta tst.