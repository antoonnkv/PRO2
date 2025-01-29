/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Antón Vilas Pazos  LOGIN 1: anton.vilas.pazos@udc.es
 * AUTHOR 2: Alejandro Mosquera Cardeso LOGIN 2: alejandro.mosquera.cardeso@udc.es
 * GROUP: 4.2
 * DATE: 25 / 04 / 24
 */

#ifndef USER_LIST_H
#define USER_LIST_H

#include "types.h"
#include "song_list.h"

#define NULLU NULL

typedef struct tNode *tPosU;

typedef struct {
    tUserName userName;
    tPlayTime totalPlayTime;
    tUserCategory userCategory;
    tListS songList;
} tItemU;


struct tNode{
    tItemU data;
    tPosU next;
};
typedef tPosU tListU;

void createEmptyListU(tListU *L);
/*
• Objetivo del procedimiento/función: Crear una lista vacía y inicializarla.
• Entradas: La lista.
• Salidas:Una lista vacía.
• Precondiciones: Ninguna.
• Postcondiciones: La lista vacía.
 */

bool isEmptyListU(tListU L);
/*
• Objetivo del procedimiento/función: Comprobar si una lista esta vacía.
• Entradas: La lista
• Salidas: El booleano true si está vacía y false si no lo está.
• Precondiciones: La lista debe de estar creada.
• Postcondiciones: Ninguna.
 */

tPosU firstU(tListU L);
/*
• Objetivo del procedimiento/función: Devolver la primera posición de una lista.
• Entradas: La lista
• Salidas: La primera posición de la lista.
• Precondiciones: La lista debe de estar creada.
• Postcondiciones: Ninguna.
 */

tPosU lastU(tListU L);
/*
• Objetivo del procedimiento/función: Devolver la última posición de una lista.
• Entradas: La lista.
• Salidas: La última posición de la lista.
• Precondiciones: La lista debe de estar creada.
• Postcondiciones: Ninguna.
 */

tPosU nextU(tPosU pos, tListU L);
/*
• Objetivo del procedimiento/función: Devolver la posición siguiente a una posición introducida
 por parámetro.
• Entradas: La lista y una posición de la lista.
• Salidas: La posición siguiente a la pasada por parámetro o null si la posición pasada
  es la última.
• Precondiciones: La lista debe de estar creada, y la posición ser una posición válida.
• Postcondiciones: Ninguna.
 */

tPosU previousU(tPosU pos, tListU L);
/*
• Objetivo del procedimiento/función: Devolver la posición anterior a una posición introducida
 por parámetro.
• Entradas: La lista y una posición de la lista.
• Salidas: La posición anterior a la pasada por parámetro o null si la posición pasada
  es la primera.
• Precondiciones: La lista debe de estar creada, y la posición ser una posición válida.
• Postcondiciones: Ninguna.
 */

bool insertItemU(tItemU item, tListU *L);
/*
• Objetivo del procedimiento/función: Inseertar un elemento en la posición anterior
 a la pasada por parámetro, si esta es LNULL se añade al final de la lista.
• Entradas: La lista y una posición de la lista, y un item para insertar.
• Salidas: Devuelve un valor true si el elemento fue insertado,
false en caso contrario.
• Precondiciones: La lista debe de estar creada, y la posición ser una posición válida.
• Postcondiciones: Las posiciones de los elementos de la lista que se encuentran después de la del
 elemento insertado varían.
 */

void deleteAtPositionU(tPosU pos, tListU *L);
/*
• Objetivo del procedimiento/función: Eliminar de la lista el elemento de la posición
 pasada por parámetro.
• Entradas: La lista y una posición de la lista.
• Salidas: La lista modificada con 1 elemento menos.
• Precondiciones: La lista debe de estar creada y no estar vacía, y la posición ser una posición válida.
• Postcondiciones: Las posiciones de los elementos posteriores a la de la posicion eliminada varían.
 */
tItemU getItemU(tPosU pos, tListU L);
/*
• Objetivo del procedimiento/función: Devolver el elemento que se encuentra en la posición
 pasada por parámetro.
• Entradas: La lista y una posición de la lista.
• Salidas: El item/elemento que se encuentra en la posición pasada por parámetro.
• Precondiciones: La lista debe de estar creada, y la posición ser una posición válida.
• Postcondiciones: Ninguna
 */

void updateItemU(tItemU item, tPosU pos, tListU *L);
/*
• Objetivo del procedimiento/función: En la posición de la lista pasada por parámetro modificar
 el item que se encuentra en dicha posición.
• Entradas: La lista, una posición de la lista y un item.
• Salidas: La lista con el elemento modificado.
• Precondiciones: La lista debe de estar creada, y la posición ser una posición válida.
• Postcondiciones: No se modifica el orden de la lista.
 */

tPosU findItemU(tUserName name, tListU L);
/*
• Objetivo del procedimiento/función: Buscar un nombre de usuario en la lista y devolver la posición
 en la que aparece en la lista.
• Entradas: La lista y un nombre de usuario para buscar en la lista.
• Salidas: La posición en la que se encuentra el elemento buscado o null si no se encuentra
 el elemento.
• Precondiciones: La lista debe de estar creada.
• Postcondiciones: Ninguna
 */



#endif
