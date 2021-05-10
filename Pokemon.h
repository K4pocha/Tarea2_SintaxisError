#ifndef POKEMON_H
#define POKEMON_H

typedef struct Pokedex Pokedex;

typedef struct Pokemon Pokemon;

const char *get_csv_field (char * tmp, int k);

void ImpotarExportarArchivo(HashMap * PokedexName, HashMap * almacenamientoId,int * nroPokemon,int * nroPokedex,int * flag);    //Lee el csv y almacena datos en los mapas implementados

void buscarPorNombrePokedex (HashMap * mapaPokedex);

void buscarPorNombrAlmacenamiento (HashMap * almacenamientoPoke);

void pokemonAtrapado(HashMap * mapaPokedex, HashMap * almacenamientoId,int * nroPokemon);

void evolucionarPokemon(HashMap * mapaPokedex,HashMap * almacenamientoId);

void buscarPokemonPorTipo(HashMap * mapaPokedex,HashMap * almacenamientoId);

void bubbleSortNroPokedex(Pokedex ** Array,int nroPokedex);

void mostrarPokemonPokedex(HashMap * mapaPokedex,int nroPokedex);

void bubbleSortPC(Pokemon ** Array,int nroPokedex);

void mostrarPokemonOrdenadosPorPc(HashMap * almacenamientoId,int nroPokemon);

void liberarPokemon(HashMap * almacenamientoId, HashMap * mapaPokedex,int * nroPokemon);

void mostarPokemonPorRegion(HashMap * mapaPokedex);

#endif /* POKEMON_h */