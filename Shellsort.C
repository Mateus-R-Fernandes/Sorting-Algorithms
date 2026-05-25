#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_NAME_LEN 100
#define MAX_DESC_LEN 255
#define MAX_TYPES 2
#define MAX_ABILITIES 100
#define MAX_LINE_LEN 1024
int countComps = 0;
int countSwaps = 0;

typedef struct {
    int id;
    int generation;
    char name[MAX_NAME_LEN];
    char description[MAX_DESC_LEN];
    char *types[MAX_TYPES];
    char abilities[MAX_ABILITIES];
    double weight;
    double height;
    int captureRate;
    int isLegendary;
    char data[10];
} Pokemon;

void printPokemon(Pokemon *pokemon) {
    printf("[#%d -> %s: %s - [", pokemon->id, pokemon->name, pokemon->description);
    
    printf("'%s'", pokemon->types[0]);
    if (pokemon->types[1] && pokemon->types[1][0] != '\0') {
        printf(", '%s'", pokemon->types[1]);
    }
    printf("] - ");

    printf("%s", pokemon->abilities);
    printf(" - %.1fkg - %.1fm - %d%% - %s - %d gen] - %s\n",
           pokemon->weight, pokemon->height, pokemon->captureRate,
           pokemon->isLegendary ? "true" : "false", pokemon->generation, pokemon->data);
}

void substituirVirgulasDentroColchetes(char *str) {
    int dentroColchetes = 0;

    while (*str) {
        if (*str == '[') {
            dentroColchetes = 1;
        } else if (*str == ']') {
            dentroColchetes = 0;
        } else if (*str == ',' && dentroColchetes) {
            *str = ';';
        }
        str++;
    }
}

char *strsep(char **stringp, const char *delim) {
    char *start = *stringp;
    char *end;

    if (start == NULL) {
        return NULL;
    }

    end = strpbrk(start, delim);
    if (end) {
        *end = '\0';
        *stringp = end + 1;
    } else {
        *stringp = NULL;
    }

    return start;
}

Pokemon *createPokemon(int id, int generation, const char *name, const char *description,
                       const char *type1, const char *type2, const char *ability,
                       double weight, double height, int captureRate, int isLegendary) {
    Pokemon *pokemon = malloc(sizeof(Pokemon));
    if (pokemon == NULL) {
        return NULL;
    }

    pokemon->id = id;
    pokemon->generation = generation;
    strncpy(pokemon->name, name, MAX_NAME_LEN - 1);
    pokemon->name[MAX_NAME_LEN - 1] = '\0';
    strncpy(pokemon->description, description, MAX_DESC_LEN - 1);
    pokemon->description[MAX_DESC_LEN - 1] = '\0';

    pokemon->types[0] = malloc(strlen(type1) + 1);
    strcpy(pokemon->types[0], type1);
    if (type2 && strlen(type2) > 0) {
        pokemon->types[1] = malloc(strlen(type2) + 1);
        strcpy(pokemon->types[1], type2);
    } else {
        pokemon->types[1] = NULL;
    }

    strcpy(pokemon->abilities, ability);
    pokemon->weight = weight;
    pokemon->height = height;
    pokemon->captureRate = captureRate;
    pokemon->isLegendary = isLegendary;

    return pokemon;
}

void freePokemon(Pokemon *pokemon) {
    for (int i = 0; i < MAX_TYPES; i++) {
        if (pokemon->types[i] != NULL) {
            free(pokemon->types[i]);
        }
    }
    free(pokemon);
}

void removeAspas(char *str) {
    char *p = str;
    while (*str) {
        if (*str != '"') {
            *p++ = *str;
        }
        str++;
    }
    *p = '\0';
}

void trocaPontoVirgula(char *str) {
    char *p = str;
    while (*p) {
        if (*p == ';') {
            *p = ',';
        }
        p++;
    }
    *p = '\0';
}

