#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_LINHA 803 // Tamanho máximo de cada linha no arquivo CSV

struct Pokemon
    {
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

int main() 
{
    FILE *arquivo;
    char linha[MAX_LINHA];
    const char *delimitador = ",";

    char Snumero[4];

    //printf("digita seu numero ai meu brother: ");
    scanf("%s", Snumero);
    int numero = atoi(Snumero);

    arquivo = fopen("/Users/mateusmac/Projects/AEDS_2/Tp2/pokemon.csv", "r");
    //arquivo = fopen("/tmp/pokemon.csv", "r");
    if (arquivo == NULL) 
    {
        printf("Deu Merda ai meu patrao\n");
        return 1;
    }

    while(strcmp(Snumero, "FIM") != 0)
    {

        while (fgets(linha, MAX_LINHA, arquivo)) 
        {
            Pokemon pokemon;
            bool tipo2 = false;

            char *token = strtok(linha, "\"");
            token = strtok(NULL, "\"");
            pokemon.habilidades = token;
            token = strtok(NULL, "\"");

            char *string1 = strtok(linha, delimitador);
            pokemon.id = string1;
            string1 = strtok(NULL, delimitador);
            pokemon.generation = string1;
            string1 = strtok(NULL, delimitador);
            pokemon.nome = string1;
            string1 = strtok(NULL, delimitador);
            pokemon.descricao = string1;
            string1 = strtok(NULL, delimitador);
            pokemon.types[0] = string1;
            string1 = strtok(NULL, delimitador);
            if(string1 == NULL)
            {
                pokemon.types[1] = NULL;
            }
            else
            {
                pokemon.types[1] = string1;
            }

            char *string2 = token;
            char *token2 = strtok(string2, delimitador);
            int cont = 0;
            bool ratata = false;
            for(int i = 0; i<5; i++)
            {
                if(token2[i] == '.')
                {
                    cont++;
                }
                if(cont == 0)
                {
                    ratata = true;
                }
                else
                {
                    ratata = false;
                }
            }
            if(ratata == false){pokemon.peso = token2;}else{pokemon.peso = "0.0";}
            if(ratata == false){token2 = strtok(NULL, delimitador);}
            if(ratata == false){pokemon.altura = token2;}else{pokemon.altura = "0.0";}
            if(ratata == false){token2 = strtok(NULL, delimitador);}
            pokemon.raridade = token2;
            token2 = strtok(NULL, delimitador);
            pokemon.eLendario = token2;
            if(pokemon.eLendario == NULL || strcmp(pokemon.eLendario, "1") != 0) 
            {
                char ajuda[10] = "false";
                pokemon.eLendario = ajuda;
            } 
            else
            {
                char ajuda[10] = "true";
                pokemon.eLendario = ajuda;
            }
            token2 = strtok(NULL, delimitador);
            pokemon.data = token2;

            int id = atoi(pokemon.id);

            if(id == numero)
            {
                if(pokemon.types[1] == NULL)
                {
                    printf("[#%s -> %s: %s - ['%s'] - %s - %skg - %sm - %s%% - %s - %s gen] - %s", pokemon.id, pokemon.nome, pokemon.descricao, pokemon.types[0], pokemon.habilidades, pokemon.peso, pokemon.altura, pokemon.raridade, pokemon.eLendario, pokemon.generation, pokemon.data);
                }
                else
                {
                    printf("[#%s -> %s: %s - ['%s', '%s'] - %s - %skg - %sm - %s%% - %s - %s gen] - %s", pokemon.id, pokemon.nome, pokemon.descricao, pokemon.types[0], pokemon.types[1], pokemon.habilidades, pokemon.peso, pokemon.altura, pokemon.raridade, pokemon.eLendario, pokemon.generation, pokemon.data);
                }
            }
        }

        //printf("digita seu numero ai meu brother: ");
        scanf("%s", Snumero);
        numero = atoi(Snumero);

        rewind(arquivo);
    }
    


    fclose(arquivo);
    return 0;
}

