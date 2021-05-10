#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "Pokemon.h"

typedef struct Pokedex {  //Nodo de la pokedex
    char nombre[50];//Nombre
    char tipo[50];//Tipos
    char prevEvo[50];//Evolucion previa
    char sigEvo[50];//Evolucion siguiente
    int numeroPokedex;//Numero en la pokedex
    char region[50];//region a al que pertenece el pokemon
    int cantidadPoke;//Existencias total del pokemon en el almacenamiento
}Pokedex;

typedef struct Pokemon{ //Variable que va dentro de PokeStorage que es el mapa que almacena los pokemons capturados
    int id;//numero Identificador del Pokemon
    char nombre[50];//nombre
    int PC;//puntos de combate del Pokemon
    int PS;//puntos de salud del Pokemon
    char genero[50];//Sexo del Pokemon
}Pokemon;

//Funcion para leer el contenido de un archivo csv
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

void ImpotarExportarArchivo(HashMap * mapaPokedex, HashMap * almacenamientoId,int * nroPokemon,int * nroPokedex, int * flag){
    char nombreArchivo[50];
    FILE * archivo;
    char auxId[5];
    printf(" Que operacion desea realizar:\n");
    printf(" 1. Importar Pokemon\n");
    printf(" 2. Exportar Pokemon\n");
    printf(" 0. Volver al menu\n");
    printf ("===============================================================\n");
    int op;
    printf(" Ingrese un Numero: ");
    scanf(" %d",&op);
    while((op < 0 || op > 2)){
        printf ("===============================================================\n");
        printf (" Por favor ingrese uno de los numeros anteriores: ");
        while(getchar()!='\n');
        scanf (" %d", &op);
    }
    if(op == 1){
        if(*flag == 1){
            printf("Ya se ha abierto un archivo, Exporte sus Pokemon\n");
            return;
        }
        printf(" Ingrese el nombre del archivo: ");
        getchar();
        gets(nombreArchivo);
        archivo = fopen(nombreArchivo,"r");
        if(archivo == NULL){
            printf(" El archivo no existe\n");
            return;
        }
        *flag = 1;
        char * linea = (char*)malloc(1024*sizeof(char));
        Pokedex * newPokedex;
        Pokemon * newPokemon;
        linea = fgets(linea, 1024, archivo);
        while(fgets (linea, 1023, archivo) != NULL &&  *nroPokemon <= 100){
            newPokemon = (Pokemon *)malloc(sizeof(Pokemon));
            newPokemon->id = atoi(get_csv_field(linea,0));
            strcpy(auxId,get_csv_field(linea,0));
            strcpy(newPokemon->nombre,get_csv_field(linea,1));
            newPokemon->PC = atoi(get_csv_field(linea,3));
            newPokemon->PS = atoi(get_csv_field(linea,4));
            strcpy(newPokemon->genero,get_csv_field(linea,5));
            insertMap(almacenamientoId, strdup(auxId),newPokemon);   //Guardado en el mapa de "almacenamiento"
            *nroPokemon += 1;
            Pokedex* aux = searchMap(mapaPokedex,newPokemon->nombre);
            if(aux != NULL){
                aux->cantidadPoke++;
            }
            else{
                newPokedex = (Pokedex *)malloc(sizeof(Pokedex));
                strcpy(newPokedex->nombre,get_csv_field(linea,1));
                strcpy(newPokedex->tipo,get_csv_field(linea,2));
                strcpy(newPokedex->prevEvo,get_csv_field(linea,6));
                strcpy(newPokedex->sigEvo,get_csv_field(linea,7));
                newPokedex->numeroPokedex = atoi(get_csv_field(linea,8));
                strcpy(newPokedex->region,get_csv_field(linea,9));
                newPokedex->cantidadPoke = 1;
                *nroPokedex += 1;
                insertMap(mapaPokedex,strdup(newPokedex->nombre),newPokedex);
            }
        }
        if(*nroPokemon <= 100){
            printf(" Archivo leido correctamente\n");
        }
        if(*nroPokemon >100){
            printf(" El almacenamiento alcanzo su capacidad Maxima\n");
            printf(" Recuerde exportar sus Pokemon en un CAJA\n");
            printf(" Y vuelva a Importar el archivo\n");
        }
        fclose(archivo);
    }
    else if(op == 2){
        if(*flag == 0){
            printf("Aun no se importan sus Pokemon, recuerde Importar\n");
            return;
        }
        *flag = 0;
        *nroPokemon = 0;
        archivo = fopen("Caja_Auxiliar.csv","r+");
        fseek(archivo,-1,SEEK_END);
        Pokemon * auxPokemon = firstMap(almacenamientoId);
        Pokedex * auxPokedex;
        while(auxPokemon != NULL){
            auxPokedex = searchMap(mapaPokedex,auxPokemon->nombre);
            fprintf(archivo,"%d,",auxPokemon->id);
            fprintf(archivo,"%s,",auxPokemon->nombre);
            fprintf(archivo,"%s,",auxPokedex->tipo);
            fprintf(archivo,"%d,",auxPokemon->PC);
            fprintf(archivo,"%d,",auxPokemon->PS);
            fprintf(archivo,"%s,",auxPokemon->genero);
            fprintf(archivo,"%s,",auxPokedex->prevEvo);
            fprintf(archivo,"%s,",auxPokedex->sigEvo);
            fprintf(archivo,"%d,",auxPokedex->numeroPokedex);
            fprintf(archivo,"%s\n",auxPokedex->region);
            auxPokedex->cantidadPoke --;
            sprintf(auxId,"%d",auxPokemon->id);
            eraseMap(almacenamientoId,auxId);
            auxPokemon = nextMap(almacenamientoId);
        }
        printf(" Pokemon exportados en Caja_Auxiliar.csv correctamente\n");
        fclose(archivo);
    }
    else{
        return;
    }
    
}

