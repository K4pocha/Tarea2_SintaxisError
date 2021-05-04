#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"
#include <string.h>
#include <stdbool.h>


typedef struct Pokedex {  //Nodo de la pokedex
    char nombre[50];//Nombre
    char tipo[50];//Tipos
    char prevEvo[50];//Evolucion previa
    char sigEvo[50];//Evolucion siguiente
    int numeroPokedex;//Numero en la pokedex
    char region[50];
    int cantidadPoke;//Existencias total del pokemon en el almacenamiento
}Pokedex;

typedef struct Pokemon{ //Variable que va dentro de PokeStorage que es el mapa que almacena los pokemons capturados
    int id;
    char nombre[50];
    int PC;
    int PS;
    char genero[50];
}Pokemon;

const char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}

void leerArchivo(HashMap * PokedexID, HashMap * PokedexName, HashMap * almacenamientoPoke, FILE * archivo);    //Lee el csv y almacena datos en los mapas implementados
void crearPokedex(char * name, char * type, char * prevEvo, char * nextEvo, char * region, int idPokedex, Pokedex * nuevaID);//La variable exist se añade después en la funcion pokeAtrapado
Pokemon * crearPokemon(int id, int PC, int PS, char * nombre, char * genero);   //Inicializa una estructura nueva, y returna la misma estructura rellenada si corresponde
void guardarPokedex(HashMap * mapaPokedex, HashMap * PokedexID, Pokedex * nuevoID);
void buscarPorNombre (HashMap * almacenamientoPoke);
void buscarPorNombrePokedex (HashMap * mapaPokedex);


int main()
{
    HashMap * mapaPokedex = createMap(200);
    HashMap * PokedexID = createMap(200);//Almacena PokeID por numero de pokedex
    HashMap * almacenamientoPoke = createMap(200); //que es lo que tiene dentro?
    FILE * archivo = fopen("pokemon Archivo1.csv","r");
    leerArchivo(PokedexID, mapaPokedex, almacenamientoPoke, archivo);
    //buscarPorNombre (almacenamientoPoke);
    buscarPorNombrePokedex (mapaPokedex);



    /** int op;
        while(op < 10)
    {
        op = 0;
        printf("1.- Exportar Pokemon\n");
        printf("2.- Capturar Pokemon\n");
        printf("3.- Evolucionar Pokemon\n");
        printf("4.- Buscar Pokemon por Tipo\n");
        printf("5.- Buscar Pokemon por nombre\n");
        printf("6.- Buscar por nombre en pokedex\n");
        printf("7.- Mostrar todos los pokemon de la pokedex\n");
        printf("8.- Mostrar ordenados por PC\n");
        printf("9.- Liberar Pokemon\n");
        printf("10.- Mostrar por region\n");
        printf("Indica la opcion: ");
        scanf("%d", &op);
        fflush(stdin);

        switch(op)
        {
            case 1: 
                leerArchivo(PokedexID, PokedexName, PokeStorage, archivo);
                break;

            case 2:
                break;

            case 3:
                break;

            case 4: 
                break;

            case 5:
                break;

            case 6: 

                break;

            case 7: 

                break;

            case 8:

                break;

            case 9:

                break;

            case 10: 

                break;

            case 11: 
                 break;
        }
    } **/
    return 0;
}

void leerArchivo(HashMap * PokedexID, HashMap * mapaPokedex, HashMap * almacenamientoPoke, FILE * archivo){

    char * linea = (char*)malloc(1024*sizeof(char));
    Pokedex * nuevaID = (Pokedex *)malloc(sizeof(Pokedex));
    Pokemon * nuevoPoke = (Pokemon *)malloc(sizeof(Pokemon));
    linea = fgets(linea, 100, archivo);
    int encontrado=0;
    printf("primera linea = %s", linea);
    char * auxkey = (char*)malloc(50*sizeof(char));

    while(fgets (linea, 1023, archivo) != NULL){

       encontrado++;
       nuevaID->cantidadPoke = 0;
       nuevoPoke->id = atoi(get_csv_field(linea, 0));//ID
       strcpy(nuevoPoke->nombre, get_csv_field(linea,1));
       strdup(nuevoPoke->nombre);
       nuevoPoke->PC = atoi(get_csv_field(linea,3));//PC
       nuevoPoke->PS = atoi(get_csv_field(linea,4));//PS
       strcpy(nuevoPoke->genero, get_csv_field(linea,5));//Genero
       strdup(nuevoPoke->genero);

       strcpy(nuevaID->nombre, get_csv_field(linea,1));//Nombre
       strcpy(nuevaID->tipo, get_csv_field(linea,2));//Tipos
       itoa(nuevoPoke->id, auxkey, 10);
       printf("Pokemon numero = %d - Nombre: %s - ID: %d - key aux = ID %s\n", encontrado, nuevoPoke->nombre, nuevoPoke->id, auxkey);
       strcpy(nuevaID->prevEvo, strdup(get_csv_field(linea,6)));//Ev. previa
       strdup(nuevaID->prevEvo);
       strcpy(nuevaID->sigEvo, get_csv_field(linea,7));//Ev. post
       strdup(nuevaID->sigEvo);
       nuevaID->numeroPokedex = atoi(get_csv_field(linea,8));//Num. pokedex
       strcpy(nuevaID->region, get_csv_field(linea,9));//Region
       strdup(nuevaID->region);

       insertMap(almacenamientoPoke, strdup(auxkey),nuevoPoke);   //Guardado en el mapa de "almacenamiento"
       guardarPokedex(mapaPokedex, PokedexID, nuevaID); //Guardado en mapa de pokedex
       nuevaID = (Pokedex *)malloc(sizeof(Pokedex));
       nuevoPoke = (Pokemon *)malloc(sizeof(Pokemon));
    }
    printf("Archivo leido correctamente\n");
}

