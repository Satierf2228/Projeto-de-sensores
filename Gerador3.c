#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

time_t converter_para_timestap(int dia, int mes, int ano, int hora, int min, int seg) 
{
    struct tm t;

    t.tm_year = ano - 1900;
    t.tm_mon = mes - 1;
    t.tm_mday = dia;
    t.tm_hour = hora;
    t.tm_min = min;
    t.tm_sec = seg;
    t.tm_isdst = -1;

    time_t timestamp = mktime(&t);
    if (timestamp == -1) {
        printf("Data inválida. Tente novamente.\n");
    } else {
        return timestamp;
    }
}

time_t gerar_timestamp_aleatorio(time_t inicio, time_t fim) {
    if (fim <= inicio) return inicio;
    return inicio + rand() % (fim - inicio + 1);
}

void gerar_valor(const char *tipo, char *buffer_valor, size_t size) {
    if (strcmp(tipo, "CONJ_Z") == 0) {
        int val = rand() % 1000;
        snprintf(buffer_valor, size, "%d", val);
    } else if (strcmp(tipo, "CONJ_Q") == 0) {
        float val = ((float)(rand() % 10000)) / 100.0f;
        snprintf(buffer_valor, size, "%.2f", val);
    } else if (strcmp(tipo, "BINARIO") == 0) {
        int val = rand() % 2;
        snprintf(buffer_valor, size, "%s", val ? "true" : "false");
    } else if (strcmp(tipo, "TEXTO") == 0) {

        int val = rand() % 2;
        snprintf(buffer_valor, size, "%s", val ? "ON" : "OFF");
    } else {
        snprintf(buffer_valor, size, "0"); 
    }
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Uso: %s <data_inicio> <data_fim> <sensores> <tipos>\n", argv[0]);
        printf("Exemplo: %s \"2025-06-01 00:00:00\" \"2025-06-02 23:59:59\" TEMP,PRES,VIBR INT,FLOAT,BOOL\n", argv[0]);
        return 1;
    }

    time_t inicio = converter_para_timestamp(argv[1]);
    time_t fim = converter_para_timestamp(argv[2]);
    if (inicio == -1 || fim == -1) return 1;

    char sensores[100][50];
    char tipos[100][20];
    int total_sensores = 0;

    char *token;
    char sensores_str[1000], tipos_str[1000];
    strncpy(sensores_str, argv[3], sizeof(sensores_str)-1);
    strncpy(tipos_str, argv[4], sizeof(tipos_str)-1);

    token = strtok(sensores_str, ",");
    while (token != NULL) {
        strncpy(sensores[total_sensores], token, sizeof(sensores[0])-1);
        token = strtok(NULL, ",");
        total_sensores++;
    }

    int total_tipos = 0;
    token = strtok(tipos_str, ",");
    while (token != NULL) {
        strncpy(tipos[total_tipos], token, sizeof(tipos[0])-1);
        token = strtok(NULL, ",");
        total_tipos++;
    }

    if (total_sensores != total_tipos) {
        printf("Erro: Quantidade de sensores e tipos diferente.\n");
        return 1;
    }

    srand(time(NULL));

    for (int i = 0; i < total_sensores; i++) {
        char nome_arquivo[100];
        snprintf(nome_arquivo, sizeof(nome_arquivo), "%s.txt", sensores[i]);

        FILE *f = fopen(nome_arquivo, "w");
        if (!f) {
            printf("Erro ao abrir arquivo %s\n", nome_arquivo);
            continue;
        }

        for (int j = 0; j < 2000; j++) {
            time_t ts = gerar_timestamp_aleatorio(inicio, fim);
            char valor[50];
            gerar_valor(tipos[i], valor, sizeof(valor));
            fprintf(f, "%ld %s %s\n", ts, sensores[i], valor);
        }
        fclose(f);
        printf("Arquivo %s gerado com sucesso.\n", nome_arquivo);
    }

    return 0;
}
