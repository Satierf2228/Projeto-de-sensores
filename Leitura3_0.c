#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define maximo_registros 2000
#define num_sensores 5

typedef struct{
    long timestamp;
    char sensor[30];
    float valor;
}Registro;

typedef struct{
    char nome[10];
    Registro dados[maximo_registros];
    int count;
}sensor_data;

int comparar_timestamp(const void *a, const void *b){
    Registro *ra = (Registro *)a;
    Registro *rb = (Registro *)b;
    return(ra->timestamp > rb->timestamp) - (ra->timestamp < rb->timestamp);
}

void guardar_arquivos(const char *nome_arquivo, Registro *dados, int count){
    FILE *saida = fopen(nome_arquivo, "w");
    if (!saida){
        printf("Erro ao tentar criar o arquivo saida");
        return;
    }
    for (int i = 0; i<count; i++){
        fprintf(saida, "%ld %s %.2f\n", dados[i].timestamp, dados[i].sensor, dados[i].valor);
    }
    fclose(saida);
}

int main(int argc, char *argv[]){
    FILE *temp, *pres, *vibr, *umid, *flux;
    char sensor[20];
    long timestamp;
    float valor;

    if (argc != 2){
        printf("Uso correto: %s <arquivo_entrada\n", argv[0]);
        return 1;
    }


    FILE *entrada = fopen(argv[1], "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    sensor_data sensores[num_sensores] ={
    {"TEMP", {}, 0},
    {"PRES", {}, 0},
    {"VIBR", {}, 0},
    {"UMID", {}, 0},
    {"FLUX", {}, 0}
   
    };
       
    while (fscanf(entrada, "%ld %s %f", &timestamp, sensor, &valor) == 3) {
        for (int i = 0; i < num_sensores; i++) {
            if (strcmp(sensor, sensores[i].nome) == 0) {
                Registro *reg = &sensores[i].dados[sensores[i].count];
                reg->timestamp = timestamp;
                strcpy(reg->sensor, sensor);
                reg->valor = valor;
                sensores[i].count++;
                break;
            }
        }
    }
    
    fclose(entrada);
    
    for (int i = 0; i < num_sensores; i++)
    {
        qsort(sensores[i].dados, sensores[i].count, sizeof(Registro),comparar_timestamp);
        char nome_arquivo[30];
        snprintf(nome_arquivo, sizeof(nome_arquivo), "%s.txt", sensores[i].nome);

        guardar_arquivos(nome_arquivo, sensores[i].dados, sensores[i].count);
    }   

    printf("Organização concluída!\n");
    return 0; 
}