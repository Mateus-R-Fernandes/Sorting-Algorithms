Sorting Algorithms — Pokédex Benchmark
Implementação e análise comparativa de algoritmos de ordenação clássicos aplicados a um dataset real de Pokémon. Cada algoritmo é instrumentado para registrar comparações, movimentações e tempo de execução.

Trabalho prático da disciplina de Algoritmos e Estruturas de Dados II — PUC Minas (2024)


Algoritmos implementados
AlgoritmoLinguagemMelhor casoCaso médioPior casoEstávelInsertion SortJavaO(n)O(n²)O(n²)✓Shell SortCO(n log n)O(n^1.5)O(n²)✗Quick SortJavaO(n log n)O(n log n)O(n²)✗Merge SortJavaO(n log n)O(n log n)O(n log n)✓Counting SortJavaO(n+k)O(n+k)O(n+k)✓Radix SortCO(nk)O(nk)O(nk)✓Busca SequencialJavaO(1)O(n)O(n)—Busca BináriaJavaO(1)O(log n)O(log n)—

Dataset
pokemon.csv — 800 Pokémon com os atributos:

id, nome, geração, descrição, raridade
peso, altura, isLendário
tipo1, tipo2, habilidades
data de captura

Os algoritmos ordenam o dataset por diferentes critérios (nome, altura, geração) e registram métricas de desempenho em arquivo de log.

Métricas coletadas
Cada execução gera um log com:
<matrícula>    <comparações>    <movimentações>    <tempo_ms>
Isso permite comparar o comportamento real de cada algoritmo no mesmo conjunto de dados, em vez de só analisar a complexidade teórica.

Estrutura do repositório
sorting-algorithms/
├── java/
│   ├── quicksort.java        # Quick Sort com pivô mediana
│   ├── mergesort.java        # Merge Sort recursivo
│   ├── countingsort.java     # Counting Sort por geração
│   ├── Insercao.java         # Insertion Sort
│   ├── sequencial.java       # Busca Sequencial
│   ├── pokedex.java          # Pokédex base
│   ├── pokedex2.java         # Pokédex com ordenação múltipla
│   └── pokedex_altura.java   # Pokédex ordenado por altura
├── c/
│   ├── radixsort.c           # Radix Sort
│   ├── Shellsort.C           # Shell Sort
│   ├── main.c                # entrada principal C
│   ├── sequenciabinaria.C    # Busca Binária em C
│   └── pokedex.C / pokedex2.C
├── data/
│   └── pokemon.csv           # dataset com 800 Pokémon
└── README.md

Como executar
Java:
bashjavac quicksort.java
java quicksort
C:
bashgcc radixsort.c -o radixsort
./radixsort
Cada programa lê pokemon.csv, executa a ordenação/busca e imprime as métricas no terminal e em arquivo de log.

Por que Pokémon?
O dataset de Pokémon é ideal para benchmarks de ordenação: tem volume suficiente (800 registros), atributos variados (string, int, double, boolean) que permitem testar diferentes critérios de ordenação, e distribuição de dados não trivial — o que expõe bem as diferenças entre algoritmos como Quick Sort e Insertion Sort em dados parcialmente ordenados.

Autor
Mateus Ribeiro Fernandes
Ciência da Computação — PUC Minas
