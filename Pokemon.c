#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "Pokemon.h"

struct pokemonPokedex{
    char * nombre[20];
    int existencia;
    char ** tipos[20][20];
    char * preEvolucion[20];
    char * evolucion[20];
    int numero;
    char * region[10];
};

struct pokemonAlmacenamiento{
    int id;
    char * nombre[20];
    int pc;
    int ps;
    char * sexo[10];
};