/** Hubieron problemas con el almacenamiento, pero se "soluciono" con un strdup en el insertmap de la lectura de archivo. 
 * CAMBIAR TODOS LOS STRINGS ALMACENADOS A UN STRING CON STRDUP **/

void buscarPorNombrePokedex (HashMap * mapaPokedex)
{
    printf("Ingrese el nombre del Pokemon: ");
    char pokeBuscado[50];
    scanf(" %s",pokeBuscado);
    Pokedex * actual = searchMap(mapaPokedex,pokeBuscado);
    int flag = 0;
    if(actual == NULL){
        flag = 1;
    }
    if(flag == 0){
        printf ("----------------\n");
        printf ("Pokemon: %s \n", actual->nombre);
        printf ("Tipo: %s \n", actual->tipo);
        printf ("Evolucion: %s \n", actual->sigEvo);
        printf ("Antevolucion: %s \n", actual->prevEvo);
        printf ("Region: %s \n", actual->region);
        printf ("ID Pokedex: %d \n", actual->numeroPokedex);
        printf ("Cantidad: %d \n", actual->cantidadPoke);
        printf ("----------- \n");
    }
    if (flag == 1) printf ("No se encuentra almacenado el Pokemon de nombre: %s \n", pokeBuscado);
}

void buscarPorNombrAlmacenamiento (HashMap * almacenamientoPoke)
{
    Pokemon * actual = firstMap(almacenamientoPoke);
    char pokeBuscado[50];

    printf ("Ingresa nombre del Pokemon: \n");
    gets(pokeBuscado);
    int existe = 0;
    printf ("------------------ \n");
    while (actual != NULL) {
        
        if (strcmp(actual->nombre, pokeBuscado) == 0) {
            existe = 1;
            printf ("ID: %d\n", actual->id);
            printf ("Pokemon: %s \n", actual->nombre);
            printf ("PC: %d \n", actual->PC);
            printf ("PS: %d \n", actual->PS);
            printf ("------------------ \n");
        }
        actual = nextMap(almacenamientoPoke);
    }
    if (existe == 0) printf ("No se encuentra almacenado el Pokemon de nombre: %s \n", pokeBuscado);
}

