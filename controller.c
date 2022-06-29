#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "movie.h"
#include "parser.h"
#include "controller.h"
#include <time.h>



/** \brief Carga los datos de las peliculas desde el archivo csv (modo texto).
 * \param char* path
 * \param LinkedList* lista
 * \return int error 0(sin errores) || error 1(con error)
 */

int controller_loadFromText(char* path, LinkedList* lista)
{
    int error=-1;
    FILE* f=fopen(path, "r");
    char confirma='n';

    if(f==NULL)
    {
        printf("El path ingresado no existe\n");
        printf("Ocurrio un error\n");
        error=-1;
    }
    else
    {
        if(ll_len(lista))
        {
            printf("Los datos cargados actualmente se van a sobreescribir. Confirma? s/n \n");
            fflush(stdin);
            scanf("%c", &confirma);
        }


        if(confirma=='s' || !ll_len(lista))
        {
            ll_clear(lista);
            if(!(parser_movieFromText(f, lista)))
            {
                fclose(f);
                error=0;
            }
            else
            {
                printf("Ocurrio un error al cargar las peliculas\n");
                error=-1;
            }
        }

    }

    return error;
}


/** \brief Listar peliculas cargadas
 * \param LinkedList* lista
 * \return int error 0(sin errores) || error 1(con error)
 */
int controller_listMovies(LinkedList* lista)
{
    int error=-1;
    eMovie* aux = movie_new();
    int largo= ll_len(lista);


    if(lista!=NULL)
    {
        system("cls");
        printf("\n          *** LISTADO DE PELICULAS CARGADAS EN SISTEMA ***    \n");
        printf("--------------------------------------------------------------------------\n\n");

        printf("   Id                   Nombre                Genero        Rating          \n");
        printf("----------------------------------------------------------------------------\n\n");
        for(int i=0; i<largo; i++)
        {
            aux= (eMovie*) ll_get(lista,i);
            controller_listMovie(aux);
        }
        error=0;

    }

    return error;
}

/** \brief Lista una pelicula cargada
 * \param eMovie* elemento
 */
void controller_listMovie(eMovie* aux)
{

    printf("%3d %30s %20s   %.1f\n", aux->id, aux->titulo, aux->genero, aux->rating);
}



/** \brief Guarda los datos de las peliculas en un archivo csv (modo texto).
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int error 0(sin errores) || error 1(con error)
 */
int controller_saveAsText(char* path, LinkedList* lista)
{
    FILE* punteroArchivo;
    punteroArchivo= fopen(path, "w");
    eMovie* aux;
    int largo;
    int error=-1;
    int auxInt;
    float auxFloat;
    char auxStr[100];

    if(lista!=NULL && punteroArchivo!=NULL)
    {
        largo= ll_len(lista);
        fprintf(punteroArchivo,"id,titulo,genero,rating\n");

        for(int i=0; i< largo; i++)
        {
            aux= (eMovie*) ll_get(lista,i);

            movie_getId(aux, &auxInt);
            fprintf(punteroArchivo, "%d,", auxInt);

            movie_getTitulo(aux, auxStr);
            fprintf(punteroArchivo, "%s,", auxStr);

            movie_getGenero(aux, auxStr);
            fprintf(punteroArchivo, "%s,", auxStr);

            movie_getRating(aux, &auxFloat);
            fprintf(punteroArchivo, "%.1f\n", auxFloat);
        }

        fclose(punteroArchivo);
        error=0;
    }
    return error;
}


/** \brief muestra menu principal de opciones
 * \return opcion elegida por el usuario
 */
int menu()
{

    int opcion;

    printf("       *** MENU OPCIONES *** \n");
    printf("------------------------------\n");
    printf("1- Cargar archivo de texto \n");
    printf("2- Imprimir lista \n");
    printf("3- Asignar rating \n");
    printf("4- Asignar genero \n");
    printf("5- Filtrar por genero \n");
    printf("6- Ordenar pelicula - por genero y rating \n");
    printf("7- Guardar en archivo de texto \n");
    printf("8- Salir \n");
    printf("\nIngrese opcion: ");
    scanf("%d", &opcion);

    return opcion;
}


/** \brief muestra menu para filtrado de lista
 * \return opcion elegida por el usuario
 */
int menuFiltrado()
{

    int opcion;

    printf("       *** MENU FILTRADO *** \n");
    printf("------------------------------\n");
    printf("Mostrar lista de peliculas segun genero: \n");
    printf("1- Drama \n");
    printf("2- Comedia \n");
    printf("3- Accion \n");
    printf("4- Terror \n");

    printf("\nIngrese opcion: ");
    scanf("%d", &opcion);

    return opcion;
}


/** \brief llama a ll_map y le pasa un puntero a funcion
 * \param linkedList* lista
 * \return 0 sin errores || -1 con error
 */
