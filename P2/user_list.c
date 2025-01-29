/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Antón Vilas Pazos  LOGIN 1: anton.vilas.pazos@udc.es
 * AUTHOR 2: Alejandro Mosquera Cardeso LOGIN 2: alejandro.mosquera.cardeso@udc.es
 * GROUP: 4.2
 * DATE: 25 / 04 / 24
 */


#include "user_list.h"
#include "string.h"
#include "stdlib.h"


//Funcion auxiliar para crear nodos, necesaria en la función insertar.
bool createNode(tPosU *p){
    *p = malloc(sizeof(struct tNode));
    return *p != NULLU;
}

void createEmptyListU(tListU *L){
    //Se crea una lista vacía , poniendo el puntero de la lista a nulo.
    *L=NULLU;
}

bool isEmptyListU(tListU L){
    //Devuelve true si la lista está vacía.
    return L==NULLU;
}

tPosU firstU(tListU L){
    //Devuelve la primera posición de la lista
    return L;
}

tPosU lastU(tListU L){
    tPosU p;
    //Se recorre la lista hasta llegar al ultimo elemento.
    for(p=L;(p->next!=NULLU);p=p->next);
    //Se devuelve la posición del ultimo elemento.
    return p;
}


tPosU nextU(tPosU pos, tListU L){
    //Devuelve la posición siguiente.
    return pos->next;
}




tPosU previousU(tPosU pos, tListU L){
    tPosU q;
    //Si la posición pasada por parámetro es la primera se devuelve nulo, dado que no existe una posición anterior.
    if(pos==L) q=NULLU;
    else
        for(q=L;q->next!=pos;q=q->next);
    //Se devuelve la posicion anterior a la pasada por parámetro.
    return q;
}

 //Devuelve la posición en la que se encuentra un elemento
tPosU findPosition(tListU *L,tItemU item){
    tPosU p = L;

    while(p->next != NULLU && strcmp(p->next->data.userName,item.userName)<0)
        p = p->next;
    return p;
}



bool insertItemU(tItemU item, tListU *L){
    tPosU q,p;

    if (!createNode(&q)) return false;
    else{
        q->data = item;
        q->next = NULLU;
        //Comprobar si la lista está vacía
        if(isEmptyListU(*L)) {
            *L = q;
        }else if(strcmp(item.userName,(*L)->data.userName) < 0){
            q->next = *L;
            *L = q;
            // Insertar al inicio
        }else {
            p = findPosition(*L,item);
            q->next = p->next;
            p->next = q;
            //Insertar en posicion final o media
        }
        return true;
    }
}


void deleteAtPositionU(tPosU pos, tListU *L){
    //Si la posicion es la primera, el puntero L se apunta a la siguiente posicion.
    if(pos == *L)
        *L =(*L)->next;
    else previousU(pos,*L)->next = pos->next;
    //Se libera la memoria del nodo borrado
    free(pos);
}

tItemU getItemU(tPosU pos, tListU L){
    //Devuelve el item que se encuentra en la posición pasada por parámetro.
    return pos->data;
}

void updateItemU(tItemU item, tPosU pos, tListU *L){
    //Se modifica el item que se encuentra en la posición pasada por parámetro igualandola al item también pasado por parámetro.
    pos->data=item;
}


tPosU findItemU(tUserName name,tListU L) {
    tPosU p;

    //Se recorre toda la lista mediante un bucle for.
    for (p = L; (p != NULLU) && (strcmp(p->data.userName, name) != 0); p = p->next);

    //Si se encuentra un item con igual userName se devuelve su posición.
    if (p != NULLU && strcmp(p->data.userName, name) == 0) return p;
        //En caso contrario se devuelve LNULL.
    else return NULLU;
}