void pokemonAtrapado(HashMap * mapaPokedex, HashMap * almacenamientoId,int * nroPokemon){
    Pokemon * newPokemon = (Pokemon *)malloc(sizeof(Pokemon));
    Pokedex * newPokedex;
    char auxId[5]; 
    int auxNum;
    *nroPokemon += 1;
    if(*nroPokemon > 100){
        printf(" El almacenamiento alcanzo su capacidad Maxima\n");
        printf(" Recuerde exportar sus Pokemon en un CAJA\n");
        printf(" Y vuelva a Importar el archivo\n");
        return;
    }
    printf(" Ingresa los datos de Pokemon\n");
    newPokemon->id = *nroPokemon;
    printf("Nombre: ");
    scanf(" %s",newPokemon->nombre);
    printf("Sexo: ");
    scanf(" %s",newPokemon->genero);
    printf("PC: ");
    scanf("%d",&auxNum);
    newPokemon->PC = auxNum;
    printf("PS: ");
    scanf("%d",&auxNum);
    newPokemon->PS = auxNum;
    sprintf(auxId,"%d",*nroPokemon);
    insertMap(almacenamientoId,strdup(auxId),newPokemon);
    Pokedex * aux = searchMap(mapaPokedex,newPokemon->nombre);
    if(aux != NULL){
        aux->cantidadPoke ++;
    }
    else{
        newPokedex = (Pokedex*)malloc(sizeof(Pokedex));
        strcpy(newPokedex->nombre,newPokemon->nombre);
        printf("Evolucion Previa: ");
        scanf(" %s",newPokedex->prevEvo);
        printf("Evolucion Posterior: ");
        scanf(" %s",newPokedex->sigEvo);
        printf("Tipo: ");
        while(getchar()!='\n');
        gets(newPokedex->tipo);
        while(getchar()!='\n');
        printf("Numero de la Pokedex: ");
        scanf("%d",&auxNum);
        newPokedex->numeroPokedex = auxNum;
        printf("Region: ");
        scanf(" %s",newPokedex->region);
        newPokedex->cantidadPoke = 1;
        insertMap(mapaPokedex,strdup(newPokedex->nombre),newPokedex);
    }
}

void evolucionarPokemon(HashMap * mapaPokedex,HashMap * almacenamientoId){
    char auxId[5];
    printf(" Escribe la Id del Pokemon que deseas Evolucionar\n");
    scanf(" %s",auxId);
    Pokemon * aux = searchMap(almacenamientoId,auxId);
    if(aux == NULL){
        printf(" Pokemon no encontrado\n");
        return;
    }
    Pokedex * auxPokedex1 = searchMap(mapaPokedex,aux->nombre);//aux que apunta al nombre del pokemon a evolucionar
    if(auxPokedex1 == NULL){
        printf(" Pokemon no encontrado en la pokedex");
        return;
    }
    if(strcmp(auxPokedex1->sigEvo,"No Tiene") == 0){
        printf(" El Pokemon ya alcanzo su ultima evolucion\n");
        return;
    }
    else{
        printf("---------------");
        printf(" Tu Pokemon %s esta Evolucionando...\n",aux->nombre);
        strcpy(aux->nombre,auxPokedex1->sigEvo);
        printf("Tu Pokemon ha evolucionado a %s\n",aux->nombre);
        aux->PC += (aux->PC * 0.5);
        aux->PS += (aux->PS * 0.25);
        printf("Sus PC han aumentado a %d\n",aux->PC);
        printf("Sus PS han aumentado a %d\n",aux->PS);
        auxPokedex1->cantidadPoke -= 1;
    }
}

void buscarPokemonPorTipo(HashMap * mapaPokedex,HashMap * almacenamientoId){
    Pokemon * aux = firstMap(almacenamientoId);
    Pokedex * auxPokedex;
    printf(" Ingrese el tipo que desea buscar: ");
    char Tipo[50],auxTipo[50];
    int contador,cantidad = 0;
    scanf(" %s",Tipo);
    printf(" Pokemon de tipo %s\n",Tipo);
    while(aux != NULL){
        auxPokedex = searchMap(mapaPokedex,aux->nombre);
        if(auxPokedex == NULL){
            aux = nextMap(almacenamientoId);
        }
        else{
            strcpy(auxTipo,auxPokedex->tipo);
            strcat(auxTipo," ");
            contador = 0;
            while(get_csv_field(auxTipo,contador) != NULL){
                if(strcmp(get_csv_field(auxTipo,contador),Tipo) == 0){
                    printf("ID: %d   ",aux->id);
                    printf("Nombre: %s   ",aux->nombre);
                    printf("Genero: %s   ",aux->genero);
                    printf("PC: %d   ",aux->PC);
                    printf("PS: %d\n",aux->PS);
                    contador = 200;
                    cantidad +=1;
                }
                else{
                    contador += 1;
                }
            }
            aux = nextMap(almacenamientoId);
        }
    }
    printf(" Se encontraron %d Pokemon de tipo %s\n",cantidad,Tipo);
}

void bubbleSortNroPokedex(Pokedex ** Array,int nroPokedex){
    int i,j;
    Pokedex * aux;


    for(i = 0;i < nroPokedex - 1;i++){
        for(j = 0;j < nroPokedex- i - 1;j++){
            if(Array[j]->numeroPokedex > Array[j+1]->numeroPokedex){
                aux = Array[j+1];
                Array[j+1] = Array[j];
                Array[j] = aux;
            }
        }
    }
}

