#include "stdio.h"
#include "stdlib.h"
#include "lseneutra.h"
#include "math.h"

typedef struct elem_dd t_elem_dd; 
struct elem_dd{
    int chave;
    void* carga;
};

t_elem_dd* criar_elem_dd(int chave, void* info)
{
    t_elem_dd *novo = malloc(sizeof(t_elem_dd));
    novo->chave = chave;
    novo->carga = info;

    return novo;
}

int comparar_elem_dd(void* e1, void* e2)
{
    t_elem_dd* ee1 = e1;
    t_elem_dd* ee2 = e2;

    return (ee1->chave - ee2->chave);
}

static int funcao_hash(int M, int chave)
{
    // 100  % 101 = 100
    // 1000 % 101 = 100
    return (chave%M);

}

typedef struct dd t_dd;
struct dd{
    t_lse* *entradas;
    int M; // tamanho da tabela
    int fc;
};



t_dd* criar_dd(int M, int fc)
{
    t_dd *dd =  malloc(sizeof(t_dd));
    dd->M = M; // 101 - entrada
    dd->fc = fc;// 10 por entrada

    dd->entradas = malloc(sizeof(t_lse*)*M);
    for(int i=0;i<M;i++){
    dd->entradas[i] = criar_lse(NULL,comparar_elem_dd);
    }

    return dd; 
}

void inserir_dd(t_dd *dd, int chave, void* info){
    t_elem_dd* novo = criar_elem_dd(chave, info);

    int k = funcao_hash(dd->M, chave);

    inserir_lse(dd->entradas[k], novo);
}

void* buscar_dd(t_dd* dd, int chave){

    int k = funcao_hash(dd->M, chave);

    t_elem_dd* e = buscar_lse(dd->entradas[k],&chave);
    if (e!=NULL){
        return e->carga;
    }else{
        return NULL;
    }

}

void* remover_dd(t_dd* dd, int chave)
{
    
    int k = funcao_hash(dd->M, chave);

    t_elem_dd* e = remover_conteudo_lse(dd->entradas[k],&chave);
    void* retorno =  NULL;
    if (e!=NULL)
    {
        retorno = e->carga;
    
        free(e);
    }
    return retorno;
}

union u_medida
{
    int luminosidade;
    int umidade;
    int movimento;
    double temperatura;
};

typedef struct medida_sensor
{
    int tipo;
    union u_medida medida;
    int hora, min, seg;
}t_medida_sensor;

t_medida_sensor* criar_medida_sensor(int tipo, union u_medida medida, int hora, int min, int seg)
{
    t_medida_sensor *novo = malloc(sizeof(t_medida_sensor));
    novo -> tipo = tipo;
    novo -> hora = hora;
    novo -> min = min;
    novo -> seg = seg;

    if (tipo == 3)
    {
        novo -> medida.luminosidade = medida.luminosidade;
    }
    else if (tipo == 2)
    {
        novo -> medida.movimento = medida.movimento;
    }
    else if (tipo == 1)
    {
        novo -> medida.temperatura = medida.temperatura;
    }
    else
    {
        novo -> medida.umidade = medida.umidade;
    }
    return novo;
}

long int criar_chave(t_medida_sensor *m)
{
    long int chave = m -> tipo * pow(10,6) + m -> hora * pow(10,4) + m -> min * pow(10,2) + m -> seg * pow(10,0);
    printf("%ld %d %d:%d:%d\n", chave, m -> tipo, m -> hora, m -> min, m -> seg);
    return chave;
}

int main()
{
    int sensor, hora, min, seg;
    union u_medida medida;

    t_dd* medidas = criar_dd(5,2);
    for (int i = 1; i <= 10; i++)
    {    
        
        scanf("%d", &sensor);

        if (sensor == 1)
        {
            scanf("%lf", &(medida.temperatura));
        }
        else if (sensor == 2)
        {
            scanf("%d", &(medida.movimento));
        }
        else if (sensor == 3)
        {
            scanf("%d", &(medida.luminosidade));
        }
        scanf("%d", &hora);
        scanf("%d", &min);
        scanf("%d", &seg);
        t_medida_sensor *novo = criar_medida_sensor(sensor, medida, hora, min, seg);
        long int chave = criar_chave(novo);

        inserir_dd(medidas, chave, novo);
    }
}