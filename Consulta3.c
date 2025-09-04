#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_REGISTROS 2000

typedef struct{
    long timestamp;
    char sensor;
    float valor;

}Registro;

int busca_binaria_decres(Registro *dados, int a, long resultado){
    int inicio = 0;
    int fim = a - 1;
    int meio;
    long menor_difer = 999999999;
    int melhor_indice = -1;


while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        long difer = labs(dados[meio].timestamp - resultado);

        if (difer < menor_difer) {
            menor_difer = difer;
            melhor_indice = meio;
        }

        if (dados[meio].timestamp > resultado) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
         return melhor_indice;
    }

}

int main(int argc, char *argv[]){
if (argc != 3){
    printf("Uso correto do: %s <nome_sensor> <timestamp>\n", argv[0]);
    return 1;
}

FILE *arquivo;
char *sensor = argv[1];
long timestamp_desejado =atol(argv[2]), timestamp_arquivo;
char nome_arquivo[50];
int menor_difer;

strcpy(sensor, argv[1]);

sprintf(nome_arquivo, "%s.txt",sensor);

arquivo = fopen(nome_arquivo, "r");
if(arquivo == NULL) {
printf("Erro: sensor nao encontrado\n",sensor);
return 1;
}

Registro dados[MAX_REGISTROS];
int count = 0;

while (count < MAX_REGISTROS && fscanf(arquivo, "%ld %s %f", &dados[count].timestamp, dados[count].sensor, &dados[count].valor)==3){
count++;
}

fclose(arquivo);

if (count ==0){
    printf("Arquivo vazio ou formato não válido.\n");
    return 1;
}

int indice = busca_binaria_decres(dados, count, timestamp_desejado);
Registro *resultado = &dados[indice];

if (menor_difer == -1){
    printf("Leitura nao encontrada no arquivo\n");
} else{
    printf("Leitura mais próxima:\n");
printf("Timestamp: %ld\n",dados[indice].timestamp);
printf("Valor %.2f:\n", dados[indice].valor);
printf("Sensor: %s\n", dados[indice].sensor);
}

return 0;

}