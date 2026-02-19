# ==========================================
# Makefile - Dicionário Dinâmico Instrumentado
# Estrutura: Compilação Modular e Linkagem
# ==========================================

# 1. Definições do Compilador
CC = gcc
# Flags: 
# -I./src: Indica onde procurar os arquivos .h (Header files)
# -Wall -Wextra: Ativa avisos de qualidade de código (QA)
# -g: Permite debug (gdb)
CFLAGS = -Wall -Wextra -I./src -g

# 2. Definição dos Arquivos
# Onde estão os códigos fonte
SRC_DIR = src
# Lista de objetos que serão gerados (um para cada .c)
OBJS = $(SRC_DIR)/usadd.o $(SRC_DIR)/dd.o $(SRC_DIR)/lseneutra.o

# Nome do executável final
TARGET = dd_instrumental

# ==========================================
# Regras de Build (A "Receita")
# ==========================================

# Regra principal (o que roda ao digitar 'make')
all: $(TARGET)

# Fase de Linkagem (Junta os objetos .o para criar o executável)
$(TARGET): $(OBJS)
	@echo "🔨 [LINKER] Gerando executável final: $(TARGET)..."
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "✅ Build concluído com sucesso!"

# Fase de Compilação (Transforma .c em .o)
# A regra genérica %.o : %.c diz: "Para criar qualquer .o, pegue o .c correspondente"
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "⚙️  [CC] Compilando módulo: $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Teste de carga de 32 medições (2⁵)
run_2_5:
	@echo "\n=== Iniciando Teste 2_5 (32 medições) ==="
	./dd_instrumental < datasets/medidas_2_5.in > data/resultados_2_5.txt


# Testa a carga de 1024 medições (2¹⁰)
run_2_10:
	@echo "\n=== Iniciando Teste 2_10 (1024 medições) ==="
	./dd_instrumental < datasets/medidas_2_10.in > data/resultados_2_10.txt

# Teste com carga de 32.768 medições (2¹⁵)
run_2_15:
	@echo "\n=== Iniciando Teste de Estresse 2_15 (32.768 medições) ==="
	./dd_instrumental < datasets/medidas_2_15.in > data/resultados_2_15.txt

# Regra de Limpeza (Remove binários para garantir rebuild limpo)
clean:
	@echo "🧹 Limpando arquivos temporários e binários..."
	rm -f $(SRC_DIR)/*.o $(TARGET) *~