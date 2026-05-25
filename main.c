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
    countSwaps++;
}


int getCharAtPosition(char *str, int pos) {
    int len = strlen(str);
    if (pos >= len) {
        return 0; // Retorna 0 se o caractere não existir (para padronizar o tamanho).
    }
    return (int)str[pos];
}

// Função para pegar a primeira habilidade (antes da vírgula) de uma string de habilidades
void getFirstAbility(char *abilities, char *firstAbility) {
    int i = 0;
    while (abilities[i] != '\0' && abilities[i] != ',') {
        firstAbility[i] = abilities[i];
        i++;
    }
    firstAbility[i] = '\0'; // Finaliza a string
}

// Função para comparar a primeira habilidade e desempatar pelo nome
int compareAbilities(const Pokemon *a, const Pokemon *b) {
    char abilityA[MAX_ABILITIES], abilityB[MAX_ABILITIES];
    getFirstAbility(a->abilities, abilityA);
    getFirstAbility(b->abilities, abilityB);

    int cmp = strcmp(abilityA, abilityB);
    if (cmp == 0) {
        // Se as habilidades são iguais, desempate pelo nome
        return strcmp(a->name, b->name);
    }
    return cmp;
}

// Função de ordenação por inserção com comparação personalizada
void insertionSort(Pokemon pokedex[], int n) {
    for (int i = 1; i < n; i++) {
        Pokemon key = pokedex[i];
        int j = i - 1;

        // Mover os elementos de pokedex[0..i-1] que são maiores que key para uma posição à frente
        while (j >= 0 && compareAbilities(&pokedex[j], &key) > 0) {
            pokedex[j + 1] = pokedex[j];
            j--;
        }
        pokedex[j + 1] = key;
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

    arquivo = fopen("/tmp/pokemon.csv", "r");
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
    insertionSort(pokedex, numPokemonsPokedex);
    end = clock();

    for (int i = 0; i < numPokemonsPokedex; i++) {
        printPokemon(&pokedex[i]);
    }

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    FILE *logFile = fopen("844871_radixsort.txt", "w");
    if (logFile == NULL) {

        printf("Erro ao criar o arquivo de log.\n");
        return 1;

    } else {
        double timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
        fprintf(logFile, "844871\t%.2fms\t%d\tcomparações\t%d\ttrocas", timeTaken, countComps, countSwaps);
        fclose(logFile);
    }

    for (int i = 0; i < numPokemons; i++) {
        freePokemon(listaPokemons[i]);
    }
    free(listaPokemons);
    free(pokedex);

    return 0;
}
    