int controller_asignarRatings(LinkedList* lista)
{
    int error=-1;

    if(lista!=NULL)
    {
        if(ll_map(lista, controller_generarRating)!=NULL)
        {
            printf("\nRatings asignados con exito\n");
        }
        error=0;
    }

    return error;
}

/** \brief llama a ll_map y le pasa un puntero a funcion
 * \param linkedList* lista
 * \return 0 sin errores || -1 con error
 */
int controller_asignarGeneros(LinkedList* lista)
{
    int error=-1;

    if(lista!=NULL)
    {
        if(ll_map(lista, controller_generarGenero)!=NULL)
        {
            printf("\nGeneros asignados con exito.\n");
        }
        error=0;
    }

    return error;
}


/** \brief Genera un numero random entre 1 y 10 con 1 decimal y lo asigna a campo rating mediante setter.
 * \param puntero a void
 * \return puntero a void con rating cargado
 */
void* controller_generarRating(void* pelicula)
{
    eMovie* auxPelicula=(eMovie*) pelicula;
    float rating;
    int min=10;
    int max=100;

    if(pelicula!=NULL)
    {
        rating=(float)(rand()%(max-min+1)+min)/10;
        movie_setRating(auxPelicula, rating);
    }

    return (void*)auxPelicula;
}


/** \brief Genera un numero random entre 1 y 4 y lo asigna a campo genero mediante setter.
 * \param puntero a void
 * \return puntero a void con genero cargado
 */
void* controller_generarGenero(void* pelicula)
{
    eMovie* auxPelicula=NULL;
    int numGenero;
    int min=1;
    int max=4;

    if(pelicula!=NULL)
    {
        auxPelicula= (eMovie*) pelicula;
        numGenero=rand()%(max-min+1)+min;


        if(numGenero==1)
        {
            movie_setGenero(auxPelicula, "Drama");
        }
        else if(numGenero==2)
        {
            movie_setGenero(auxPelicula, "Comedia");
        }
        else if(numGenero==3)
        {
            movie_setGenero(auxPelicula, "Accion");
        }
        else if(numGenero==4)
        {
            movie_setGenero(auxPelicula, "Terror");
        }
    }

    return (void*)auxPelicula;
}


/** \brief funcion que filtra lista segun genero elegido por el usuario
 * \param puntero a void
 * \return 1 o 0 segun corresponda a la listao o no
 */
int controller_filterDrama(void* aux)
{
    int retorno;
    eMovie* pMovie=NULL;

    if(aux !=NULL)
    {
        pMovie= (eMovie*) aux;
        if(stricmp(pMovie->genero, "drama")==0)
        {
            retorno=1;
        }
        else
        {
            retorno=0;
        }

    }
    return retorno;
}


/** \brief funcion que filtra lista segun genero elegido por el usuario
 * \param puntero a void
 * \return 1 o 0 segun corresponda a la listao o no
 */
int controller_filterTerror(void* aux)
{
    int retorno;
    eMovie* pMovie=NULL;

    if(aux !=NULL)
    {
        pMovie= (eMovie*) aux;
        if(stricmp(pMovie->genero, "terror")==0)
        {
            retorno=1;
        }
        else
        {
            retorno=0;
        }

    }
    return retorno;
}


/** \brief funcion que filtra lista segun genero elegido por el usuario
 * \param puntero a void
 * \return 1 o 0 segun corresponda a la listao o no
 */
int controller_filterAccion(void* aux)
{
    int retorno;
    eMovie* pMovie=NULL;

    if(aux !=NULL)
    {
        pMovie= (eMovie*) aux;
        if(stricmp(pMovie->genero, "accion")==0)
        {
            retorno=1;
        }
        else
        {
            retorno=0;
        }

    }
    return retorno;
}


/** \brief funcion que filtra lista segun genero elegido por el usuario
 * \param puntero a void
 * \return 1 o 0 segun corresponda a la listao o no
 */
int controller_filterComedia(void* aux)
{
    int retorno;
    eMovie* pMovie=NULL;

    if(aux !=NULL)
    {
        pMovie= (eMovie*) aux;
        if(stricmp(pMovie->genero, "comedia")==0)
        {
            retorno=1;
        }
        else
        {
            retorno=0;
        }

    }
    return retorno;
}


/** \brief Funcion para ordenamiento segun genero y rating descendente
 * \param  dos punteros a void para realizar la comparacion
 * \return 1 o 0 segun corresponda
 */
int controller_sortGeneroRating(void* auxI, void* auxJ)
{
    int retorno=0;
    eMovie* pAuxI=NULL;
    eMovie* pAuxJ=NULL;

    if(auxI!= NULL && auxJ!=NULL)
    {
        pAuxI= (eMovie*) auxI;
        pAuxJ= (eMovie*) auxJ;
        if(stricmp(pAuxI->genero, pAuxJ->genero)<0)
        {
            retorno=1;
        }
        else if((stricmp(pAuxI->genero, pAuxJ->genero)==0) && pAuxI->rating<pAuxJ->rating)
        {
            retorno=1;
        }
    }

    return retorno;
}
