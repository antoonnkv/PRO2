/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Antón Vilas Pazos  LOGIN 1: anton.vilas.pazos@udc.es
 * AUTHOR 2: Alejandro Mosquera Cardeso LOGIN 2: alejandro.mosquera.cardeso@udc.es
 * GROUP: 4.2
 * DATE: 18 / 03 / 24
 */

#include "static_list.h"
#include "string.h"

void createEmptyList(tList *L){
    //La ultima posición de la lista se iguala a nulo indicando que está vacía.
    L -> lastPos = LNULL;
}

bool isEmptyList(tList L){
    //Si la ultima posicion de la lista es nula, significa que esta está vacía por lo tanto devuelve true
    if( L.lastPos == LNULL ) return true;
    //En caso contrario se devuelve true
    else return false;
}

tPosL first(tList L){
    //Devuelve 0 por que la primera posición de una lista es siempre 0.
    return 0;
}

tPosL last(tList L){
    //Devuelve lastPos, que es la ultima posición de la lista.
    return L.lastPos;
}

tPosL next(tPosL pos, tList L){
    //Devuelve LNULL si la posicion de la lista es la ultima por que no existe una posición siguiente.
    if( pos == L.lastPos ) return LNULL;
    //En caso contrario devuelve la siguiente posicion
    else return ++pos;
}

tPosL previous(tPosL pos, tList L){
    //Devuelve LNULL si la posicion de la lista es la primera por que no existe una posición anterior.
    if( pos == 0 ) return LNULL;
    //En caso contrario devuelve la posición anterior
    else return --pos;
}


bool insertItem(tItemL item, tPosL pos, tList *L) {
    tPosL i;
    /*Si la ultima posición de la lista es la máxima posible devuelve false,
      por que no se puede insertar en una lista llena*/
    if(L->lastPos == MAX -1) return false;
    else{
        //Si hay espacio en la lista, se aumenta el tamaño de la lista en 1.
        L->lastPos++;
        //A la hora de insertar si la posición pasada es nula se inserta al final
        if (pos == LNULL) L->data[L->lastPos] = item;
        else{
            //Si no se inicializa un bluce, despalazando todos los items para poder colocar el item nuevo en la posición deseada
            for (i = L->lastPos; i >= pos + 1; i--)
                L->data[i] = L->data[i - 1];
            L->data[pos] = item;
        }

    }
    //Devuelve true si la inserción ha sido realizada correctamente
    return true;
}

void deleteAtPosition(tPosL pos, tList *L){
    tPosL i;
    /*A partir de la posicion que queremos eliminar, se inicializa un bucle
    hasta la ultima posición, pasando todos los items una posición a la izquierda*/
    for( i = pos; i<L->lastPos; i++){
        L->data[i] = L->data[i+1];
    }
    //Se disminuye el tamaño de la lista en 1
    L->lastPos--;

}


tItemL getItem(tPosL pos, tList L){
    //Devuelve el item que se encuentra en dicha posición de la lista.
    return L.data[pos];
}

void updateItem(tItemL item, tPosL pos, tList *L){
    //Iguala el item de una posición de la lista al item pasado por parámetro.
    L->data[pos] = item;
}


tPosL findItem(tUserName name, tList L){
    tPosL i;

    //Si la lista está vacía no se va encontrar ese item, por lo tanto devuelve LNULL.
    if(isEmptyList(L)) return LNULL;
    else{
        /*Con un bucle se recorre toda la lista hasta que uno de los items tenga igual username
         que el pasado por parámetro, cuando encuentra un item de igual nombre el bucle se rompe
         y se guarda ese item en una variable, si no se encuentra ninguno de igual username se devuelve LNULL*/
        for(i=0;(i<= L.lastPos)&&(strcmp(L.data[i].userName,name)!=0);i++);
        if(strcmp(L.data[i].userName,name)==0) return i;
        else return LNULL;
    }

}






