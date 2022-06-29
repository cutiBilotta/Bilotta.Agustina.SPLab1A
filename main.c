#include <stdio.h>
#include <stdlib.h>
#include "controller.h"
#include "movie.h"
#include "LinkedList.h"


int main()
{
    char confirma='n';
    int opcion=0;
    LinkedList* lista= ll_newLinkedList();
    LinkedList* listaFiltrada=NULL;
    char path[50];
    int flagCarga=0;


    do{

    switch(menu(opcion)){
        case 1:
            printf("Ingrese el nombre del archivo: ");
            fflush(stdin);
            gets(path);
            if(!controller_loadFromText(path, lista)){
                flagCarga=1;
            }
        break;

        case 2:
            if(!flagCarga){
                printf("Primero debe cargar un archivo\n");
            }else{
                controller_listMovies(lista);
            }

        break;

        case 3:
            if(!flagCarga){
                printf("Primero debe cargar un archivo\n");
            }else{
                controller_asignarRatings(lista);
            }

        break;

        case 4:
            if(!flagCarga){
                printf("Primero debe cargar un archivo\n");
            }else{
                controller_asignarGeneros(lista);
            }

        break;

        case 5:
            if(!flagCarga){
                printf("Primero debe cargar un archivo\n");
            }else{
                switch(menuFiltrado()){
                    case 1:
                        listaFiltrada=ll_filter(lista, controller_filterTerror);
                        controller_listMovies(listaFiltrada);
                        break;
                    case 2:
                        listaFiltrada=ll_filter(lista,controller_filterAccion);
                        controller_listMovies(listaFiltrada);
                        break;
                    case 3:
                        listaFiltrada=ll_filter(lista,controller_filterDrama);
                         controller_listMovies(listaFiltrada);
                        break;
                    case 4:
                        listaFiltrada=ll_filter(lista,controller_filterComedia);
                         controller_listMovies(listaFiltrada);
                        break;
                    default:
                        printf("Opcion invalida\n");
                        break;

                    }
            }
        break;

        case 6:
            if(!flagCarga){
                printf("Primero debe cargar un archivo\n");
            }else{
                ll_sort(lista, controller_sortGeneroRating,1);
            }

        break;

        case 7:
            if(!flagCarga){
                printf("Primero debe cargar un archivo\n");
            }else{
                printf("Ingrese el nombre del archivo donde desea guardar el listado de peliculas: ");
                fflush(stdin);
                gets(path);
                if(!controller_saveAsText(path, lista)){
                    printf("Archivo guardado con exito.\n");
                }else{
                    printf("Ocurrio un error al cargar el archivo. \n");
                }
            }

        break;

        case 8:
            printf("Confirma salida? s/n \n");
            fflush(stdin);
            scanf("%c", &confirma);
            if(ll_len(lista)){
                 ll_deleteLinkedList(lista);
            }
            if(ll_len(listaFiltrada)){
                ll_deleteLinkedList(listaFiltrada);
            }

        break;

        default:
            printf("opcion invalida\n");
            break;

    }
        system("pause");
        system("cls");
    }while(confirma!='s');
}