void crearPokedex(char * nombre, char * tipo, char * prevEvo, char * sigEvo, char * region, int idPokedex, Pokedex * nuevo){

    strcpy(nuevo->nombre, nombre);
    strcpy(nuevo->sigEvo, sigEvo);
    strcpy(nuevo->prevEvo, prevEvo);
    strcpy(nuevo->region, region);
    strcpy(nuevo->tipo, tipo);
    nuevo->numeroPokedex = idPokedex;
}

Pokemon * crearPokemon(int id, int PC, int PS, char * nombre, char * genero){
    Pokemon * nuevo = (Pokemon *)malloc(sizeof(Pokemon));

    strcpy(nuevo->genero, genero);
    strcpy(nuevo->nombre, nombre);
    nuevo->id = id;
    nuevo->PC = PC;
    nuevo->PS = PS;
    return nuevo;
}

void guardarPokedex(HashMap * mapaPokedex, HashMap * PokedexID, Pokedex * nuevoID){
    Pokedex * auxPoke;
    char * auxkey = (char*)malloc(50*sizeof(char));

    if(searchMap(mapaPokedex, nuevoID->nombre)!= NULL){
        auxPoke = searchMap(mapaPokedex, nuevoID->nombre);
        auxPoke->cantidadPoke ++;
        itoa(nuevoID->numeroPokedex, auxkey, 10);
        auxPoke = searchMap(PokedexID, auxkey);
        auxPoke->cantidadPoke ++;
        return;

    }else if(searchMap(mapaPokedex, nuevoID->nombre)== NULL){
        insertMap(mapaPokedex, nuevoID->nombre, nuevoID);
        itoa(nuevoID->numeroPokedex, auxkey, 10);
        insertMap(PokedexID,auxkey, nuevoID);
        return;
    }
}

/** Hubieron problemas con el almacenamiento, pero se "soluciono" con un strdup en el insertmap de la lectura de archivo. 
 * CAMBIAR TODOS LOS STRINGS ALMACENADOS A UN STRING CON STRDUP **/

void buscarPorNombrePokedex (HashMap * mapaPokedex)
{
    Pokedex * actual = firstMap(mapaPokedex);
    char * pokeBuscado = (char *)malloc(50*sizeof(char));
    char * auxiliar = (char *)malloc(50*sizeof(char));  //Variable para almacenar nombre pokemon leido de el mapa

    printf ("Ingresa nombre del Pokemon: \n");
    gets(pokeBuscado);
    int existe = 0;

    while (actual != NULL) {
        auxiliar = strtok(actual->nombre, " "); //strtok = strtoken -> Separa el string segun el delimitador (en este caso, " "), para solo leer el nombre del pokemon. Posibles problemas con pokemons con nombres compuestos o de dos palabras
        strdup(auxiliar);
        strdup(pokeBuscado);
        //printf (" %d -", actual->numeroPokedex);
        if (strcmp(auxiliar, pokeBuscado) == 0) {
            existe = 1;
            printf ("----------------\n");
            printf ("Pokemon: %s \n", actual->nombre);
            printf ("Tipo: %s \n", actual->tipo);
            printf ("Evolucion: %s \n", actual->sigEvo);
            printf ("Antevolucion: %s \n", actual->prevEvo);
            printf ("Region: %s \n", actual->region);
            printf ("ID Pokedex: %d \n", actual->numeroPokedex);
            printf ("Cantidad: %d \n", actual->cantidadPoke);
            printf ("----------- \n");
            break;
        }
        actual = nextMap(mapaPokedex);
    }
    if (existe == 0) printf ("No se encuentra almacenado el Pokemon de nombre: %s \n", pokeBuscado);
}

void buscarPorNombre (HashMap * almacenamientoPoke)
{
    Pokemon * actual = firstMap(almacenamientoPoke);
    char * pokeBuscado = (char *)malloc(50*sizeof(char));
    char * auxiliar = (char *)malloc(50*sizeof(char));  //Variable para almacenar nombre pokemon leido de el mapa

    printf ("Ingresa nombre del Pokemon: \n");
    gets(pokeBuscado);
    int existe = 0;

    while (actual != NULL) {
        auxiliar = strtok(actual->nombre, " "); //strtok = strtoken -> Separa el string segun el delimitador (en este caso, " "), para solo leer el nombre del pokemon. Posibles problemas con pokemons con nombres compuestos o de dos palabras
        strdup(auxiliar);
        strdup(pokeBuscado);
        //printf (" %d -", actual->id);
        if (strcmp(auxiliar, pokeBuscado) == 0) {
            existe = 1;
            printf ("---------------- \n");
            printf ("Pokemon: %s \n", actual->nombre);
            printf ("PC: %d \n", actual->PC);
            printf ("PS: %d \n", actual->PS);
            printf ("-----------");
            break;
        }
        actual = nextMap(almacenamientoPoke);
    }
    if (existe == 0) printf ("No se encuentra almacenado el Pokemon de nombre: %s \n", pokeBuscado);
}