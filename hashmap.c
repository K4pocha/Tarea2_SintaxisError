#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"

typedef struct Pair Pair;
typedef struct HashMap HashMap;
int enlarge_called=0;

struct Pair {
     char * key;
     void * value;
};

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {

  long hashKey = hash(key,map->capacity); //poscicion
  Pair * dato = createPair(key,value);  //Auxiliar para insertar datos

  while (map->buckets[hashKey] != NULL && map->buckets[hashKey]->key != NULL){ //Validacion (ciclo) que corre mientras buckets tenga datos y que la key exista
    if(is_equal(map->buckets[hashKey]->key, key) == 1) return; //Caso en que el dato es repetido
    hashKey = (hashKey + 1) % map->capacity;  
  }
  
  map->buckets[hashKey] = dato;
  map->size++;
  if (map->size / map->capacity > 0.70) enlarge(map); //Actualizacion si el mapa se queda sin espacio
  
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
  
    Pair ** aux = map->buckets; 
    long capacity = map->capacity;

    map->capacity=map->capacity*2;  //Aumento de capacidad del mapa
    map->buckets=(Pair**) calloc (map->capacity, sizeof(Pair *)); //Redireccionando y reasignando memoria de los bukets segun la nueva capacidad
    long i;
    for (i = 0; i < capacity; i++){
      if (aux[i] != NULL)
      {
        insertMap(map,aux[i]->key, aux[i]->value); //Insertando buckets con nueva capacidad del mapa
      }
    }


}


HashMap * createMap(long capacity) {

  HashMap * map = (HashMap *)malloc(sizeof(HashMap)); //Creacion y reserva del mapa
  map->buckets = (Pair **) calloc (capacity, sizeof(Pair *)); //Creacion y reserva pares clave-valor mapa
  //Iniciado default mapa
  map->capacity = capacity;   
  map->size = 0;
  map->current = -1;

  long i;
  for (i = 0; i < capacity; i++) {
    if (map->buckets == NULL) return 0;
    else
      map->buckets[i] = NULL;
  }

  return map;
}

void eraseMap(HashMap * map,  char * key) {    
  long hashKey = hash(key,map->capacity); //Buscando posicicon segun funcion hash
  //long pos = hashKey;

  for ( ; hashKey < map->capacity; hashKey++) //Recorre el mapa hasta ver si el bucket ingresado esta vacio, o hasta que encuentra la key dentro del mapa y la elimina.
  {
    if (map->buckets[hashKey] == NULL) break; //Es void, no void *, por lo que no retorna nada --> usar break
    if(is_equal(map->buckets[hashKey]->key, key) == 1) {
      map->size--;
      map->buckets[hashKey]->key = NULL;
      map->buckets[hashKey]->value = NULL;

    }
  }

  /** map->buckets[pos]->value = NULL;
  map->buckets[pos]->key = NULL;
  map->size--; **/ 
  
}

void * searchMap(HashMap * map,  char * key) {   
  long hashKey = hash(key, map->capacity);

  for ( ; hashKey < map->capacity; hashKey++)  //Recorrido segun la hashKey. Finaliza si es mayor al tamaño del mapa
  {
    if (map->buckets[hashKey] != NULL) //Caso en que SI hay datos en esa poscicion del bucket
    {
      if (is_equal(map->buckets[hashKey]->key, key))  //Son el mismo dato?
      {
        map->current = hashKey;
        return map->buckets[hashKey]->value;  //Retorna el dato que encontro segun la key
      }
  
    }
    else if (map->buckets[hashKey] == NULL) return NULL; //No existen datos en ese bucket por lo que no hay que buscar nada.
  }
    return NULL;
}

void * firstMap(HashMap * map) {
  long i = 0;


  while (map->buckets[i] == NULL || map->buckets[i]->key == NULL) /** Intente recorrer con un while(map->capacity < i, y con if cuando eran != a NULL pero no me salio) **/
  {
    i++;
  }
  map->current = i;

  return map->buckets[i]->value;

  /** map->current = 0;
 return map->buckets[0]->value; **/
 return NULL;
}

void * nextMap(HashMap * map) {
  long i = map->current;
  i++;
  for (; i < map->capacity; i++)  //For que recorrera hasta encontrar un bucket con datos
  {
    if (map->buckets[i] != NULL)  //Caso en que el siguiente NO esta vacio
    {
      map->current = i;
      return map->buckets[i]->value;
    }
  }

    return NULL; 
}
