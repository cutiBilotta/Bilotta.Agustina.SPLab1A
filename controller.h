#include "movie.h"
#include "LinkedList.h"

#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED



#endif // CONTROLLER_H_INCLUDED


int menu();
int menuFiltrado();

void controller_listMovie(eMovie* aux);
int controller_listMovies(LinkedList* lista);

//funciones para calcular y asignar randoms
void* controller_generarRating(void* aux);
void* controller_generarGenero(void* aux);
int controller_asignarRatings(LinkedList* lista);
int controller_asignarGeneros(LinkedList* lista);


//funciones para filtrar lista segun genero
int controller_filterComedia(void* aux);
int controller_filterTerror(void* aux);
int controller_filterAccion(void* aux);
int controller_filterDrama(void* aux);


//funcion de ordenamiento
int controller_sortGeneroRating(void* auxI, void* auxJ);


//funciones que interactuan conc archivos
int controller_loadFromText(char* path, LinkedList* lista);
int controller_saveAsText(char* path, LinkedList* lista);
