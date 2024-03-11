typedef struct dd t_dd;
t_dd* criar_dd(int M, int fc);
void inserir_dd(t_dd *dd, int chave, void* info);
void* buscar_dd(t_dd* dd, int chave);
void* remover_dd(t_dd* dd, int chave);
void stats_dd(t_dd* dd);
