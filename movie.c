#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "movie.h"


eMovie* movie_new()
{
    eMovie* nuevaMovie = (eMovie*) calloc(1,sizeof(eMovie));

    return nuevaMovie;
}

/*
eMovie* eMovie_newMovieParam(char* idStr,char* nombre,char* genero, char* tipoPasajero, char* codigoVuelo, char* estadoVuelo)
{
    int error=-1;
    Passenger* nuevoPasajero = Passenger_new();
    if(nuevoPasajero != NULL)
    {
        if(!(Passenger_setId(nuevoPasajero, atoi(idStr)) &&
                Passenger_setNombre(nuevoPasajero, nombre) &&
                Passenger_setApellido(nuevoPasajero, apellido) &&
                Passenger_setPrecio(nuevoPasajero, precio) &&
                Passenger_setTipoPasajero(nuevoPasajero, tipoPasajero)&&
                Passenger_setCodigoVuelo(nuevoPasajero, codigoVuelo) &&
                Passenger_setEstadoVuelo(nuevoPasajero, estadoVuelo)))
        {
            error=0;
        }
        else
        {
            error=-1;
            free(nuevoPasajero);
        }
    }
    return nuevoPasajero;
}
*/


void movie_delete(eMovie* pMovie)
{
    free(pMovie);
}

int movie_setId(eMovie* p,int id)
{
    int error=-1;


    if(p!=NULL && id>0)
    {
        p->id=id;
        error=0;

    }
    return error;
}

int movie_getId(eMovie* p,int* id)
{
    int error = -1;

    if(p != NULL && id != NULL )
    {
        *id= p->id;
        error=0;
    }
    return error;
}

int movie_setTitulo(eMovie* p, char* titulo)
{
    int error = 0;
    char auxStr[50];
    int valido=1;


    if(p != NULL && titulo != NULL && (strlen(titulo) <50 && strlen(titulo) > 0))
    {
        strcpy(auxStr, titulo);
        for(int i=0; i<strlen(auxStr); i++)
        {
            if(!(auxStr[i]>=65 && auxStr[i]<=90) && !(auxStr[i]>=97 && auxStr[i]<=122) && (auxStr[i]!=32) && (auxStr[i]!=46) && !(auxStr[i]>=48 && auxStr[i]<=57))
            {
                error=-1;
                valido=0;
                break;
            }

        }
        if(valido)
        {
            strupr(auxStr);
            strcpy(p->titulo, auxStr);
        }
    }

    return error;
}
int movie_getTitulo(eMovie* p,char* titulo)
{
    int error = -1;

    if(p != NULL && titulo != NULL )
    {
        strcpy(titulo, p->titulo);
        error=0;
    }
    return error;
}

int movie_getRating(eMovie* p, float* rating)
{
    int error = -1;

    if(p != NULL && rating != NULL )
    {
        *rating= p->rating;
        error=0;
    }
    return error;
}

int movie_setRating(eMovie* p,float rating)
{
    int error=-1;
    if(p!=NULL && rating>=0 && rating<=10)
    {
        p->rating=rating;
        error=0;
    }
    return error;
}

int movie_getGenero(eMovie* p,char* genero)
{
    int error = -1;

    if(p != NULL && genero!= NULL )
    {
        strcpy(genero, p->genero);
        error=0;
    }
    return error;
}

int movie_setGenero(eMovie* p,char* genero)
{
    int error=1;
    char auxStr[50];
    strcpy(auxStr, genero);
    int valido=0;

	if(p!=NULL && genero!=NULL)
	{
	    for(int i=0; i<strlen(auxStr);i++){
            if(strlen(auxStr)<1 && (!(auxStr[i]>=65 && auxStr[i]<=90) && !(auxStr[i]>=97 && auxStr[i]<=122) && (auxStr[i]!=32)))
            {
                valido=0;
                break;
            }else{
                valido=1;
            }
	    }
        if(valido){
            strcpy(p->genero, auxStr);
            error=0;
        }

	}
	return error;
}