void mostrarPokemonPokedex(HashMap * mapaPokedex,int nroPokedex){
    Pokedex ** new = (Pokedex**)malloc(sizeof(Pokedex*)*nroPokedex);
    Pokedex * aux = firstMap(mapaPokedex);
    for(int i = 0;aux != NULL;i++){
        new[i] = aux;
        aux = nextMap(mapaPokedex); 
    }
    bubbleSortNroPokedex(new,nroPokedex);
    for(int i = 0;i < nroPokedex;i++){
        printf("Pokemon %d\n",new[i]->numeroPokedex);
        printf("Nombre: %s   ",new[i]->nombre);
        printf("Tipo(s): %s   ",new[i]->tipo);
        printf("Cantidad: %d   \n",new[i]->cantidadPoke);
        printf("Evolucion Previa: %s   ",new[i]->prevEvo);
        printf("Evolucion Posterior: %s   \n",new[i]->sigEvo);
        printf("Region: %s   \n",new[i]->region);
        printf("---------------------------------------------------------------\n");
    }
    free(aux);
}

void bubbleSortPC(Pokemon ** Array,int nroPokedex){
    int i,j;
    Pokemon * aux;


    for(i = 0;i < nroPokedex - 1;i++){
        for(j = 0;j < nroPokedex- i - 1;j++){
            if(Array[j]->PC < Array[j+1]->PC){
                aux = Array[j+1];
                Array[j+1] = Array[j];
                Array[j] = aux;
            }
        }
    }
}

void mostrarPokemonOrdenadosPorPc(HashMap * almacenamientoId,int nroPokemon){
    Pokemon ** new =(Pokemon**)malloc(nroPokemon * (sizeof(Pokemon *)));
    Pokemon * aux = firstMap(almacenamientoId);
    for(int i = 0;aux != NULL;i++){
        new[i] = aux;
        aux = nextMap(almacenamientoId);
    }
    bubbleSortPC(new,nroPokemon);
    for(int i = 0;i < nroPokemon;i++){
        printf("Pokemon %d\n",new[i]->id);
        printf("Nombre: %s   ",new[i]->nombre);
        printf("Sexo: %s\n",new[i]->genero);
        printf("PC: %d   ",new[i]->PC);
        printf("PS: %d\n",new[i]->PS);
        printf("---------------------------------------------------------------\n");
    }
    free(aux);
}

void liberarPokemon(HashMap * almacenamientoId, HashMap * mapaPokedex,int * nroPokemon){
    int id = -1;
    printf("Escriba la ID del Pokemon a eliminar: ");
    scanf("%d",&id);
    char auxId[5];
    sprintf(auxId,"%d",id);
    Pokemon * aux = searchMap(almacenamientoId,auxId);
    Pokedex * auxPokedex;
    if(aux == NULL){
        printf("Pokemon no encontrado\n");
        return;
    }
    else{
        auxPokedex = searchMap(mapaPokedex,aux->nombre);
        if(auxPokedex != NULL){
            auxPokedex->cantidadPoke -= 1;
        }
        eraseMap(almacenamientoId,auxId);
        printf("Pokemon Eliminado\n");
        *nroPokemon -= 1;
    }
}

void mostarPokemonPorRegion(HashMap * mapaPokedex){
    Pokedex * actual = firstMap(mapaPokedex);
    char regionBuscada[50];
    int cantidad = 0;
    int existe = 0;
    printf ("Ingresa la Region que buscas: \n");
    gets(regionBuscada);
    printf ("---------------------------------------------------------------\n");
    while (actual != NULL) {
        
        if (strcmp(actual->region, regionBuscada) == 0) {
            existe = 1;
            printf ("Nro Pokedex: %d   ", actual->numeroPokedex);
            printf ("Pokemon: %s \n", actual->nombre);
            printf ("Evolucion previa: %s   ", actual->prevEvo);
            printf ("Evolucion Posterior: %s \n", actual->sigEvo);
            printf ("Tipo: %s \n", actual->tipo);
            printf ("---------------------------------------------------------------\n");
            cantidad = cantidad + actual->cantidadPoke;
        }
        actual = nextMap(mapaPokedex);
    }
    if (existe == 0) printf ("No se encuentra la region %s en la Pokedex. \n", regionBuscada);
    printf("La cantidad de Pokemon que tienes almacenados en esta region es: %d\n",cantidad);
}