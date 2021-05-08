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

void ImpotarExportarArchivo(HashMap * PokedexName, HashMap * almacenamientoId,int * nroPokemon);    //Lee el csv y almacena datos en los mapas implementados
void buscarPorNombrePokedex (HashMap * mapaPokedex);
void pokemonAtrapado(HashMap * mapaPokedex, HashMap * almacenamientoId,int * nroPokemon);
void evolucionarPokemon(HashMap * mapaPokedex,HashMap * almacenamientoId);


int main()
{
    int nroPokemon = 0;//cuenta la cantidad de pokemon que hay en el almacenamiento
    HashMap * mapaPokedex = createMap(200);//almacena Pokemon de la pokedex por nombre
    HashMap * PokedexID = createMap(200);//Almacena Pokemon de la pokedex por numero de pokedex
    HashMap * almacenamientoPoke = createMap(200); //almacena todos los pokemon que tiene el usuario por nombre
    HashMap * almacenamientoId = createMap(200); //Almacena pokemon del usuario por id
    //buscarPorNombre (almacenamientoPoke);
    
    int op;
    int flag=0;
    int menu;
    menu = 0;

    while (menu >= 0 && menu <= 10) {
        printf("===============================================================\n");
        printf("                            POKEDEX                            \n");
        printf("===============================================================\n");
        printf("|   1.- Importar o Exportar Pokemon                           |\n");
        printf("|   2.- Pokemon Atrapado                                      |\n");
        printf("|   3.- Evolucionar Pokemon                                   |\n");
        printf("|   4.- Buscar mis Pokemon por tipo                           |\n");
        printf("|   5.- Buscar mis Pokemon por nombre                         |\n");
        printf("|   6.- Buscar Pokemon por nombre en Pokedex                  |\n");
        printf("|   7.- Mostrar todos los Pokemon de la Pokedex               |\n");
        printf("|   8.- Mostrar mis Pokemon ordenados por PC                  |\n");
        printf("|   9.- Liberar Pokemon                                       |\n");
        printf("|  10.- Mostrar Pokemon por region                            |\n");
        printf("|   0.- Salir                                                 |\n");
        printf("===============================================================\n");
        printf(" Ingrese un numero: ");
        scanf(" %s", menu);
        while(menu < 0 || menu > 10){
            printf ("===============================================================\n");
            printf (" Por favor ingrese uno de los numeros anteriores: ");
            scanf (" %s", menu);
            if(menu == 0 ) exit(0);
        }
        printf("===============================================================\n");
        fflush(stdin);
            
        switch(menu)
        {
            case 1:
                ImpotarExportarArchivo(mapaPokedex,almacenamientoId,&nroPokemon);
                printf ("===============================================================\n");
                printf ("          Volver al menu: 1 - Salir del programa: 0\n");
                printf ("===============================================================\n");
                printf(" Ingrese un numero: ");
                scanf ("%s", op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    scanf (" %s", op);
                }
                if (op == 0) return 0;
                if (op == 1) break;
                break;


            case 2:
                if (flag == 0){
                    printf(" Archivo no iniciado, recuerde importar sus Pokemon\n");
                    break;
                } 
                pokemonAtrapado(mapaPokedex,almacenamientoId,&nroPokemon);
                printf ("===============================================================\n");
                printf ("          Volver al menu: 1 - Salir del programa: 0\n");
                printf ("===============================================================\n");
                printf(" Ingrese un numero: ");
                scanf ("%s", op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    scanf (" %s", op);
                }
                if (op == 0) return 0;
                if (op == 1) break;
                break;


            case 3:
                if (flag == 0){
                    printf(" Archivo no iniciado, recuerde importar Pokemon\n");
                    break;
                } 
                evolucionarPokemon(mapaPokedex, almacenamientoId);
                printf ("===============================================================\n");
                printf ("          Volver al menu: 1 - Salir del programa: 0\n");
                printf ("===============================================================\n");
                printf(" Ingrese un numero: ");
                scanf ("%s", op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    scanf (" %s", op);
                }
                if (op == 0) return 0;
                if (op == 1) break;
                break;

            case 4:
                if (flag == 0){
                    printf(" Archivo no iniciado, recuerde importar Pokemon\n");
                    break;
                } 
                //**************************************************************
                printf ("===============================================================\n");
                printf ("          Volver al menu: 1 - Salir del programa: 0\n");
                printf ("===============================================================\n");
                printf(" Ingrese un numero: ");
                scanf ("%s", op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    scanf (" %s", op);
                }
                if (op == 0) return 0;
                if (op == 1) break;
                 break;

            case 5:
                if (flag == 0){
                    printf(" Archivo no iniciado, recuerde importar Pokemon\n");
                    break;
                } 
                //*****************************************************
                printf ("===============================================================\n");
                printf ("          Volver al menu: 1 - Salir del programa: 0\n");
                printf ("===============================================================\n");
                printf(" Ingrese un numero: ");
                scanf ("%s", op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    scanf (" %s", op);
                }
                if (op == 0) return 0;
                if (op == 1) break;
                break;

            case 6:
                if (flag == 0){
                    printf(" Archivo no iniciado, recuerde importar Pokemon\n");
                    break;
                } 
                buscarPorNombrePokedex (mapaPokedex);
                printf ("===============================================================\n");
                printf ("          Volver al menu: 1 - Salir del programa: 0\n");
                printf ("===============================================================\n");
                printf(" Ingrese un numero: ");
                scanf ("%s", op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    scanf (" %s", op);
                }
                if (op == 0) return 0;
                if (op == 1) break;
                break;

            case 7:
                if (flag == 0){
                    printf(" Archivo no iniciado, recuerde importar Pokemon\n");
                    break;
                } 
                //********************************************************************
                printf ("===============================================================\n");
                printf ("          Volver al menu: 1 - Salir del programa: 0\n");
                printf ("===============================================================\n");
                printf(" Ingrese un numero: ");
                scanf ("%s", op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    scanf (" %s", op);
                }
                if (op == 0) return 0;
                if (op == 1) break;
                break;

            case 8:
                if (flag == 0){
                    printf(" Archivo no iniciado, recuerde importar Pokemon\n");
                    break;
                } 
                //aqui va la funcion********************
                printf ("===============================================================\n");
                printf ("          Volver al menu: 1 - Salir del programa: 0\n");
                printf ("===============================================================\n");
                printf(" Ingrese un numero: ");
                scanf ("%s", op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    scanf (" %s", op);
                }
                if (op == 0) return 0;
                if (op == 1) break;
                break;

            case 9:
                if (flag == 0){
                    printf(" Archivo no iniciado, recuerde importar Pokemon\n");
                    break;
                } 
                //********************
                printf ("===============================================================\n");
                printf ("          Volver al menu: 1 - Salir del programa: 0\n");
                printf ("===============================================================\n");
                printf(" Ingrese un numero: ");
                scanf ("%s", op);
            while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    scanf (" %s", op);
                }
                if (op ==  0) return 0;
                if (op == 1) break;
                break;

            case 10:
                if (flag == 0){
                    printf(" Archivo no iniciado, recuerde importar Pokemon\n");
                    break;
                } 
                //¨***************************************************************
                printf ("===============================================================\n");
                printf ("          Volver al menu: 1 - Salir del programa: 0\n");
                printf ("===============================================================\n");
                printf(" Ingrese un numero: ");
                scanf ("%s", op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    scanf (" %s", op);
                }
                if (op == 0) return 0;
                if (op == 1) break;
                break;

            case 0: 
                exit(0);
                break;
        }
    }

    return 0;
}

