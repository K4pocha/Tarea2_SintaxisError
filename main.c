#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"
#include "Pokemon.h"
#include <string.h>
#include <stdbool.h>

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
        menu = -1;
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
        scanf(" %d", &menu);

        while(menu < 0 || menu > 10){
            printf ("===============================================================\n");
            printf (" Por favor ingrese uno de los numeros anteriores: ");
            while(getchar()!='\n'); //limpiar buffer del teclado en caso de que el usuario ingrese una 
            //opcion no valida
            scanf (" %d", &menu);
            if(menu == 0 ) exit(0);
        }
        printf("===============================================================\n");
        fflush(stdin);
            
        switch(menu)
        {   
            op = -1;
            case 1:
                ImpotarExportarArchivo(mapaPokedex,almacenamientoId,&nroPokemon,&flag);
                printf ("===============================================================\n");
                printf ("          Volver al menu: 1 - Salir del programa: 0\n");
                printf ("===============================================================\n");
                printf(" Ingrese un numero: ");
                scanf ("%d", &op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    while(getchar()!='\n');
                    scanf ("%d", &op);
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
                scanf ("%d", &op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    while(getchar()!='\n');
                    scanf ("%d", &op);
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
                scanf ("%d", &op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    while(getchar()!='\n');
                    scanf ("%d", &op);
                }
                if (op == 0) return 0;
                if (op == 1) break;
                break;

            case 4:
                if (flag == 0){
                    printf(" Archivo no iniciado, recuerde importar Pokemon\n");
                    break;
                } 
                buscarPokemonPorTipo(mapaPokedex,almacenamientoId);
                printf ("===============================================================\n");
                printf ("          Volver al menu: 1 - Salir del programa: 0\n");
                printf ("===============================================================\n");
                printf(" Ingrese un numero: ");
                scanf ("%d", &op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    while(getchar()!='\n');
                    scanf ("%d", &op);
                }
                if (op == 0) return 0;
                if (op == 1) break;
                 break;

            case 5:
                if (flag == 0){
                    printf(" Archivo no iniciado, recuerde importar Pokemon\n");
                    break;
                } 
                buscarPorNombrAlmacenamiento(almacenamientoId);
                printf ("===============================================================\n");
                printf ("          Volver al menu: 1 - Salir del programa: 0\n");
                printf ("===============================================================\n");
                printf(" Ingrese un numero: ");
                scanf ("%d", &op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    while(getchar()!='\n');
                    scanf ("%d", &op);
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
                scanf ("%d", &op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    while(getchar()!='\n');
                    scanf ("%d", &op);
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
                scanf ("%d", &op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    while(getchar()!='\n');
                    scanf ("%d", &op);
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
                scanf ("%d", &op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    while(getchar()!='\n');
                    scanf ("%d", &op);
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
                scanf ("%d", &op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    while(getchar()!='\n');
                    scanf ("%d", &op);
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
                scanf ("%d", &op);
                while(op < 0 || op > 1){
                    printf ("===============================================================\n");
                    printf (" Por favor ingrese uno de los numeros anteriores: ");
                    while(getchar()!='\n');
                    scanf ("%d", &op);
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