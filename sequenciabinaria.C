#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

#define MAX_LINHA 803 // Tamanho máximo de cada linha no arquivo CSV
#define MAX_POKEMONS 100 // Limite de Pokémons no array

struct Pokemon {
    char* id;
    char* generation;
    char* nome;
    char* descricao;
    char* types[2];
    char* habilidades;
    char* peso;
    char* altura;
    char* raridade;
    char* eLendario;
    char* data;
};

void salvar_pokemon(Pokemon* pokemons, int* count, Pokemon p) {
    pokemons[*count] = p;
    (*count)++;
}

int main() {
    FILE *arquivo;
    char linha[MAX_LINHA];
    const char *delimitador = ",";
    
    Pokemon pokemons[MAX_POKEMONS]; // Array para armazenar Pokémons
    int count = 0; // Contador de Pokémons armazenados

    arquivo = fopen("/Users/mateusmac/Projects/AEDS_2/Tp2/pokemon.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo CSV.\n");
        return 1;
    }

    char entradaIds[256]; // Para armazenar os IDs digitados
    printf("Digite os IDs dos Pokémons separados por espaço (digite 'FIM' para encerrar): ");
    fgets(entradaIds, 256, stdin); // Lê os IDs

    while (strcmp(entradaIds, "FIM\n") != 0) {
        char *idAtual = strtok(entradaIds, " ");
        
        while (idAtual != NULL) {
            int numero = atoi(idAtual); // Converte o ID para número

            rewind(arquivo); // Reposiciona o ponteiro do arquivo para o início
            while (fgets(linha, MAX_LINHA, arquivo)) {
                Pokemon pokemon;
                bool tipo2 = false;

                char *token = strtok(linha, "\"");
                token = strtok(NULL, "\"");
                pokemon.habilidades = strdup(token); // Corrigido com strdup
                token = strtok(NULL, "\"");

                char *string1 = strtok(linha, delimitador);
                pokemon.id = strdup(string1); // Corrigido com strdup
                string1 = strtok(NULL, delimitador);
                pokemon.generation = strdup(string1); // Corrigido com strdup
                string1 = strtok(NULL, delimitador);
                pokemon.nome = strdup(string1); // Corrigido com strdup
                string1 = strtok(NULL, delimitador);
                pokemon.descricao = strdup(string1); // Corrigido com strdup
                string1 = strtok(NULL, delimitador);
                pokemon.types[0] = strdup(string1); // Corrigido com strdup
                string1 = strtok(NULL, delimitador);
                pokemon.types[1] = (string1 == NULL) ? NULL : strdup(string1); // Corrigido com strdup

                char *string2 = token;
                char *token2 = strtok(string2, delimitador);
                pokemon.peso = (token2 == NULL) ? strdup("0.0") : strdup(token2); // Corrigido com strdup
                token2 = strtok(NULL, delimitador);
                pokemon.altura = (token2 == NULL) ? strdup("0.0") : strdup(token2); // Corrigido com strdup
                pokemon.raridade = strdup(strtok(NULL, delimitador)); // Corrigido com strdup
                pokemon.eLendario = strdup(strtok(NULL, delimitador)); // Corrigido com strdup
                pokemon.data = strdup(strtok(NULL, delimitador)); // Corrigido com strdup

                if (pokemon.eLendario == NULL || strcmp(pokemon.eLendario, "1") != 0) {
                    pokemon.eLendario = strdup("false"); // Corrigido com strdup
                } else {
                    pokemon.eLendario = strdup("true"); // Corrigido com strdup
                }

                int id = atoi(pokemon.id);

                if (id == numero) {
                    salvar_pokemon(pokemons, &count, pokemon); // Salva o Pokémon no array
                    break; // Já encontramos o Pokémon com o ID desejado
                }
            }
            idAtual = strtok(NULL, " "); // Pega o próximo ID
        }

        // Solicita a entrada de mais IDs
        printf("Digite mais IDs ou 'FIM' para encerrar: ");
        fgets(entradaIds, 256, stdin);
    }

    fclose(arquivo);

    // Exibe os Pokémons armazenados
    printf("\nPokémons armazenados:\n");
    for (int i = 0; i < count; i++) {
        Pokemon p = pokemons[i];
        if (p.types[1] == NULL) {
            printf("[#%s -> %s: %s - ['%s'] - %s - %skg - %sm - %s%% - %s - %s gen] - %s\n", 
                p.id, p.nome, p.descricao, p.types[0], p.habilidades, p.peso, p.altura, p.raridade, p.eLendario, p.generation, p.data);
        } else {
            printf("[#%s -> %s: %s - ['%s', '%s'] - %s - %skg - %sm - %s%% - %s - %s gen] - %s\n", 
                p.id, p.nome, p.descricao, p.types[0], p.types[1], p.habilidades, p.peso, p.altura, p.raridade, p.eLendario, p.generation, p.data);
        }
    }

    return 0;
}
