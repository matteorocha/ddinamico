# Instrumentação de Software: Dicionário Dinâmico e Análise de Performance

## 🎯 Visão Geral do Projeto
Este projeto implementa uma **Estrutura de Dados de Alto Desempenho** (Hash Table / Dicionário Dinâmico) em Linguagem C, com foco em **Instrumentação de Software** e análise de complexidade (Big-O).

Diferente de implementações acadêmicas comuns, este sistema foi projetado com uma camada de monitoramento interno que coleta métricas de execução em tempo real (Runtime Analytics), permitindo diagnosticar gargalos de processamento, saturação de memória e o custo computacional de colisões.

> **Contexto de Engenharia:** A solução simula um sistema de coleta de dados de sensores industriais (Temperatura, Umidade, Luminosidade e Movimento), onde a eficiência de leitura e a blindagem contra dados corrompidos (I/O) são críticas.

## ⚙️ Tecnologias e Arquitetura Aplicada
* **Linguagem C (ANSI):** Gerenciamento rigoroso de memória manual (`malloc`/`free`) com prevenção de *Memory Leaks* em nós duplicados.
* **Estruturas de Dados:** Tabela Hash configurada intencionalmente com capacidade restrita (M=5) para forçar o tratamento de colisões via Lista Simplesmente Encadeada (LSE).
* **Segurança de I/O:** Blindagem contra *Buffer Poisoning* e *Data Corruption* na leitura de streams de dados (`stdin`).
* **Automação de Build:** Compilação modular (Makefile) otimizada com flags de qualidade rigorosa (`-Wall -Wextra`).

## 🚀 Compilação e Execução
O projeto conta com automação via `Makefile` para gerar datasets dinamicamente e rodar baterias de teste:

1. **Compilar (Build):**
   ```bash
    make
    ```

2. **Teste de Saturação (32 medições):**
    ```Bash

    make run_2_5
    ```


3. **Teste de Saturação (1.024 medições):**
    ```Bash

    make run_2_10
    ```

4. **Teste de Estresse de Leitura (32.768 medições):**
    ```Bash

    make run_2_15
    ```

5. **Limpeza de Binários (Clean):**
    ```Bash

    make clean
    ```

## 📊 Análise de Performance e Big-O (Resultados da Instrumentação)

O sistema foi submetido a baterias de estresse com datasets crescentes. Como a tabela foi inicializada com M=5 (5 posições) e um Fator de Carga ideal de fc=2, os testes demonstraram matematicamente a degradação da performance de busca de O(1) para O(N) devido à saturação.
Dataset	Operações (I/O)	Itens Únicos Armazenados	Fator de Carga	Comparações Totais	Média de Comparações por Busca
Leve (2_5)	32	32	100%	105	3.28 (Alta Eficiência)
Saturação (2_10)	1.024	1.024	100%	104.644	102.19 (Gargalo Linear O(N))
Estresse (2_15)	32.768	1.024	100%	~3.3 Milhões	102.19 (Estabilidade Read-Heavy)
🔍 Conclusão Técnica

Os resultados da instrumentação comprovam a teoria de Tabelas Hash:

    Saturação Absoluta: Ao injetar 1.024 elementos em apenas 5 posições, o Fator de Carga atingiu 100% de desvio. As Listas Encadeadas (LSE) incharam para uma média de ~204 itens cada.

    Custo Matemático Exato: Para buscar um elemento em uma lista de 204 itens, o algoritmo percorre estatisticamente a metade dela. A nossa métrica de 102.19 comparações médias reflete essa exatidão perfeitamente.

    Estabilidade em Estresse: No teste de 32.768 operações, o sistema descartou corretamente as chaves duplicadas (sem vazamento de memória), mantendo a tabela com 1.024 nós e suportando milhões de cálculos de forma estável. Em um cenário real, uma rotina de Rehashing (redimensionamento dinâmico do 'M') seria implementada para restaurar a performance para O(1).

👨‍💻 Autor: Matheus Rocha