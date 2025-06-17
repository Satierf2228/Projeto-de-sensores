# Projeto de sensores
 Programa 1 = Leitura3_0

Objetivo: O primeiro programa deve processar um arquivo contendo diversas leituras no seguinte formato:

<TIMESTAMP> <ID_SENSOR> <VALOR>

Onde os campos representam;

<TIMESTAMP> data e hora da medida no formato unix epoch.
<ID_SENSOR> string sem espaço que representa cada sensor
<VALOR> Valor informado do sensor.
Cada sensor informa sempre o mesmo tipo de dado.
Sensores diferentes podem informar valores de tipos diferentes.
O programa deve suportar pelo menos 4 tipos de dados diferentes:

Números inteiros
Booleano (true ou false)
Número racional
String (código de até 16 letras)
Essas leituras referem-se a diferentes sensores, que aparecem misturados ao longo do arquivo.

Esse programa deverá:

Tratar o arquivo indicado como argumento da linha de comando de execução do programa.
Identificar os diferentes sensores presentes, dentro de uma lista de finita de tipos surportatos.

Separar os dados em arquivos distintos para cada sensor.

Em cada arquivo, ordenar as leituras por timestamp (data e hora representada em unix epoch) em ordem decrescente.

Programa 2 - Consulta3

O segundo programa deve pesquisar a medida de um sensor especifico mais próxima de uma data e hora informada.

Esse programa deve receber da linha de comanda:

O nome de um sensor;

Uma data e hora da medida consultada;

O programa deve então localizar, usando busca binária, a leitura registrada com timestamp (data e hora representada em unix epoch)  mais próximo daquele instante no arquivo correspondente ao sensor, e exibir as informações da leitura.

OBS:
A busca binária é obrigatória para garantir desempenho adequado em grandes volumes de dados.
E buscar arquivo ordenado em ordem decrescente.

Programa 3 - Gerador3

Crie um programa adicional que gere um arquivo de teste com as seguintes características:

O programa deve receber como argumento da linha de comando:

data e hora de início do intervalo de amostras geradas aleatoriamente.

data e hora de fim do intervalo de amostras  geradas aleatoriamente.

nome dos sensores.

tipo do dado da amostra informada por cada tipo de sensor.
Para cada sensor, o programa deve criar 2000 leituras aleatórias com valores numéricos aleatórios e timestamps sorteados dentro da data fornecida pelo usuário.

Os dados indicado na linha de execução seja:

CONJ_Z:  para dados tipo inteiro.
CONJ_Q: para dados do tipo float.
TEXTO para dados do tipo string.
BINARIO: para dados do tipo booleano.

O arquivo gerado deve seguir o formato: <TIMESTAMP> <ID_SENSOR> <VALOR>

<TIMESTAMP> data e hora da medida no formato unix epoch.
<ID_SENSOR> string sem espaço que representa cada sensor
<VALOR> Valor aleatório da amostra de acordo com o tipo indicado para o sensor.