void ImpotarExportarArchivo(HashMap * mapaPokedex, HashMap * almacenamientoId,int * nroPokemon){
    char nombreArchivo[50];
    FILE * archivo;
    char auxId[5];
    printf(" Que operacion desea realizar:\n");
    printf(" 1. Importar Pokemon\n");
    printf(" 2. Exportar Pokemon\n");
    printf(" 0. Volver al menu\n");
    char op[10];
    scanf(" %s",op);
    while((op[0] < '0' || op[0] > '2') || (int)strlen(op) > 1){
        printf ("===============================================================\n");
        printf (" Por favor ingrese uno de los numeros anteriores: ");
        scanf (" %s", op);
    }
    if(op[0] == '1'){
        printf(" Ingrese el nombre del archivo:\n");
        scanf("%s",nombreArchivo);
        archivo = fopen(nombreArchivo,"r");
        if(archivo == NULL){
            printf(" El archivo no existe\n");
            return;
        }
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
    else if(op[0] == '2'){
        *nroPokemon = 0;
        archivo = fopen("Caja_Auxiliar.csv","w");
        fprintf(archivo,"id,nombre,tipos,pc,ps,sexo,evolucion previa,evolucion posterior,numero pokedex,region\n");
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
    printf("Genero: ");
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
        printf("Evolucion Posterior");
        scanf(" %s",newPokedex->sigEvo);
        printf("Tipo: ");
        gets(newPokedex->tipo);
        getchar();
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
    Pokedex * auxPokedex2 = searchMap(mapaPokedex,aux->nombre);//apunta al nombre del Pokemon Evolucionado
    if(auxPokedex2 != NULL){
        auxPokedex2->cantidadPoke += 1;
        return;
    }
    else{
        auxPokedex2 = (Pokedex *)malloc(sizeof(Pokemon));
        auxPokedex2->cantidadPoke = 1;
        strcpy(auxPokedex2->nombre,aux->nombre);
        auxPokedex2->numeroPokedex = auxPokedex1->numeroPokedex + 1;
        strcpy(auxPokedex2->prevEvo,auxPokedex1->nombre);
        strcpy(auxPokedex2->sigEvo,"No Tiene");
        strcpy(auxPokedex2->region,auxPokedex1->region);
        strcpy(auxPokedex2->tipo,auxPokedex1->tipo);
        insertMap(mapaPokedex,strdup(auxPokedex2->nombre),auxPokedex2);
    }
}