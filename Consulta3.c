#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]){
if (argc != 8){
    printf("Uso correto do: %s <nome_sensor> <timestamp>\n", argv[0]);
    return 1;
}

FILE *arquivo;
char *sensores = argv[1];
long timestamp_desejado =atol(argv[2]), timestamp_arquivo;
char sensor[20];
char id_sensor[20];
char nome_arquivo[50];
float valor;

printf("Digite o nome do sensor(EX:TEMP, PRES, VIBR, UMID ou FLUX): ");
scanf("%s", sensor);

printf("Digite o timestamp desejado: ");
scanf("%ld", &timestamp_desejado);

sprintf(nome_arquivo, "%s.txt",sensor);

arquivo = fopen(nome_arquivo, "r");
if(arquivo == NULL) {
printf("Erro: sensor nao encontrado\n");
return 1;
}

long menor_diferencas= 1000000000;
long melhor_timestamp = 0;
long melhor_valor = 0.0;

while(fscanf(arquivo, "%ld %s %f", &timestamp_arquivo,id_sensor, &valor)==3){
long diferenca = labs(timestamp_arquivo -timestamp_desejado);
if(diferenca < menor_diferencas ){
menor_diferencas = diferenca;
melhor_timestamp = timestamp_arquivo;
melhor_valor= valor;
}
}
fclose(arquivo);

printf("Leitura mais próxima:\n");
printf("Melhor timestamp: %ld\n",melhor_timestamp);
printf("Melhor valor %.2f:\n", melhor_valor);

return 0;

}