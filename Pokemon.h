#ifndef POKEMON_H
#define POKEMON_H

typedef struct Pokedex Pokedex;

typedef struct Pokemon Pokemon;

const char *get_csv_field (char * tmp, int k);

void ImpotarExportarArchivo(HashMap * PokedexName, HashMap * almacenamientoId,int * nroPokemon,int * flag);    //Lee el csv y almacena datos en los mapas implementados

void buscarPorNombrePokedex (HashMap * mapaPokedex);

void pokemonAtrapado(HashMap * mapaPokedex, HashMap * almacenamientoId,int * nroPokemon);

void evolucionarPokemon(HashMap * mapaPokedex,HashMap * almacenamientoId);

void buscarPokemonPorTipo(HashMap * mapaPokedex,HashMap * almacenamientoId);

#endif /* POKEMON_h */