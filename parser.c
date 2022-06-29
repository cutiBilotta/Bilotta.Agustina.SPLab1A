#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "movie.h"
#include "parser.h"

/** \brief Parsea los datos los datos de las peliculas desde el archivo csv (modo texto).
 *
 * \param path char*
 * \param LinkedList* lista
 * \return int error 0(sin errores) || error -1(con errores)
 *
 */
int parser_movieFromText(FILE* pFile, LinkedList* lista)
{

    char buffer[7][50];
    int error=0;


    if(pFile!=NULL)
    {
        fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", buffer[0],buffer[1],buffer[2],buffer[3]);
        while(!feof(pFile))
        {
            eMovie* aux = movie_new();

            fscanf(pFile, "%[^,], %[^,],%[^,],%[^\n]\n", buffer[0],buffer[1],buffer[2],buffer[3]);

            if(!(movie_setId(aux, atoi(buffer[0]))) &&
               !(movie_setTitulo(aux,buffer[1]))    &&
               !(movie_setGenero(aux, buffer[2]))  &&
               !(movie_setRating(aux, atof(buffer[3]))))
            {
                ll_add(lista, aux);
            }
            else
            {
                printf("Ocurrio un error\n");
                movie_delete(aux);
                error=-1;
                break;
            }
        }
    }


    return error;
}
