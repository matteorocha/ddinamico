#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "dd.h"

union u_medida
{
        int luminosidade; // media da luminosidade
        int umidade; // media da umidade 
        int movimento; 
        double temperatura;
};

typedef struct medida_sensor{
    int tipo;
    union u_medida medida;
    int hora, min, seg;
} t_medida_sensor;

t_medida_sensor* criar_medida_sensor(int tipo, union u_medida medida, int hora, int min, int seg){
    t_medida_sensor *novo = malloc(sizeof(t_medida_sensor));
    novo->tipo = tipo;
    novo->hora = hora;
    novo->min = min;
    novo->seg = seg;
    if (tipo == 3){
        novo->medida.luminosidade=medida.luminosidade;
    }else if (tipo == 2){
        novo->medida.movimento = medida.movimento;
    }else if (tipo == 1){
        novo->medida.temperatura = medida.temperatura;
    }else{
        novo->medida.umidade = medida.umidade;
    }

    return novo;
}

void mostrar_medida_sensor(t_medida_sensor *m){
    printf("%d ", m->tipo);
    if (m->tipo==1)
        printf("%.3lf",m->medida.temperatura);
    else if(m->tipo == 3){
        printf("%d", m->medida.luminosidade);
    }else if(m->tipo == 2){
        printf("%d", m->medida.movimento);
    }else{
        printf("%d", m->medida.umidade);
    }
    printf(" %02d:%02d:%02d\n", m->hora, m->min, m->seg);
}

long int criar_chave(t_medida_sensor *m){
    long int chave = m->tipo*pow(10,6)+m->hora*pow(10,4)+m->min*pow(10,2)+m->seg*pow(10,0);
    printf("%ld %d %d:%d:%d\n", chave, m->tipo, m->hora, m->min, m->seg);

    return chave;
}

int main(){
    int sensor, hora, min, seg;
    union u_medida medida;
    
    t_dd* medidas = criar_dd(5,2);

    int total_operacoes = 0; // contador para o total de operações de busca/remoção

    for(int i=1;i<=10;i++){
        scanf("%d", &sensor);
        if (sensor == 1){
            scanf("%lf", &(medida.temperatura));
        }else if(sensor == 2){
            scanf("%d",&(medida.movimento));
        }else if(sensor == 3){
            scanf("%d", &(medida.luminosidade));
        }else{
            scanf("%d", &(medida.umidade));
        }
        scanf("%d:%d:%d", &hora, &min, &seg);

        t_medida_sensor *novo = criar_medida_sensor(sensor,medida,hora,min,seg);
        long int chave = criar_chave(novo);
        
        t_medida_sensor* recuperado = buscar_dd(medidas,chave);
        
        if (recuperado == NULL){
            inserir_dd(medidas,chave,novo);
        }else{
            // tratar a repetição 
            // calcular um valor medio para a referida medição.
            // media simples, media ponderada, Media ponderada exponencial
            if (sensor = 1)
            {
                double media = (recuperado -> medida.temperatura + medida.temperatura) / 2.0;
                recuperado -> medida.temperatura = media;
            }
        }
        recuperado = buscar_dd(medidas,chave);

        total_operacoes++; // incrementa o contador de operações
        
        mostrar_medida_sensor(recuperado);
    }

    // Imprime o número médio de comparações e a porcentagem de entradas com FC maior que o definido
    printf("Número médio de comparações: %.2f\n", (float) medidas->comparacoes / total_operacoes);
    printf("Porcentagem de entradas com FC maior que o definido: %.2f%%\n", calcular_porcentagem_fc_maior(medidas));
}
