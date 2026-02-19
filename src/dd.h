typedef struct dd t_dd;
t_dd* criar_dd(int M, int fc);
void inserir_dd(t_dd *dd, int chave, void* info);
void* buscar_dd(t_dd* dd, int chave);
void* remover_dd(t_dd* dd, int chave);
int obter_total_comparacoes(t_dd* dd);
float calcular_porcentagem_fc_maior(t_dd* dd);