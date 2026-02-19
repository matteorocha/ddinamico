#include <stdio.h>
#include <stdlib.h>
#include "dd.h"

union u_medida {
    int luminosidade;
    int umidade;
    int movimento;
    double temperatura;
};

typedef struct medida_sensor {
    int tipo;
    union u_medida medida;
    int hora, min, seg;
} t_medida_sensor;

t_medida_sensor* criar_medida_sensor(int tipo, union u_medida medida, int hora, int min, int seg) {
    t_medida_sensor *novo = malloc(sizeof(t_medida_sensor));
    novo->tipo = tipo;
    novo->hora = hora;
    novo->min = min;
    novo->seg = seg;
    
    if (tipo == 3) {
        novo->medida.luminosidade = medida.luminosidade;
    } else if (tipo == 2) {
        novo->medida.movimento = medida.movimento;
    } else if (tipo == 1) {
        novo->medida.temperatura = medida.temperatura;
    } else {
        novo->medida.umidade = medida.umidade;
    }

    return novo;
}

void mostrar_medida_sensor(t_medida_sensor *m) {
    printf("%d ", m->tipo);
    if (m->tipo == 1) {
        printf("%.3lf", m->medida.temperatura);
    } else if (m->tipo == 3) {
        printf("%d", m->medida.luminosidade);
    } else if (m->tipo == 2) {
        printf("%d", m->medida.movimento);
    } else {
        printf("%d", m->medida.umidade);
    }
    printf(" %02d:%02d:%02d\n", m->hora, m->min, m->seg);
}

// Otimização: matemática inteira no lugar de pow() evita perda de precisão
long int criar_chave(int tipo, int hora, int min, int seg) {
    return tipo * 1000000 + hora * 10000 + min * 100 + seg;
}

int main() {
    int sensor, hora, min, seg;
    union u_medida medida;
    
    // Tabela criada com M=5 para forçar colisões de propósito no dataset maior
    t_dd* medidas = criar_dd(5, 2); 
    int total_operacoes = 0;

    // Leitura Dinâmica: o loop agora roda até o fim do arquivo (EOF)
    while (scanf("%d", &sensor) == 1) {
        
        
        // ele interrompe o processo para não poluir a sua estrutura de dados e evita o loop infinito.
        if (sensor < 1 || sensor > 4) {
            printf("\n[ERRO FATAL] Dado corrompido encontrado (Sensor lido: %d). Abortando leitura.\n", sensor);
            break; 
        }

        if (sensor == 1) {
            scanf("%lf", &(medida.temperatura));
        } else if (sensor == 2) {
            scanf("%d", &(medida.movimento));
        } else if (sensor == 3) {
            scanf("%d", &(medida.luminosidade));
        } else {
            scanf("%d", &(medida.umidade));
        }
        scanf("%d:%d:%d", &hora, &min, &seg);
        
        long int chave = criar_chave(sensor, hora, min, seg);
        t_medida_sensor *novo = criar_medida_sensor(sensor, medida, hora, min, seg);
        
        // Instrumentação precisa: apenas UMA busca por ciclo
        t_medida_sensor* recuperado = buscar_dd(medidas, chave);
        total_operacoes++; 
        
        if (recuperado == NULL) {
            inserir_dd(medidas, chave, novo);
            recuperado = novo; // Aponta para o novo elemento para exibir no final
        } else {
            // Tratar a repetição (Média simples para temperatura)
            if (sensor == 1) {
                recuperado->medida.temperatura = (recuperado->medida.temperatura + medida.temperatura) / 2.0;
            }
            
            // Prevenção de Memory Leak: liberamos a struct recém-criada 
            // já que ela não foi inserida na tabela (pois a chave já existia)
            free(novo); 
        }
        
        mostrar_medida_sensor(recuperado);
    }

    // --- Relatório de Instrumentação ---
    int total_comp = obter_total_comparacoes(medidas);
    float media_comparacoes = 0.0;
    if (total_operacoes > 0) {
        media_comparacoes = (float)total_comp / total_operacoes;
    }
    float saturacao_fc = calcular_porcentagem_fc_maior(medidas);

    printf("\n=== Relatório de Instrumentação de Software ===\n");
    printf("[-] Total de Operações Realizadas: %d\n", total_operacoes);
    printf("[-] Total de Comparações (Custo):  %d\n", total_comp);
    printf("[*] Média de Comparações por Op:   %.2f\n", media_comparacoes);
    printf("[*] Desvio de Fator de Carga (FC): %.2f%%\n", saturacao_fc);
    printf("===============================================\n");

    return 0;
}