void lerLinhaCsv(char *linha, Pokemon *pokemon) {
    substituirVirgulasDentroColchetes(linha);

    char *token;
    linha[strcspn(linha, "\r\n")] = 0;
    char *rest = linha;

    token = strsep(&rest, ",");
    pokemon->id = atoi(token);

    token = strsep(&rest, ",");
    pokemon->generation = atoi(token);

    token = strsep(&rest, ",");
    strncpy(pokemon->name, token, MAX_NAME_LEN - 1);
    pokemon->name[MAX_NAME_LEN - 1] = '\0';

    token = strsep(&rest, ",");
    strncpy(pokemon->description, token, MAX_DESC_LEN - 1);
    pokemon->description[MAX_DESC_LEN - 1] = '\0';

    token = strsep(&rest, ",");
    if (token) {
        pokemon->types[0] = strdup(token);
        removeAspas(pokemon->types[0]);
    } else {
        pokemon->types[0] = NULL;
    }

    token = strsep(&rest, ",");
    if (token) {
        pokemon->types[1] = strdup(token);
        removeAspas(pokemon->types[1]);
    } else {
        pokemon->types[1] = NULL;
    }

    token = strsep(&rest, ",");
    removeAspas(token);
    trocaPontoVirgula(token);
    strcpy(pokemon->abilities, token);

    token = strsep(&rest, ",");
    if (token) {
        pokemon->weight = atof(token);
    } else {
        pokemon->weight = 0.0;
    }

    token = strsep(&rest, ",");
    if (token) {
        pokemon->height = atof(token);
    } else {
        pokemon->height = 0.0;
    }

    token = strsep(&rest, ",");
    if (token) {
        pokemon->captureRate = atoi(token);
    } else {
        pokemon->captureRate = 0;
    }

    token = strsep(&rest, ",");
    if (token) {
        pokemon->isLegendary = atoi(token);
    } else {
        pokemon->isLegendary = 0;
    }

    token = strsep(&rest, ",");
    strcpy(pokemon->data, token);
}

Pokemon *buscarPokemonPorId(Pokemon *lista[], int tamanhoLista, int id) {
    for (int i = 0; i < tamanhoLista; i++) {
        if (lista[i]->id == id) {
            return lista[i];
        }
    }
    return NULL;
}

void swap(Pokemon *a, Pokemon *b) {
    Pokemon temp = *a;
    *a = *b;
    *b = temp;
}

void shellSortGeneration(Pokemon pokedex[], int tamanho) {
    for (int gap = tamanho / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < tamanho; i++) {
            Pokemon temp = pokedex[i];
            int j;
            for (j = i; j >= gap && 
                (pokedex[j - gap].generation > temp.generation || 
                (pokedex[j - gap].generation == temp.generation && 
                strcmp(pokedex[j - gap].name, temp.name) > 0)); j -= gap) {

                (countComps)++;
                pokedex[j] = pokedex[j - gap];
                (countSwaps)++;
            }
            pokedex[j] = temp;
        }
    }
}

int main() {
    FILE *arquivo;
    Pokemon **listaPokemons = NULL;
    int numPokemons = 0;
    char input[MAX_NAME_LEN];

    int numPokemonsPokedex = 0;
    Pokemon *pokedex = malloc((802) * sizeof(Pokemon));
    clock_t start, end;

    arquivo = fopen("/Users/mateusmac/Projects/AEDS_2/Tp2/pokemon.csv", "r");
    if (arquivo == NULL) { 
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char linha[MAX_LINE_LEN];
    fgets(linha, MAX_LINE_LEN, arquivo);

    while (fgets(linha, MAX_LINE_LEN, arquivo) != NULL) {
        Pokemon *pokemon = createPokemon(0, 0, "", "", "", "", "", 0.0, 0.0, 0, 0);
        lerLinhaCsv(linha, pokemon);
        listaPokemons = realloc(listaPokemons, (numPokemons + 1) * sizeof(Pokemon *));
        listaPokemons[numPokemons] = pokemon;
        numPokemons++;
    }

    fclose(arquivo);

    scanf("%s", input);
    while (strcmp(input, "FIM") != 0) {
        int id = atoi(input);
        Pokemon *pokemonEncontrado = buscarPokemonPorId(listaPokemons, numPokemons, id);
        if (pokemonEncontrado) {
            pokedex[numPokemonsPokedex] = *pokemonEncontrado;
            numPokemonsPokedex++;
        }
        scanf("%s", input);
    }

    start = clock();
    shellSortGeneration(pokedex, numPokemonsPokedex);
    end = clock();

    for (int i = 0; i < numPokemonsPokedex; i++) {
        printPokemon(&pokedex[i]);
    }

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %.5f segundos\n", time_taken);
    printf("Comparações: %d\n", countComps);
    printf("Trocas: %d\n", countSwaps);

    for (int i = 0; i < numPokemons; i++) {
        freePokemon(listaPokemons[i]);
    }
    free(listaPokemons);
    free(pokedex);

    return 0;
}
    