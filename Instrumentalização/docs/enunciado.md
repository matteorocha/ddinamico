# Instrumentalização do dicionário.

A instrumentação de software é um processo de adicionar código a um software existente para coletar dados sobre seu comportamento e desempenho. Esse código adicional, chamado de "instrumentação", é usado para monitorar e registrar informações específicas sobre o software durante sua execução.

Um dos objetivos da instrumentação de software é a __Análise de desempenho__, avaliar a performance do software e identificar gargalos.

Nesta tarefa você deverá obter o código implementada em sala de aula, para o TAD de dicionário dinâmico, e instrumentalizá-lo. Ao final, o seu codigo deve ser capaz de responder as seguintes perguntas:

- Qual é o número médio de comparações executadas para concluir uma busca(remoção) no dicionário?
- Qual é a porcentagem de entradas que tem FC (fator de carga) maior(menor) que o definido para o dicionário?

_Nota 01:_ considere apenas comparações envolvendo as chaves do par __<chave,informação>__.

Em anexo, estão os seguintes arquivos:

- _dd.c_, implementação do dicionário;
- _usadd.c_, caso de uso com o dicionário;
- _lseneutra.c_, a LSE usada armazenar os elementos mapeados para entradas da tabela;
- _medidas\_2\_10.in_, uma amostra de dados.

_Nota 02:_ o caso de uso implementada armazena na tabela os dados coletados sobre sensores.

